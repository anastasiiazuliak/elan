import { apiDelete, apiGet, apiPost, apiPut, canManageCatalogs, closeModal, formatUaPhone, hideElement, initPasswordReveal, initUaPhoneInput, isClient, openModal } from "/frontend/layouts/utils.js";
import { loadConfirmModal, openConfirm } from "/frontend/layouts/confirm-modal.js";

const API = "http://localhost:18080/coaches";
const STYLES_API = "http://localhost:18080/styles";
const PHOTO_STORE_KEY = "elanCoachPhotos";

let editingId = null;
let fields = {};
let allStyles = [];
let coaches = [];
let selectedPhoto = "";
let coachFilters = { query: "", styleId: "" };

async function loadCoaches() {
  try {
    coaches = await apiGet(API);
    applyCoachFilters();
  } catch (e) {
    console.error("loadCoaches error:", e);
  }
}

function applyCoachFilters() {
  const query = coachFilters.query.toLowerCase();
  const filtered = coaches.filter(coach => {
    const matchesQuery = !query || JSON.stringify(coach).toLowerCase().includes(query);
    const matchesStyle = !coachFilters.styleId || (coach.styleIds || []).some(id => String(id) === String(coachFilters.styleId));
    return matchesQuery && matchesStyle;
  });

  renderCoachCards(filtered);

  const info = document.getElementById("coaches-info");
  if (info) info.innerText = `Всього: ${filtered.length}`;
}

