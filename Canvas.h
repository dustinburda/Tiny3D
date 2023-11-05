//
// Created by Dustin Burda on 11/4/23.
//

#ifndef RASTERIZATIONENGINE_CANVAS_H
#define RASTERIZATIONENGINE_CANVAS_H


#include <fstream>
#include <array>
#include <string>
#include <iostream>
#include <filesystem>

using Color = std::array<double, 3>;

class Canvas {
public:
    Canvas() = delete;

    explicit Canvas(uint16_t width, uint16_t height) : screen_width_{width}, screen_height_{height} {
        buffer_.reserve(screen_width_ * screen_height_);
        buffer_.resize(screen_width_ * screen_height_);
    }

    Color pixal_at(int x, int y) const;
    Color write_pixel(const Color& color, int x, int y);

    void flush_color(std::ofstream& canvas, Color& color);
    void flush(std::string& path);


    inline uint16_t screen_width() const { return screen_width_; }
    inline uint16_t screen_height() const { return screen_height_; }


private:
    std::vector<Color> buffer_;
    uint16_t screen_width_;
    uint16_t screen_height_;
};


#endif //RASTERIZATIONENGINE_CANVAS_H