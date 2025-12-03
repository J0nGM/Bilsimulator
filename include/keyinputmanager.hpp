#ifndef TANK_KEYINPUTHANDLER_HPP
#define TANK_KEYINPUTHANDLER_HPP

#include <threepp/threepp.hpp>

class key_input_handler : public threepp::KeyListener {
public:
    struct KeyState {
        bool up {false};
        bool down {false};
        bool left {false};
        bool right {false};
        bool space {false}; //boost key
        bool e {false}; //shoot key
        bool r {false}; //reset key
    };

    void onKeyPressed(threepp::KeyEvent evt) override;
    void onKeyReleased(threepp::KeyEvent evt) override;

    const KeyState& get_keys() const { return keys_; }

private:
    KeyState keys_;
};

#endif //TANK_KEYINPUTHANDLER_HPP
