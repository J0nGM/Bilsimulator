add_library(TankLib
        tank.cpp
        keycontrolls.cpp
        camercontrolls.cpp
        landscape.cpp
        WindowResize.cpp
        collision.cpp
        gamemanger.cpp
        powerups/boost.cpp
        powerups/bullet.cpp
        powerups/ammo.cpp
        level2/portalLVL2.cpp
        level2/landscape2.cpp
        level2/enemy.cpp
)

target_include_directories(TankLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TankLib PUBLIC threepp::threepp assimp::assimp)