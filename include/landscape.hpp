//
// Created by L14 G5 on 10/11/2025.
//

#ifndef TANK_LANDSCAPE_HPP
#define TANK_LANDSCAPE_HPP
#include <iostream>
#include <threepp/threepp.hpp>

class landscape {
public:
    std::shared_ptr<PlaneGeometry>groundGeometry = PlaneGeometry::create(1000, 1000);
    std::shared_ptr<MeshStandardMaterial>groundMaterial = MeshStandardMaterial::create({{"color", Color::green}});
    std::shared_ptr<Mesh>groundMesh = Mesh::create(groundGeometry, groundMaterial);

    std::shared_ptr<Mesh> roadMesh;

    landscape() {
        groundMesh->rotation.x = -math::PI / 2; //Gjør slik at bakken blir helt flat
        groundMesh->position.y = 0;

        //Lager vei, for landskapet
        auto roadGeometry = PlaneGeometry::create(1000, 20);
        auto roadMaterial = MeshStandardMaterial::create({{"color", Color::gray}});
        this->roadMesh = Mesh::create(roadGeometry, roadMaterial);

        roadMesh->rotation.x = -math::PI / 2;
        roadMesh->position.y = 0.01;
        roadMesh->position.z = 0;
    }
};
#endif //TANK_lANDSCAPE_HPP