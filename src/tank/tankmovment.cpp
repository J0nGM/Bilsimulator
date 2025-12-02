#include "tankmovment.hpp"

using namespace threepp;

tank_movement::tank_movement(Object3D &tank)
    : tank_(&tank) {
}

void tank_movement::add_boost() {
    boost_collected_++;
    boost_time_left_ += boost_duration_; //Stack amount of boost time
}

float tank_movement::get_boost_multiplier(bool boost_pressed) const {
    if (boost_pressed && boost_time_left_ > 0.0f) {
        return boost_multiplier_;
    }
    return 1.0f;
}

void tank_movement::update(const key_input_handler::KeyState &input, float dt, float speed_multiplier) {
    //This is to assist with the direction the movement of the tank is
    int move_direction = 0;
    if (input.up) move_direction = 1;
    else if (input.down) move_direction = -1;

    //Tried to make my own "smooth" Acceleration/deceleration. Got some assistanbse from AI here
    if (move_direction != 0) {
        speed_ += acceleration_ * dt;
        if (speed_ > max_speed_) speed_ = max_speed_;
    } else {
        speed_ -= deceleration_ * dt;
        if (speed_ < 0.0f) speed_ = 0.0f;
    }

    //Speed multiplier for when boost is active
    float actual_speed = speed_ * speed_multiplier;

    //Move forward/backward of the tank
    if (move_direction != 0) {
        tank_->translateX(-actual_speed * move_direction * dt);
    }

    //Rotation left/right
    if (input.right) tank_->rotateY(-turn_speed_ * dt);
    if (input.left) tank_->rotateY(turn_speed_ * dt);

    //When the boost is all used up then it stops reducing below 0
    if (input.space && boost_time_left_ > 0.0f) {
        boost_time_left_ -= dt;
        if (boost_time_left_ < 0.0f) boost_time_left_ = 0.0f;
    }
}