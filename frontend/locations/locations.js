import {
  apiGet,
  apiPost,
  apiPut,
  apiDelete,
  canManageCatalogs,
  icon,
  openModal,
  closeModal,
} from "/frontend/layouts/utils.js";
import {
  loadConfirmModal,
  openConfirm,
} from "/frontend/layouts/confirm-modal.js";
import { initSchedule, updateScheduleSelectors } from "./schedule.js";

const API = "/locations";

const DAY_LABELS = ["Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Нд"];
const TIME_LABELS = [
  "08:00",
  "09:00",
  "10:00",
  "11:00",
  "12:00",
  "13:00",
  "14:00",
  "15:00",
  "16:00",
  "17:00",
  "18:00",
  "19:00",
  "20:00",
];
const HALL_TYPES = ["Танцювальний", "Кардіо", "Силовий", "Йога"];

let editingLocationId = null;
let activeHallLocationId = null;
let editingHallId = null;
export let allLocations = [];

// ═══════════ LOAD LOCATIONS ═══════════
export async function loadLocations() {
  try {
    const res = await apiGet(API);

    allLocations = res?.data ?? res ?? [];
    if (!Array.isArray(allLocations)) allLocations = [];

    renderLocationCards();
    updateScheduleSelectors(); // Оновлюємо селектори в розкладі
  } catch (e) {
    console.error("loadLocations error:", e);
    allLocations = [];
  }
}

// ═══════════ LOCATION CARDS ═══════════
function renderLocationCards() {
  const container = document.getElementById("location-cards");
  if (!container) return;

  if (!allLocations.length) {
    container.innerHTML = `<div style="color:var(--text-muted);padding:40px;">Немає локацій</div>`;
    return;
  }

  container.innerHTML = allLocations
    .map(
      (loc) => `
    <div class="location-card">
      <div class="location-card-head">
        <div class="location-card-title">${icon("location")} ${loc.address}</div>
        ${canManageCatalogs() ? `<div style="display:flex;gap:6px;">
          <button class="action-btn" onclick="startEditLocation(${loc.id})" title="Редагувати">${icon("edit")}</button>
          <button class="action-btn" onclick="deleteLocation(${loc.id})" title="Видалити">${icon("delete")}</button>
        </div>` : ""}
      </div>

      <div class="location-card-body">
        <div style="font-size:12px;color:var(--text-muted);margin-bottom:8px;font-weight:600;text-transform:uppercase;">
          Зали
        </div>

        ${renderHallRows(loc)}

        ${canManageCatalogs() ? `<button class="btn btn-ghost"
          style="width:100%;margin-top:10px;font-size:12px;"
          onclick="openAddHall(${loc.id})">
          + Додати зал
        </button>` : ""}
      </div>
    </div>
  `,
    )
    .join("");
}

function renderHallRows(loc) {
  const halls = loc.halls ?? [];

  if (!Array.isArray(halls) || halls.length === 0) {
    return `<div style="color:var(--text-muted);font-size:13px;padding:8px 0;">Немає залів</div>`;
  }

  return halls
    .map(
      (h) => `
    <div class="hall-row">
      <div>
        <span style="font-weight:600;">
          ${h.name || HALL_TYPES[h.type] || "Зал"}
        </span>
        <span style="color:var(--text-muted);margin-left:6px;">
          ${icon("users")} ${h.capacity}
        </span>
      </div>

      ${canManageCatalogs() ? `<div class="hall-actions">
        <button class="action-btn"
          onclick="startEditHall(${loc.id}, ${h.id}, ${h.capacity}, '${(h.name || "").replace(/'/g, "\\'")}')"
          title="Редагувати">
          ${icon("edit")}
        </button>
        <button class="action-btn" onclick="deleteHall(${loc.id}, ${h.id})" title="Видалити">${icon("delete")}</button>
      </div>` : ""}
    </div>
  `,
    )
    .join("");
}

// ═══════════ GLOBAL ACTIONS ═══════════
window.startEditLocation = (id) => {
  if (!canManageCatalogs()) return;

  const loc = allLocations.find((l) => l.id === id);
  if (!loc) return;

  editingLocationId = id;
  document.getElementById("location-address").value = loc.address;

  document.getElementById("location-modal-title").textContent =
    "Редагувати локацію";
  document.getElementById("location-save").textContent = "Оновити";

  openModal("location-modal");
};

window.deleteLocation = (id) => {
  if (!canManageCatalogs()) return;

  openConfirm("Видалити локацію?", async () => {
    await apiDelete(`${API}/${id}`);
    loadLocations();
  });
};

