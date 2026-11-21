export function openModal(id) {
  document.getElementById(id)?.classList.add("open");
}
window.openModal = openModal;

export function closeModal(id) {
  document.getElementById(id)?.classList.remove("open");
}
window.closeModal = closeModal;

export function closeOnOverlay(event, id) {
  if (event.target === event.currentTarget) closeModal(id);
}

export function filterTable(input, tableId) {
  const query = input.value.toLowerCase();
  document.querySelectorAll(`#${tableId} tbody tr`).forEach(row => {
    row.style.display = row.textContent.toLowerCase().includes(query) ? "" : "none";
  });
}
window.filterTable = filterTable;

export function unwrapData(response) {
  return response?.data ?? response ?? [];
}

export function setText(id, value) {
  const element = document.getElementById(id);
  if (element) element.textContent = value;
}

export const ROLES = {
  Admin: 0,
  Client: 1,
  Employee: 2,
  Coach: 3
};

export function getCurrentUser() {
  return JSON.parse(localStorage.getItem("elanUser") || "null");
}

export function isAdmin() {
  return getCurrentUser()?.role === ROLES.Admin;
}

export function isSystemAdmin() {
  return isAdmin();
}

export function isLocationAdmin() {
  return getCurrentUser()?.role === ROLES.Employee;
}

export function isClient() {
  return getCurrentUser()?.role === ROLES.Client;
}

export function isCoach() {
  return getCurrentUser()?.role === ROLES.Coach;
}

export function canManageCatalogs() {
  return isAdmin();
}

export function canCreateClient() {
  return isLocationAdmin();
}

export function canMarkAttendance() {
  return isAdmin() || isLocationAdmin();
}

export function hideElement(id) {
  const element = document.getElementById(id);
  if (element) element.style.display = "none";
}

const ICON_PATHS = {
  view: "M15 3h6v6M10 14 21 3M18 13v6a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2V8a2 2 0 0 1 2-2h6",
  eye: "M2 12s3.5-7 10-7 10 7 10 7-3.5 7-10 7S2 12 2 12M12 15a3 3 0 1 0 0-6 3 3 0 0 0 0 6",
  eyeOff: "M3 3l18 18M10.6 10.6A3 3 0 0 0 13.4 13.4M9.9 4.2A10.4 10.4 0 0 1 12 4c6.5 0 10 8 10 8a18.8 18.8 0 0 1-3.2 4.3M6.6 6.6C3.6 8.5 2 12 2 12s3.5 8 10 8a10.7 10.7 0 0 0 4.2-.9",
  edit: "M12 20h9M16.5 3.5a2.1 2.1 0 0 1 3 3L7 19l-4 1 1-4Z",
  delete: "M3 6h18M8 6V4h8v2M6 6l1 15h10l1-15M10 11v6M14 11v6",
  check: "M20 6 9 17l-5-5",
  home: "M3 11 12 3l9 8v9a1 1 0 0 1-1 1h-5v-6H9v6H4a1 1 0 0 1-1-1z",
  users: "M16 21v-2a4 4 0 0 0-4-4H6a4 4 0 0 0-4 4v2M9 11a4 4 0 1 0 0-8 4 4 0 0 0 0 8M22 21v-2a4 4 0 0 0-3-3.87M16 3.13a4 4 0 0 1 0 7.75",
  groups: "M3 3h8v8H3zM13 3h8v8h-8zM3 13h8v8H3zM13 13h8v8h-8z",
  staff: "M12 3l3 6 6 .9-4.5 4.4 1.1 6.2L12 17.6 6.4 20.5l1.1-6.2L3 9.9 9 9z",
  coach: "M12 2a5 5 0 0 1 5 5v2a5 5 0 0 1-10 0V7a5 5 0 0 1 5-5M4 22a8 8 0 0 1 16 0",
  location: "M12 21s7-5.2 7-11a7 7 0 1 0-14 0c0 5.8 7 11 7 11M12 13a3 3 0 1 0 0-6 3 3 0 0 0 0 6",
  style: "M12 3l9 5-9 5-9-5zM3 12l9 5 9-5M3 16l9 5 9-5",
  subscription: "M4 4h16v16H4zM8 8h8M8 12h8M8 16h5",
  plus: "M12 5v14M5 12h14",
  calendar: "M8 2v4M16 2v4M3 10h18M5 4h14a2 2 0 0 1 2 2v14H3V6a2 2 0 0 1 2-2",
  close: "M18 6 6 18M6 6l12 12",
  sun: "M12 17a5 5 0 1 0 0-10 5 5 0 0 0 0 10M12 1v2M12 21v2M4.22 4.22l1.42 1.42M18.36 18.36l1.42 1.42M1 12h2M21 12h2M4.22 19.78l1.42-1.42M18.36 5.64l1.42-1.42",
  moon: "M21 12.79A9 9 0 1 1 11.21 3 7 7 0 0 0 21 12.79"
};

export function icon(name) {
  const path = ICON_PATHS[name] || ICON_PATHS.view;
  return `<svg class="icon" viewBox="0 0 24 24" aria-hidden="true"><path d="${path}"></path></svg>`;
}

