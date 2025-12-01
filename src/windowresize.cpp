#include "windowresize.hpp"

using namespace threepp;

window_resize_handler::window_resize_handler(threepp::PerspectiveCamera &camera,
                                             threepp::GLRenderer &renderer) : camera_(camera), renderer_(renderer) {
}

void window_resize_handler::operator()(const threepp::WindowSize &size) {
    camera_.aspect = size.aspect();
    camera_.updateProjectionMatrix();
    renderer_.setSize(size);
}
