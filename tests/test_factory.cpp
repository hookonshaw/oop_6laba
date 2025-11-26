#include <gtest/gtest.h>
#include <sstream>
#include "npc_factory.h"

TEST(FactoryTest, CreateNPC) {
    auto queen = NPCFactory::create(NpcType::Queen, "TestQueen", 10, 20);
    auto dragon = NPCFactory::create(NpcType::Dragon, "TestDragon", 30, 40);
    auto knight = NPCFactory::create(NpcType::KnightErrant, "TestKnight", 50, 60);

    EXPECT_NE(queen, nullptr);
    EXPECT_NE(dragon, nullptr);
    EXPECT_NE(knight, nullptr);

    EXPECT_EQ(queen->getType(), "Queen");
    EXPECT_EQ(dragon->getType(), "Dragon");
    EXPECT_EQ(knight->getType(), "KnightErrant");
}

TEST(FactoryTest, Serialization) {
    auto queen = NPCFactory::create(NpcType::Queen, "TestQueen", 10, 20);
    
    std::stringstream ss;
    NPCFactory::save(queen, ss);
    
    auto loaded = NPCFactory::create(ss);
    
    EXPECT_NE(loaded, nullptr);
    EXPECT_EQ(loaded->getType(), "Queen");
    EXPECT_EQ(loaded->getName(), "TestQueen");
    EXPECT_EQ(loaded->getX(), 10);
    EXPECT_EQ(loaded->getY(), 20);
}

TEST(FactoryTest, InvalidType) {
    std::stringstream ss("InvalidType Name 1 2");
    auto npc = NPCFactory::create(ss);
    EXPECT_EQ(npc, nullptr);
}