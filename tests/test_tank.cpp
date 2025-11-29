#include "tank.hpp"
#include "bulletmanager.hpp"
#include "levelmanger.hpp"
#include "enemymanager.hpp"
#include "collisionmanger.hpp"
#include "threepp/threepp.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace threepp;

TEST_CASE("Tank creation") {
    Tank tank("../assets/3Dmodell/viecal/Tank.glb");

    // Check if the tank's mesh is created
    REQUIRE(tank.mesh != nullptr);
}

TEST_CASE("Moving forwards") {
    Tank tank("../assets/3Dmodell/viecal/Tank.glb");
    float start_in_Z = tank.mesh->position.z;
    tank.mesh->translateZ(1.0f); // Move forward

    REQUIRE(tank.mesh->position.z < start_in_Z);
}

TEST_CASE("Shooting bullets") {
    bullet_manager bullets;
    auto scene = Scene::create();

    bullets.spawn_bullet(*scene, Vector3(0, 0, 0), Vector3(1, 0, 0), 200.0f);

    REQUIRE(bullets.get_bullets().size() == 1);
}

TEST_CASE("Tree creation") {
    Landscape landscape;
    REQUIRE(landscape.objects.size() ==0 ); // To check if the landscape starts empty

    landscape.add_tree(Vector3(10, 0, 10));

    REQUIRE(landscape.objects.size() == 1); //Check if the tree is added
}

TEST_CASE("Tree destroyed") {
    auto scene = Scene::create();
    bullet_manager bullets;
    Landscape landscape;

    Vector3 tree_position(6, 0, 7);
    landscape.add_tree(tree_position);
    REQUIRE(landscape.objects[0]->visible == true);

    Vector3 bullet_direction(1, 0, 1);
    bullet_direction.normalize();

    Vector3 bullet_position = tree_position - bullet_direction;
    bullets.spawn_bullet(*scene, bullet_position, bullet_direction, 200.0f);

    bullets.update(0.02f);

    bool hit = collision_manager::check_bullet_tree_collision(
    bullets.get_bullets()[0]->get_position(),
    landscape.objects
);

    if (hit) {
        bullets.get_bullets()[0]->deactivate();
    }

    REQUIRE(hit);
    REQUIRE(landscape.objects[0]->visible == false);
}