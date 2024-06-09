add_executable(app main.cpp)

set_target_properties(app PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)

target_link_options(
  app
  PRIVATE
  "SHELL: -sENVIRONMENT='web'"
  -sEXPORT_ES6
  -sEXPORT_NAME=CppApp
  -sUSE_WEBGL2=1
  -sMODULARIZE=1
  -sALLOW_MEMORY_GROWTH=1
  -sASSERTIONS=1
  -sEXIT_RUNTIME=1
  -sINVOKE_RUN=0
  # RelWithDebInfo build flags, automatically enables split dwarf
  $<$<CONFIG:RELWITHDEBINFO>:-gseparate-dwarf=${CMAKE_CURRENT_BINARY_DIR}/app.dwarf>
  $<$<CONFIG:RELWITHDEBINFO>:-g>
  $<$<CONFIG:RELWITHDEBINFO>:-O2>
  # Debug build flags
  $<$<CONFIG:DEBUG>:-fwasm-exceptions>
  $<$<CONFIG:DEBUG>:-g>
  $<$<CONFIG:DEBUG>:-O0>
  # Exported Emscripten runtime methods
  "SHELL:-sEXPORTED_RUNTIME_METHODS='[\"callMain\"]'")

set(WEB_OUT_DIR ${PROJECT_SOURCE_DIR}/web/src/cpp)

add_custom_command(
  DEPENDS app
  OUTPUT ${WEB_OUT_DIR}/app.js ${WEB_OUT_DIR}/app.wasm
  COMMAND cmake -E make_directory ${WEB_OUT_DIR}
  COMMAND cmake -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/app.js
          ${CMAKE_CURRENT_BINARY_DIR}/app.wasm ${WEB_OUT_DIR})

add_custom_target(
  copy_wasm_to_app ALL
  DEPENDS ${WEB_OUT_DIR}/app.js ${WEB_OUT_DIR}/app.wasm
  COMMENT "Copying wasm build to ${WEB_OUT_DIR}")
