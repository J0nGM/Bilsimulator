#ifndef EXAM_TANK_HPP
#define EXAM_TANK_HPP

#pragma once //Fikk hjelp av AI for dettte
#include <threepp/threepp.hpp>
#include "threepp/loaders/AssimpLoader.hpp"

class Tank: public threepp::Object3D {
private:
    std::vector<std::shared_ptr<threepp::Mesh>> left_stripes_;
    std::vector<std::shared_ptr<threepp::Mesh>> right_stripes_;
    float stripes_speed_ = 2.0f;
    float stripe_length_ = 1.0f;
    public:
    std::shared_ptr<threepp::Mesh> mesh = threepp::Mesh::create();

    Tank(const std::string& path);

    void update_stripes(double dt, float tank_speed, float dir);

 };

#endif //EXAM_TANK_HPP