import { apiPost } from "/frontend/layouts/utils.js";

const ROLE_REDIRECTS = {
  0: "/page/clients",
  2: "/page/dashboard",
  3: "/page/dashboard"
};

document.getElementById("login-form").addEventListener("submit", async event => {
  event.preventDefault();

  const form = event.currentTarget;
  const error = document.getElementById("login-error");
  const payload = {
    username: form.username.value.trim(),
    password: form.password.value
  };

  error.classList.remove("visible");

  try {
    const user = await apiPost("/auth/login", payload);
    localStorage.setItem("elanUser", JSON.stringify(user));
    window.location.href = ROLE_REDIRECTS[user.role] || "/page/dashboard";
  } catch {
    error.classList.add("visible");
  }
});
