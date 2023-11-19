//
// Created by Dustin Burda on 11/4/23.
//

#include "Canvas.h"

Color Canvas::pixal_at(int x, int y) const{
    if(x < 0 || x >= screen_width_ || y < 0 || y >= screen_height_)
        throw std::logic_error("Must input a coordinate within screen dimensions!");
    return buffer_[y * screen_width_ + x];
}

Color Canvas::write_pixel(const Color& color, int x, int y) {
    if(x < 0 || x >= screen_width_ || y < 0 || y >= screen_height_){
        std::cout << "Out of dimensions! x: " << x << "  y: " << y << std::endl;
        return color;
    }
    buffer_[y * screen_width_ + x] = color;
    return color;
}

void Canvas::flush_color(std::ofstream& canvas, Color& color) {
    auto r = std::clamp(color[0], 0.0, 1.0);
    auto g = std::clamp(color[1], 0.0, 1.0);
    auto b = std::clamp(color[2], 0.0, 1.0);

    canvas << std::ceil(255.0 * r) << ' ' << std::ceil(255.0 * g) << ' ' << std::ceil(255.0 * b) << '\n';
}

void Canvas::flush(std::string& path) {
    std::filesystem::path cwd = std::filesystem::current_path();
    std::string full_path = cwd.string() + '/' + path;

    std::ofstream canvas(full_path, std::ios::trunc | std::ios::out);

    canvas << "P3\n";
    canvas << screen_width_ << ' ' << screen_height_ << "\n";
    canvas << "255\n";

    for(auto& color : buffer_) {
        flush_color(canvas, color);
    }

    canvas.flush();
}
