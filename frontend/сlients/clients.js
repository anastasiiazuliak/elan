import { apiGet, apiPost, apiPut, apiDelete, renderTable, openModal, closeModal } from "/frontend/layouts/utils.js";
import { loadConfirmModal, openConfirm } from "/frontend/layouts/confirm-modal.js";

const API       = "http://localhost:18080/clients";
const SUBS_API  = "http://localhost:18080/subscriptions";

let editingId = null;
let fields = {};
let subscriptions = [];

// ---------- TABLE ----------
async function loadClients() {
  try {
    const data = await apiGet(API);

    renderTable(
      "clients-table",
      data,
      [
        { key: "firstName" },
        { key: "lastName" },
        { key: "phone" },
        { key: "birthDate" },
        { key: "subscriptionId" }
      ],
      {
        edit:   (id) => openEdit(id, data),
        delete: (id) => openConfirm("Видалити цього клієнта?", async () => {
          await apiDelete(`${API}/${id}`);
          loadClients();
        })
      }
    );

    const info = document.getElementById("clients-info");
    if (info) info.innerText = `Всього: ${data.length}`;
  } catch (e) {
    console.error("loadClients error:", e);
  }
}

// ---------- SUBSCRIPTIONS DROPDOWN ----------
async function loadSubscriptions() {
  try {
    subscriptions = await apiGet(SUBS_API);
    const sel = document.getElementById("client-subscription");
    if (!sel) return;
    subscriptions.forEach(s => {
      const opt = document.createElement("option");
      opt.value = s.id;
      opt.textContent = s.name;
      sel.appendChild(opt);
    });
  } catch (e) {
    console.error("loadSubscriptions error:", e);
  }
}

// ---------- MODAL ----------
async function loadClientModal() {
  if (document.getElementById("client-modal")) return;

  const res  = await fetch("/frontend/clients/client-modal.html");
  const html = await res.text();
  document.body.insertAdjacentHTML("beforeend", html);

  fields = {
    firstName:      document.getElementById("client-firstName"),
    lastName:       document.getElementById("client-lastName"),
    patronymic:     document.getElementById("client-patronymic"),
    birthDate:      document.getElementById("client-birthDate"),
    phone:          document.getElementById("client-phone"),
    subscription:   document.getElementById("client-subscription"),
    username:       document.getElementById("client-username"),
    password:       document.getElementById("client-password"),
    passwordGroup:  document.getElementById("client-password-group"),
  };

  await loadSubscriptions();

  document.getElementById("client-close").onclick =
  document.getElementById("client-cancel").onclick = closeClientModal;

  document.getElementById("client-modal").addEventListener("click", e => {
    if (e.target.id === "client-modal") closeClientModal();
  });

  document.getElementById("client-save").onclick = saveClient;
}

function resetForm() {
  editingId = null;
  Object.values(fields).forEach(f => { if (f && f.tagName !== "DIV") f.value = ""; });
  document.getElementById("client-modal-title").textContent = "Додати клієнта";
  document.getElementById("client-save").textContent = "Зберегти";
  if (fields.passwordGroup) fields.passwordGroup.style.display = "";
}

function closeClientModal() {
  closeModal("client-modal");
  resetForm();
}

function openEdit(id, data) {
  const item = data.find(r => String(r.id) === String(id));
  if (!item) return;

  editingId = id;
  fields.firstName.value    = item.firstName    ?? "";
  fields.lastName.value     = item.lastName     ?? "";
  fields.patronymic.value   = item.patronymic   ?? "";
  fields.birthDate.value    = item.birthDate    ?? "";
  fields.phone.value        = item.phone        ?? "";
  fields.username.value     = item.username     ?? "";
  fields.subscription.value = item.subscriptionId ?? "";

  // при редагуванні пароль необов'язковий — ховаємо
  if (fields.passwordGroup) fields.passwordGroup.style.display = "none";
  fields.password.value = "";

  document.getElementById("client-modal-title").textContent = "Редагувати клієнта";
  document.getElementById("client-save").textContent = "Оновити";

  openModal("client-modal");
}

// ---------- SAVE ----------
async function saveClient(e) {
  e.preventDefault();

  const payload = {
    firstName:      fields.firstName.value.trim(),
    lastName:       fields.lastName.value.trim(),
    patronymic:     fields.patronymic.value.trim(),
    birthDate:      fields.birthDate.value,
    phone:          fields.phone.value.trim(),
    username:       fields.username.value.trim(),
    password:       fields.password.value,
    subscriptionId: parseInt(fields.subscription.value) || 0,
  };

  if (!payload.firstName) { fields.firstName.focus(); return; }

  try {
    if (editingId) {
      await apiPut(`${API}/${editingId}`, payload);
    } else {
      await apiPost(API, payload);
    }
    closeClientModal();
    loadClients();
  } catch (err) {
    console.error("saveClient error:", err);
  }
}

// ---------- INIT ----------
document.addEventListener("DOMContentLoaded", async () => {
  await loadConfirmModal();
  await loadClientModal();

  document.getElementById("add-client-btn").onclick = () => {
    resetForm();
    openModal("client-modal");
  };

  loadClients();
});