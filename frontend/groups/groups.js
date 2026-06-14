import { apiDelete, apiGet, apiPost, apiPut, canManageCatalogs, closeModal, hideElement, openModal, renderTable, setText } from "/frontend/layouts/utils.js";
import { loadConfirmModal, openConfirm } from "/frontend/layouts/confirm-modal.js";
import { API, CATEGORY_LABELS, LEVEL_LABELS, findName, getCategoryLabel, getFullName, loadGroupPageData } from "./group-data.js";
import { backToGroupList, openGroupClients } from "./group-clients.js";
import { buildScheduleGrid, updateGroupFilter } from "./group-schedule.js";

let state = { groups: [], coaches: [], styles: [], subscriptions: [] };
let editingId = null;
let fields = {};
let groupFilters = { query: "", category: "", level: "", styleId: "" };

document.addEventListener("DOMContentLoaded", initGroupsPage);

async function initGroupsPage() {
  await loadConfirmModal();
  state = await loadGroupPageData();
  await loadGroupModal();

  bindTabs();
  bindActions();
  bindGroupFilters();
  renderGroups();
  openGroupFromUrl();
}

function bindActions() {
  if (!canManageCatalogs()) {
    hideElement("add-group-btn");
  }

  document.getElementById("add-group-btn")?.addEventListener("click", () => {
    resetForm();
    openModal("group-modal");
  });

  document.getElementById("back-to-groups-btn")?.addEventListener("click", () => {
    window.history.pushState({}, "", window.location.pathname);
    backToGroupList();
  });

  document.getElementById("schedule-group-filter").addEventListener("change", event => {
    buildScheduleGrid(state, event.target.value);
  });

  window.addEventListener("popstate", openGroupFromUrl);
}

function bindTabs() {
  document.querySelectorAll(".tab-btn").forEach(button => {
    button.addEventListener("click", () => {
      document.getElementById("group-clients-panel").style.display = "none";
      document.getElementById("tab-list").style.display = "";
      document.querySelectorAll(".tab-btn").forEach(item => item.classList.remove("active"));
      document.querySelectorAll(".tab-panel").forEach(panel => panel.classList.remove("active"));
      button.classList.add("active");
      document.getElementById(`tab-${button.dataset.tab}`).classList.add("active");

      if (button.dataset.tab === "schedule") {
        buildScheduleGrid(state);
      }
    });
  });
}

function renderGroups() {
  const query = groupFilters.query.toLowerCase();
  const filteredGroups = state.groups.filter(group => {
    const enrichedText = [
      group.name,
      getFullName(state.coaches.find(coach => String(coach.id) === String(group.coachId))),
      findName(state.styles, group.styleId),
      getCategoryLabel(group.category),
      LEVEL_LABELS[group.skillLevel]
    ].join(" ").toLowerCase();

    return (!query || enrichedText.includes(query)) &&
      (!groupFilters.category || String(group.category) === String(groupFilters.category)) &&
      (!groupFilters.level || String(group.skillLevel) === String(groupFilters.level)) &&
      (!groupFilters.styleId || String(group.styleId) === String(groupFilters.styleId));
  });

  const rows = filteredGroups.map(group => ({
    ...group,
    coachName: getFullName(state.coaches.find(coach => String(coach.id) === String(group.coachId))),
    styleName: findName(state.styles, group.styleId),
    levelName: LEVEL_LABELS[group.skillLevel] || group.skillLevel,
    categoryName: getCategoryLabel(group.category),
    subscriptionNames: state.subscriptions
      .filter(subscription => (group.subscriptionIds || []).some(id => String(id) === String(subscription.id)))
      .map(subscription => subscription.name)
      .join(", ") || "-"
  }));

  const actions = {};
  actions.view = id => openGroupDetails(id);
  if (canManageCatalogs()) {
    actions.edit = id => openEdit(id);
    actions.delete = id => openConfirm("Видалити цю групу?", async () => {
      await apiDelete(`${API}/groups/${id}`);
      await reloadGroups();
    });
  }

  renderTable(
    "groups-table",
    rows,
    [
      { key: "name" },
      { key: "coachName" },
      { key: "styleName" },
      { key: "levelName" },
      { key: "categoryName" },
      { key: "subscriptionNames" }
    ],
    actions
  );

  setText("groups-info", filteredGroups.length ? `Всього: ${filteredGroups.length}` : "Немає даних");
  updateGroupFilter(state);
}

