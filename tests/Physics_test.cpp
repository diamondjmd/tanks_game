#include <gtest/gtest.h>
//#include <gmock/gmock.h>

#include "../src/engine/Physics.h"  
#include "../src/engine/AnimationManager.h"  
#include "../src/game/Player.h"    
#include "../src/game/Bullet.h"    

// fixture for Physics tests
class PhysicsTest : public ::testing::Test {
protected:
    Physics physics;
    AnimationManager animationManager;
    std::unordered_map<std::string, Player> players;
    std::vector<Bullet> bullets;
    

    // Setup code specific
    void SetUp() override {
       
        Point worldSize(1280.0f, 960.0f);
        physics.setWorldBox(worldSize);

        auto playerStriker = Player{"Striker", Tank{Point{640.0f, 480.0f}}};
        auto playerTarget = Player{"Target", Tank{Point{1280.0f, 960.0f}}};
        // Add some players to the players map 
        players[playerStriker.getName()] = std::move(playerStriker);
        players[playerTarget.getName()] = std::move(playerTarget);
    }

    // Teardown code specific
    void TearDown() override {
        // Teardown code
    }
};


// Test the move function of the Physics class
// TEST_F(PhysicsTest, MoveBullets) {
//     // bullets
//     bullets.push_back(Bullet(players["Striker"].getTank().getPosition() , players["Target"].getTank().getPosition(),"Striker", players["Striker"].getTank().getRotation()));

//     float deltaTime = 1.f;
//     // Call the update function to test the move function
//     physics.update(players, bullets, animationManager, deltaTime);

//     // check the position of the bullet after the move function
//     Point finalPosition (640.8f, 480.6f);
//     EXPECT_EQ(bullets[0].getPosition() , finalPosition)  << "Bullet position: " << bullets[0].getPosition();

// }   



// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }