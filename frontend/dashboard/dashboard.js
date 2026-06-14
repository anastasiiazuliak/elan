import { apiGet, apiPatch, getCurrentUser, isClient, setText, unwrapData } from "/frontend/layouts/utils.js";

const API = "http://localhost:18080";
const DAY_LABELS = ["Пн", "Вт", "Ср", "Чт", "Пт", "Сб"];
const TIME_LABELS = ["08:00", "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00", "18:00", "19:00", "20:00"];

let state = {
  groups: [],
  locations: [],
  subscriptions: [],
  coaches: [],
  styles: [],
  client: null,
  clientGroups: []
};

document.addEventListener("DOMContentLoaded", initDashboard);

async function initDashboard() {
  updateClock();
  setInterval(updateClock, 30000);

  const [groups, locations, subscriptions, coaches, styles] = await Promise.all([
    apiGet(`${API}/groups`).then(unwrapData).catch(() => []),
    apiGet(`${API}/locations`).then(unwrapData).catch(() => []),
    apiGet(`${API}/subscriptions`).then(unwrapData).catch(() => []),
    apiGet(`${API}/coaches`).then(unwrapData).catch(() => []),
    apiGet(`${API}/styles`).then(unwrapData).catch(() => [])
  ]);

  state = { groups, locations, subscriptions, coaches, styles, client: null, clientGroups: [] };

  if (isClient()) {
    await initClientDashboard();
  } else {
    renderCurrentSessions();
  }
}

function updateClock() {
  const now = new Date();
  setText("current-time", now.toLocaleTimeString("uk-UA", { hour: "2-digit", minute: "2-digit" }));
}

async function renderCurrentSessions() {
  const sessions = await getCurrentSessions();
  const container = document.getElementById("sessions");

  if (!sessions.length) {
    setText("dashboard-subtitle", "Зараз занять немає");
    container.innerHTML = `<div class="card"><div class="empty-panel">Немає даних</div></div>`;
    return;
  }

  setText("dashboard-subtitle", `Активні заняття: ${sessions.length}`);
  container.innerHTML = sessions.map(renderSession).join("");
  bindAttendanceButtons();
}

async function getCurrentSessions() {
  const day = getCurrentDayIndex();
  const time = getCurrentTimeIndex();

  if (day < 0 || time < 0) return [];

  const schedules = state.locations.flatMap(location =>
    (location.halls || []).flatMap(hall =>
      (location.schedule || []).map(slot => ({ ...slot, location, hall }))
    )
  );

  let currentSlots = schedules.filter(slot => slot.day === day && slot.time === time);

  if (!currentSlots.length) {
    currentSlots = await loadCurrentSlotsFromApi(day, time);
  }

  return Promise.all(currentSlots.map(async slot => {
    const group = state.groups.find(item => String(item.id) === String(slot.groupId));
    const clients = group ? await apiGet(`${API}/groups/${group.id}/memberships`).then(unwrapData).catch(() => []) : [];
    return { ...slot, group, clients };
  }));
}

async function loadCurrentSlotsFromApi(day, time) {
  const slots = [];

  for (const location of state.locations) {
    const schedule = await apiGet(`${API}/locations/${location.id}/schedule?day=${day}`).then(unwrapData).catch(() => []);
    schedule
      .filter(slot => slot.time === time)
      .forEach(slot => {
        const hall = (location.halls || []).find(item => String(item.id) === String(slot.hallId));
        slots.push({ ...slot, location, hall });
      });
  }

  return slots;
}

function getCurrentDayIndex() {
  const day = new Date().getDay();
  return day >= 1 && day <= 6 ? day - 1 : -1;
}

function getCurrentTimeIndex() {
  const hour = new Date().getHours();
  return TIME_LABELS.findIndex(label => Number(label.slice(0, 2)) === hour);
}

function renderSession(session) {
  const groupName = session.group?.name || `Група #${session.groupId}`;
  const locationName = session.location?.address || "Локація не вказана";
  const hallName = session.hall?.name || `Зал #${session.hallId}`;
  const clients = session.clients || [];

  return `
    <article class="session-card">
      <div class="session-header">
        <div>
          <div class="session-title">${groupName}</div>
          <div class="session-meta">${locationName} · ${hallName}</div>
        </div>
        <div class="session-time">${DAY_LABELS[session.day]} · ${TIME_LABELS[session.time]}</div>
      </div>
      <div class="attendance-list">
        ${clients.length ? clients.map(client => renderClientRow(client, session.groupId)).join("") : `<div class="empty-panel">Немає даних</div>`}
      </div>
    </article>
  `;
}

function renderClientRow(client, groupId) {
  const name = [client.clientLastName, client.clientFirstName].filter(Boolean).join(" ") || `Клієнт #${client.clientId}`;
  const subscription = state.subscriptions.find(item => String(item.id) === String(client.subscriptionId))?.name || "Абонемент не вказаний";
  const key = attendanceKey(groupId, client.clientId);
  const marked = localStorage.getItem(key) === "1";

  return `
    <div class="attendance-row">
      <div>
        <div class="client-name">${name}</div>
        <div class="client-note">${subscription} · залишок ${client.remainingWorkouts ?? 0}</div>
      </div>
      <button class="attendance-btn ${marked ? "marked" : ""}" data-client-id="${client.clientId}" data-membership-id="${client.id}" data-group-id="${groupId}" ${marked ? "disabled" : ""}>
        ${marked ? "Відмічено" : "Відмітити"}
      </button>
    </div>
  `;
}

function bindAttendanceButtons() {
  document.querySelectorAll(".attendance-btn:not(.marked)").forEach(button => {
    button.addEventListener("click", async () => {
      await apiPatch(`${API}/memberships/${button.dataset.membershipId}/use`);
      localStorage.setItem(attendanceKey(button.dataset.groupId, button.dataset.clientId), "1");
      button.textContent = "Відмічено";
      button.classList.add("marked");
      button.disabled = true;
    });
  });
}