function bindGroupFilters() {
  fillFilterSelect("group-category-filter", CATEGORY_LABELS, "Усі категорії");
  fillFilterSelect("group-level-filter", LEVEL_LABELS, "Усі рівні");

  const styleSelect = document.getElementById("group-style-filter");
  if (styleSelect) {
    styleSelect.innerHTML = `
      <option value="">Усі стилі</option>
      ${state.styles.map(style => `<option value="${style.id}">${style.name}</option>`).join("")}
    `;
  }

  document.getElementById("group-search")?.addEventListener("input", event => {
    groupFilters.query = event.target.value;
    renderGroups();
  });

  document.getElementById("group-category-filter")?.addEventListener("change", event => {
    groupFilters.category = event.target.value;
    renderGroups();
  });

  document.getElementById("group-level-filter")?.addEventListener("change", event => {
    groupFilters.level = event.target.value;
    renderGroups();
  });

  document.getElementById("group-style-filter")?.addEventListener("change", event => {
    groupFilters.styleId = event.target.value;
    renderGroups();
  });
}

function fillFilterSelect(id, labels, emptyLabel) {
  const select = document.getElementById(id);
  if (!select) return;

  select.innerHTML = `
    <option value="">${emptyLabel}</option>
    ${Object.entries(labels).map(([value, label]) => `<option value="${value}">${label}</option>`).join("")}
  `;
}

async function reloadGroups() {
  state = await loadGroupPageData();
  renderGroups();
}

function openGroupDetails(groupId, options = {}) {
  if (options.pushState !== false) {
    window.history.pushState({}, "", `${window.location.pathname}?groupId=${groupId}`);
  }

  openGroupClients(state, groupId);
}

function openGroupFromUrl() {
  const groupId = new URLSearchParams(window.location.search).get("groupId");
  if (groupId) {
    openGroupDetails(groupId, { pushState: false });
  } else {
    backToGroupList();
  }
}

async function loadGroupModal() {
  if (!document.getElementById("group-modal")) {
    const response = await fetch("/frontend/groups/group-modal.html");
    document.body.insertAdjacentHTML("beforeend", await response.text());
  }

  fields = {
    name: document.getElementById("group-name"),
    coach: document.getElementById("group-coach"),
    style: document.getElementById("group-style"),
    level: document.getElementById("group-level"),
    category: document.getElementById("group-category"),
    subscriptionsBox: document.getElementById("group-subscriptions-checkboxes")
  };

  fillSelect(fields.coach, state.coaches, coach => getFullName(coach));
  fillStyleSelectForCoach();
  fillCategorySelect();
  renderSubscriptionCheckboxes();

  fields.coach.addEventListener("change", () => fillStyleSelectForCoach());
  document.getElementById("group-close").onclick = closeGroupModal;
  document.getElementById("group-cancel").onclick = closeGroupModal;
  document.getElementById("group-save").onclick = saveGroup;
  document.getElementById("group-modal").addEventListener("click", event => {
    if (event.target.id === "group-modal") closeGroupModal();
  });
}

