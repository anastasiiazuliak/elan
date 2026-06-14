import { allLocations } from "./locations.js";
import { openModal, closeModal, apiGet, apiPost, apiDelete, canManageCatalogs } from "/frontend/layouts/utils.js";

const API_BASE = "http://localhost:18080";

const DAY = ["Пн","Вт","Ср","Чт","Пт","Сб"];

const TIME = [
  "08:00","09:00","10:00","11:00","12:00",
  "13:00","14:00","15:00","16:00","17:00","18:00","19:00","20:00"
];

const LEVEL_LABELS = {
  "beginner": "Початківці",
  "intermediate": "Середній",
  "advanced": "Профі"
};

let selected = {
  hallId: null,
  day: null,
  time: null
};

function getSelectedHall() {
  const locId = document.getElementById("schedule-location-sel").value;
  const hallId = document.getElementById("schedule-hall-sel").value;

  return { locId, hallId };
}

// ================= INIT =================
export function initSchedule() {
  renderGrid();
  bindSelectors();
  
  // Закриття модалки при кліку на фон
  const modal = document.getElementById("schedule-modal");
  if (modal) {
    modal.addEventListener("click", (e) => {
      if (e.target === modal) closeModal("schedule-modal");
    });
  }
}

// ================= GRID =================
async function renderGrid() {
  const grid = document.getElementById("schedule-grid");
  if (!grid) return;

  const { locId, hallId } = getSelectedHall();
  let activeSchedule = [];
  
  // Якщо вибрано зал, тягнемо його розклад
  if (locId && hallId) {
    try {
      const response = await apiGet(`${API_BASE}/locations/${locId}/halls/${hallId}/schedule`);
      activeSchedule = response?.data ?? response ?? [];
    } catch (e) { console.error("Помилка завантаження розкладу", e); }
  }

  const groupsResponse = await apiGet(`${API_BASE}/groups`).catch(() => []);
  const groups = groupsResponse?.data ?? groupsResponse ?? [];

  let html = `<div class="sg-head"></div>`;
  DAY.forEach(d => html += `<div class="sg-head">${d}</div>`);

  TIME.forEach((t, ti) => {
    html += `<div class="sg-time">${t}</div>`;
    for (let d = 0; d < DAY.length; d++) {
      const slot = activeSchedule.find(s => s.day === d && s.time === ti);
      const editable = canManageCatalogs();
      html += `<div class="sg-cell" ${editable ? `onclick="window.openSlot(${d},${ti})"` : ""}>`;

      if (slot) {
        const group = groups.find(g => String(g.id) === String(slot.groupId));
        const groupName = group?.name || `Group #${slot.groupId}`;
        html += `
          <div class="sg-event" title="${groupName} - ${t}">
            ${groupName}<br>
            <small>${t}</small>
            ${editable ? `<button class="sg-delete action-btn" onclick="event.stopPropagation(); window.deleteSlot(${slot.day}, ${slot.time}, ${slot.groupId})" title="Видалити">×</button>` : ""}
          </div>`;
      }
      html += `</div>`;
    }
  });

  grid.innerHTML = html;
}

window.deleteSlot = async (day, time, groupId) => {
  if (!canManageCatalogs()) return;

  const { locId, hallId } = getSelectedHall();
  if (!locId || !hallId) return;
  if (!confirm("Видалити це заняття з розкладу?")) return;
  
  // Бекенд очікує DELETE з тілом для видалення слоту
  try {
    await fetch(`${API_BASE}/locations/${locId}/schedule`, {
      method: "DELETE",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        day: parseInt(day),
        time: parseInt(time),
        hallId: parseInt(hallId),
        groupId: parseInt(groupId)
      })
    });
    renderGrid();
  } catch (e) { console.error("Помилка видалення:", e); }
};

// ================= SLOT CLICK =================
window.openSlot = async (day, time) => {
  if (!canManageCatalogs()) return;

  selected.day = day;
  selected.time = time;

  document.getElementById("schedule-day").value = DAY[day];
  document.getElementById("schedule-time").value = TIME[time];

  // groups
  const groupsResponse = await apiGet(`${API_BASE}/groups`);
  const groups = groupsResponse?.data ?? groupsResponse ?? [];

  const sel = document.getElementById("schedule-group");
  sel.innerHTML = `<option value="">Оберіть групу</option>`;

  groups.forEach(g => {
    sel.innerHTML += `<option value="${g.id}">${g.name}</option>`;
  });

  openModal("schedule-modal");
};

// ================= SAVE =================
window.saveSchedule = async () => {
  if (!canManageCatalogs()) return;

  const groupId = document.getElementById("schedule-group").value;
  const { locId, hallId } = getSelectedHall();

  if (!groupId || !locId || !hallId) {
    alert("Будь ласка, оберіть локацію, зал та групу!");
    return;
  }

  try {
    await apiPost(`${API_BASE}/locations/${locId}/schedule`, {
      day: parseInt(selected.day),
      time: parseInt(selected.time),
      hallId: parseInt(hallId),
      groupId: parseInt(groupId),
      isOccupied: true
    });
    renderGrid();
    closeModal("schedule-modal");
  } catch (e) {
    alert("Не вдалося зберегти розклад. Можливо, цей слот уже зайнятий.");
  }
};

// ================= SELECTORS UPDATE =================
export function updateScheduleSelectors() {
  const locSel = document.getElementById("schedule-location-sel");
  if (!locSel) return;

  const currentVal = locSel.value;
  locSel.innerHTML = `<option value="">— Локація —</option>`;
  
  allLocations.forEach(l => {
    const opt = document.createElement("option");
    opt.value = l.id;
    opt.textContent = l.address;
    locSel.appendChild(opt);
  });
  
  if (currentVal) locSel.value = currentVal;
}

// ================= SELECTORS =================
function bindSelectors() {
  const locSel = document.getElementById("schedule-location-sel");
  const hallSel = document.getElementById("schedule-hall-sel");
  if (!locSel || !hallSel) return;

  locSel.onchange = () => {
    const loc = allLocations.find(l => String(l.id) === String(locSel.value));

    hallSel.innerHTML = `<option value="">— Зал —</option>`;

    loc?.halls?.forEach(h => {
      hallSel.innerHTML += `
        <option value="${h.id}">${h.name}</option>
      `;
    });

    selected.hallId = null;
    renderGrid();
  };

  hallSel.onchange = () => {
    selected.hallId = hallSel.value;
    renderGrid();
  };
}
