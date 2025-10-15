
#ifndef TANK_CAMERA_HPP
#define TANK_CAMERA_HPP

#include <threepp/threepp.hpp>


// C++
class WindowResizeHandler {

    public:
    WindowResizeHandler(threepp::PerspectiveCamera& camera, threepp::GLRenderer& renderer)
        : camera_(camera), renderer_(renderer) {}

    void operator()(const threepp::WindowSize& size) {
        camera_.aspect = size.aspect();
        camera_.updateProjectionMatrix();
        renderer_.setSize(size);
    }

private:
    threepp::PerspectiveCamera& camera_;
    threepp::GLRenderer& renderer_;
};

#endif //TANK_CAMERA_HPP