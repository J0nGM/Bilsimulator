//
// Created by L14 G5 on 10/11/2025.
//

#ifndef TANK_LANDSCAPE_HPP
#define TANK_LANDSCAPE_HPP
#include <iostream>
#include <threepp/threepp.hpp>

class Landscape {
public:
    std::shared_ptr<threepp::PlaneGeometry>groundGeometry = threepp::PlaneGeometry::create(500, 500);
    std::shared_ptr<threepp::MeshStandardMaterial>groundMaterial = threepp::MeshStandardMaterial::create({{"color", threepp::Color::green}});
    std::shared_ptr<threepp::Mesh>groundMesh = threepp::Mesh::create(groundGeometry, groundMaterial);

    std::vector<std::shared_ptr<threepp::Mesh>> roads;

    Landscape();
};
#endif //TANK_lANDSCAPE_HPP