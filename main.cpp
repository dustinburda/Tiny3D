#include <iostream>
#include "Canvas.h"

void line(int x0, int y0, int x1, int y1, Canvas& canvas, const Color& color) {
    if(x0 > x1)
        return line(x1, y1, x0, y0, canvas, color);

    bool swapped { false };
    if(std::abs(y0 - y1) > std::abs(x0 - x1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        swapped = true;
    }

    for(int x = x0; x < x1; x++) {
        float t = (x - x0) / static_cast<float>(x1 - x0);
        int y = y0 * (1.0 -t) + y1 * t;

        swapped ? canvas.write_pixel(color, y, x)
                : canvas.write_pixel(color, x, y);
    }
}


int main() {
    Canvas canvas {1000, 1000};
    // line(130, 200, 800, 400, canvas, {1.0, 1.0, 1.0});

    /* TODO: Write Vec, Matrix class
     * TODO: Shape interface w/ Render method (For line, triangle, sphere, cube, etc)
     * TODO: Mesh class
     * TODO: OBJ Loader
     * */

    line(800, 400, 130, 200, canvas, {1.0, 0.0, 0.0});
    std::string path { "line.ppm" };
    canvas.flush(path);
}
