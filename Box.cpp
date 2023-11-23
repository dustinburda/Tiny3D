//
// Created by Dustin Burda on 11/20/23.
//

#include "Box.h"

Box::Box(const std::vector<ScreenPoint>& points) {
    min_ = ScreenPoint {{std::numeric_limits<int>::max(),std::numeric_limits<int>::max()}};
    max_ = ScreenPoint {{ 0, 0 }};
    for(auto& point : points) {
        min_[0] = std::min(min_[0], point[0]);
        max_[0] = std::max(max_[0], point[0]);

        min_[1] = std::min(min_[1], point[1]);
        max_[1] = std::max(max_[1], point[1]);
    }
}