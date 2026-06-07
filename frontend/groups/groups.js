import { apiGet, apiPost, apiPut, apiDelete, renderTable, openModal, closeModal } from "/frontend/layouts/utils.js";
import { loadConfirmModal, openConfirm } from "/frontend/layouts/confirm-modal.js";

const API         = "http://localhost:18080/groups";
const COACHES_API = "http://localhost:18080/coaches";
const STYLES_API  = "http://localhost:18080/styles";

const LEVEL_LABELS = { 0: "Початківець", 1: "Середній", 2: "Просунутий" };
const DAY_LABELS   = ["Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Нд"];
const TIME_LABELS  = ["08:00","09:30","11:00","12:30","14:00","15:30","17:00","18:30","20:00"];

let editingId = null;
let fields = {};
let allCoaches = [], allStyles = [], allGroups = [];

// ═══════════ TABLE ═══════════
async function loadGroups() {
  try {
    allGroups = await apiGet(API);

    const coachMap = {}, styleMap = {};
    allCoaches.forEach(c => { coachMap[c.id] = `${c.firstName} ${c.lastName}`; });
    allStyles.forEach(s => { styleMap[s.id] = s.name; });

    const enriched = allGroups.map(g => ({
      ...g,
      coachName:  coachMap[g.coachId]  || "—",
      styleName:  styleMap[g.styleId]  || "—",
      levelName:  LEVEL_LABELS[g.skillLevel] ?? g.skillLevel,
      clientCount: g.clientCount ?? 0
    }));

    renderTable(
      "groups-table",
      enriched,
      [
        { key: "coachName" },
        { key: "styleName" },
        { key: "levelName" },
        { key: "clientCount" }
      ],
      {
        edit:   (id) => openEdit(id, allGroups),
        delete: (id) => openConfirm("Видалити цю групу?", async () => {
          await apiDelete(`${API}/${id}`);
          loadGroups();
        })
      }
    );

    const info = document.getElementById("groups-info");
    if (info) info.innerText = `Всього: ${allGroups.length}`;

    updateGroupFilter();
  } catch (e) {
    console.error("loadGroups error:", e);
  }
}

// ═══════════ SCHEDULE GRID ═══════════
function updateGroupFilter() {
  const sel = document.getElementById("schedule-group-filter");
  // зберігаємо вибране
  const current = sel.value;
  // очищаємо крім першого
  while (sel.options.length > 1) sel.remove(1);

  const coachMap = {}, styleMap = {};
  allCoaches.forEach(c => { coachMap[c.id] = `${c.firstName} ${c.lastName}`; });
  allStyles.forEach(s => { styleMap[s.id] = s.name; });

  allGroups.forEach(g => {
    const opt = document.createElement("option");
    opt.value = g.id;
    opt.textContent = `#${g.id} ${styleMap[g.styleId] || "?"} — ${coachMap[g.coachId] || "?"}`;
    sel.appendChild(opt);
  });

  sel.value = current;
}

async function buildScheduleGrid(filterGroupId = "") {
  // збираємо розклади всіх груп (або конкретної)
  const groups = filterGroupId
    ? allGroups.filter(g => String(g.id) === String(filterGroupId))
    : allGroups;

  // для кожної групи тягнемо розклад
  const allSchedules = [];
  await Promise.all(groups.map(async g => {
    try {
      const schedule = await apiGet(`${API}/${g.id}/schedule`);
      schedule.forEach(s => allSchedules.push({ ...s, groupId: g.id }));
    } catch { /* група може не мати розкладу */ }
  }));

  const coachMap = {}, styleMap = {};
  allCoaches.forEach(c => { coachMap[c.id] = `${c.firstName} ${c.lastName}`; });
  allStyles.forEach(s => { styleMap[s.id] = s.name; });

  const grid = document.getElementById("schedule-grid");
  if (!grid) return;

  // header row
  let html = `<div class="sg-head"></div>`;
  DAY_LABELS.forEach(d => { html += `<div class="sg-head">${d}</div>`; });

  // rows by time
  TIME_LABELS.forEach((timeLabel, timeIdx) => {
    html += `<div class="sg-time">${timeLabel}</div>`;
    for (let dayIdx = 0; dayIdx < 7; dayIdx++) {
      const events = allSchedules.filter(
        s => s.day === dayIdx && s.time === timeIdx
      );
      html += `<div class="sg-cell">`;
      events.forEach(ev => {
        const g = allGroups.find(g => g.id === ev.groupId);
        const styleName = g ? (styleMap[g.styleId] || "?") : "?";
        const coachName = g ? (coachMap[g.coachId] || "?").split(" ")[1] || "?" : "?";
        const level = g ? (LEVEL_LABELS[g.skillLevel] || "") : "";
        html += `<div class="sg-event" title="${styleName} — ${coachName} (${level})">
          🎵 ${styleName}<br><small>${coachName}</small>
        </div>`;
      });
      html += `</div>`;
    }
  });

  grid.innerHTML = html;
}

