#ifndef TANK_GAMEMANGER_HPP
#define TANK_GAMEMANGER_HPP

#include <threepp/threepp.hpp>
#include <vector>
#include <memory>
#include <cmath>
#include "tank.hpp"
#include "keycontrolls.hpp"
#include "landscape.hpp"
#include "camercontrolls.hpp"
#include "boost.hpp"
#include "bullet.hpp"
#include "ammo.hpp"

class game_manger {
private:
    threepp::Scene& scene_;
    Tank& tank_;
    Key_controlls& key_controlls_;
    Landscape& landscape_;
    Camera_follow& camera_follow_;

    std::vector<std::unique_ptr<power_up_boost>> powerups_;
    std::vector<std::unique_ptr<ammo>> ammo_;
    std::vector<std::unique_ptr<bullet>> bullets_;


public:
    game_manger(
        threepp::Scene& scene,
        Tank& tank,
        Key_controlls& key_controls,
        Landscape& land,
        Camera_follow& camera_follow);

    void setup_powerups(int num_powerups);
    void setup_ammo(int num_ammo);
    void update(float dt);

private:
    void handle_tank_movement(float dt);
    void handle_shooting();
    void update_bullets(float dt);
    void cleanup_bullets();
    void handle_powerup_collisions();
    void handle_ammo_collisions();
    void bullet_collisions_with_tree();

    float calcualte_distance(
        const threepp::Vector3& pos1,
        const threepp::Vector3& pos2) {
        float dx = pos1.x - pos2.x;
        float dz = pos1.z - pos2.z;
        return std::sqrt(dx * dx + dz * dz);
    }

    threepp::Vector3 random_position(float range_x = 400.0f, float y = 3.0f, float range_z = 400.0f);

    //AI helped me created this funciton, so that it can be used for any object type
template<typename T>
    void spawn_item_pickup(std::vector<std::unique_ptr<T>>& container, int count) {
    for (int i = 0; i < count; i++) {
        auto pickup = std::make_unique<T>(random_position());
        scene_.add(pickup->getMesh());
        container.push_back(std::move(pickup));
    }
}

};

#endif //TANK_GAMEMANGER_HPP
