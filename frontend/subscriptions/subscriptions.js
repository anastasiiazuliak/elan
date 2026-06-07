import { apiGet, apiPost, apiPut, apiDelete, renderTable, openModal, closeModal } from "/frontend/layouts/utils.js";
import { loadConfirmModal, openConfirm } from "/frontend/layouts/confirm-modal.js";

const API = "http://localhost:18080/subscriptions";

const CATEGORY_LABELS = { 0: "Базова", 1: "Стандарт", 2: "Преміум" };

let editingId = null;
let fields = {};

// ---------- TABLE ----------
async function loadSubscriptions() {
  try {
    const data = await apiGet(API);

    const enriched = data.map(s => ({
      ...s,
      categoryName: CATEGORY_LABELS[s.category] ?? s.category
    }));

    renderTable(
      "subscriptions-table",
      enriched,
      [
        { key: "name" },
        { key: "categoryName" },
        { key: "duration" },
        { key: "numberOfWorkouts" }
      ],
      {
        edit:   (id) => openEdit(id, data),
        delete: (id) => openConfirm("Видалити цей абонемент?", async () => {
          await apiDelete(`${API}/${id}`);
          loadSubscriptions();
        })
      }
    );

    const info = document.getElementById("subscriptions-info");
    if (info) info.innerText = `Всього: ${data.length}`;
  } catch (e) {
    console.error("loadSubscriptions error:", e);
  }
}

// ---------- MODAL ----------
async function loadSubscriptionModal() {
  if (document.getElementById("subscription-modal")) return;

  const res  = await fetch("/frontend/subscriptions/subscription-modal.html");
  const html = await res.text();
  document.body.insertAdjacentHTML("beforeend", html);

  fields = {
    name:     document.getElementById("subscription-name"),
    category: document.getElementById("subscription-category"),
    duration: document.getElementById("subscription-duration"),
    workouts: document.getElementById("subscription-workouts"),
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
  fields.name.value     = "";
  fields.category.value = "0";
  fields.duration.value = "";
  fields.workouts.value = "";
  document.getElementById("subscription-modal-title").textContent = "Додати абонемент";
  document.getElementById("subscription-save").textContent = "Зберегти";
}

function closeSubscriptionModal() {
  closeModal("subscription-modal");
  resetForm();
}

function openEdit(id, data) {
  const item = data.find(r => String(r.id) === String(id));
  if (!item) return;

  editingId = id;
  fields.name.value     = item.name              ?? "";
  fields.category.value = item.category          ?? 0;
  fields.duration.value = item.duration          ?? "";
  fields.workouts.value = item.numberOfWorkouts  ?? "";

  document.getElementById("subscription-modal-title").textContent = "Редагувати абонемент";
  document.getElementById("subscription-save").textContent = "Оновити";
  openModal("subscription-modal");
}

async function saveSubscription(e) {
  e.preventDefault();

  const payload = {
    name:             fields.name.value.trim(),
    category:         parseInt(fields.category.value),
    duration:         parseInt(fields.duration.value) || 0,
    numberOfWorkouts: parseInt(fields.workouts.value) || 0,
  };

  if (!payload.name) { fields.name.focus(); return; }

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

// ---------- INIT ----------
document.addEventListener("DOMContentLoaded", async () => {
  await loadConfirmModal();
  await loadSubscriptionModal();

  document.getElementById("add-subscription-btn").onclick = () => {
    resetForm();
    openModal("subscription-modal");
  };

  loadSubscriptions();
});