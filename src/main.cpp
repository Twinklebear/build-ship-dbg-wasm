#include <iostream>

#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgpu.h>
#endif

void app_loop(void *);

int main(int argc, const char **argv)
{
    emscripten_set_main_loop_arg(app_loop, nullptr, -1, 0);

    return 0;
}

void app_loop(void *)
{
    std::cout << "Hello\n";
}
