#include <iostream>
#include "Canvas.h"
#include "Line.h"
#include "Mesh.h"




int main() {
    Canvas canvas {1000, 1000};
    // line(130, 200, 800, 400, canvas, {1.0, 1.0, 1.0});

    /* TODO: Write Matrix class
     * TODO: Shape interface w/ Render method (For line, triangle, sphere, cube, etc)
     * */

    std::string object = "head";
    Mesh m{ object + ".obj"};

    m.raster_wireframe(canvas, Color{0.0, 1.0, 1.0});


    std::string path { object + ".ppm" };
    canvas.flush(path);
}
