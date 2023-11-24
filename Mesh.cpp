//
// Created by Dustin Burda on 11/17/23.
//

#include "Mesh.h"
#include "Triangle.h"


Mesh::Mesh(const std::string& filename) {
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

void Mesh::raster(Canvas& canvas, const Color& color, const Light& l) {
    for(auto& face : faces()) {
        std::array<Vec<3, float>, 3> normals;

        std::array<Vec<3, float>, 3> world_coord;
        std::array<ScreenPoint, 3> screen_coord;
        for(size_t i = 0; i < 3; i++) {
            auto index = face[i];

            Vec<3, float> vec = vertices()[index];
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

void Mesh::raster_wireframe(Canvas& canvas, const Color& color) {
    for(auto& face : faces()) {
        for(size_t i = 0; i < 3; i++) {
            auto index1 = face[i];
            auto index2 = face[(i + 1) % 3];

            Vec<3, float> Vec1 = vertices()[index1];
            Vec<3, float> Vec2 = vertices()[index2];


            ScreenPoint p1 {{ std::clamp( static_cast<int>(((Vec1[0] + 1.0)/2.0) * 1000), 1, canvas.screen_width() - 1),
                       1000 - std::clamp( static_cast<int>(((Vec1[1] + 1.0)/2.0) * 1000), 1, canvas.screen_height() - 1)}};

            ScreenPoint p2 {{ std::clamp( static_cast<int>(((Vec2[0] + 1.0)/2.0) * 1000), 1, canvas.screen_width() - 1),
                       1000 - std::clamp( static_cast<int>(((Vec2[1] + 1.0)/2.0) * 1000), 1, canvas.screen_height() - 1)}};

            Line l1 {p1, p2};

            l1.raster(canvas, color);
        }
    }
}

Prefix_Type Mesh::get_parse_type(std::string& line) {
    auto prefix = line.substr(0, 2);
    if(prefix == "v "){
        return Prefix_Type::Vertex;
    } else if (prefix == "vt") {
        return Prefix_Type::Texture;
    } else if (prefix == "vn") {
        return Prefix_Type::Normal;
    } else if (prefix == "f "){
        return Prefix_Type::Face;
    } else {
        return Prefix_Type::Unrecognized;
    }
}

void Mesh::parse_face(std::string& line) {
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

int Mesh::parse_index(std::string& line) {
    int index = 0;

    size_t pos = 0;
    while(pos < line.size() && line[pos] != '/' && line[pos] != '\r') {
        index = index * 10 + (line[pos] - '0');
        pos++;
    }

    return index;
}

void Mesh::parse_vertex(std::string& line) {
    // std::cout << line << std::endl;

    std::istringstream s {line};

    Vec<3, float> vertex;
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
