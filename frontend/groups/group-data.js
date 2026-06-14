import { apiGet, unwrapData } from "/frontend/layouts/utils.js";

export const API = "http://localhost:18080";

export const LEVEL_LABELS = {
  0: "Початківець",
  1: "Середній",
  2: "Просунутий"
};

export const CATEGORY_LABELS = {
  0: "3-5",
  1: "5+",
  2: "6+",
  3: "7+",
  4: "10-12",
  5: "14+",
  6: "16+"
};

export const DAY_LABELS = ["Пн", "Вт", "Ср", "Чт", "Пт", "Сб"];
export const TIME_LABELS = ["08:00", "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00", "18:00", "19:00", "20:00"];

export async function loadGroupPageData() {
  const [groups, coaches, styles, subscriptions] = await Promise.all([
    apiGet(`${API}/groups`).then(unwrapData).catch(() => []),
    apiGet(`${API}/coaches`).then(unwrapData).catch(() => []),
    apiGet(`${API}/styles`).then(unwrapData).catch(() => []),
    apiGet(`${API}/subscriptions`).then(unwrapData).catch(() => [])
  ]);

  return { groups, coaches, styles, subscriptions };
}

export function getFullName(person) {
  return [person?.firstName, person?.lastName, person?.patronymic].filter(Boolean).join(" ") || "-";
}

export function getClientName(client) {
  return [client?.lastName, client?.firstName, client?.patronymic].filter(Boolean).join(" ") || `Клієнт #${client?.id}`;
}

export function findName(items, id, fallback = "-") {
  return items.find(item => String(item.id) === String(id))?.name || fallback;
}

export function getCategory(client) {
  if (client?.category !== undefined && client?.category !== null) return Number(client.category);

  const birthDate = client?.birthDate ? new Date(client.birthDate) : null;
  if (!birthDate || Number.isNaN(birthDate.getTime())) return 6;

  const today = new Date();
  let age = today.getFullYear() - birthDate.getFullYear();
  const monthDiff = today.getMonth() - birthDate.getMonth();
  if (monthDiff < 0 || (monthDiff === 0 && today.getDate() < birthDate.getDate())) age -= 1;

  if (age >= 16) return 6;
  if (age >= 14) return 5;
  if (age >= 10 && age <= 12) return 4;
  if (age >= 7) return 3;
  if (age >= 6) return 2;
  if (age >= 5) return 1;
  return 0;
}

export function getCategoryLabel(value) {
  return CATEGORY_LABELS[Number(value)] || "-";
}
