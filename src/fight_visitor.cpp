#include "fight_visitor.h"
#include "observer.h"
#include "queen.h"
#include "dragon.h"
#include "knight_errant.h"

FightVisitor::FightVisitor(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<IFightObserver>& observer)
    : attacker(attacker), observer(observer) {}

bool FightVisitor::visit(const std::shared_ptr<Queen>& defender) {
    bool success = attacker->fight(defender);
    if (observer) {
        observer->onFight(attacker, defender, success);
    }
    return success;
}

bool FightVisitor::visit(const std::shared_ptr<Dragon>& defender) {
    bool success = attacker->fight(defender);
    if (observer) {
        observer->onFight(attacker, defender, success);
    }
    return success;
}

bool FightVisitor::visit(const std::shared_ptr<KnightErrant>& defender) {
    bool success = attacker->fight(defender);
    if (observer) {
        observer->onFight(attacker, defender, success);
    }
    return success;
}