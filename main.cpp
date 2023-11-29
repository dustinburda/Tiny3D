#include <iostream>
#include <chrono>
#include "Canvas.h"
#include "Line.h"
#include "Mesh.h"
#include "Triangle.h"
#include "util.h"
#include "Instance.h"

int main() {
    Canvas canvas {height, width};

    const auto time_start = std::chrono::steady_clock::now();

    std::string object = "bunny2";
    Mesh m{ object + ".obj"};


    Instance head{&m, nullptr};
    head.set_transformation(Transformations::Translate(0.2, -0.75, 0)*Transformations::RotateY(pi/7)*Transformations::Scale(8.0, 8.0, 8.0));
    // head.raster(canvas, Color{1.0, 1.0, 1.0}, Light{{0, 0, -1}});
     head.raster_wireframe(canvas, Color{1.0, 0.0, 0.0});

    std::string path { object + ".ppm" };
    canvas.flush(path);

    const auto time_end = std::chrono::steady_clock::now();

    std::cout << (std::chrono::duration_cast<std::chrono::seconds>(time_end - time_start)).count()  << std::endl;
}
