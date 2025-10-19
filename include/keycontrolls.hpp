

#ifndef TANK_KEYCONTROLLS_HPP
#define TANK_KEYCONTROLLS_HPP

#include <iostream>
#include <threepp/threepp.hpp>
#include "threepp/loaders/AssimpLoader.hpp"
#include <iostream>
#include "threepp/input/KeyListener.hpp"
#include <cmath>
#include   "threepp/loaders/AssimpLoader.hpp"

using namespace threepp;


class keycontrolls: public KeyListener {

    private: Object3D* obj_;
    Vector3 initial_position_;
    Quaternion initial_rotation_;

    //Gir indikasjon på hvilken knapp som er trykket inn
    struct key_state {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    } key_state_;

    float speed_ = 0.0f;
    float max_Speed_ = 20.0f;   //Farten på W/S
    float accleration_ = 10.0f;
    float deaccleration_ = 30.0f;

    float angel_Speed_ = 2.5f; //Farten på A/D

public:keycontrolls(Object3D& obj)
        : obj_(&obj),
        initial_position_(obj.position),
        initial_rotation_(obj.quaternion)  {}

    //For å få delay på kamera, som jeg kan skal bruke i camercontrolls.hpp
    float get_speed() const {
    return speed_;
}

    int get_direction_moved () const {
    if (key_state_.up) return 1;
    if (key_state_.down) return -1;
    return 0;
}
    void onKeyPressed(KeyEvent evt) override {
    if (evt.key == Key::W) {
        key_state_.up = true;
    } else if (evt.key == Key::S) {
        key_state_.down = true;
    } else if (evt.key == Key::D) {
        key_state_.right = true;
    } else if (evt.key == Key::A) {
        key_state_.left = true;
    }else if (evt.key == Key::R) { //Legger til en reset kanpp for tanksen
        obj_->position.copy(initial_position_);
        obj_->quaternion.copy(initial_rotation_);
    }

    }

    void onKeyReleased(KeyEvent evt) override {
        if (evt.key == Key::W) {
            key_state_.up = false;
        } else if (evt.key == Key::S) {
            key_state_.down = false;
        } else if (evt.key == Key::D) {
            key_state_.right = false;
        } else if (evt.key == Key::A) {
            key_state_.left = false;
        }
    }



    void update(float dt) {
    int move_Direction = 0;
    if (key_state_.up) move_Direction = 1;
    else if (key_state_.down) move_Direction = -1;
    // Acceleration and deceleration
    if (move_Direction != 0) {
        speed_ += accleration_ * dt;
        if (speed_ > max_Speed_) speed_ = max_Speed_;
    } else {
        speed_ -= deaccleration_ * dt;
        if (speed_ < 0.0f) speed_ = 0.0f;
    }

    if (move_Direction != 0) obj_->translateX(-speed_ * move_Direction * dt);

    //rotasjon
    if (key_state_.right) obj_->rotateY(-angel_Speed_ *dt);
    if (key_state_.left) obj_->rotateY(angel_Speed_ *dt);
}
};
#endif //TANK_KEYCONTROLLS_HPP