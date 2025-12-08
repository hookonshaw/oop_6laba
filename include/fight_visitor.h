#pragma once

#include <memory>

#include "npc.h"
#include "observer.h"

class FightVisitor {
private:
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<IFightObserver> observer;

public:
    FightVisitor(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<IFightObserver>& observer = nullptr);
    
    
    bool visit(const std::shared_ptr<Queen>& defender);
    bool visit(const std::shared_ptr<Dragon>& defender);
    bool visit(const std::shared_ptr<KnightErrant>& defender);
    
    std::shared_ptr<NPC> getAttacker() const { return attacker; }
};