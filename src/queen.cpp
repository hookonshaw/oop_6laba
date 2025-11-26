#include "queen.h"
#include "fight_visitor.h"

Queen::Queen(const std::string& name, int x, int y) : NPC(name, x, y) {

}

bool Queen::accept(const std::shared_ptr<FightVisitor>& attacker) {
    return attacker->visit(shared_from_this());
}

bool Queen::fight(const std::shared_ptr<Queen>& other) {
    return false;
}

bool Queen::fight(const std::shared_ptr<Dragon>& other) {
    return false;
}

bool Queen::fight(const std::shared_ptr<KnightErrant>& other) {
    return false;
}