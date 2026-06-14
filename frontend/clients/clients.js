import { apiGet, apiPost, apiPut, canCreateClient, closeModal, formatUaPhone, hideElement, initPasswordReveal, initUaPhoneInput, isClient, isLocationAdmin, openModal, renderTable, setText, unwrapData } from "/frontend/layouts/utils.js";
import { API as ROOT_API, CATEGORY_LABELS, getCategory, getCategoryLabel } from "/frontend/groups/group-data.js";

const API = "http://localhost:18080/clients";
const GROUPS_API = "http://localhost:18080/groups";
const SUBS_API = "http://localhost:18080/subscriptions";
const MEMBERSHIPS_API = "http://localhost:18080/memberships";

let editingId = null;
let selectedClient = null;
let fields = {};
let membershipFields = {};
let clients = [];
let groups = [];
let subscriptions = [];
let clientFilters = { query: "", category: "" };

document.addEventListener("DOMContentLoaded", async () => {
  if (isClient()) {
    document.querySelector(".content").innerHTML = `
      <div class="page-header">
        <h1>Немає доступу</h1>
      </div>
      <div class="card">
        <div class="empty-panel">Клієнт не має доступу до списку інших клієнтів.</div>
      </div>
    `;
    return;
  }

  await Promise.all([loadClientModal(), loadMembershipModal()]);
  await loadPageData();
  await loadClients();
  bindClientFilters();
  bindClientDetailsNavigation();

  if (!canCreateClient()) {
    hideElement("add-client-btn");
    return;
  }

  document.getElementById("add-client-btn")?.addEventListener("click", () => {
    resetForm();
    openClientModal();
  });
});

async function loadPageData() {
  [groups, subscriptions] = await Promise.all([
    apiGet(GROUPS_API).then(unwrapData).catch(() => []),
    apiGet(SUBS_API).then(unwrapData).catch(() => [])
  ]);
}

async function loadClients() {
  clients = await apiGet(API).then(unwrapData).catch(() => []);
  renderClients();
  openClientFromUrl();
}

function renderClients() {
  const query = clientFilters.query.toLowerCase();
  const filtered = clients.filter(client => {
    const matchesQuery = !query || JSON.stringify(client).toLowerCase().includes(query);
    const matchesCategory = !clientFilters.category || String(getCategory(client)) === String(clientFilters.category);
    return matchesQuery && matchesCategory;
  });

  const rows = clients.map(client => ({
    ...client,
    phone: client.phone ? formatUaPhone(client.phone) : "-",
    categoryName: getCategoryLabel(getCategory(client))
  })).filter(client => filtered.some(item => String(item.id) === String(client.id)));

  const actions = { view: id => openClientDetails(id) };

  renderTable(
    "clients-table",
    rows,
    [
      { key: "firstName" },
      { key: "lastName" },
      { key: "patronymic" },
      { key: "username" },
      { key: "phone" },
      { key: "categoryName" }
    ],
    actions
  );

  setText("clients-info", filtered.length ? `Всього: ${filtered.length}` : "Немає даних");
}

function bindClientFilters() {
  const categorySelect = document.getElementById("client-category-filter");
  if (categorySelect) {
    categorySelect.innerHTML = `
      <option value="">Усі категорії</option>
      ${Object.entries(CATEGORY_LABELS)
        .map(([value, label]) => `<option value="${value}">${label}</option>`)
        .join("")}
    `;
  }

  document.getElementById("client-search")?.addEventListener("input", event => {
    clientFilters.query = event.target.value;
    renderClients();
  });

  categorySelect?.addEventListener("change", event => {
    clientFilters.category = event.target.value;
    renderClients();
  });
}

function bindClientDetailsNavigation() {
  document.getElementById("back-to-clients-btn")?.addEventListener("click", backToClientList);
  window.addEventListener("popstate", openClientFromUrl);
}

