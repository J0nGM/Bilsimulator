#include "keyinputmanager.hpp"

using namespace threepp;

void key_input_handler::onKeyPressed(KeyEvent evt) {
    if (evt.key == Key::W) {
        keys_.up = true;
    }
    if (evt.key == Key::S) {
        keys_.down = true;
    }
    if (evt.key == Key::A) {
        keys_.left = true;
    }
    if (evt.key == Key::D) {
        keys_.right = true;
    }
    if (evt.key == Key::SPACE) {
        keys_.space = true;
    }
    if (evt.key == Key::E) {
        keys_.e = true;
    }
    if (evt.key == Key::R) {
        keys_.r = true;
    }
}

void key_input_handler::onKeyReleased(KeyEvent evt) {
    if (evt.key == Key::W) {
        keys_.up = false;
    }
    if (evt.key == Key::S) {
        keys_.down = false;
    }
    if (evt.key == Key::A) {
        keys_.left = false;
    }
    if (evt.key == Key::D) {
        keys_.right = false;
    }
    if (evt.key == Key::SPACE) {
        keys_.space = false;
    }
    if (evt.key == Key::E) {
        keys_.e = false;
    }
    if (evt.key == Key::R) {
        keys_.r = false;
    }
}
