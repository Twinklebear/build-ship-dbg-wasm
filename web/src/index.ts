import CppApp from "./cpp/app.js";

(async () => {
  let app = await CppApp();

  // We set -sINVOKE_RUN=0 so now we can callMain ourselves
  // when appropriate in the application, and prevent
  // some Emscripten internals from gobbling errors
  try {
    app.callMain();
  } catch (e) {
    console.error(e.stack);
  }
})();
