import { apiGet, apiPost, apiPut, apiDelete, renderTable, openModal, closeModal } from "/frontend/layouts/utils.js";
import { loadConfirmModal, openConfirm } from "/frontend/layouts/confirm-modal.js";

const API        = "http://localhost:18080/coaches";
const STYLES_API = "http://localhost:18080/styles";

let editingId  = null;
let fields     = {};
let allStyles  = [];

// ---------- TABLE ----------
async function loadCoaches() {
  try {
    const data = await apiGet(API);

    // підтягуємо стилі для відображення назв
    const stylesMap = {};
    allStyles.forEach(s => { stylesMap[s.id] = s.name; });

    // додаємо поле styleNames для таблиці
    const enriched = data.map(c => ({
      ...c,
      styleNames: (c.styleIds || []).map(id => stylesMap[id] || id).join(", ") || "—"
    }));

    renderTable(
      "coaches-table",
      enriched,
      [
        { key: "firstName" },
        { key: "lastName" },
        { key: "phone" },
        { key: "styleNames" },
        { key: "description" }
      ],
      {
        edit:   (id) => openEdit(id, data),
        delete: (id) => openConfirm("Видалити цього тренера?", async () => {
          await apiDelete(`${API}/${id}`);
          loadCoaches();
        })
      }
    );

    const info = document.getElementById("coaches-info");
    if (info) info.innerText = `Всього: ${data.length}`;
  } catch (e) {
    console.error("loadCoaches error:", e);
  }
}

// ---------- MODAL ----------
async function loadCoachModal() {
  if (document.getElementById("coach-modal")) return;

  const res  = await fetch("/frontend/coaches/coach-modal.html");
  const html = await res.text();
  document.body.insertAdjacentHTML("beforeend", html);

  fields = {
    firstName:   document.getElementById("coach-firstName"),
    lastName:    document.getElementById("coach-lastName"),
    patronymic:  document.getElementById("coach-patronymic"),
    birthDate:   document.getElementById("coach-birthDate"),
    phone:       document.getElementById("coach-phone"),
    username:    document.getElementById("coach-username"),
    password:    document.getElementById("coach-password"),
    passwordGroup: document.getElementById("coach-password-group"),
    description: document.getElementById("coach-description"),
    stylesBox:   document.getElementById("coach-styles-checkboxes"),
  };

  renderStyleCheckboxes();

  document.getElementById("coach-close").onclick =
  document.getElementById("coach-cancel").onclick = closeCoachModal;

  document.getElementById("coach-modal").addEventListener("click", e => {
    if (e.target.id === "coach-modal") closeCoachModal();
  });

  document.getElementById("coach-save").onclick = saveCoach;
}

function renderStyleCheckboxes(selectedIds = []) {
  const box = document.getElementById("coach-styles-checkboxes");
  if (!box) return;

  box.innerHTML = allStyles.map(s => `
    <label class="checkbox-label">
      <input type="checkbox" value="${s.id}" ${selectedIds.includes(s.id) ? "checked" : ""} />
      ${s.name}
    </label>
  `).join("");
}

function getSelectedStyleIds() {
  const box = document.getElementById("coach-styles-checkboxes");
  if (!box) return [];
  return [...box.querySelectorAll("input[type=checkbox]:checked")]
    .map(cb => parseInt(cb.value));
}

function resetForm() {
  editingId = null;
  ["firstName","lastName","patronymic","phone","username","description"].forEach(k => {
    if (fields[k]) fields[k].value = "";
  });
  if (fields.birthDate) fields.birthDate.value = "";
  if (fields.password) fields.password.value = "";
  if (fields.passwordGroup) fields.passwordGroup.style.display = "";
  renderStyleCheckboxes();
  document.getElementById("coach-modal-title").textContent = "Додати тренера";
  document.getElementById("coach-save").textContent = "Зберегти";
}

function closeCoachModal() {
  closeModal("coach-modal");
  resetForm();
}

function openEdit(id, data) {
  const item = data.find(r => String(r.id) === String(id));
  if (!item) return;

  editingId = id;
  fields.firstName.value  = item.firstName  ?? "";
  fields.lastName.value   = item.lastName   ?? "";
  fields.patronymic.value = item.patronymic ?? "";
  fields.birthDate.value  = item.birthDate  ?? "";
  fields.phone.value      = item.phone      ?? "";
  fields.username.value   = item.username   ?? "";
  fields.description.value = item.description ?? "";

  if (fields.passwordGroup) fields.passwordGroup.style.display = "none";
  fields.password.value = "";

  renderStyleCheckboxes(item.styleIds || []);

  document.getElementById("coach-modal-title").textContent = "Редагувати тренера";
  document.getElementById("coach-save").textContent = "Оновити";

  openModal("coach-modal");
}

// ---------- SAVE ----------
async function saveCoach(e) {
  e.preventDefault();

  const payload = {
    firstName:   fields.firstName.value.trim(),
    lastName:    fields.lastName.value.trim(),
    patronymic:  fields.patronymic.value.trim(),
    birthDate:   fields.birthDate.value,
    phone:       fields.phone.value.trim(),
    username:    fields.username.value.trim(),
    password:    fields.password.value,
    description: fields.description.value.trim(),
    styleIds:    getSelectedStyleIds(),
  };

  if (!payload.firstName) { fields.firstName.focus(); return; }

  try {
    if (editingId) {
      await apiPut(`${API}/${editingId}`, payload);
    } else {
      await apiPost(API, payload);
    }
    closeCoachModal();
    loadCoaches();
  } catch (err) {
    console.error("saveCoach error:", err);
  }
}

// ---------- INIT ----------
document.addEventListener("DOMContentLoaded", async () => {
  await loadConfirmModal();
  allStyles = await apiGet(STYLES_API).catch(() => []);
  await loadCoachModal();

  document.getElementById("add-coach-btn").onclick = () => {
    resetForm();
    openModal("coach-modal");
  };

  loadCoaches();
});