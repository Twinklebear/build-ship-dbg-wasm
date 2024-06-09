#include <array>
#include <cstdint>
#include <iostream>

#include <GL/gl.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgl.h>

std::array<float, 3> hsv_to_rgb(const std::array<float, 3> &hsv);

void app_loop(void *);

int main(int argc, const char **argv)
{
    // Setup the WebGL2 context
    EmscriptenWebGLContextAttributes attrs = {};
    emscripten_webgl_init_context_attributes(&attrs);
    attrs.minorVersion = 0;
    attrs.majorVersion = 2;
    attrs.explicitSwapControl = false;

    // Our canvas ID is just "canvas"
    const auto context = emscripten_webgl_create_context("canvas", &attrs);
    emscripten_webgl_make_context_current(context);

    // Start the app loop
    emscripten_set_main_loop_arg(app_loop, nullptr, -1, 0);

    return 0;
}

uint32_t hue = 0;

void app_loop(void *)
{
    hue = (hue + 1) % 360;
    const auto rgb = hsv_to_rgb({static_cast<float>(hue), 0.8f, 0.8f});

    glClearColor(rgb[0], rgb[1], rgb[2], 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

std::array<float, 3> hsv_to_rgb(const std::array<float, 3> &hsv)
{
    std::array<float, 3> rgb = {0.f};

    const float sector = std::floor(hsv[0] / 60.f);
    const float frac = hsv[0] / 60.f - sector;
    const float o = hsv[2] * (1.f - hsv[1]);
    const float p = hsv[2] * (1.f - hsv[1] * frac);
    const float q = hsv[2] * (1.f - hsv[1] * (1.f - frac));

    switch (int(sector)) {
    default:
    case 0:
        rgb[0] = hsv[2];
        rgb[1] = q;
        rgb[2] = o;
        break;
    case 1:
        rgb[0] = p;
        rgb[1] = hsv[2];
        rgb[2] = o;
        break;
    case 2:
        rgb[0] = o;
        rgb[1] = hsv[2];
        rgb[2] = q;
        break;
    case 3:
        rgb[0] = o;
        rgb[1] = p;
        rgb[2] = hsv[2];
        break;
    case 4:
        rgb[0] = q;
        rgb[1] = o;
        rgb[2] = hsv[2];
        break;
    case 5:
        rgb[0] = hsv[2];
        rgb[1] = o;
        rgb[2] = q;
        break;
    }

    return rgb;
}
