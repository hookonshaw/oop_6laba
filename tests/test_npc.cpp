#include <gtest/gtest.h>

#include "npc.h"
#include "queen.h"
#include "dragon.h"
#include "knight_errant.h"

TEST(NPCTest, Creation) {
    auto queen = std::make_shared<Queen>("Queen1", 10, 20);
    auto dragon = std::make_shared<Dragon>("Dragon1", 30, 40);
    auto knight = std::make_shared<KnightErrant>("Knight1", 50, 60);

    EXPECT_EQ(queen->getName(), "Queen1");
    EXPECT_EQ(queen->getType(), "Queen");
    EXPECT_TRUE(queen->isAlive());

    EXPECT_EQ(dragon->getType(), "Dragon");
    EXPECT_EQ(knight->getType(), "KnightErrant");
}

TEST(NPCTest, Distance) {
    auto npc1 = std::make_shared<Queen>("Queen1", 0, 0);
    auto npc2 = std::make_shared<Queen>("Queen2", 3, 4);

    EXPECT_NEAR(npc1->distanceTo(npc2), 5.0, 0.001);
}

TEST(NPCTest, KillMethod) {
    auto queen = std::make_shared<Queen>("Queen1", 0, 0);
    EXPECT_TRUE(queen->isAlive());
    
    queen->kill();
    EXPECT_FALSE(queen->isAlive());
}

TEST(NPCTest, DistanceToNull) {
    auto queen = std::make_shared<Queen>("Queen1", 0, 0);
    double distance = queen->distanceTo(nullptr);
    EXPECT_EQ(distance, 0.0);
}