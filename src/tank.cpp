#include "tank.hpp"


#include "threepp/threepp.hpp"
using namespace threepp;

Tank::Tank(const std::string &path) {
    threepp::AssimpLoader loader;
    auto loadedGroup = loader.load(path);

    loadedGroup->traverseType<threepp::Mesh>([](threepp::Mesh &m) {
        m.receiveShadow = true;
        m.castShadow = true;
    });
    loadedGroup->scale.set(0.00001f, 0.00001f, 0.00001f);
    //loadedGroup->rotateY(threepp::math::PI); //Rotere tanksen 180 grader, for at W/S går riktig vei

    add(loadedGroup);
}
