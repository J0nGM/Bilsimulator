#include "arenawalls.hpp"
#include <iostream>

using namespace threepp;

arena_walls::arena_walls() {

}
void arena_walls::create_single_wall(
    threepp::Scene& scene,
    std::shared_ptr<threepp::BufferGeometry> geometry,
    std::shared_ptr<threepp::Material> material,
    const threepp::Vector3& position) {

    auto wall = Mesh::create(geometry, material);
    wall->position.copy(position);
    wall->castShadow = true;
    wall->receiveShadow = true;
    wall->userData["isWall"] = true;

    walls_.push_back(wall);
    scene.add(wall);
}

void arena_walls::add_walls_to_scene(threepp::Scene &scene, float arena_size) {
    clear_walls(scene);

    //Had an issue with arena size not being set correctly, but this line fiex it
   arena_size_ = arena_size;
    //std::cout << "=== Arena size set to: " << arena_size_ << " ===" << std::endl; //for debugging

    float wall_length = arena_size * 2.0f;

    // Shared geometries
    auto horizontal_wall = BoxGeometry::create(wall_length, 20, 5);
    auto vertical_wall = BoxGeometry::create(5, 20, wall_length);

    // Shared material
    auto material = MeshPhongMaterial::create(
        {{"color", Color::gray},
            {"emissive", Color::darkgray},
            {"emissiveIntensity", 0.3f}});

    //Create four walls around the arena
    create_single_wall(scene, horizontal_wall, material, Vector3(0, 10, arena_size));    //North wall
    create_single_wall(scene, horizontal_wall, material, Vector3(0, 10, -arena_size));   //South wall
    create_single_wall(scene, vertical_wall, material, Vector3(arena_size, 10, 0));      //East wall
    create_single_wall(scene, vertical_wall, material, Vector3(-arena_size, 10, 0));     //West wall

    std::cout << "Added 4 walls to scene" << std::endl;
}

//Have to remove walls from level 1, have diffrent arena sizes in level 2
void arena_walls::clear_walls(threepp::Scene& scene) {
    for (auto& wall : walls_) {
        scene.remove(*wall);
    }
    walls_.clear();
}

bool arena_walls::check_collision(const threepp::Box3& box) const {
    for (const auto& wall : walls_) {
        threepp::Box3 wall_box;
        wall_box.setFromObject(*wall);

        if (box.intersectsBox(wall_box)) {
            return true;
        }
    }
    return false;
}
