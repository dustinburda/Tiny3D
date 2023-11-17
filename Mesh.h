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

using Vec = std::array<float, 3>;
using Face = std::vector<int>;

class Mesh {
public:
    explicit Mesh(const std::string& filename) {
        std::string path = std::filesystem::current_path();

        std::string absolute_filename = path + "/" +  filename;
        std::ifstream mesh {absolute_filename};

        std::cout << mesh.is_open() << std::endl;

        std::string line { "" };
        while(std::getline(mesh, line)) {
            switch(line[0]) {
                case 'v':
                    parse_vertex(line);
                    break;
                case 'f':
                    parse_face(line);
                    break;
                default:
                    break;
            }
        }
    }

    void parse_face(std::string& line) {
        std::cout << line << std::endl;

        std::istringstream s {line};

        // TODO: FINISH THIS

    }

    void parse_vertex(std::string& line) {
        std::cout << line << std::endl;

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

    size_t num_vertices() { return vertices_.size(); }
    size_t num_faces_() { return faces_.size(); }

private:
    std::vector<Vec> vertices_;
    std::vector<Face> faces_;
};


#endif //RASTERIZATIONENGINE_MESH_H
