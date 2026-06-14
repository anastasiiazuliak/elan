import { apiGet, apiPatch, canManageCatalogs, renderTable, unwrapData } from "/frontend/layouts/utils.js";
import { API, LEVEL_LABELS, findName, getCategoryLabel } from "./group-data.js";

let selectedGroupId = null;

export function openGroupClients(state, groupId) {
  selectedGroupId = groupId;

  const group = state.groups.find(item => String(item.id) === String(groupId));
  if (!group) return;

  document.getElementById("tab-list").style.display = "none";
  document.getElementById("tab-schedule").classList.remove("active");
  document.getElementById("group-clients-panel").style.display = "";
  document.querySelector(".tabs").style.display = "none";
  document.getElementById("add-group-btn").style.display = "none";
  document.querySelectorAll(".tab-btn").forEach(button => button.classList.remove("active"));

  document.getElementById("group-clients-title").textContent = group.name || `Група #${group.id}`;
  document.getElementById("group-clients-subtitle").textContent =
    `${LEVEL_LABELS[group.skillLevel] || "-"} · ${findName(state.styles, group.styleId, "Стиль не вказаний")} · ${getCategoryLabel(group.category)}`;

  loadGroupClients(state);
}

export async function loadGroupClients(state) {
  if (!selectedGroupId) return;

  const memberships = await apiGet(`${API}/groups/${selectedGroupId}/memberships`).then(unwrapData).catch(() => []);

  renderTable(
    "group-clients-table",
    memberships.map(membership => ({
      ...membership,
      clientName: [membership.clientLastName, membership.clientFirstName].filter(Boolean).join(" ") || `Клієнт #${membership.clientId}`,
      subscriptionName: findName(state.subscriptions, membership.subscriptionId),
      workoutsBalance: `${membership.remainingWorkouts ?? 0} / ${(membership.remainingWorkouts ?? 0) + (membership.completedWorkouts ?? 0)}`
    })),
    [
      { key: "clientName" },
      { key: "subscriptionName" },
      { key: "startDate" },
      { key: "endDate" },
      { key: "workoutsBalance" }
    ],
    {
      view: id => openClientPage(id, memberships),
      ...(canManageCatalogs()
        ? {
            workout: async id => {
              await apiPatch(`${API}/memberships/${id}/use`);
              await loadGroupClients(state);
            }
          }
        : {})
    }
  );
}

function openClientPage(membershipId, memberships) {
  const membership = memberships.find(item => String(item.id) === String(membershipId));
  if (!membership?.clientId) return;
  window.location.href = `/page/clients?clientId=${membership.clientId}`;
}

export function backToGroupList() {
  selectedGroupId = null;
  document.getElementById("group-clients-panel").style.display = "none";
  document.getElementById("tab-list").style.display = "";
  document.getElementById("tab-list").classList.add("active");
  document.querySelector(".tabs").style.display = "";
  if (canManageCatalogs()) {
    document.getElementById("add-group-btn").style.display = "";
  }
  document.querySelector('.tab-btn[data-tab="list"]')?.classList.add("active");
}
