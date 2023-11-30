#include <iostream>
#include <chrono>
#include "Canvas.h"
#include "Line.h"
#include "Mesh.h"
#include "Triangle.h"
#include "util.h"
#include "Instance.h"

const Vec<3, double> camera {{ 0.0, 0.0, 3.0 }};

int main() {
    Canvas canvas {height, width};

    const auto time_start = std::chrono::steady_clock::now();

    std::string object = "cube";
    Mesh m{ object + ".obj"};



    Instance head{&m, nullptr};
    head.set_transformation(Transformations::Translate(-0.5, -0.5, -3.5));
    // head.raster(canvas, Color{1.0, 1.0, 1.0}, Light{{0, 0, -1}});
     head.raster_wireframe(canvas, Color{1.0, 0.0, 0.0});

    std::string path { object + ".ppm" };
    canvas.flush(path);

    const auto time_end = std::chrono::steady_clock::now();

    std::cout << (std::chrono::duration_cast<std::chrono::seconds>(time_end - time_start)).count()  << std::endl;
}
