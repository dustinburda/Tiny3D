//
// Created by Dustin Burda on 11/27/23.
//

#ifndef RASTERIZATIONENGINE_INSTANCE_H
#define RASTERIZATIONENGINE_INSTANCE_H

#include "Mesh.h"
#include <memory>
#include "Transformations.h"
#include "Texture.h"
#include "util.h"


static Matrix<3,3, double> viewport(double height, double width) {
    Matrix<3,3, double> vw(0);
    vw[0][0] = width / 2.0;
    vw[0][2] = width / 2.0;
    vw[1][1] = -height / 2.0;
    vw[1][2] = height / 2.0;
    vw[2][2] = 1.0;
}

class Instance {
public:
    Instance(Mesh* mesh, Texture* texture) : mesh_{mesh}, texture_{texture}, transformation_{Id<4, double>()} {}

    void set_transformation(const Matrix<4,4, double>& transformation) { transformation_ = transformation; }

    void raster(Canvas& canvas, const Color& color, const Light& l) {
        for(auto& face : mesh_->faces()) {
            std::array<Vec<3, double>, 3> normals;

            std::array<Vec<3, double>, 3> world_coord;
            std::array<ScreenPoint, 3> screen_coord;
            for(size_t i = 0; i < 3; i++) {
                auto index = face[i];

                Vec<3, double> vec = mesh_->vertices()[index];
                world_coord[i] = vec;

                ScreenPoint p {{ std::clamp( static_cast<int>(((vec[0] + 1.0)/2.0) * 1000), 1, canvas.screen_width() - 1),
                                 1000 - std::clamp( static_cast<int>(((vec[1] + 1.0)/2.0) * 1000), 1, canvas.screen_height() - 1)}};
                screen_coord[i] = p;
            }

            auto normal = cross(world_coord[2] - world_coord[0], world_coord[1] - world_coord[0]).normalize();
            assert(std::abs(normal.magnitude() - 1) < 10e-5);

            // TODO: make a color class
            auto intensity = dot(normal, l);
            if(intensity > 0) {
                Triangle t(screen_coord[0], screen_coord[1], screen_coord[2]);
                Color c {{ color[0] * intensity, color[1] * intensity, color[2] * intensity}};
                t.raster_triangle_mesh(world_coord, canvas, c);
            }

        }
    }

    void raster_wireframe(Canvas& canvas, const Color& color) {
        for(auto& face : mesh_->faces()) {
            for(size_t i = 0; i < 3; i++) {
                auto index1 = face[i];
                auto index2 = face[(i + 1) % 3];

                Vec<3, double> Vec1 = mesh_->vertices()[index1];
                Vec<3, double> Vec2 = mesh_->vertices()[index2];

                Vec1 = (transformation_ * Vec1.homogenize_vector()).dehomogenize_vector();
                Vec2 = (transformation_ * Vec2.homogenize_vector()).dehomogenize_vector();

//                Matrix<3,3, double> viewport_matrix = viewport(height, width);
//                Vec1 = viewport_matrix * Vec1;
//                Vec2 = viewport_matrix * Vec2;

                ScreenPoint p1 {{ std::clamp( static_cast<int>(((Vec1[0] + 1.0)/2.0) * 1000), 1, canvas.screen_width() - 1),
                                  1000 - std::clamp( static_cast<int>(((Vec1[1] + 1.0)/2.0) * 1000), 1, canvas.screen_height() - 1)}};

                ScreenPoint p2 {{ std::clamp( static_cast<int>(((Vec2[0] + 1.0)/2.0) * 1000), 1, canvas.screen_width() - 1),
                                  1000 - std::clamp( static_cast<int>(((Vec2[1] + 1.0)/2.0) * 1000), 1, canvas.screen_height() - 1)}};

//                ScreenPoint p1 {{  static_cast<int>(Vec1[0]), static_cast<int>(Vec1[1] )}};
//                ScreenPoint p2 {{   static_cast<int>(Vec2[0]), static_cast<int>(Vec2[1])}};

                Line l1 {p1, p2};

                l1.raster(canvas, color);
            }
        }
    }


private:
    Mesh* mesh_;
    Texture* texture_;
    Matrix<4,4, double> transformation_;
};


#endif //RASTERIZATIONENGINE_INSTANCE_H
