#include "landscape.hpp"

using namespace threepp;

Landscape::Landscape() {
    groundMesh->rotation.x = -math::PI / 2; //Gjør slik at bakken blir helt flat
    groundMesh->position.y = 0;

    //Lager vei, for landskapet
    auto roadGeometry1 = PlaneGeometry::create(500, 20);
    auto roadMaterial1 = MeshStandardMaterial::create({{"color", Color::gray}});
    auto road1 = Mesh::create(roadGeometry1, roadMaterial1);
    road1->rotation.x = -math::PI / 2;
    road1->position.y = 0.01;
    road1->position.z = 0;
    roads.push_back(road1);

    //Vei 2
    auto roadGeometry2 = PlaneGeometry::create(500, 20);
    auto roadMaterial2 = MeshStandardMaterial::create({{"color", Color::gray}});
    auto road2 = Mesh::create(roadGeometry2, roadMaterial2);
    road2->rotation.x = -math::PI / 2;
    road2->position.y = 0.01;
    road2->position.z = 100;
    roads.push_back(road2);
}
