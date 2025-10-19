#include <iostream>
#include <threepp/threepp.hpp>
#include "tank.hpp"
#include "threepp/materials/LineBasicMaterial.hpp"
#include "keycontrolls.hpp"
#include "landscape.hpp"
#include "WindowResize.hpp"
#include "camercontrolls.hpp"

int main() {
    using namespace threepp;
    Canvas canvas;
    GLRenderer renderer(canvas.size());

    PerspectiveCamera camera(45, canvas.aspect(), 0.1, 10000);
    camera.position.set(5, 6, -30);
   // OrbitControls controls{camera, canvas};

    //Gjør slik at man kan ha stort vindu
    WindowResizeHandler resizeHandler(camera, renderer);
    canvas.onWindowResize(resizeHandler);


    //Legger til lys
    auto light = HemisphereLight::create(0xffffbb, 0x080820);

    std::cout << std::filesystem::current_path();

    //For å lage scenen
    auto scene = Scene::create();
    scene->background = Color::aliceblue;
    scene->add(light);



    //Legger til tanksen i scenen
    Tank tank("../assets/Tank3.stl");
    tank.position.y = 0.25;
    scene->add(tank);
    camera_follow camera_follow(camera, tank, Vector3(60, 20, 0));

    //Landskap for at tanksen kan kjøre rundt
    landscape land;
    auto ground_mesh = land.groundMesh;
    ground_mesh->position.y = -0.5f;
    ground_mesh->receiveShadow = true;
    scene->add(ground_mesh);
    for (const auto& road : land.roads) {
        scene->add(road);
    }


    //Object3D obj;
    keycontrolls key_controls(tank); // Pass the tank's mesh
    canvas.addKeyListener(key_controls);
    std::cout << "Press 'r' to reset tank position. Use WASD keys to steer tank" << std::endl;

    Clock clock;
    canvas.animate([&] {
        double dt = clock.getDelta();
        key_controls.update(dt); //For å knappen av bevegsel til å oppdatere seg
        camera_follow.update(static_cast<float>(dt));

        renderer.render(*scene, camera);
    });

    return 0;
}