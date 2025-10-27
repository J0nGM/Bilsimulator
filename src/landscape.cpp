#include "landscape.hpp"
#include "threepp/loaders/AssimpLoader.hpp"

using namespace threepp;

//Slik at jeg kan endre høyden på træerene. Kansje rydde opp i den funksjonen seinre.
Landscape::Landscape() {
    groundMesh->rotation.x = -math::PI / 2; //Gjør slik at bakken blir helt flat
    groundMesh->position.y = 0;

    //Lager vei, for landskapet
    auto roadGeometry1 = PlaneGeometry::create(500, 20);
    auto roadMaterial1 = MeshStandardMaterial::create({{"color", Color::gray}});
    auto road1 = Mesh::create(roadGeometry1, roadMaterial1);
    road1->rotation.x = -math::PI / 2;
    road1->position.y = 0.01;
    road1->position.z = 0;
    roads.push_back(road1);

    //Vei 2
    auto roadGeometry2 = PlaneGeometry::create(500, 20);
    auto roadMaterial2 = MeshStandardMaterial::create({{"color", Color::gray}});
    auto road2 = Mesh::create(roadGeometry2, roadMaterial2);
    road2->rotation.x = -math::PI / 2;
    road2->position.y = 0.01;
    road2->position.z = 100;
    roads.push_back(road2);
}

    void Landscape::add_tree(threepp::Vector3 position) {
        auto tree = threepp::Group::create();

        auto tree_log_geometry = threepp::CylinderGeometry::create(tree_log_radius_, tree_log_radius_, tree_log_height_);
        auto tree_log_material = threepp::MeshStandardMaterial::create({{"color", threepp::Color::brown}});
        auto tree_log = threepp::Mesh::create(tree_log_geometry, tree_log_material);
        tree_log->position.y= tree_log_height_ *0.5f;


        tree_log->castShadow = true;
        tree_log->receiveShadow = true;
        tree->add(tree_log);

        auto tree_cone_geometry = threepp::ConeGeometry::create(
            height_tree_ * cone_width_,
            height_tree_ * cone_height_,
            8
            );
        auto tree_cone_material = threepp::MeshStandardMaterial::create({{"color", threepp::Color::green}});
        auto tree_cone = threepp::Mesh::create(tree_cone_geometry, tree_cone_material);
        tree_cone->castShadow = true;
        tree_cone->receiveShadow = true;
        tree_cone->position.y = height_tree_ + (height_tree_ * cone_height_ * 0.6f); //Ender høyden på stammen
        tree->add(tree_cone);

        tree->position.copy(position);
        objects.push_back(tree);
}

bool Landscape::check_collision_box(threepp::Box3 tank_box) {
    for (const auto&tree : objects){
        if (!tree->children.empty()) {
            auto trunk = tree->children[0];

            Box3 trunk_box;
            trunk_box.setFromObject(*trunk);

            float shrink_amount = 8.0f;
            Vector3 min = trunk_box.min();
            Vector3 max = trunk_box.max();

            min.x += shrink_amount;
            min.z += shrink_amount;
            max.x -= shrink_amount;
            max.z -= shrink_amount;

            trunk_box.set(min, max);

            if (tank_box.intersectsBox(trunk_box)) {
                std::cout << "Collision detected!" << std::endl;
                return true;

            }
        }
    }
    return false;
}