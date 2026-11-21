import { apiGet, getCurrentUser, isCoach, setText, unwrapData } from "/frontend/layouts/utils.js";
import { API, LEVEL_LABELS, findName, getCategoryLabel, loadGroupPageData } from "/frontend/groups/group-data.js";

let state = {
  groups: [],
  styles: [],
  subscriptions: [],
  membershipsByGroup: new Map()
};

document.addEventListener("DOMContentLoaded", initMyGroups);

async function initMyGroups() {
  const user = getCurrentUser();

  if (!user || !isCoach()) {
    window.location.href = "/page/dashboard";
    return;
  }

  const data = await loadGroupPageData();
  state = {
    ...data,
    groups: data.groups.filter(group => String(group.coachId) === String(user.id)),
    membershipsByGroup: new Map()
  };

  await Promise.all(state.groups.map(group => loadGroupMemberships(group.id)));

  document.getElementById("back-to-my-groups")?.addEventListener("click", renderGroupList);
  renderGroupList();
}

function renderGroupList() {
  const container = document.getElementById("coach-groups");
  const backButton = document.getElementById("back-to-my-groups");

  setText("my-groups-title", "Мої групи");
  setText("my-groups-subtitle", state.groups.length ? `Ваші групи: ${state.groups.length}` : "Вас ще не додано до груп");
  if (backButton) backButton.style.display = "none";

  if (!state.groups.length) {
    container.innerHTML = `<div class="card"><div class="empty-panel">Немає даних</div></div>`;
    return;
  }

  container.innerHTML = `
    <div class="card">
      <div class="card-header">
        <div class="card-title">Список груп</div>
      </div>
      <div class="table-wrapper">
        <table>
          <thead>
            <tr>
              <th>№</th>
              <th>Назва</th>
              <th>Стиль</th>
              <th>Рівень</th>
              <th>Категорія</th>
              <th>Клієнтів</th>
            </tr>
          </thead>
          <tbody>
            ${state.groups.map((group, index) => renderGroupRow(group, index)).join("")}
          </tbody>
        </table>
      </div>
    </div>
  `;

  container.querySelectorAll("tr[data-group-id]").forEach(row => {
    row.addEventListener("click", () => renderGroupClients(row.dataset.groupId));
  });
}

function renderGroupRow(group, index) {
  const styleName = findName(state.styles, group.styleId, "Стиль не вказаний");
  const clientsCount = state.membershipsByGroup.get(String(group.id))?.length ?? "-";

  return `
    <tr class="clickable-row" data-group-id="${group.id}">
      <td>${index + 1}</td>
      <td>${group.name || `Група #${group.id}`}</td>
      <td>${styleName}</td>
      <td>${LEVEL_LABELS[group.skillLevel] || "-"}</td>
      <td>${getCategoryLabel(group.category)}</td>
      <td>${clientsCount}</td>
    </tr>
  `;
}

async function renderGroupClients(groupId) {
  const group = state.groups.find(item => String(item.id) === String(groupId));
  const container = document.getElementById("coach-groups");
  const backButton = document.getElementById("back-to-my-groups");
  if (!group || !container) return;

  const memberships = await loadGroupMemberships(groupId);
  const styleName = findName(state.styles, group.styleId, "Стиль не вказаний");

  setText("my-groups-title", group.name || `Група #${group.id}`);
  setText("my-groups-subtitle", `${styleName} · ${LEVEL_LABELS[group.skillLevel] || "-"} · ${getCategoryLabel(group.category)}`);
  if (backButton) backButton.style.display = "";

  container.innerHTML = `
    <div class="card">
      <div class="card-header">
        <div class="card-title">Клієнти групи</div>
        <span class="badge badge-pink">Клієнтів: ${memberships.length}</span>
      </div>
      <div class="table-wrapper">
        <table>
          <thead>
            <tr>
              <th>№</th>
              <th>Клієнт</th>
              <th>Абонемент</th>
              <th>Початок</th>
              <th>Діє до</th>
              <th>Занять</th>
            </tr>
          </thead>
          <tbody>
            ${memberships.length
              ? memberships.map((membership, index) => renderClientRow(membership, index)).join("")
              : `<tr><td colspan="6" class="empty-cell">Немає даних</td></tr>`}
          </tbody>
        </table>
      </div>
    </div>
  `;
}

async function loadGroupMemberships(groupId) {
  const key = String(groupId);
  if (!state.membershipsByGroup.has(key)) {
    const memberships = await apiGet(`${API}/groups/${groupId}/memberships`).then(unwrapData).catch(() => []);
    state.membershipsByGroup.set(key, memberships);
  }

  return state.membershipsByGroup.get(key);
}

function renderClientRow(membership, index) {
  const clientName = [membership.clientLastName, membership.clientFirstName].filter(Boolean).join(" ") || `Клієнт #${membership.clientId}`;
  const subscriptionName = findName(state.subscriptions, membership.subscriptionId, "Абонемент не вказаний");
  const completed = membership.completedWorkouts ?? 0;
  const remaining = membership.remainingWorkouts ?? 0;

  return `
    <tr>
      <td>${index + 1}</td>
      <td>${clientName}</td>
      <td>${subscriptionName}</td>
      <td>${membership.startDate || "-"}</td>
      <td>${membership.endDate || "-"}</td>
      <td>${remaining} / ${remaining + completed}</td>
    </tr>
  `;
}
