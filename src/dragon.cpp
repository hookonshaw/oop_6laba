#include "dragon.h"
#include "fight_visitor.h"

Dragon::Dragon(const std::string& name, int x, int y) : NPC(name, x, y) {

}

bool Dragon::accept(const std::shared_ptr<FightVisitor>& attacker) {
    return attacker->visit(shared_from_this());
}

bool Dragon::fight(const std::shared_ptr<Queen>& other) {
    return true;
}

bool Dragon::fight(const std::shared_ptr<Dragon>& other) {
    return false;
}

bool Dragon::fight(const std::shared_ptr<KnightErrant>& other) {
    return false;
}