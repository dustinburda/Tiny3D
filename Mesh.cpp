//
// Created by Dustin Burda on 11/17/23.
//

#include "Mesh.h"


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

    Vec<3, double> vertex;
    int index = 0;

    std::string token;
    while(getline(s, token, ' ')) {
        if(token == "v")
            continue;
        else {
            vertex[index] = std::stod(token);
            index++;
        }
    }
    vertices_.push_back(vertex);
}
