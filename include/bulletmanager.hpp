#ifndef TANK_BULLET_MANAGER_HPP
#define TANK_BULLET_MANAGER_HPP

#include "threepp/threepp.hpp"
#include "bullet.hpp"
#include <vector>
#include <memory>

class bullet_manager {
private:
    std::vector<std::unique_ptr<bullet> > bullets_;

public:
    void spawn_bullet(
        threepp::Scene &scene,
        const threepp::Vector3 &position,
        const threepp::Vector3 &direction,
        float speed);

    void update(float dt);

    void cleanup(threepp::Scene &scene);

    void clear(threepp::Scene &scene);

    const std::vector<std::unique_ptr<bullet> > &get_bullets() const { return bullets_; }
};

#endif
