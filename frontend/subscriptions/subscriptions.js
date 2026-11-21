import { apiDelete, apiGet, apiPost, apiPut, canManageCatalogs, closeModal, hideElement, openModal, renderTable } from "/frontend/layouts/utils.js";
import { loadConfirmModal, openConfirm } from "/frontend/layouts/confirm-modal.js";

const API = "/subscriptions";

let editingId = null;
let fields = {};

async function loadSubscriptions() {
  try {
    const data = await apiGet(API);
    const actions = canManageCatalogs()
      ? {
          edit: id => openEdit(id, data),
          delete: id => openConfirm("Видалити цей абонемент?", async () => {
            await apiDelete(`${API}/${id}`);
            loadSubscriptions();
          })
        }
      : {};

    renderTable(
      "subscriptions-table",
      data,
      [
        { key: "name" },
        { key: "duration" },
        { key: "numberOfWorkouts" },
        { key: "price", render: row => formatPrice(row.price) }
      ],
      actions
    );

    const info = document.getElementById("subscriptions-info");
    if (info) info.innerText = `Всього: ${data.length}`;
  } catch (e) {
    console.error("loadSubscriptions error:", e);
  }
}

async function loadSubscriptionModal() {
  if (document.getElementById("subscription-modal")) return;

  const res = await fetch("/frontend/subscriptions/subscription-modal.html");
  const html = await res.text();
  document.body.insertAdjacentHTML("beforeend", html);

  fields = {
    name: document.getElementById("subscription-name"),
    duration: document.getElementById("subscription-duration"),
    workouts: document.getElementById("subscription-workouts"),
    price: document.getElementById("subscription-price")
  };

  document.getElementById("subscription-close").onclick =
  document.getElementById("subscription-cancel").onclick = closeSubscriptionModal;

  document.getElementById("subscription-modal").addEventListener("click", e => {
    if (e.target.id === "subscription-modal") closeSubscriptionModal();
  });

  document.getElementById("subscription-save").onclick = saveSubscription;
}

function resetForm() {
  editingId = null;
  fields.name.value = "";
  fields.duration.value = "";
  fields.workouts.value = "";
  fields.price.value = "";
  document.getElementById("subscription-modal-title").textContent = "Додати абонемент";
  document.getElementById("subscription-save").textContent = "Зберегти";
}

function closeSubscriptionModal() {
  closeModal("subscription-modal");
  resetForm();
}

function openEdit(id, data) {
  const item = data.find(row => String(row.id) === String(id));
  if (!item) return;

  editingId = id;
  fields.name.value = item.name ?? "";
  fields.duration.value = item.duration ?? "";
  fields.workouts.value = item.numberOfWorkouts ?? "";
  fields.price.value = item.price ?? "";

  document.getElementById("subscription-modal-title").textContent = "Редагувати абонемент";
  document.getElementById("subscription-save").textContent = "Оновити";
  openModal("subscription-modal");
}

async function saveSubscription(e) {
  e.preventDefault();

  const payload = {
    name: fields.name.value.trim(),
    duration: parseInt(fields.duration.value) || 0,
    numberOfWorkouts: parseInt(fields.workouts.value) || 0,
    price: parseFloat(fields.price.value) || 0
  };

  if (!payload.name) {
    fields.name.focus();
    return;
  }

  try {
    if (editingId) {
      await apiPut(`${API}/${editingId}`, payload);
    } else {
      await apiPost(API, payload);
    }
    closeSubscriptionModal();
    loadSubscriptions();
  } catch (err) {
    console.error("saveSubscription error:", err);
  }
}

function formatPrice(value) {
  const price = Number(value);
  if (!Number.isFinite(price)) return "-";
  return `${price.toLocaleString("uk-UA")} грн`;
}

document.addEventListener("DOMContentLoaded", async () => {
  await loadConfirmModal();
  await loadSubscriptionModal();

  if (canManageCatalogs()) {
    document.getElementById("add-subscription-btn").onclick = () => {
      resetForm();
      openModal("subscription-modal");
    };
  } else {
    hideElement("add-subscription-btn");
  }

  loadSubscriptions();
});
