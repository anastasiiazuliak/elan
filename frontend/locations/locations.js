import { apiGet, apiPost, apiPut, apiDelete, openModal, closeModal } from "/frontend/layouts/utils.js";
import { loadConfirmModal, openConfirm } from "/frontend/layouts/confirm-modal.js";

const API = "http://localhost:18080/locations";

const DAY_LABELS  = ["Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Нд"];
const TIME_LABELS = ["08:00","09:30","11:00","12:30","14:00","15:30","17:00","18:30","20:00"];
const HALL_TYPES  = ["Танцювальний", "Кардіо", "Силовий", "Йога"];

let editingLocationId = null;
let activeHallLocationId = null;
let editingHallId = null;
let allLocations = [];

// ═══════════ LOCATION CARDS ═══════════
async function loadLocations() {
  try {
    allLocations = await apiGet(API);
    renderLocationCards();
    populateLocationSelect();
  } catch (e) {
    console.error("loadLocations error:", e);
  }
}

function renderLocationCards() {
  const container = document.getElementById("location-cards");
  if (!container) return;

  if (!allLocations.length) {
    container.innerHTML = `<div style="color:var(--text-muted);padding:40px;">Немає локацій</div>`;
    return;
  }

  container.innerHTML = allLocations.map(loc => `
    <div class="location-card">
      <div class="location-card-head">
        <div class="location-card-title">📍 ${loc.address}</div>
        <div style="display:flex;gap:6px;">
          <button class="action-btn" onclick="startEditLocation(${loc.id})">✏️</button>
          <button class="action-btn" onclick="deleteLocation(${loc.id})">🗑️</button>
        </div>
      </div>
      <div class="location-card-body">
        <div style="font-size:12px;color:var(--text-muted);margin-bottom:8px;font-weight:600;text-transform:uppercase;letter-spacing:.05em;">Зали</div>
        ${renderHallRows(loc)}
        <button class="btn btn-ghost" style="width:100%;margin-top:10px;font-size:12px;"
          onclick="openAddHall(${loc.id})">+ Додати зал</button>
      </div>
    </div>
  `).join("");
}

function renderHallRows(loc) {
  if (!loc.halls || !loc.halls.length) {
    return `<div style="color:var(--text-muted);font-size:13px;padding:8px 0;">Немає залів</div>`;
  }
  return loc.halls.map(h => `
    <div class="hall-row">
      <div>
        <span style="font-weight:600;">${HALL_TYPES[h.type] ?? "Зал"}</span>
        <span style="color:var(--text-muted);margin-left:6px;">👥 ${h.capacity}</span>
      </div>
      <div class="hall-actions">
        <button class="action-btn" onclick="startEditHall(${loc.id}, ${h.id}, ${h.capacity})">✏️</button>
        <button class="action-btn" onclick="deleteHall(${loc.id}, ${h.id})">🗑️</button>
      </div>
    </div>
  `).join("");
}

// expose to inline onclick
window.startEditLocation = (id) => {
  const loc = allLocations.find(l => l.id === id);
  if (!loc) return;
  editingLocationId = id;
  document.getElementById("location-address").value = loc.address;
  document.getElementById("location-modal-title").textContent = "Редагувати локацію";
  document.getElementById("location-save").textContent = "Оновити";
  openModal("location-modal");
};

window.deleteLocation = (id) => {
  openConfirm("Видалити цю локацію разом із залами?", async () => {
    await apiDelete(`${API}/${id}`);
    loadLocations();
  });
};

window.openAddHall = (locationId) => {
  activeHallLocationId = locationId;
  editingHallId = null;
  document.getElementById("hall-capacity").value = "";
  document.getElementById("hall-type").value = "0";
  document.getElementById("hall-modal-title").textContent = "Додати зал";
  document.getElementById("hall-save").textContent = "Зберегти";
  openModal("hall-modal");
};

window.startEditHall = (locationId, hallId, capacity) => {
  activeHallLocationId = locationId;
  editingHallId = hallId;
  document.getElementById("hall-capacity").value = capacity;
  document.getElementById("hall-modal-title").textContent = "Редагувати зал";
  document.getElementById("hall-save").textContent = "Оновити";
  openModal("hall-modal");
};

window.deleteHall = (locationId, hallId) => {
  openConfirm("Видалити цей зал?", async () => {
    await apiDelete(`${API}/${locationId}/halls/${hallId}`);
    loadLocations();
  });
};

// ═══════════ MODAL ═══════════
async function loadLocationModal() {
  if (document.getElementById("location-modal")) return;

  const res  = await fetch("/frontend/locations/location-modal.html");
  const html = await res.text();
  document.body.insertAdjacentHTML("beforeend", html);

  // location modal handlers
  document.getElementById("location-close").onclick =
  document.getElementById("location-cancel").onclick = closeLocationModal;

  document.getElementById("location-modal").addEventListener("click", e => {
    if (e.target.id === "location-modal") closeLocationModal();
  });

  document.getElementById("location-save").onclick = saveLocation;

  // hall modal handlers
  document.getElementById("hall-close").onclick =
  document.getElementById("hall-cancel").onclick = () => closeModal("hall-modal");

  document.getElementById("hall-modal").addEventListener("click", e => {
    if (e.target.id === "hall-modal") closeModal("hall-modal");
  });

  document.getElementById("hall-save").onclick = saveHall;
}

