#include "knight_errant.h"
#include "fight_visitor.h"

KnightErrant::KnightErrant(const std::string& name, int x, int y) : NPC(name, x, y) {

}

bool KnightErrant::accept(const std::shared_ptr<FightVisitor>& attacker) {
    return attacker->visit(shared_from_this());
}

bool KnightErrant::fight(const std::shared_ptr<Queen>& other) {
    return false;
}

bool KnightErrant::fight(const std::shared_ptr<Dragon>& other) {
    return true;
}

bool KnightErrant::fight(const std::shared_ptr<KnightErrant>& other) {
    return false;
}