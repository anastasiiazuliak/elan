import { apiGet, apiPost, apiPut, apiDelete, renderTable, openModal, closeModal } from "/frontend/layouts/utils.js";
import { loadConfirmModal, openConfirm } from "/frontend/layouts/confirm-modal.js";

const API      = "http://localhost:18080/employees";
const LOCS_API = "http://localhost:18080/locations";

let editingId = null;
let fields = {};
let locations = [];

// ---------- TABLE ----------
async function loadEmployees() {
  try {
    const data = await apiGet(API);

    const locsMap = {};
    locations.forEach(l => { locsMap[l.id] = l.address; });

    const enriched = data.map(e => ({
      ...e,
      locationName: locsMap[e.locationId] || "—"
    }));

    renderTable(
      "employees-table",
      enriched,
      [
        { key: "firstName" },
        { key: "lastName" },
        { key: "phone" },
        { key: "email" },
        { key: "locationName" }
      ],
      {
        edit:   (id) => openEdit(id, data),
        delete: (id) => openConfirm("Видалити цього працівника?", async () => {
          await apiDelete(`${API}/${id}`);
          loadEmployees();
        })
      }
    );

    const info = document.getElementById("employees-info");
    if (info) info.innerText = `Всього: ${data.length}`;
  } catch (e) {
    console.error("loadEmployees error:", e);
  }
}

// ---------- MODAL ----------
async function loadEmployeeModal() {
  if (document.getElementById("employee-modal")) return;

  const res  = await fetch("/frontend/employees/employee-modal.html");
  const html = await res.text();
  document.body.insertAdjacentHTML("beforeend", html);

  fields = {
    firstName:     document.getElementById("employee-firstName"),
    lastName:      document.getElementById("employee-lastName"),
    patronymic:    document.getElementById("employee-patronymic"),
    birthDate:     document.getElementById("employee-birthDate"),
    phone:         document.getElementById("employee-phone"),
    email:         document.getElementById("employee-email"),
    location:      document.getElementById("employee-location"),
    username:      document.getElementById("employee-username"),
    password:      document.getElementById("employee-password"),
    passwordGroup: document.getElementById("employee-password-group"),
  };

  // fill location dropdown
  const sel = fields.location;
  locations.forEach(l => {
    const opt = document.createElement("option");
    opt.value = l.id;
    opt.textContent = l.address;
    sel.appendChild(opt);
  });

  document.getElementById("employee-close").onclick =
  document.getElementById("employee-cancel").onclick = closeEmployeeModal;

  document.getElementById("employee-modal").addEventListener("click", e => {
    if (e.target.id === "employee-modal") closeEmployeeModal();
  });

  document.getElementById("employee-save").onclick = saveEmployee;
}

function resetForm() {
  editingId = null;
  ["firstName","lastName","patronymic","phone","email","username"].forEach(k => {
    if (fields[k]) fields[k].value = "";
  });
  if (fields.birthDate) fields.birthDate.value = "";
  if (fields.password) fields.password.value = "";
  if (fields.location) fields.location.value = "";
  if (fields.passwordGroup) fields.passwordGroup.style.display = "";
  document.getElementById("employee-modal-title").textContent = "Додати працівника";
  document.getElementById("employee-save").textContent = "Зберегти";
}

function closeEmployeeModal() {
  closeModal("employee-modal");
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
  fields.email.value      = item.email      ?? "";
  fields.username.value   = item.username   ?? "";
  fields.location.value   = item.locationId ?? "";

  if (fields.passwordGroup) fields.passwordGroup.style.display = "none";
  fields.password.value = "";

  document.getElementById("employee-modal-title").textContent = "Редагувати працівника";
  document.getElementById("employee-save").textContent = "Оновити";
  openModal("employee-modal");
}

async function saveEmployee(e) {
  e.preventDefault();

  const payload = {
    firstName:  fields.firstName.value.trim(),
    lastName:   fields.lastName.value.trim(),
    patronymic: fields.patronymic.value.trim(),
    birthDate:  fields.birthDate.value,
    phone:      fields.phone.value.trim(),
    email:      fields.email.value.trim(),
    username:   fields.username.value.trim(),
    password:   fields.password.value,
    locationId: parseInt(fields.location.value) || 0,
  };

  if (!payload.firstName) { fields.firstName.focus(); return; }

  try {
    if (editingId) {
      await apiPut(`${API}/${editingId}`, payload);
    } else {
      await apiPost(API, payload);
    }
    closeEmployeeModal();
    loadEmployees();
  } catch (err) {
    console.error("saveEmployee error:", err);
  }
}

// ---------- INIT ----------
document.addEventListener("DOMContentLoaded", async () => {
  await loadConfirmModal();
  locations = await apiGet(LOCS_API).catch(() => []);
  await loadEmployeeModal();

  document.getElementById("add-employee-btn").onclick = () => {
    resetForm();
    openModal("employee-modal");
  };

  loadEmployees();
});