//
// Created by Dustin Burda on 11/19/23.
//

#ifndef RASTERIZATIONENGINE_BOUNDINGBOX_H
#define RASTERIZATIONENGINE_BOUNDINGBOX_H

#include "Vector.h"


/*
 * 2D Bounding Box for efficient rasterization
 *
 *
 * */
class Box {
private:
    Vec<2> min_;
    Vec<2> max_;
};

#endif //RASTERIZATIONENGINE_BOUNDINGBOX_H
