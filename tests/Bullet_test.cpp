#include "gtest/gtest.h"
#include "Bullet.h"
#include "../engine/Point.h"

class BulletTest : public testing::Test {
protected:
    Point<float> position;
    Point<float> target;
    Point<float> size;
    std::string texture;
    unsigned short speed; 
    unsigned short damage;
    
    void SetUp() override {
        position = Point<float>(10.0f, 20.0f);
        target= Point<float>(30.0f, 40.0f);
        texture = "bullet_texture.png";
        size = Point<float>(15.0f, 25.0f);
        speed = 5;
        damage = 30;

    }

    void TearDown() override {
        // Optional: Add any teardown code you want to run after each test
    }
};

TEST_F(BulletTest, ConstructorWithDefaultValues) {
    Bullet bullet(position, target, "Joe", controls::Action::Right);

    // Check if the bullet has the correct default values
    EXPECT_EQ(bullet.getPosition(), position);
    EXPECT_EQ(bullet.getDirection(), normalize(target - position));
    EXPECT_EQ(bullet.getDamage(), 20); // Default damage
    EXPECT_EQ(bullet.getSpeed(), 6);   // Default speed
    EXPECT_EQ(bullet.getSize(), Point<float>(10.0f, 20.0f)); // Default size
}

TEST_F(BulletTest, ConstructorWithCustomValues) {

   Bullet bullet(position, target,"Joe", controls::Action::Right, texture, size, speed, damage, graphs::Color::Beige);

    // Check if the bullet has the correct custom values
    EXPECT_EQ(bullet.getPosition(), position);
    EXPECT_EQ(bullet.getDirection(), normalize(target - position));
    EXPECT_EQ(bullet.getDamage(), damage);
    EXPECT_EQ(bullet.getSpeed(), speed);
    EXPECT_EQ(bullet.getSize(), size);
}

