#include <gtest/gtest.h>

#include "queen.h"
#include "dragon.h"
#include "knight_errant.h"
#include "fight_visitor.h"

class MockObserver : public IFightObserver {
public:
    bool fightObserved = false;
    std::shared_ptr<NPC> lastAttacker;
    std::shared_ptr<NPC> lastDefender;
    bool lastSuccess = false;

    void onFight(const std::shared_ptr<NPC>& attacker, 
                 const std::shared_ptr<NPC>& defender, 
                 bool success) override {
        fightObserved = true;
        lastAttacker = attacker;
        lastDefender = defender;
        lastSuccess = success;
    }
};

TEST(VisitorTest, FightRules) {
    // Правила боев на основе вашей реализации:
    // Dragon побеждает Queen
    // KnightErrant побеждает Dragon
    // Одинаковые типы не побеждают друг друга
    
    auto queen = std::make_shared<Queen>("Queen", 0, 0);
    auto dragon = std::make_shared<Dragon>("Dragon", 0, 0);
    auto knight = std::make_shared<KnightErrant>("Knight", 0, 0);

    // Dragon против Queen - dragon побеждает
    auto visitor1 = std::make_shared<FightVisitor>(dragon);
    EXPECT_TRUE(queen->accept(visitor1));

    // Knight против Dragon - knight побеждает
    auto visitor2 = std::make_shared<FightVisitor>(knight);
    EXPECT_TRUE(dragon->accept(visitor2));

    // Queen против Knight - queen проигрывает
    auto visitor3 = std::make_shared<FightVisitor>(queen);
    EXPECT_FALSE(knight->accept(visitor3));

    // Dragon против Dragon - ничья
    auto dragon2 = std::make_shared<Dragon>("Dragon2", 0, 0);
    auto visitor4 = std::make_shared<FightVisitor>(dragon);
    EXPECT_FALSE(dragon2->accept(visitor4));

    // Knight против Knight - ничья
    auto knight2 = std::make_shared<KnightErrant>("Knight2", 0, 0);
    auto visitor5 = std::make_shared<FightVisitor>(knight);
    EXPECT_FALSE(knight2->accept(visitor5));

    // Queen против Queen - ничья
    auto queen2 = std::make_shared<Queen>("Queen2", 0, 0);
    auto visitor6 = std::make_shared<FightVisitor>(queen);
    EXPECT_FALSE(queen2->accept(visitor6));
}

TEST(VisitorTest, ObserverNotification) {
    auto dragon = std::make_shared<Dragon>("Dragon", 0, 0);
    auto queen = std::make_shared<Queen>("Queen", 0, 0);
    auto observer = std::make_shared<MockObserver>();

    auto visitor = std::make_shared<FightVisitor>(dragon, observer);
    bool result = queen->accept(visitor);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(observer->fightObserved);
    EXPECT_TRUE(observer->lastSuccess);
    EXPECT_EQ(observer->lastAttacker, dragon);
    EXPECT_EQ(observer->lastDefender, queen);
}

TEST(VisitorTest, VisitorAttacker) {
    auto knight = std::make_shared<KnightErrant>("Knight", 0, 0);
    auto visitor = std::make_shared<FightVisitor>(knight);
    
    EXPECT_EQ(visitor->getAttacker(), knight);
}