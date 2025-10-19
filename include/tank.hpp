#ifndef EXAM_TANK_HPP
#define EXAM_TANK_HPP

#pragma once //Fikk hjelp av AI for dettte
#include <threepp/threepp.hpp>
#include "threepp/loaders/AssimpLoader.hpp"

class Tank: public threepp::Object3D {
public:
    std::shared_ptr<threepp::Mesh> mesh = threepp::Mesh::create();

    Tank(const std::string& path) {
        threepp::AssimpLoader loader;
        auto loadedGroup = loader.load(path);

        loadedGroup->traverseType<threepp::Mesh>([](threepp::Mesh& m) {
            m.receiveShadow = true;
            m.castShadow = true;
        });

        loadedGroup->scale.set(15.0f, 15.0f, 15.0f);
        loadedGroup->rotateY(threepp::math::PI); //Rotere tanksen 180 grader, for at W/S går riktig vei
        add(loadedGroup);
    }

};

#endif //EXAM_TANK_HPP