function attendanceKey(groupId, clientId) {
  const date = new Date().toISOString().slice(0, 10);
  const hour = new Date().getHours();
  return `elanAttendance:${date}:${hour}:${groupId}:${clientId}`;
}

async function initClientDashboard() {
  const user = getCurrentUser();
  if (!user) return;

  state.client = await apiGet(`${API}/clients/${user.id}`).then(unwrapData).catch(() => null);
  state.clientGroups = await loadClientGroups(user.id);

  setText("dashboard-title", "Моя відвідуваність");
  setText("dashboard-subtitle", state.clientGroups.length ? "Ваші заняття та відмітки присутності" : "Вас ще не додано до груп");
  renderClientDashboard();
}

async function loadClientGroups(clientId) {
  const memberships = await apiGet(`${API}/clients/${clientId}/memberships`).then(unwrapData).catch(() => []);
  const groupIds = new Set(memberships.map(membership => String(membership.groupId)));

  return state.groups.filter(group => groupIds.has(String(group.id)));
}

function renderClientDashboard() {
  const container = document.getElementById("sessions");
  const client = state.client;

  if (!client || !state.clientGroups.length) {
    container.innerHTML = `<div class="card"><div class="empty-panel">Немає даних</div></div>`;
    return;
  }

  container.innerHTML = `
    <section class="client-attendance-panel">
      <div class="client-attendance-toolbar">
        <select id="client-group-select" class="btn btn-ghost">
          ${state.clientGroups.map(group => `<option value="${group.id}">${group.name || `Група #${group.id}`}</option>`).join("")}
        </select>
        <select id="client-day-select" class="btn btn-ghost">
          <option value="">Усі дні</option>
          ${DAY_LABELS.map((day, index) => `<option value="${index}">${day}</option>`).join("")}
        </select>
        <div class="workout-balance ${Number(client.remainingWorkouts) > 0 ? "is-burning" : ""}">
          <span class="fire-dot"></span>
          Залишок: ${client.remainingWorkouts ?? 0}
        </div>
      </div>
      <div id="client-attendance-list" class="client-attendance-list"></div>
    </section>
  `;

  document.getElementById("client-group-select")?.addEventListener("change", renderClientAttendanceList);
  document.getElementById("client-day-select")?.addEventListener("change", renderClientAttendanceList);
  renderClientAttendanceList();
}

async function renderClientAttendanceList() {
  const groupId = document.getElementById("client-group-select")?.value;
  const dayFilter = document.getElementById("client-day-select")?.value;
  const list = document.getElementById("client-attendance-list");
  const group = state.clientGroups.find(item => String(item.id) === String(groupId));

  if (!group || !list) return;

  const schedule = await apiGet(`${API}/groups/${group.id}/schedule`).then(unwrapData).catch(() => []);
  const visibleSlots = schedule
    .filter(slot => dayFilter === "" || String(slot.day) === String(dayFilter))
    .sort((a, b) => a.day - b.day || a.time - b.time);

  if (!visibleSlots.length) {
    list.innerHTML = `<div class="empty-panel">Для цієї групи розкладу немає</div>`;
    return;
  }

  list.innerHTML = visibleSlots.map(slot => renderClientSlot(group, slot)).join("");
}

function renderClientSlot(group, slot) {
  const coach = state.coaches.find(item => String(item.id) === String(group.coachId));
  const style = state.styles.find(item => String(item.id) === String(group.styleId));
  const locationInfo = findLocationForHall(slot.hallId);
  const attended = hasAttendanceMark(group.id, state.client.id, slot);

  return `
    <article class="client-session ${attended ? "is-attended" : ""}">
      <div>
        <div class="session-title">${group.name || `Група #${group.id}`}</div>
        <div class="session-meta">
          ${DAY_LABELS[slot.day] || "-"} · ${TIME_LABELS[slot.time] || "-"} · ${style?.name || "Стиль не вказаний"}
        </div>
        <div class="session-meta">
          ${getPersonName(coach) || "Тренер не вказаний"} · ${locationInfo}
        </div>
      </div>
      <div class="attendance-status">${attended ? "Присутній" : "Очікує відмітки"}</div>
    </article>
  `;
}

function hasAttendanceMark(groupId, clientId, slot) {
  const prefix = "elanAttendance:";
  for (let index = 0; index < localStorage.length; index++) {
    const key = localStorage.key(index);
    if (!key?.startsWith(prefix) || localStorage.getItem(key) !== "1") continue;

    const [, date, hour, markedGroupId, markedClientId] = key.split(":");
    const markedDate = new Date(`${date}T${String(hour).padStart(2, "0")}:00:00`);
    const markedDay = getScheduleDayIndex(markedDate);

    if (
      String(markedGroupId) === String(groupId) &&
      String(markedClientId) === String(clientId) &&
      markedDay === Number(slot.day) &&
      Number(hour) === Number(TIME_LABELS[slot.time]?.slice(0, 2))
    ) {
      return true;
    }
  }

  return false;
}

function getScheduleDayIndex(date) {
  const day = date.getDay();
  return day >= 1 && day <= 6 ? day - 1 : -1;
}

function findLocationForHall(hallId) {
  for (const location of state.locations) {
    const hall = (location.halls || []).find(item => String(item.id) === String(hallId));
    if (hall) return `${location.address} · ${hall.name || `Зал #${hall.id}`}`;
  }

  return "Локація не вказана";
}

function getPersonName(person) {
  return [person?.lastName, person?.firstName, person?.patronymic].filter(Boolean).join(" ");
}
