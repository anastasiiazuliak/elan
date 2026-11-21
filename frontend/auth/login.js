import { apiPost } from "/frontend/layouts/utils.js";

const THEME_KEY = "elanTheme";

const ROLE_REDIRECTS = {
  0: "/page/clients",
  2: "/page/dashboard",
  3: "/page/my-groups"
};

function getStoredTheme() {
  const saved = localStorage.getItem(THEME_KEY);
  if (saved === "dark" || saved === "light") return saved;
  return window.matchMedia("(prefers-color-scheme: dark)").matches ? "dark" : "light";
}

document.documentElement.classList.toggle("dark", getStoredTheme() === "dark");

const form = document.getElementById("login-form");
const error = document.getElementById("login-error");
const submitButton = form.querySelector(".auth-submit");

form.addEventListener("submit", async event => {
  event.preventDefault();

  const payload = {
    username: form.username.value.trim(),
    password: form.password.value
  };

  error.classList.remove("visible");
  submitButton.setAttribute("aria-busy", "true");
  submitButton.disabled = true;

  try {
    const user = await apiPost("/auth/login", payload);
    localStorage.setItem("elanUser", JSON.stringify(user));
    window.location.href = ROLE_REDIRECTS[user.role] || "/page/dashboard";
  } catch {
    error.classList.add("visible");
    submitButton.removeAttribute("aria-busy");
    submitButton.disabled = false;
  }
});
