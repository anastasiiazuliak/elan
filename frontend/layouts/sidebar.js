async function loadSidebar() {
  try {
    const res = await fetch("/frontend/layouts/sidebar.html");
    const html = await res.text();

    const container = document.getElementById("sidebar-container");
    container.innerHTML = html;

    setActiveSidebarItem();

  } catch (err) {
    console.error("Sidebar load error:", err);
  }
}

/* ── підсвітка активного пункту ── */
function setActiveSidebarItem() {
  const links = document.querySelectorAll(".nav-item");
  const path = window.location.pathname.split("/").pop();

  links.forEach(link => {
    const href = link.getAttribute("href");

    if (href && href === path) {
      link.classList.add("active");
    }
  });
}

/* ── init ── */
document.addEventListener("DOMContentLoaded", loadSidebar);