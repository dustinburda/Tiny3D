#include <iostream>
#include "Canvas.h"
#include "Line.h"
#include "Mesh.h"
#include "Triangle.h"



int main() {
    Canvas canvas {1000, 1000};
    // line(130, 200, 800, 400, canvas, {1.0, 1.0, 1.0});

    /* TODO: Write Matrix class
     * */

    std::string object = "triangle";
//    Mesh m{ object + ".obj"};

     // m.raster_wireframe(canvas, Color{0.0, 1.0, 1.0});
        Triangle t {ScreenPoint{{725, 500}}, ScreenPoint{{875, 420}}, ScreenPoint{{925, 180}} };
        t.raster(canvas, Color{1.0, 0.0, 0.0});
    t.raster_wireframe(canvas, Color{0.0, 1.0, 1.0});

    std::string path { object + ".ppm" };
    canvas.flush(path);
}
