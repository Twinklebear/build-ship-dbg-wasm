import CppApp from "./cpp/app.js";

export async function runWasm(canvas: string) {
  const app = await CppApp();
  try {
    app.callMain([canvas]);
  } catch (e) {
    console.error(e);
  }
}
