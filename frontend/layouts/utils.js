/* ═══════════════════════════════════════
   utils.js — допоміжні функції
═══════════════════════════════════════ */

/* ── Modal ── */
export function openModal(id) {
  document.getElementById(id).classList.add('open');
}

export function closeModal(id) {
  document.getElementById(id).classList.remove('open');
}

export function closeOnOverlay(event, id) {
  if (event.target === event.currentTarget) closeModal(id);
}

/* ── Table search filter ── */
export function filterTable(input, tableId) {
  const q = input.value.toLowerCase();
  const rows = document.querySelectorAll(`#${tableId} tbody tr`);
  rows.forEach(row => {
    row.style.display = row.textContent.toLowerCase().includes(q) ? '' : 'none';
  });
}

/* ── Render a table from array of objects ──
   Usage:
     renderTable('myTableId', data, [
       { key: 'name',  label: "Ім'я" },
       { key: 'email', label: 'Email' },
     ]);
*/
export function renderTable(tableId, data, columns, actions = {}) {
  const tbody = document.querySelector(`#${tableId} tbody`);
  if (!tbody) return;

  if (!data || data.length === 0) {
    tbody.innerHTML = `
      <tr>
        <td colspan="${columns.length + 2}" style="text-align:center; padding:40px; color:var(--text-muted);">
          Немає даних
        </td>
      </tr>`;
    return;
  }

  tbody.innerHTML = data.map((row, index) => `
    <tr>
      <td>${index + 1}</td>

      ${columns.map(col => `<td>${row[col.key] ?? '—'}</td>`).join('')}

      <td>
        ${actions.edit ? `<button class="action-btn" data-id="${row.id}" data-action="edit">✏️</button>` : ''}
        ${actions.delete ? `<button class="action-btn" data-id="${row.id}" data-action="delete">🗑️</button>` : ''}
      </td>
    </tr>
  `).join('');

  tbody.querySelectorAll("button").forEach(btn => {
    btn.addEventListener("click", () => {
      const id = btn.dataset.id;
      const action = btn.dataset.action;

      actions[action]?.(id);
    });
  });
}

/* ── Simple fetch helpers ── */
export async function apiGet(url) {
  const res = await fetch(url);
  if (!res.ok) throw new Error(`GET ${url} → ${res.status}`);
  return res.json();
}

export async function apiPost(url, body) {
  const res = await fetch(url, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(body),
  });

  if (!res.ok) throw new Error(`POST ${url} → ${res.status}`);
  return res.json();
}

export async function apiPut(url, body) {
  const res = await fetch(url, {
    method: 'PUT',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(body),
  });

  if (!res.ok) throw new Error(`PUT ${url} → ${res.status}`);
  return res.json();
}

export async function apiDelete(url) {
  const res = await fetch(url, { method: 'DELETE' });

  if (!res.ok) throw new Error(`DELETE ${url} → ${res.status}`);
  return res.ok;
}