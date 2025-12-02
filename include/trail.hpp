#ifndef TANK_TRAIL_HPP
#define TANK_TRAIL_HPP
#include "threepp/threepp.hpp"

class trail {
public:
    std::shared_ptr<threepp::Mesh>mesh;
    float life_time;
    float max_lifetime_;

    trail(std::shared_ptr<threepp::Mesh> m)
        : mesh(m), life_time(2.0f), max_lifetime_(2.0f) {}
};

#endif //TANK_TRAIL_HPP