#ifndef EXAM_TANK_HPP
#define EXAM_TANK_HPP

#pragma once //Fikk hjelp av AI for dettte
#include <threepp/threepp.hpp>
#include "threepp/loaders/AssimpLoader.hpp"

class Tank : public threepp::Object3D {
private:
public:
    std::shared_ptr<threepp::Mesh> mesh = threepp::Mesh::create();

    Tank(const std::string &path);
};

#endif //EXAM_TANK_HPP
