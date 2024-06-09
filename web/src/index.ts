import CppApp from "./cpp/app.js";

(async () => {
  // We set -sINVOKE_RUN=0 when building and call main ourselves because something
  // within the promise -> call directly chain was gobbling exceptions
  // making it hard to debug
  let app = await CppApp();

  try {
    app.callMain();
  } catch (e) {
    console.error(e.stack);
  }
})();
