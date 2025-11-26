#include "npc_factory.h"
#include "dragon.h"
#include "queen.h"
#include "knight_errant.h"

std::shared_ptr<NPC> NPCFactory::create(NpcType type, const std::string& name, int x, int y) {
    switch (type) {
        case NpcType::Queen:
            return std::make_shared<Queen>(name, x, y);
        case NpcType::Dragon:
            return std::make_shared<Dragon>(name, x, y);
        case NpcType::KnightErrant:
            return std::make_shared<KnightErrant>(name, x, y);
        default:
            return nullptr;
    }
}

std::shared_ptr<NPC> NPCFactory::create(std::istream& is) {
    std::string type, name;
    int x, y;
    
    if (is >> type >> name >> x >> y) {
        if (type == "Queen") {
            return std::make_shared<Queen>(name, x, y);
        } else if (type == "Dragon") {
            return std::make_shared<Dragon>(name, x, y);
        } else if (type == "KnightErrant") {
            return std::make_shared<KnightErrant>(name, x, y);
        }
    }
    return nullptr;
}

void NPCFactory::save(const std::shared_ptr<NPC>& npc, std::ostream& os) {
    if (npc) {
        os << npc->getType() << " " << npc->getName() << " " << npc->getX() << " " << npc->getY() << "\n";
    }
}