function closeLocationModal() {
  editingLocationId = null;
  document.getElementById("location-address").value = "";
  document.getElementById("location-modal-title").textContent = "Додати локацію";
  document.getElementById("location-save").textContent = "Зберегти";
  closeModal("location-modal");
}

async function saveLocation(e) {
  e.preventDefault();
  const address = document.getElementById("location-address").value.trim();
  if (!address) { document.getElementById("location-address").focus(); return; }

  try {
    if (editingLocationId) {
      await apiPut(`${API}/${editingLocationId}`, { address });
    } else {
      await apiPost(API, { address });
    }
    closeLocationModal();
    loadLocations();
  } catch (err) {
    console.error("saveLocation error:", err);
  }
}

async function saveHall(e) {
  e.preventDefault();
  const capacity = parseInt(document.getElementById("hall-capacity").value) || 0;
  const type     = parseInt(document.getElementById("hall-type").value);

  if (!capacity) { document.getElementById("hall-capacity").focus(); return; }

  try {
    if (editingHallId) {
      await apiPut(`${API}/${activeHallLocationId}/halls/${editingHallId}`, { capacity });
    } else {
      await apiPost(`${API}/${activeHallLocationId}/halls`, { capacity, type });
    }
    closeModal("hall-modal");
    loadLocations();
  } catch (err) {
    console.error("saveHall error:", err);
  }
}

// ═══════════ SCHEDULE ═══════════
function populateLocationSelect() {
  const sel = document.getElementById("schedule-location-sel");
  while (sel.options.length > 1) sel.remove(1);
  allLocations.forEach(l => {
    const opt = document.createElement("option");
    opt.value = l.id;
    opt.textContent = l.address;
    sel.appendChild(opt);
  });
  // reset hall select
  const hallSel = document.getElementById("schedule-hall-sel");
  while (hallSel.options.length > 1) hallSel.remove(1);
}

async function onLocationSelectChange(locationId) {
  const hallSel = document.getElementById("schedule-hall-sel");
  while (hallSel.options.length > 1) hallSel.remove(1);

  if (!locationId) {
    document.getElementById("schedule-grid").innerHTML = "";
    return;
  }

  const loc = allLocations.find(l => String(l.id) === String(locationId));
  if (!loc || !loc.halls) return;

  loc.halls.forEach(h => {
    const opt = document.createElement("option");
    opt.value = h.id;
    opt.textContent = `${HALL_TYPES[h.type] ?? "Зал"} (${h.capacity} місць)`;
    hallSel.appendChild(opt);
  });

  // якщо є хоч один зал — одразу показуємо
  if (loc.halls.length > 0) {
    hallSel.value = loc.halls[0].id;
    buildHallSchedule(locationId, loc.halls[0].id);
  }
}

async function buildHallSchedule(locationId, hallId) {
  const grid = document.getElementById("schedule-grid");
  if (!grid) return;

  if (!locationId || !hallId) {
    grid.innerHTML = "";
    return;
  }

  let schedule = [];
  try {
    schedule = await apiGet(`${API}/${locationId}/halls/${hallId}/schedule`);
  } catch {
    schedule = [];
  }

  let html = `<div class="sg-head"></div>`;
  DAY_LABELS.forEach(d => { html += `<div class="sg-head">${d}</div>`; });

  TIME_LABELS.forEach((timeLabel, timeIdx) => {
    html += `<div class="sg-time">${timeLabel}</div>`;
    for (let dayIdx = 0; dayIdx < 7; dayIdx++) {
      const events = schedule.filter(s => s.day === dayIdx && s.time === timeIdx);
      html += `<div class="sg-cell">`;
      events.forEach(ev => {
        html += `<div class="sg-event">👥 Група #${ev.groupId}</div>`;
      });
      html += `</div>`;
    }
  });

  grid.innerHTML = html;
}

// ═══════════ TABS ═══════════
function initTabs() {
  document.querySelectorAll(".tab-btn").forEach(btn => {
    btn.addEventListener("click", () => {
      document.querySelectorAll(".tab-btn").forEach(b => b.classList.remove("active"));
      document.querySelectorAll(".tab-panel").forEach(p => p.classList.remove("active"));
      btn.classList.add("active");
      document.getElementById(`tab-${btn.dataset.tab}`).classList.add("active");
    });
  });

  document.getElementById("schedule-location-sel").addEventListener("change", e => {
    onLocationSelectChange(e.target.value);
  });

  document.getElementById("schedule-hall-sel").addEventListener("change", e => {
    const locId = document.getElementById("schedule-location-sel").value;
    buildHallSchedule(locId, e.target.value);
  });
}

// ═══════════ INIT ═══════════
document.addEventListener("DOMContentLoaded", async () => {
  await loadConfirmModal();
  await loadLocationModal();
  initTabs();

  document.getElementById("add-location-btn").onclick = () => {
    editingLocationId = null;
    document.getElementById("location-address").value = "";
    document.getElementById("location-modal-title").textContent = "Додати локацію";
    document.getElementById("location-save").textContent = "Зберегти";
    openModal("location-modal");
  };

  loadLocations();
});