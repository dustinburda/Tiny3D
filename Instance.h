//
// Created by Dustin Burda on 11/27/23.
//

#ifndef RASTERIZATIONENGINE_INSTANCE_H
#define RASTERIZATIONENGINE_INSTANCE_H

#include "Mesh.h"
#include <memory>
#include "Transformations.h"


class Instance {
private:
    Mesh* mesh_;
    Matrix<4,4, double> transformation_;
};


#endif //RASTERIZATIONENGINE_INSTANCE_H
