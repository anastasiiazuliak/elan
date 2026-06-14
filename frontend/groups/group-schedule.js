import { apiGet, unwrapData } from "/frontend/layouts/utils.js";
import { API, DAY_LABELS, LEVEL_LABELS, TIME_LABELS, findName, getFullName } from "./group-data.js";

export function updateGroupFilter(state) {
  const select = document.getElementById("schedule-group-filter");
  if (!select) return;

  const current = select.value;
  select.innerHTML = `<option value="">Усі групи</option>`;

  state.groups.forEach(group => {
    const option = document.createElement("option");
    option.value = group.id;
    option.textContent = group.name || `Група #${group.id}`;
    select.appendChild(option);
  });

  select.value = current;
}

export async function buildScheduleGrid(state, filterGroupId = "") {
  const grid = document.getElementById("schedule-grid");
  if (!grid) return;

  const groups = filterGroupId
    ? state.groups.filter(group => String(group.id) === String(filterGroupId))
    : state.groups;

  const schedules = [];

  await Promise.all(groups.map(async group => {
    const schedule = await apiGet(`${API}/groups/${group.id}/schedule`).then(unwrapData).catch(() => []);
    schedule.forEach(slot => schedules.push({ ...slot, groupId: group.id }));
  }));

  let html = `<div class="sg-head"></div>`;
  DAY_LABELS.forEach(day => {
    html += `<div class="sg-head">${day}</div>`;
  });

  TIME_LABELS.forEach((timeLabel, timeIndex) => {
    html += `<div class="sg-time">${timeLabel}</div>`;

    DAY_LABELS.forEach((_, dayIndex) => {
      const events = schedules.filter(slot => slot.day === dayIndex && slot.time === timeIndex);
      html += `<div class="sg-cell">${events.map(slot => renderScheduleEvent(state, slot)).join("")}</div>`;
    });
  });

  grid.innerHTML = html;
}

function renderScheduleEvent(state, slot) {
  const group = state.groups.find(item => String(item.id) === String(slot.groupId));
  if (!group) return "";

  const style = findName(state.styles, group.styleId);
  const coach = getFullName(state.coaches.find(item => String(item.id) === String(group.coachId)));
  const level = LEVEL_LABELS[group.skillLevel] || "-";

  return `
    <div class="sg-event" title="${group.name} - ${style} - ${coach} (${level})">
      ${group.name || `Група #${group.id}`}<br>
      <small>${style}, ${coach}</small>
    </div>`;
}