window.openAddHall = (locationId) => {
  if (!canManageCatalogs()) return;

  activeHallLocationId = locationId;
  editingHallId = null;

  document.getElementById("hall-name").value = "";
  document.getElementById("hall-capacity").value = "";

  document.getElementById("hall-modal-title").textContent = "Додати зал";
  document.getElementById("hall-save").textContent = "Зберегти";

  openModal("hall-modal");
};

window.startEditHall = (locationId, hallId, capacity, name) => {
  if (!canManageCatalogs()) return;

  activeHallLocationId = locationId;
  editingHallId = hallId;

  document.getElementById("hall-name").value = name || "";
  document.getElementById("hall-capacity").value = capacity;

  document.getElementById("hall-modal-title").textContent = "Редагувати зал";
  document.getElementById("hall-save").textContent = "Оновити";

  openModal("hall-modal");
};

window.deleteHall = (locationId, hallId) => {
  if (!canManageCatalogs()) return;

  openConfirm("Видалити зал?", async () => {
    await apiDelete(`${API}/${locationId}/halls/${hallId}`);
    loadLocations();
  });
};

// ═══════════ MODAL ═══════════
async function loadLocationModal() {
  if (document.getElementById("location-modal")) return;

  const res = await fetch("/frontend/locations/location-modal.html");
  const html = await res.text();
  document.body.insertAdjacentHTML("beforeend", html);

  document.getElementById("location-close").onclick = document.getElementById(
    "location-cancel",
  ).onclick = closeLocationModal;

  document.getElementById("location-save").onclick = saveLocation;

  document.getElementById("hall-close").onclick = document.getElementById(
    "hall-cancel",
  ).onclick = () => closeModal("hall-modal");

  document.getElementById("hall-save").onclick = saveHall;

  document.querySelectorAll(".modal-overlay").forEach((modal) => {
    modal.addEventListener("click", (e) => {
      if (e.target === modal) {
        modal.classList.remove("open");
      }
    });
  });
}

function closeLocationModal() {
  editingLocationId = null;

  document.getElementById("location-address").value = "";
  document.getElementById("location-modal-title").textContent =
    "Додати локацію";
  document.getElementById("location-save").textContent = "Зберегти";

  closeModal("location-modal");
}

// ═══════════ SAVE LOCATION ═══════════
async function saveLocation(e) {
  e.preventDefault();
  if (!canManageCatalogs()) return;

  const address = document.getElementById("location-address").value.trim();
  if (!address) {
    alert("Введіть адресу локації!");
    return;
  }

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

// ═══════════ SAVE HALL (FIXED JSON SAFE) ═══════════
async function saveHall(e) {
  e.preventDefault();
  if (!canManageCatalogs()) return;

  const name = document.getElementById("hall-name").value.trim();
  const capacity = Number(document.getElementById("hall-capacity").value);

  if (!name || !capacity) {
    alert("Заповніть назву та місткість залу!");
    return;
  }

  try {
    const payload = { name, capacity };

    if (editingHallId) {
      await apiPut(
        `${API}/${activeHallLocationId}/halls/${editingHallId}`,
        payload,
      );
    } else {
      await apiPost(`${API}/${activeHallLocationId}/halls`, payload);
    }

    closeModal("hall-modal");
    loadLocations();
  } catch (err) {
    console.error("saveHall error:", err);
  }
}

// ═══════════ TABS ═══════════

function initTabs() {
  document.querySelectorAll(".tab-btn").forEach((btn) => {
    btn.addEventListener("click", () => {
      document
        .querySelectorAll(".tab-btn")
        .forEach((b) => b.classList.remove("active"));

      document
        .querySelectorAll(".tab-panel")
        .forEach((p) => p.classList.remove("active"));

      btn.classList.add("active");

      document.getElementById(`tab-${btn.dataset.tab}`).classList.add("active");
    });
  });
}

// ═══════════ INIT ═══════════
document.addEventListener("DOMContentLoaded", async () => {
  await loadConfirmModal();
  await loadLocationModal();
  renderTabIcons();
  initSchedule(); // Ініціалізуємо розклад окремо

  initTabs();

  document.getElementById("add-location-btn").onclick = () => {
    editingLocationId = null;

    document.getElementById("location-address").value = "";
    document.getElementById("location-modal-title").textContent =
      "Додати локацію";
    document.getElementById("location-save").textContent = "Зберегти";

    openModal("location-modal");
  };

  loadLocations();
});

function renderTabIcons() {
  document.querySelectorAll("[data-icon]").forEach((element) => {
    element.innerHTML = icon(element.dataset.icon);
  });
}
