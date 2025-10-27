#include "keycontrolls.hpp"

#include "../cmake-build-debug/_deps/assimp-src/contrib/Open3DGC/o3dgcVector.h"

Key_controlls::Key_controlls(Object3D &obj) : obj_(&obj),
                                              initial_position_(obj.position),
                                              initial_rotation_(obj.quaternion) {
}

float Key_controlls::get_speed() const {
    return speed_;
}

int Key_controlls::get_direction_moved() const {
    if (key_state_.up) return 1;
    if (key_state_.down) return -1;
    return 0;
}
void Key_controlls::setLandscape(Landscape *land){
    landscape_ = land;
}


void Key_controlls::onKeyPressed(KeyEvent evt) {
    if (evt.key == Key::W) {
        key_state_.up = true;
    } else if (evt.key == Key::S) {
        key_state_.down = true;
    } else if (evt.key == Key::D) {
        key_state_.right = true;
    } else if (evt.key == Key::A) {
        key_state_.left = true;
    } else if (evt.key == Key::R) {
        //Legger til en reset kanpp for tanksen
        obj_->position.copy(initial_position_);
        obj_->quaternion.copy(initial_rotation_);
        std::cout << "Restarted position" << std::endl;
    }
}

void Key_controlls::onKeyReleased(KeyEvent evt) {
    if (evt.key == Key::W) {
        key_state_.up = false;
        key_state_.up = false;
    } else if (evt.key == Key::S) {
        key_state_.down = false;
    } else if (evt.key == Key::D) {
        key_state_.right = false;
    } else if (evt.key == Key::A) {
        key_state_.left = false;
    }
}

void Key_controlls::update(float dt) {
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

    Vector3 old_position = obj_->position;
    //bevegelse
    if (move_Direction != 0) obj_->translateX(-speed_ * move_Direction * dt);
    //rotasjon
    if (key_state_.right) obj_->rotateY(-angel_Speed_ * dt);
    if (key_state_.left) obj_->rotateY(angel_Speed_ * dt);

    if (landscape_) {
        Box3 bb;
        bb.setFromObject(*obj_);

        if (landscape_->check_collision_box(bb)) {
            obj_->position.copy(old_position);
        }

    }
}