function openClientFromUrl() {
  const clientId = new URLSearchParams(window.location.search).get("clientId");
  if (clientId) {
    openClientDetails(clientId, { pushState: false });
  } else {
    showClientList();
  }
}

async function openClientDetails(clientId, options = {}) {
  selectedClient = clients.find(client => String(client.id) === String(clientId));
  if (!selectedClient) return;

  if (options.pushState !== false) {
    window.history.pushState({}, "", `${window.location.pathname}?clientId=${selectedClient.id}`);
  }

  document.getElementById("clients-list-panel")?.classList.remove("active");
  document.getElementById("clients-list-panel").style.display = "none";
  const panel = document.getElementById("client-memberships-panel");
  panel.style.display = "";
  document.getElementById("client-memberships-title").textContent = getClientLabel(selectedClient);
  document.getElementById("client-memberships-subtitle").textContent =
    `Категорія: ${getCategoryLabel(getCategory(selectedClient))}`;

  const addButton = document.getElementById("add-membership-btn");
  if (isLocationAdmin()) {
    addButton.style.display = "";
    addButton.onclick = () => openMembershipModal();
  } else {
    addButton.style.display = "none";
  }

  await renderClientMemberships();
}

function backToClientList() {
  window.history.pushState({}, "", window.location.pathname);
  showClientList();
}

function showClientList() {
  selectedClient = null;
  const listPanel = document.getElementById("clients-list-panel");
  if (listPanel) listPanel.style.display = "";
  const detailsPanel = document.getElementById("client-memberships-panel");
  if (detailsPanel) detailsPanel.style.display = "none";
}

async function renderClientMemberships() {
  if (!selectedClient) return;

  const memberships = await apiGet(`${ROOT_API}/clients/${selectedClient.id}/memberships`).then(unwrapData).catch(() => []);
  const list = document.getElementById("client-memberships-list");

  if (!memberships.length) {
    list.innerHTML = `<div class="empty-state">Абонементів ще немає</div>`;
    return;
  }

  list.innerHTML = memberships.map(membership => {
    const group = groups.find(item => String(item.id) === String(membership.groupId));
    const subscription = subscriptions.find(item => String(item.id) === String(membership.subscriptionId));
    const active = isMembershipActive(membership);
    return `
      <div class="membership-card ${active ? "active" : "inactive"}">
        <div>
          <div class="membership-title">${subscription?.name || "Абонемент"}</div>
          <div class="membership-meta">${membership.groupName || group?.name || "Група"} · ${subscription?.duration ?? "-"} днів</div>
        </div>
        <div class="membership-stats">
          <span>${membership.remainingWorkouts ?? 0} занять</span>
          <span>до ${membership.endDate || "-"}</span>
        </div>
      </div>
    `;
  }).join("");
}

function isMembershipActive(membership) {
  if (!membership.endDate) return true;
  const end = new Date(membership.endDate);
  if (Number.isNaN(end.getTime())) return true;
  end.setHours(23, 59, 59, 999);
  return end >= new Date() && Number(membership.remainingWorkouts ?? 0) > 0;
}

async function loadClientModal() {
  if (!document.getElementById("client-modal")) {
    const response = await fetch("/frontend/clients/client-modal.html");
    document.body.insertAdjacentHTML("beforeend", await response.text());
  }

  const modal = document.getElementById("client-modal");
  fields = {
    firstName: document.getElementById("client-firstName"),
    lastName: document.getElementById("client-lastName"),
    patronymic: document.getElementById("client-patronymic"),
    birthDate: document.getElementById("client-birthDate"),
    phone: document.getElementById("client-phone"),
    username: document.getElementById("client-username"),
    password: document.getElementById("client-password"),
    passwordGroup: document.getElementById("client-password-group")
  };
  initUaPhoneInput(fields.phone);
  initPasswordReveal(fields.password);

  document.getElementById("client-close").onclick = closeClientModal;
  document.getElementById("client-cancel").onclick = closeClientModal;
  document.getElementById("client-save").onclick = saveClient;
  modal.addEventListener("click", event => {
    if (event.target.id === "client-modal") closeClientModal();
  });
}

