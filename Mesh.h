//
// Created by Dustin Burda on 11/17/23.
//

#ifndef RASTERIZATIONENGINE_MESH_H
#define RASTERIZATIONENGINE_MESH_H

#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "Line.h"

using Vec = std::array<float, 3>;
using Face = std::vector<int>;


enum class Prefix_Type {
    Vertex,
    Texture,
    Normal,
    Face
};

class Mesh {
public:
    explicit Mesh(const std::string& filename) {
        std::string path = std::filesystem::current_path();

        std::string absolute_filename = path + "/" +  filename;
        std::ifstream mesh {absolute_filename};

        // std::cout << mesh.is_open() << std::endl;

        std::string line { "" };
        while(std::getline(mesh, line)) {
            Prefix_Type type = get_parse_type(line);
            switch(type) {
                case Prefix_Type::Vertex:
                    parse_vertex(line);
                    break;
                case Prefix_Type::Face:
                    parse_face(line);
                    break;
                default:
                    break;
            }
        }
    }

    void raster_wireframe(Canvas& canvas, const Color& color) {
        for(auto& face : faces()) {
            for(size_t i = 0; i < 3; i++) {
                auto index1 = face[i];
                auto index2 = face[(i + 1) % 3];

                Vec Vec1 = vertices()[index1];
                Vec Vec2 = vertices()[index2];


                Point p1 { std::clamp(static_cast<int>(((Vec1[0] + 1.0)/2.0) * 1000), 1, canvas.screen_width() - 1),
                           1000 - std::clamp(static_cast<int>(((Vec1[1] + 1.0)/2.0) * 1000), 1, canvas.screen_height() - 1)};

                Point p2 { std::clamp(static_cast<int>(((Vec2[0] + 1.0)/2.0) * 1000), 1, canvas.screen_width() - 1),
                           1000 - std::clamp(static_cast<int>(((Vec2[1] + 1.0)/2.0) * 1000), 1, canvas.screen_height() - 1)};

                Line l1 {p1, p2};

                l1.raster(canvas, color);
            }
        }
    }

    size_t num_vertices() { return vertices_.size(); }
    size_t num_faces_() { return faces_.size(); }

    std::vector<Face>& faces() { return faces_; }
    std::vector<Vec>& vertices() { return vertices_; }

private:

    Prefix_Type get_parse_type(std::string& line) {
        auto prefix = line.substr(0, 2);
        if(prefix == "v "){
            return Prefix_Type::Vertex;
        } else if (prefix == "vt") {
            return Prefix_Type::Texture;
        } else if (prefix == "vn") {
            return Prefix_Type::Normal;
        } else if (prefix == "f "){
            return Prefix_Type::Face;
        }
    }

    void parse_face(std::string& line) {
        // std::cout << line << std::endl;

        std::istringstream s_line {line};

        std::string token;

        Face face;
        while(getline(s_line, token, ' ')) {
            if(token == "f")
                continue;
            else {
                int index = parse_index(token);
                face.push_back(index - 1);
            }
        }

        faces_.push_back(face);
    }

    int parse_index(std::string& line) {
        int index = 0;

        size_t pos = 0;
        while(line[pos] != '/') {
            index = index * 10 + (line[pos] - '0');
            pos++;
        }

        return index;
    }

    void parse_vertex(std::string& line) {
        // std::cout << line << std::endl;

        std::istringstream s {line};

        Vec vertex;
        int index = 0;

        std::string token;
        while(getline(s, token, ' ')) {
            if(token == "v")
                continue;
            else {
                vertex[index] = std::stof(token);
                index++;
            }
        }
        vertices_.push_back(vertex);
    }

private:
    std::vector<Vec> vertices_;
    std::vector<Face> faces_;
};


#endif //RASTERIZATIONENGINE_MESH_H
