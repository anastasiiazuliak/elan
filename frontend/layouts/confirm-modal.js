let confirmCallback = null;

export async function loadConfirmModal() {
  if (document.getElementById("confirm-modal")) return;

  const res = await fetch("/frontend/layouts/confirm-modal.html");
  const html = await res.text();
  document.body.insertAdjacentHTML("beforeend", html);

  document.getElementById("confirm-delete-btn").addEventListener("click", async () => {
    if (confirmCallback) await confirmCallback();
    closeConfirm();
  });

  document.getElementById("confirm-cancel-btn").addEventListener("click", closeConfirm);

  document.getElementById("confirm-modal").addEventListener("click", (e) => {
    if (e.target.id === "confirm-modal") closeConfirm();
  });
}

export function openConfirm(message, onConfirm) {
  confirmCallback = onConfirm;

  const msg = document.getElementById("confirm-message");
  if (msg) msg.textContent = message;

  document.getElementById("confirm-modal").classList.add("open");
}

export function closeConfirm() {
  document.getElementById("confirm-modal").classList.remove("open");
  confirmCallback = null;
}