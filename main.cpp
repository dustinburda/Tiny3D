#include <iostream>
#include <chrono>
#include "Canvas.h"
#include "Line.h"
#include "Mesh.h"
#include "Triangle.h"
#include "util.h"



int main() {
    Canvas canvas {1000, 1000};

    const auto time_start = std::chrono::steady_clock::now();

    std::string object = "tetrahedron";
    Mesh m{ object + ".obj"};

    // m.raster(canvas, Color{1.0, 1.0, 1.0}, Light{{0, 0, -1}});
     m.raster_wireframe(canvas, Color{1.0, 0.0, 0.0});
//        Triangle t {ScreenPoint{{725, 500}}, ScreenPoint{{875, 420}}, ScreenPoint{{925, 180}} };
//        t.raster(canvas, Color{1.0, 0.0, 0.0});
//    t.raster_wireframe(canvas, Color{0.0, 1.0, 1.0});

    std::string path { object + ".ppm" };
    canvas.flush(path);

    const auto time_end = std::chrono::steady_clock::now();

    std::cout << (std::chrono::duration_cast<std::chrono::seconds>(time_end - time_start)).count()  << std::endl;
}