async function loadMembershipModal() {
  const modal = document.getElementById("membership-modal");
  if (!modal) return;

  membershipFields = {
    group: document.getElementById("membership-group"),
    subscription: document.getElementById("membership-subscription")
  };

  document.getElementById("membership-close").onclick = closeMembershipModal;
  document.getElementById("membership-cancel").onclick = closeMembershipModal;
  document.getElementById("membership-save").onclick = saveMembership;
  membershipFields.group.addEventListener("change", fillMembershipSubscriptions);
  modal.addEventListener("click", event => {
    if (event.target.id === "membership-modal") closeMembershipModal();
  });
}

function openClientModal() {
  openModal("client-modal");
}

function closeClientModal() {
  closeModal("client-modal");
  resetForm();
}

function resetForm() {
  editingId = null;
  Object.values(fields).forEach(field => {
    if (field) field.value = "";
  });
  if (fields.phone) fields.phone.value = formatUaPhone();

  document.getElementById("client-modal-title").textContent = "Додати клієнта";
  document.getElementById("client-save").textContent = "Зберегти";
  if (fields.passwordGroup) fields.passwordGroup.style.display = "";
}

async function saveClient(event) {
  event.preventDefault();

  const payload = {
    firstName: fields.firstName.value.trim(),
    lastName: fields.lastName.value.trim(),
    patronymic: fields.patronymic.value.trim(),
    birthDate: fields.birthDate.value,
    phone: fields.phone.value.trim(),
    username: fields.username.value.trim(),
    password: fields.password.value
  };

  if (editingId) {
    await apiPut(`${API}/${editingId}`, payload);
  } else {
    await apiPost(API, payload);
  }

  closeClientModal();
  await loadClients();
}

function openMembershipModal() {
  if (!selectedClient) return;

  fillMembershipGroups();
  fillMembershipSubscriptions();
  openModal("membership-modal");
}

function closeMembershipModal() {
  closeModal("membership-modal");
  membershipFields.group.value = "";
  membershipFields.subscription.innerHTML = `<option value="">Оберіть абонемент</option>`;
}

function fillMembershipGroups() {
  const clientCategory = getCategory(selectedClient);
  const matchingGroups = groups.filter(group =>
    Number(group.category) === Number(clientCategory) &&
    (group.subscriptionIds || []).length > 0
  );

  membershipFields.group.innerHTML = `
    <option value="">Оберіть групу</option>
    ${matchingGroups.map(group => `<option value="${group.id}">${group.name}</option>`).join("")}
  `;

  membershipFields.subscription.innerHTML = `<option value="">Спочатку оберіть групу</option>`;
}

function fillMembershipSubscriptions() {
  const group = groups.find(item => String(item.id) === String(membershipFields.group.value));
  const availableSubscriptions = subscriptions.filter(subscription =>
    (group?.subscriptionIds || []).some(id => String(id) === String(subscription.id))
  );

  membershipFields.subscription.innerHTML = `
    <option value="">Оберіть абонемент</option>
    ${availableSubscriptions.map(subscription => `<option value="${subscription.id}">${subscription.name}</option>`).join("")}
  `;
}

async function saveMembership(event) {
  event.preventDefault();
  if (!selectedClient || !membershipFields.group.value || !membershipFields.subscription.value) return;

  await apiPost(MEMBERSHIPS_API, {
    clientId: Number(selectedClient.id),
    groupId: Number(membershipFields.group.value),
    subscriptionId: Number(membershipFields.subscription.value)
  });

  closeMembershipModal();
  await loadPageData();
  await renderClientMemberships();
}

function getClientLabel(client) {
  return [client.lastName, client.firstName, client.patronymic].filter(Boolean).join(" ") || `Клієнт #${client.id}`;
}