export function renderTable(tableId, data, columns, actions = {}) {
  const tbody = document.querySelector(`#${tableId} tbody`);
  if (!tbody) return;

  const visibleActions = { ...actions };
  if (!isAdmin()) {
    delete visibleActions.extra;
    delete visibleActions.edit;
    delete visibleActions.delete;
  }

  const hasActions = Boolean(visibleActions.view || visibleActions.extra || visibleActions.edit || visibleActions.delete || visibleActions.workout);
  const colspan = columns.length + 1 + (hasActions ? 1 : 0);

  if (!data || data.length === 0) {
    tbody.innerHTML = `
      <tr>
        <td colspan="${colspan}" class="empty-cell">Немає даних</td>
      </tr>`;
    return;
  }

  tbody.innerHTML = data.map((row, index) => `
    <tr data-id="${row.id}" ${visibleActions.view ? 'class="clickable-row"' : ""}>
      <td>${index + 1}</td>
      ${columns.map(col => `<td>${col.render ? col.render(row) : (row[col.key] ?? "-")}</td>`).join("")}
      ${hasActions ? `<td>
        ${visibleActions.view ? `<button class="action-btn" data-id="${row.id}" data-action="view" title="Відкрити">${icon("view")}</button>` : ""}
        ${visibleActions.extra ? visibleActions.extra(row) : ""}
        ${visibleActions.workout ? `<button class="action-btn" data-id="${row.id}" data-action="workout" title="Відмітити заняття">${icon("check")}</button>` : ""}
        ${visibleActions.edit ? `<button class="action-btn" data-id="${row.id}" data-action="edit" title="Редагувати">${icon("edit")}</button>` : ""}
        ${visibleActions.delete ? `<button class="action-btn" data-id="${row.id}" data-action="delete" title="Видалити">${icon("delete")}</button>` : ""}
      </td>` : ""}
    </tr>
  `).join("");

  tbody.querySelectorAll("button").forEach(button => {
    button.addEventListener("click", event => {
      event.stopPropagation();
      visibleActions[button.dataset.action]?.(button.dataset.id);
    });
  });

  if (visibleActions.view) {
    tbody.querySelectorAll("tr[data-id]").forEach(row => {
      row.addEventListener("click", () => visibleActions.view(row.dataset.id));
    });
  }
}

export function initPasswordReveal(input) {
  if (!input || input.closest(".password-field")) return;

  const wrapper = document.createElement("div");
  wrapper.className = "password-field";
  input.parentNode.insertBefore(wrapper, input);
  wrapper.appendChild(input);

  const button = document.createElement("button");
  button.type = "button";
  button.className = "password-toggle";
  button.title = "Показати пароль";
  button.setAttribute("aria-label", "Показати пароль");
  button.innerHTML = icon("eye");
  wrapper.appendChild(button);

  button.addEventListener("click", () => {
    const isVisible = input.type === "text";
    input.type = isVisible ? "password" : "text";
    button.title = isVisible ? "Показати пароль" : "Сховати пароль";
    button.setAttribute("aria-label", button.title);
    button.innerHTML = icon(isVisible ? "eye" : "eyeOff");
  });
}

export function formatUaPhone(value = "") {
  let digits = String(value).replace(/\D/g, "");

  if (digits.startsWith("380")) {
    digits = digits.slice(3);
  } else if (digits.startsWith("0")) {
    digits = digits.slice(1);
  }

  digits = digits.slice(0, 9);

  const parts = [];
  if (digits.slice(0, 2)) parts.push(digits.slice(0, 2));
  if (digits.slice(2, 5)) parts.push(digits.slice(2, 5));
  if (digits.slice(5, 7)) parts.push(digits.slice(5, 7));
  if (digits.slice(7, 9)) parts.push(digits.slice(7, 9));

  return parts.length ? `+380 ${parts.join(" ")}` : "+380 ";
}

export function initUaPhoneInput(input) {
  if (!input || input.dataset.uaPhoneReady === "1") return;

  input.dataset.uaPhoneReady = "1";
  input.type = "tel";
  input.inputMode = "tel";
  input.placeholder = "+380 67 123 45 67";
  input.value = formatUaPhone(input.value);

  input.addEventListener("focus", () => {
    if (!input.value.trim()) input.value = "+380 ";
  });

  input.addEventListener("input", () => {
    input.value = formatUaPhone(input.value);
  });
}

async function parseResponse(response) {
  const text = await response.text();
  if (!text) return null;

  try {
    return JSON.parse(text);
  } catch {
    return text;
  }
}

async function apiRequest(url, method, body) {
  const response = await fetch(url, {
    method,
    headers: { "Content-Type": "application/json" },
    body: body === undefined ? undefined : JSON.stringify(body)
  });

  if (!response.ok) {
    throw new Error(`${method} ${url} -> ${response.status}`);
  }

  return parseResponse(response);
}

export function apiGet(url) {
  return apiRequest(url, "GET");
}

export function apiPost(url, body) {
  return apiRequest(url, "POST", body);
}

export function apiPut(url, body) {
  return apiRequest(url, "PUT", body);
}

export function apiPatch(url, body) {
  return apiRequest(url, "PATCH", body);
}

export async function apiDelete(url) {
  const response = await fetch(url, { method: "DELETE" });

  if (!response.ok) {
    throw new Error(`DELETE ${url} -> ${response.status}`);
  }

  return true;
}
