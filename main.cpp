#include <iostream>
#include "Canvas.h"
#include "Line.h"
#include "Mesh.h"




int main() {
    Canvas canvas {1000, 1000};
    // line(130, 200, 800, 400, canvas, {1.0, 1.0, 1.0});

    /* TODO: Write Vec, Matrix class
     * TODO: Shape interface w/ Render method (For line, triangle, sphere, cube, etc)
     * TODO: Mesh class
     * TODO: OBJ Loader
     * */

    Mesh m{"head.obj"};

    Line l1 {Point {0,0}, Point {1000, 1000}};
    l1.raster(canvas, {1.0, 0.0, 0.0});

    std::string path { "line.ppm" };
    canvas.flush(path);
}