function renderCoachCards(data) {
  const grid = document.getElementById("coaches-grid");
  if (!grid) return;

  const stylesMap = {};
  allStyles.forEach(style => { stylesMap[style.id] = style.name; });

  if (!data.length) {
    grid.innerHTML = `<div class="empty-state">Немає даних</div>`;
    return;
  }

  grid.innerHTML = data.map(coach => {
    const styleNames = (coach.styleIds || []).map(id => stylesMap[id] || id).join(", ") || "-";
    const photo = getCoachPhoto(coach);
    const fullName = [coach.lastName, coach.firstName, coach.patronymic].filter(Boolean).join(" ");
    return `
      <article class="coach-card">
        <div class="coach-photo">${photo ? `<img src="${photo}" alt="${fullName}" />` : getInitials(coach)}</div>
        <div class="coach-body">
          <div class="coach-topline">
            <h2>${fullName || `Тренер #${coach.id}`}</h2>
            ${canManageCatalogs() ? `
              <div class="coach-actions">
                <button class="action-btn" data-id="${coach.id}" data-action="edit" title="Редагувати">✎</button>
                <button class="action-btn" data-id="${coach.id}" data-action="delete" title="Видалити">×</button>
              </div>
            ` : ""}
          </div>
          <div class="coach-styles">${styleNames}</div>
          <p class="coach-description">${coach.description || "Опис не додано"}</p>
          ${isClient() ? "" : `
            <dl class="coach-details">
              <div><dt>Логін</dt><dd>${coach.username || "-"}</dd></div>
              <div><dt>Дата народження</dt><dd>${coach.birthDate || "-"}</dd></div>
              <div><dt>Телефон</dt><dd>${coach.phone ? formatUaPhone(coach.phone) : "-"}</dd></div>
            </dl>
          `}
        </div>
      </article>
    `;
  }).join("");

  grid.querySelectorAll("[data-action='edit']").forEach(button => {
    button.addEventListener("click", () => openEdit(button.dataset.id, coaches));
  });
  grid.querySelectorAll("[data-action='delete']").forEach(button => {
    button.addEventListener("click", () => openConfirm("Видалити цього тренера?", async () => {
      await apiDelete(`${API}/${button.dataset.id}`);
      loadCoaches();
    }));
  });
}

async function loadCoachModal() {
  if (document.getElementById("coach-modal")) return;

  const res = await fetch("/frontend/coaches/coach-modal.html");
  const html = await res.text();
  document.body.insertAdjacentHTML("beforeend", html);

  fields = {
    firstName: document.getElementById("coach-firstName"),
    lastName: document.getElementById("coach-lastName"),
    patronymic: document.getElementById("coach-patronymic"),
    birthDate: document.getElementById("coach-birthDate"),
    phone: document.getElementById("coach-phone"),
    username: document.getElementById("coach-username"),
    password: document.getElementById("coach-password"),
    passwordGroup: document.getElementById("coach-password-group"),
    photo: document.getElementById("coach-photo"),
    preview: document.getElementById("coach-photo-preview"),
    description: document.getElementById("coach-description"),
    stylesBox: document.getElementById("coach-styles-checkboxes")
  };

  renderStyleCheckboxes();
  initUaPhoneInput(fields.phone);
  initPasswordReveal(fields.password);

  fields.photo?.addEventListener("change", handlePhotoChange);

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

  box.innerHTML = allStyles.map(style => `
    <label class="checkbox-label">
      <input type="checkbox" value="${style.id}" ${selectedIds.includes(style.id) ? "checked" : ""} />
      ${style.name}
    </label>
  `).join("");
}

function fillCoachStyleFilter() {
  const select = document.getElementById("coach-style-filter");
  if (!select) return;

  select.innerHTML = `
    <option value="">Усі стилі</option>
    ${allStyles.map(style => `<option value="${style.id}">${style.name}</option>`).join("")}
  `;
}

function getSelectedStyleIds() {
  const box = document.getElementById("coach-styles-checkboxes");
  if (!box) return [];
  return [...box.querySelectorAll("input[type=checkbox]:checked")]
    .map(cb => parseInt(cb.value));
}

function resetForm() {
  editingId = null;
  selectedPhoto = "";
  ["firstName", "lastName", "patronymic", "username", "description"].forEach(key => {
    if (fields[key]) fields[key].value = "";
  });
  if (fields.phone) fields.phone.value = formatUaPhone();
  if (fields.birthDate) fields.birthDate.value = "";
  if (fields.password) fields.password.value = "";
  if (fields.photo) fields.photo.value = "";
  if (fields.preview) fields.preview.innerHTML = "";
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
  const item = data.find(row => String(row.id) === String(id));
  if (!item) return;

  editingId = id;
  selectedPhoto = getCoachPhoto(item);
  fields.firstName.value = item.firstName ?? "";
  fields.lastName.value = item.lastName ?? "";
  fields.patronymic.value = item.patronymic ?? "";
  fields.birthDate.value = item.birthDate ?? "";
  fields.phone.value = formatUaPhone(item.phone ?? "");
  fields.username.value = item.username ?? "";
  fields.description.value = item.description ?? "";

  if (fields.passwordGroup) fields.passwordGroup.style.display = "none";
  fields.password.value = "";
  renderPhotoPreview();
  renderStyleCheckboxes(item.styleIds || []);

  document.getElementById("coach-modal-title").textContent = "Редагувати тренера";
  document.getElementById("coach-save").textContent = "Оновити";

  openModal("coach-modal");
}

async function saveCoach(e) {
  e.preventDefault();

  const payload = {
    firstName: fields.firstName.value.trim(),
    lastName: fields.lastName.value.trim(),
    patronymic: fields.patronymic.value.trim(),
    birthDate: fields.birthDate.value,
    phone: fields.phone.value.trim(),
    username: fields.username.value.trim(),
    password: fields.password.value,
    description: fields.description.value.trim(),
    styleIds: getSelectedStyleIds()
  };

  if (!payload.firstName) {
    fields.firstName.focus();
    return;
  }

  try {
    if (editingId) {
      await apiPut(`${API}/${editingId}`, payload);
      saveCoachPhoto(editingId, payload.username, selectedPhoto);
    } else {
      await apiPost(API, payload);
      saveCoachPhoto(null, payload.username, selectedPhoto);
    }
    closeCoachModal();
    loadCoaches();
  } catch (err) {
    console.error("saveCoach error:", err);
  }
}

function handlePhotoChange(event) {
  const file = event.target.files?.[0];
  if (!file) return;

  const reader = new FileReader();
  reader.onload = () => {
    selectedPhoto = String(reader.result || "");
    renderPhotoPreview();
  };
  reader.readAsDataURL(file);
}

function renderPhotoPreview() {
  if (!fields.preview) return;
  fields.preview.innerHTML = selectedPhoto ? `<img src="${selectedPhoto}" alt="Фото тренера" />` : "";
}

function getCoachPhoto(coach) {
  const photos = readPhotos();
  return coach.photoUrl || photos.byId[String(coach.id)] || photos.byUsername[coach.username] || "";
}

function saveCoachPhoto(id, username, photo) {
  if (!photo) return;
  const photos = readPhotos();
  if (id) photos.byId[String(id)] = photo;
  if (username) photos.byUsername[username] = photo;
  localStorage.setItem(PHOTO_STORE_KEY, JSON.stringify(photos));
}

function readPhotos() {
  return JSON.parse(localStorage.getItem(PHOTO_STORE_KEY) || '{"byId":{},"byUsername":{}}');
}

function getInitials(coach) {
  const initials = [coach.firstName, coach.lastName].filter(Boolean).map(part => part[0]).join("").slice(0, 2);
  return initials || "EL";
}

document.addEventListener("DOMContentLoaded", async () => {
  await loadConfirmModal();
  allStyles = await apiGet(STYLES_API).catch(() => []);
  fillCoachStyleFilter();
  await loadCoachModal();

  if (canManageCatalogs()) {
    document.getElementById("add-coach-btn").onclick = () => {
      resetForm();
      openModal("coach-modal");
    };
  } else {
    hideElement("add-coach-btn");
  }

  document.getElementById("coach-search")?.addEventListener("input", event => {
    coachFilters.query = event.target.value;
    applyCoachFilters();
  });

  document.getElementById("coach-style-filter")?.addEventListener("change", event => {
    coachFilters.styleId = event.target.value;
    applyCoachFilters();
  });

  loadCoaches();
});
