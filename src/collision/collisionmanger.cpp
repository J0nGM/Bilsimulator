#include "collisionmanger.hpp"
#include "arenawalls.hpp"
#include "obstecalelvl2.hpp"
#include <cmath>
#include <iostream>

using namespace threepp;

bool collision_manager::check_tree_collision(
    const Box3& box,
    const std::vector<std::shared_ptr<Group>>& trees) {
    
    for (const auto& tree : trees) {
        if (!tree->visible) continue;  // Skip destroyed trees
        
        Box3 tree_box;
        
        //Only use the first child (the trunk fo the tree) for the collosion, since it will not hit the leaves
        if (!tree->children.empty()) {
            auto trunk = tree->children[0];
            tree_box.setFromObject(*trunk);
        } else {
            tree_box.setFromObject(*tree);
        }
        
        //Shrink box so that it is possible to pass the trees a bit closer with ot getting stuck
        float shrink_amount = tree_collision_padding_;
        Vector3 min = tree_box.min();
        Vector3 max = tree_box.max();
        
        min.x += shrink_amount;
        min.z += shrink_amount;
        max.x -= shrink_amount;
        max.z -= shrink_amount;
        
        tree_box.set(min, max);
        
        if (box.intersectsBox(tree_box)) {
            return true;
        }
    }
    return false;
}

bool collision_manager::check_wall_collision(
    const Box3& box,
    const arenawalls& walls) {
    
    return walls.check_collision(box);
}

bool collision_manager::check_barrier_collision(
    const Box3& box,
    const obstacle_manger_lvl2& obstacles) {
    
    for (const auto& obstacle : obstacles.get_obstacles()) {
        Box3 obstacle_bb;
        obstacle_bb.setFromObject(*obstacle->get_mesh());
        
        if (box.intersectsBox(obstacle_bb)) {
            return true;
        }
    }
    return false;
}

bool collision_manager::check_bullet_tree_collision(
    const Vector3& bullet_pos,
    const std::vector<std::shared_ptr<Group>>& trees,
    float collision_distance) {

    //Insted of removing the tree, I just make it invisibal and then remove them when we go to lvl 2
    for (auto& tree : trees) {
        if (!tree->visible) continue;

        Vector3 tree_pos = tree->position;
        float distance = calculate_distance(bullet_pos, tree_pos);

        if (distance < bullet_tree_collision_distance_) {
            tree->visible = false;
            return true;
        }
    }
    return false;
}

bool collision_manager::check_bullet_enemy_collision(
    const Box3& bullet_box,
    const Box3& enemy_box) {

    return bullet_box.intersectsBox(enemy_box);
}

//Got som assistants from AI with the calculation of distance
float collision_manager::calculate_distance(
    const Vector3& pos1,
    const Vector3& pos2) {

    float dx = pos1.x - pos2.x;
    float dz = pos1.z - pos2.z;
    return std::sqrt(dx * dx + dz * dz);
}


//Check if the sphere goes beyond the arena walls
bool collision_manager::check_wall_collision_sphere(
    const Vector3& center,
    float radius,
    const arenawalls& arena) {

    float arena_size = arena.get_arena_size();

    if (center.x - radius < -arena_size || center.x + radius > arena_size ||
        center.z - radius < -arena_size || center.z + radius > arena_size) {
        return true;
        }
    return false;
}

bool collision_manager::check_barrier_collision_sphere(
    const Vector3& center,
    float radius,
    const obstacle_manger_lvl2& obstacles) {

    for (const auto& obstacle : obstacles.get_obstacles()) {
        Vector3 obstacle_pos = obstacle->get_mesh()->position;
        float distance = calculate_distance(center, obstacle_pos);

        if (distance < radius + barrier_collision_radius_) {
            return true;
        }
    }
    return false;
}