import {
  apiGet,
  apiPost,
  apiPut,
  apiDelete,
  renderTable
} from "/frontend/layouts/utils.js";

const API = "http://localhost:18080/clients";
const SUBS_API = "http://localhost:18080/subscriptions";

let editingId = null;
let fields = {};
let subscriptions = [];

// ---------- FETCH ----------
async function safeFetch(url) {
  const res = await fetch(url);
  if (!res.ok) throw new Error(`HTTP ${res.status}`);
  return res.json();
}

// ---------- LOAD CLIENTS ----------
async function loadClients() {
  try {
    const data = await safeFetch(API);

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
        edit: (id) => openEdit(id, data),
        delete: async (id) => {
          await apiDelete(`${API}/${id}`);
          loadClients();
        }
      }
    );

    document.getElementById("clients-info").innerText =
      `Всього: ${data.length}`;

  } catch (err) {
    console.error("loadClients error:", err);
  }
}

// ---------- SUBSCRIPTIONS ----------
async function loadSubscriptions() {
  subscriptions = await safeFetch(SUBS_API);

  const sel = document.getElementById("client-subscription");
  sel.innerHTML = `<option value="">— Оберіть абонемент —</option>`;

  subscriptions.forEach(s => {
    const opt = document.createElement("option");
    opt.value = s.id;
    opt.textContent = s.name;
    sel.appendChild(opt);
  });
}

// ---------- MODAL ----------
async function loadClientModal() {
  if (document.getElementById("client-modal")) return;

  const res = await fetch("/frontend/clients/client-modal.html");
  const html = await res.text();

  document.body.insertAdjacentHTML("beforeend", html);

  const modal = document.getElementById("client-modal");

  fields = {
    firstName: document.getElementById("client-firstName"),
    lastName: document.getElementById("client-lastName"),
    patronymic: document.getElementById("client-patronymic"),
    birthDate: document.getElementById("client-birthDate"),
    phone: document.getElementById("client-phone"),
    subscription: document.getElementById("client-subscription"),
    username: document.getElementById("client-username"),
    password: document.getElementById("client-password"),
    passwordGroup: document.getElementById("client-password-group"),
  };

  await loadSubscriptions();

  document.getElementById("client-close").onclick = closeClientModal;
  document.getElementById("client-cancel").onclick = closeClientModal;

  modal.addEventListener("click", (e) => {
    if (e.target.id === "client-modal") closeClientModal();
  });

  document.getElementById("client-save").onclick = saveClient;
}

// ---------- MODAL CONTROL ----------
function openClientModal() {
  document.getElementById("client-modal")?.classList.add("open");
}

function closeClientModal() {
  document.getElementById("client-modal")?.classList.remove("open");
  resetForm();
}

// ---------- RESET ----------
function resetForm() {
  editingId = null;

  Object.values(fields).forEach(f => {
    if (f) f.value = "";
  });

  document.getElementById("client-modal-title").textContent =
    "Додати клієнта";

  document.getElementById("client-save").textContent =
    "Зберегти";

  if (fields.passwordGroup)
    fields.passwordGroup.style.display = "";
}

// ---------- EDIT ----------
function openEdit(id, data) {
  const item = data.find(x => String(x.id) === String(id));
  if (!item) return;

  editingId = id;

  fields.firstName.value = item.firstName ?? "";
  fields.lastName.value = item.lastName ?? "";
  fields.patronymic.value = item.patronymic ?? "";
  fields.birthDate.value = item.birthDate ?? "";
  fields.phone.value = item.phone ?? "";
  fields.username.value = item.username ?? "";
  fields.subscription.value = item.subscriptionId ?? "";

  fields.password.value = "";

  if (fields.passwordGroup)
    fields.passwordGroup.style.display = "none";

  document.getElementById("client-modal-title").textContent =
    "Редагувати клієнта";

  document.getElementById("client-save").textContent =
    "Оновити";

  openClientModal();
}

// ---------- SAVE ----------
async function saveClient(e) {
  e.preventDefault();

  const payload = {
    firstName: fields.firstName.value.trim(),
    lastName: fields.lastName.value.trim(),
    patronymic: fields.patronymic.value.trim(),
    birthDate: fields.birthDate.value,
    phone: fields.phone.value.trim(),
    username: fields.username.value.trim(),
    password: fields.password.value,
    subscriptionId: Number(fields.subscription.value) || 0,
  };

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
  await loadClientModal();
  loadClients();

  document.getElementById("add-client-btn")
    ?.addEventListener("click", () => {
      resetForm();
      openClientModal();
    });
});