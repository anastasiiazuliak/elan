import { apiGet, apiPost, apiPut, apiDelete, renderTable, filterTable, openModal, closeModal } from "/frontend/layouts/utils.js";
import { loadConfirmModal, openConfirm } from "/frontend/layouts/confirm-modal.js";

const API = "http://localhost:18080/styles";

let editingId = null;
let nameInput, descInput;

// ---------- TABLE ----------
async function loadStyles() {
  try {
    const data = await apiGet(API);

    renderTable(
      "styles-table",
      data,
      [
        { key: "name" },
        { key: "description" }
      ],
      {
        edit: (id) => openEdit(id, data),
        delete: (id) => {
          openConfirm("Ви впевнені, що хочете видалити цей стиль?", async () => {
            await apiDelete(`${API}/${id}`);
            loadStyles();
          });
        }
      }
    );

    const info = document.getElementById("styles-info");
    if (info) info.innerText = `Всього: ${data.length}`;

  } catch (e) {
    console.error("loadStyles error:", e);
  }
}

// ---------- MODAL LOAD ----------
async function loadStyleModal() {
  if (document.getElementById("style-modal")) return;

  const res = await fetch("/frontend/styles/style-modal.html");
  const html = await res.text();
  document.body.insertAdjacentHTML("beforeend", html);

  nameInput = document.getElementById("style-name");
  descInput = document.getElementById("style-description");

  document.getElementById("style-close").onclick =
  document.getElementById("style-cancel").onclick = () => {
    closeModal("style-modal");
    resetForm();
  };

  document.getElementById("style-modal").addEventListener("click", (e) => {
    if (e.target.id === "style-modal") {
      closeModal("style-modal");
      resetForm();
    }
  });

  document.getElementById("style-save").onclick = saveStyle;
}

// ---------- RESET FORM ----------
function resetForm() {
  editingId = null;
  if (nameInput) nameInput.value = "";
  if (descInput) descInput.value = "";

  const title = document.getElementById("style-modal-title");
  if (title) title.textContent = "Додати стиль";

  const saveBtn = document.getElementById("style-save");
  if (saveBtn) saveBtn.textContent = "Зберегти";
}

// ---------- OPEN EDIT ----------
function openEdit(id, data) {
  const item = data.find(r => String(r.id) === String(id));
  if (!item) return;

  editingId = id;

  nameInput = nameInput || document.getElementById("style-name");
  descInput = descInput || document.getElementById("style-description");

  if (nameInput) nameInput.value = item.name ?? "";
  if (descInput) descInput.value = item.description ?? "";

  const title = document.getElementById("style-modal-title");
  if (title) title.textContent = "Редагувати стиль";

  const saveBtn = document.getElementById("style-save");
  if (saveBtn) saveBtn.textContent = "Оновити";

  openModal("style-modal");
}

// ---------- SAVE / UPDATE ----------
async function saveStyle(e) {
  e.preventDefault();

  const payload = {
    name: nameInput?.value?.trim() || "",
    description: descInput?.value?.trim() || ""
  };

  if (!payload.name) {
    nameInput?.focus();
    return;
  }

  try {
    if (editingId) {
      await apiPut(`${API}/${editingId}`, payload);
    } else {
      await apiPost(API, payload);
    }

    closeModal("style-modal");
    resetForm();
    loadStyles();
  } catch (err) {
    console.error("saveStyle error:", err);
  }
}

// ---------- INIT ----------
document.addEventListener("DOMContentLoaded", async () => {
  await loadConfirmModal();
  await loadStyleModal();

  // пошук — підключаємо через JS, бо oninput в HTML не бачить ES modules
  const searchInput = document.querySelector(".search-bar input");
  if (searchInput) {
    searchInput.addEventListener("input", () => filterTable(searchInput, "styles-table"));
  }

  document.getElementById("add-style-btn").onclick = () => {
    resetForm();
    openModal("style-modal");
  };

  loadStyles();
});