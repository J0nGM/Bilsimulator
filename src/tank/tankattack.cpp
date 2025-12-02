#include "tankattack.hpp"

void tank_attack::add_ammo(int amount) {
    ammo_ = ammo_ + amount;
    //So that we don't go over max ammo
    if (ammo_ > max_ammo_) {
        ammo_ = max_ammo_;
    }
}


bool tank_attack::can_shoot() const {
    //check if cooldown is done and we have ammo left
    if (shoot_cooldown_ <= 0.0f && ammo_ > 0) {
        return true;
    }
    return false;
}

void tank_attack::start_cooldown() {
    shoot_cooldown_ = shoot_cooldown_time_;
}

void tank_attack::use_ammo() {
    //dont let ammo go negative
    if (ammo_ > 0) {
        ammo_--;
    }
}

void tank_attack::update(float dt) {
    //countdown the shoot cooldown timer
    if (shoot_cooldown_ > 0.0f) {
        shoot_cooldown_ = shoot_cooldown_ - dt;
    }
}