async function fillStyleSelectForCoach(selectedStyleId = "") {
  if (!fields.style) return;

  const coachId = fields.coach?.value;
  if (!coachId) {
    fields.style.innerHTML = `<option value="">Оберіть тренера</option>`;
    return;
  }

  const styleIds = await apiGet(`${API}/coaches/${coachId}/styles`)
    .then(unwrapCoachStyleIds)
    .catch(() => {
      const coach = state.coaches.find(item => String(item.id) === String(coachId));
      return coach?.styleIds || [];
    });

  const allowedStyles = state.styles.filter(style => styleIds.some(id => String(id) === String(style.id)));
  fields.style.innerHTML = `<option value="">Оберіть</option>`;
  allowedStyles.forEach(style => {
    const option = document.createElement("option");
    option.value = style.id;
    option.textContent = style.name;
    fields.style.appendChild(option);
  });

  fields.style.value = allowedStyles.some(style => String(style.id) === String(selectedStyleId)) ? selectedStyleId : "";
}

function unwrapCoachStyleIds(response) {
  const rows = response?.data ?? response ?? [];
  return rows.map(item => Number(item.id ?? item));
}

function fillSelect(select, items, label) {
  select.innerHTML = `<option value="">Оберіть</option>`;
  items.forEach(item => {
    const option = document.createElement("option");
    option.value = item.id;
    option.textContent = label(item);
    select.appendChild(option);
  });
}

function fillCategorySelect() {
  fields.category.innerHTML = Object.entries(CATEGORY_LABELS)
    .map(([value, label]) => `<option value="${value}">${label}</option>`)
    .join("");
}

function renderSubscriptionCheckboxes(selectedIds = []) {
  if (!fields.subscriptionsBox) return;
  const selected = new Set(selectedIds.map(String));
  fields.subscriptionsBox.innerHTML = state.subscriptions.map(subscription => `
    <label class="checkbox-label">
      <input type="checkbox" value="${subscription.id}" ${selected.has(String(subscription.id)) ? "checked" : ""} />
      ${subscription.name}
    </label>
  `).join("") || `<div class="empty-inline">Спочатку створіть абонементи</div>`;
}

function getSelectedSubscriptionIds() {
  if (!fields.subscriptionsBox) return [];
  return [...fields.subscriptionsBox.querySelectorAll("input[type=checkbox]:checked")].map(input => Number(input.value));
}

function resetForm() {
  editingId = null;
  fields.name.value = "";
  fields.coach.value = "";
  fillStyleSelectForCoach();
  fields.level.value = "0";
  fields.category.value = "0";
  renderSubscriptionCheckboxes();
  document.getElementById("group-modal-title").textContent = "Додати групу";
  document.getElementById("group-save").textContent = "Зберегти";
}

function closeGroupModal() {
  closeModal("group-modal");
  resetForm();
}

async function openEdit(id) {
  const group = state.groups.find(item => String(item.id) === String(id));
  if (!group) return;

  editingId = id;
  fields.name.value = group.name ?? "";
  fields.coach.value = group.coachId ?? "";
  await fillStyleSelectForCoach(group.styleId ?? "");
  fields.level.value = group.skillLevel ?? 0;
  fields.category.value = group.category ?? 0;
  renderSubscriptionCheckboxes(group.subscriptionIds || []);

  document.getElementById("group-modal-title").textContent = "Редагувати групу";
  document.getElementById("group-save").textContent = "Оновити";
  openModal("group-modal");
}

async function saveGroup(event) {
  event.preventDefault();

  const selectedSubscriptionIds = getSelectedSubscriptionIds();
  const payload = {
    name: fields.name.value.trim(),
    coachId: Number(fields.coach.value) || 0,
    styleId: Number(fields.style.value) || 0,
    skillLevel: Number(fields.level.value),
    category: Number(fields.category.value),
    subscriptionIds: selectedSubscriptionIds
  };

  if (!payload.name || !payload.coachId || !payload.styleId) {
    alert("Заповніть назву, тренера та стиль.");
    return;
  }

  if (editingId) {
    await apiPut(`${API}/groups/${editingId}`, payload);
  } else {
    await apiPost(`${API}/groups`, payload);
  }

  closeGroupModal();
  await reloadGroups();
}
