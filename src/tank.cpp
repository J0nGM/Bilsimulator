#include "tank.hpp"


#include "threepp/threepp.hpp"
using namespace threepp;

Tank::Tank(const std::string &path) {
        threepp::AssimpLoader loader;
        auto loadedGroup = loader.load(path);

        loadedGroup->traverseType<threepp::Mesh>([](threepp::Mesh& m) {
            m.receiveShadow = true;
            m.castShadow = true;
        });

        loadedGroup->scale.set(15.0f, 15.0f, 15.0f);
        loadedGroup->rotateY(threepp::math::PI); //Rotere tanksen 180 grader, for at W/S går riktig vei

        auto stripes_geomotry = threepp::BoxGeometry::create(0.1f, 0.01f, 0.1f);
        auto stripes_material = threepp::MeshStandardMaterial::create();
        stripes_material->color = threepp::Color::yellow;

        //Lager stripe for venstre side (fikk hjelpe av Ai for denne delen her)
        for (int i = 0; i < 20; ++i) {
            auto stripes = threepp::Mesh::create(stripes_geomotry, stripes_material);
            stripes->position.set(loadedGroup->position.x + 1.0f * (i * -0.1), loadedGroup->position.y, loadedGroup->position.z+0.6f);
            //stripes->position.set(-0.6f + i * stripe_length_ * 1.5f, 0.2f, -0.0f);
            stripes->rotateY(threepp::math::PI/2); //Roterer stripen 90 grader for å passe på høyre side
            left_stripes_.push_back(stripes);
            loadedGroup->add(stripes);
        }
        //Lager stripe for høyre side
        for (int i = 0; i < 20; ++i) {
            auto stripes = threepp::Mesh::create(stripes_geomotry, stripes_material);
            stripes->position.set(loadedGroup->position.x + 1.0f * (i * -0.1), loadedGroup->position.y, loadedGroup->position.z-0.6f);
            stripes->rotateY(threepp::math::PI/2); //Roterer stripen 90 grader for å passe på høyre side
            right_stripes_.push_back(stripes);
            loadedGroup->add(stripes);
        }
        add(loadedGroup);

    }


void Tank::update_stripes(double dt, float tank_speed, float dir) {
    if (tank_speed != 0) {  // Bare beveg stripene hvis tanksen beveger seg
        float movement = tank_speed * dt * 0.1f * -dir;  // Skalerer med tank hastighet

        for (auto& stripe : left_stripes_) {
            stripe->position.x -= movement;

            if (stripe->position.x - this->position.x < -1.0f) {
                stripe->position.x =  this->position.x +1;  // 20 striper * 0.4f avstand
            }
        }

        for (auto& stripe : right_stripes_) {
            stripe->position.x -= movement;

            if (stripe->position.x - this->position.x < -1.0f) {
                stripe->position.x =  this->position.x +1;
            }
        }
    }
}