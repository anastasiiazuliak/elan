import { canCreateClient, canManageCatalogs, hideElement, icon, isClient, isLocationAdmin } from "/frontend/layouts/utils.js";

const ROLE_LABELS = {
  0: "Системний адміністратор",
  1: "Клієнт",
  2: "Адміністратор локації",
  3: "Тренер"
};

async function loadSidebar() {
  const container = document.getElementById("sidebar-container");
  if (!container) return;

  const response = await fetch("/frontend/layouts/sidebar.html");
  container.innerHTML = await response.text();

  applySidebarIcons();
  setActiveSidebarItem();
  fillUserCard();
  bindLogout();
  applyRoleAccess();
}

function applySidebarIcons() {
  const icons = {
    "/page/dashboard": "home",
    "/page/clients": "users",
    "/page/groups": "groups",
    "/page/employees": "staff",
    "/page/coaches": "coach",
    "/page/locations": "location",
    "/page/styles": "style",
    "/page/subscriptions": "subscription"
  };

  document.querySelectorAll(".nav-item").forEach(link => {
    const iconSlot = link.querySelector(".nav-icon");
    const name = icons[link.getAttribute("href")];
    if (iconSlot && name) iconSlot.innerHTML = icon(name);
  });
}

function setActiveSidebarItem() {
  const path = window.location.pathname;

  document.querySelectorAll(".nav-item").forEach(link => {
    if (link.getAttribute("href") === path) {
      link.classList.add("active");
    }
  });
}

function fillUserCard() {
  const user = JSON.parse(localStorage.getItem("elanUser") || "null");
  if (!user) return;

  const username = user.username || "Адміністратор";
  document.getElementById("sidebar-user").textContent = username;
  document.getElementById("sidebar-role").textContent = ROLE_LABELS[user.role] || "Користувач";
  document.getElementById("sidebar-avatar").textContent = username.slice(0, 2).toUpperCase();
}

function bindLogout() {
  document.getElementById("logout-btn")?.addEventListener("click", () => {
    localStorage.removeItem("elanUser");
    window.location.href = "/login";
  });
}

function applyRoleAccess() {
  if (!canCreateClient()) {
    hideElement("add-client-btn");
  }

  if (!canManageCatalogs()) {
    [
      "add-coach-btn",
      "add-employee-btn",
      "add-group-btn",
      "add-location-btn",
      "add-style-btn",
      "add-subscription-btn"
    ].forEach(hideElement);
  }

  if (isLocationAdmin()) {
    document.querySelectorAll("[data-admin-only]").forEach(element => {
      element.style.display = "none";
    });
  }

  if (isClient()) {
    document.querySelector('a[href="/page/clients"]')?.remove();
    document.querySelector('a[href="/page/employees"]')?.remove();
    [
      "add-coach-btn",
      "add-employee-btn",
      "add-group-btn",
      "add-location-btn",
      "add-style-btn",
      "add-subscription-btn"
    ].forEach(hideElement);
  }

  if (!canManageCatalogs()) {
    document.querySelector('a[href="/page/employees"]')?.remove();
  }
}

document.addEventListener("DOMContentLoaded", loadSidebar);
