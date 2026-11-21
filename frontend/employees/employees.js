import { apiDelete, apiGet, apiPost, apiPut, closeModal, formatUaPhone, initPasswordReveal, initUaPhoneInput, isAdmin, openModal, renderTable } from "/frontend/layouts/utils.js";
import { loadConfirmModal, openConfirm } from "/frontend/layouts/confirm-modal.js";

const API = "/employees";
const LOCS_API = "/locations";

let editingId = null;
let fields = {};
let locations = [];
let employees = [];
let employeeFilters = { query: "", locationId: "" };

async function loadEmployees() {
  try {
    employees = await apiGet(API);
    renderEmployees();
  } catch (e) {
    console.error("loadEmployees error:", e);
  }
}

function renderEmployees() {
  const locsMap = {};
  locations.forEach(location => { locsMap[location.id] = location.address; });

  const query = employeeFilters.query.toLowerCase();
  const filtered = employees.filter(employee => {
    const matchesQuery = !query || JSON.stringify(employee).toLowerCase().includes(query);
    const matchesLocation = !employeeFilters.locationId || String(employee.locationId) === String(employeeFilters.locationId);
    return matchesQuery && matchesLocation;
  });

  const enriched = filtered.map(employee => ({
      ...employee,
      phone: employee.phone ? formatUaPhone(employee.phone) : "-",
      locationName: locsMap[employee.locationId] || "-"
  }));

  renderTable(
      "employees-table",
      enriched,
      [
        { key: "firstName" },
        { key: "lastName" },
        { key: "patronymic" },
        { key: "username" },
        { key: "birthDate" },
        { key: "phone" },
        { key: "locationName" }
      ],
      {
        edit: id => openEdit(id, employees),
        delete: id => openConfirm("Видалити цього працівника?", async () => {
          await apiDelete(`${API}/${id}`);
          loadEmployees();
        })
      }
  );

  const info = document.getElementById("employees-info");
  if (info) info.innerText = `Всього: ${filtered.length}`;
}

function fillLocationFilter() {
  const select = document.getElementById("employee-location-filter");
  if (!select) return;

  select.innerHTML = `
    <option value="">Усі локації</option>
    ${locations.map(location => `<option value="${location.id}">${location.address}</option>`).join("")}
  `;
}

async function loadEmployeeModal() {
  if (document.getElementById("employee-modal")) return;

  const res = await fetch("/frontend/employees/employee-modal.html");
  const html = await res.text();
  document.body.insertAdjacentHTML("beforeend", html);

  fields = {
    firstName: document.getElementById("employee-firstName"),
    lastName: document.getElementById("employee-lastName"),
    patronymic: document.getElementById("employee-patronymic"),
    birthDate: document.getElementById("employee-birthDate"),
    phone: document.getElementById("employee-phone"),
    location: document.getElementById("employee-location"),
    username: document.getElementById("employee-username"),
    password: document.getElementById("employee-password"),
    passwordGroup: document.getElementById("employee-password-group")
  };
  initUaPhoneInput(fields.phone);
  initPasswordReveal(fields.password);

  const select = fields.location;
  locations.forEach(location => {
    const option = document.createElement("option");
    option.value = location.id;
    option.textContent = location.address;
    select.appendChild(option);
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
  ["firstName", "lastName", "patronymic", "username"].forEach(key => {
    if (fields[key]) fields[key].value = "";
  });
  if (fields.phone) fields.phone.value = formatUaPhone();
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
  const item = data.find(row => String(row.id) === String(id));
  if (!item) return;

  editingId = id;
  fields.firstName.value = item.firstName ?? "";
  fields.lastName.value = item.lastName ?? "";
  fields.patronymic.value = item.patronymic ?? "";
  fields.birthDate.value = item.birthDate ?? "";
  fields.phone.value = formatUaPhone(item.phone ?? "");
  fields.username.value = item.username ?? "";
  fields.location.value = item.locationId ?? "";

  if (fields.passwordGroup) fields.passwordGroup.style.display = "none";
  fields.password.value = "";

  document.getElementById("employee-modal-title").textContent = "Редагувати працівника";
  document.getElementById("employee-save").textContent = "Оновити";
  openModal("employee-modal");
}

async function saveEmployee(e) {
  e.preventDefault();

  const payload = {
    firstName: fields.firstName.value.trim(),
    lastName: fields.lastName.value.trim(),
    patronymic: fields.patronymic.value.trim(),
    birthDate: fields.birthDate.value,
    phone: fields.phone.value.trim(),
    username: fields.username.value.trim(),
    password: fields.password.value,
    locationId: parseInt(fields.location.value) || 0
  };

  if (!payload.firstName) {
    fields.firstName.focus();
    return;
  }

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

document.addEventListener("DOMContentLoaded", async () => {
  if (!isAdmin()) {
    document.querySelector(".content").innerHTML = `
      <div class="page-header">
        <h1>Немає доступу</h1>
      </div>
      <div class="card">
        <div class="empty-panel">Працівники доступні тільки системному адміністратору.</div>
      </div>
    `;
    return;
  }

  await loadConfirmModal();
  const locationsResponse = await apiGet(LOCS_API).catch(() => []);
  locations = locationsResponse?.data ?? locationsResponse ?? [];
  fillLocationFilter();
  await loadEmployeeModal();

  document.getElementById("add-employee-btn").onclick = () => {
    resetForm();
    openModal("employee-modal");
  };

  document.getElementById("employee-search")?.addEventListener("input", event => {
    employeeFilters.query = event.target.value;
    renderEmployees();
  });

  document.getElementById("employee-location-filter")?.addEventListener("change", event => {
    employeeFilters.locationId = event.target.value;
    renderEmployees();
  });

  loadEmployees();
});