// ═══════════ MODAL ═══════════
async function loadGroupModal() {
  if (document.getElementById("group-modal")) return;

  const res  = await fetch("/frontend/groups/group-modal.html");
  const html = await res.text();
  document.body.insertAdjacentHTML("beforeend", html);

  fields = {
    coach: document.getElementById("group-coach"),
    style: document.getElementById("group-style"),
    level: document.getElementById("group-level"),
  };

  // fill dropdowns
  allCoaches.forEach(c => {
    const opt = document.createElement("option");
    opt.value = c.id;
    opt.textContent = `${c.firstName} ${c.lastName}`;
    fields.coach.appendChild(opt);
  });
  allStyles.forEach(s => {
    const opt = document.createElement("option");
    opt.value = s.id;
    opt.textContent = s.name;
    fields.style.appendChild(opt);
  });

  document.getElementById("group-close").onclick =
  document.getElementById("group-cancel").onclick = closeGroupModal;

  document.getElementById("group-modal").addEventListener("click", e => {
    if (e.target.id === "group-modal") closeGroupModal();
  });

  document.getElementById("group-save").onclick = saveGroup;
}

function resetForm() {
  editingId = null;
  if (fields.coach) fields.coach.value = "";
  if (fields.style) fields.style.value = "";
  if (fields.level) fields.level.value = "0";
  document.getElementById("group-modal-title").textContent = "Додати групу";
  document.getElementById("group-save").textContent = "Зберегти";
}

function closeGroupModal() {
  closeModal("group-modal");
  resetForm();
}

function openEdit(id, data) {
  const item = data.find(r => String(r.id) === String(id));
  if (!item) return;

  editingId = id;
  fields.coach.value = item.coachId  ?? "";
  fields.style.value = item.styleId  ?? "";
  fields.level.value = item.skillLevel ?? 0;

  document.getElementById("group-modal-title").textContent = "Редагувати групу";
  document.getElementById("group-save").textContent = "Оновити";
  openModal("group-modal");
}

async function saveGroup(e) {
  e.preventDefault();

  const payload = {
    coachId:    parseInt(fields.coach.value) || 0,
    styleId:    parseInt(fields.style.value) || 0,
    skillLevel: parseInt(fields.level.value),
  };

  if (!payload.coachId) { fields.coach.focus(); return; }

  try {
    if (editingId) {
      await apiPut(`${API}/${editingId}`, payload);
    } else {
      await apiPost(API, payload);
    }
    closeGroupModal();
    loadGroups();
  } catch (err) {
    console.error("saveGroup error:", err);
  }
}

// ═══════════ TABS ═══════════
function initTabs() {
  document.querySelectorAll(".tab-btn").forEach(btn => {
    btn.addEventListener("click", () => {
      document.querySelectorAll(".tab-btn").forEach(b => b.classList.remove("active"));
      document.querySelectorAll(".tab-panel").forEach(p => p.classList.remove("active"));
      btn.classList.add("active");
      document.getElementById(`tab-${btn.dataset.tab}`).classList.add("active");
      if (btn.dataset.tab === "schedule") buildScheduleGrid();
    });
  });

  document.getElementById("schedule-group-filter").addEventListener("change", e => {
    buildScheduleGrid(e.target.value);
  });
}

// ═══════════ INIT ═══════════
document.addEventListener("DOMContentLoaded", async () => {
  await loadConfirmModal();
  [allCoaches, allStyles] = await Promise.all([
    apiGet(COACHES_API).catch(() => []),
    apiGet(STYLES_API).catch(() => []),
  ]);
  await loadGroupModal();
  initTabs();

  document.getElementById("add-group-btn").onclick = () => {
    resetForm();
    openModal("group-modal");
  };

  loadGroups();
});