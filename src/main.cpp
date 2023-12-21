#include <iostream>
#include "game/World.h"
#include "engine/Application.h"
#include "game/Tank.h"
#include "game/Player.h"
#include "engine/Color.h"

int main(){
    Point worldSize{1280.f, 960.f};
    auto tank = Tank{Point{600.0f, 30.f}, graphs::Color::YellowOutline};
    auto player = Player{"Joe", std::move(tank)};

    Application app("Tanks", worldSize.x, worldSize.y);
    

    //DELETE
    //World world{worldSize};
    //World world{"../resources/maps/map_default.json"};
    World world{"../resources/maps/map_1.json"};
    
    if (world.addPlayer(player)) {
        std::cout << "Player Added" <<std::endl;
        world.setCurrentPlayerName(player.getName());
    }else {
        std::cout << "Player NOT Added" <<std::endl;
    }

    app.run(world);

    return 0;
}