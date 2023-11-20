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
    explicit Mesh(const std::string& filename);

    void raster_wireframe(Canvas& canvas, const Color& color);

    size_t num_vertices() { return vertices_.size(); }
    size_t num_faces_() { return faces_.size(); }

    std::vector<Face>& faces() { return faces_; }
    std::vector<Vec>& vertices() { return vertices_; }

private:

    Prefix_Type get_parse_type(std::string& line);
    void parse_face(std::string& line);
    int parse_index(std::string& line);
    void parse_vertex(std::string& line);

private:
    std::vector<Vec> vertices_;
    std::vector<Face> faces_;
};


#endif //RASTERIZATIONENGINE_MESH_H
