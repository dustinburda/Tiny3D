//
// Created by Dustin Burda on 11/4/23.
//

#include <gtest/gtest.h>
#include "Canvas.h"

TEST(Canvas, ConstructorTest) {
    Canvas c(20, 10);

    EXPECT_EQ(c.screen_height(), 10);
    EXPECT_EQ(c.screen_width(), 20);
}

TEST(Canvas, DrawingTest) {
    Canvas canvas {10, 10};


    for(int x = 0; x < canvas.screen_width(); x++) {
        for(int y = 0; y < canvas.screen_height(); y++) {
            switch (x % 3) {
                case 0:
                    canvas.write_pixel({1.0, 0.0, 0.0}, x, y);
                    break;
                case 1:
                    canvas.write_pixel({0.0, 1.0, 0.0}, x, y);
                    break;
                case 2:
                    canvas.write_pixel({0.0, 0.0, 1.0}, x, y);
                    break;
            }
        }
    }


    std::string path1 = "image_vert_stripes.ppm";
    canvas.flush(path1);



    for(int x = 0; x < canvas.screen_width(); x++) {
        for(int y = 0; y < canvas.screen_height(); y++) {
            switch(y % 3) {
                case 0:
                    canvas.write_pixel({1.0, 0.0, 0.0}, x, y);
                    break;
                case 1:
                    canvas.write_pixel({0.0, 1.0, 0.0}, x, y);
                    break;
                case 2:
                    canvas.write_pixel({0.0, 0.0, 1.0}, x, y);
                    break;
            }
        }
    }

    std::string path2 = "image_horiz_stripes.ppm";
    canvas.flush(path2);
}