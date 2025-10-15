

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
    Vector3 initialPosition_;
    Quaternion initialRotation_;

    //Gir indikasjon på hvilken knapp som er trykket inn
    struct KeyState {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    } keyState_;

    float speed_ = 0.0f;
    float max_Speed_ = 20.0f;   //Farten på W/S
    float accleration_ = 10.0f;
    float deaccleration_ = 30.0f;

    float angel_Speed_ = 2.5f; //Farten på A/D

public:keycontrolls(Object3D& obj)
        : obj_(&obj),
        initialPosition_(obj.position),
        initialRotation_(obj.quaternion)  {}


    void onKeyPressed(KeyEvent evt) override {
    if (evt.key == Key::W) {
        keyState_.up = true;
    } else if (evt.key == Key::S) {
        keyState_.down = true;
    } else if (evt.key == Key::D) {
        keyState_.right = true;
    } else if (evt.key == Key::A) {
        keyState_.left = true;
    }else if (evt.key == Key::R) { //Legger til en reset kanpp for tanksen
        obj_->position.copy(initialPosition_);
        obj_->quaternion.copy(initialRotation_);
    }

    }

    void onKeyReleased(KeyEvent evt) override {
        if (evt.key == Key::W) {
            keyState_.up = false;
        } else if (evt.key == Key::S) {
            keyState_.down = false;
        } else if (evt.key == Key::D) {
            keyState_.right = false;
        } else if (evt.key == Key::A) {
            keyState_.left = false;
        }
    }



    void update(float dt) {
    int move_Direction = 0;
    if (keyState_.up) move_Direction = 1;
    else if (keyState_.down) move_Direction = -1;
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
    if (keyState_.right) obj_->rotateY(-angel_Speed_ *dt);
    if (keyState_.left) obj_->rotateY(angel_Speed_ *dt);
}
};
#endif //TANK_KEYCONTROLLS_HPP