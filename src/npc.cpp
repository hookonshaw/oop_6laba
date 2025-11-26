#include "npc.h"

#include <cmath>

NPC::NPC(const std::string& name, int x, int y) 
    : name(name), x(x), y(y), alive(true) {}

double NPC::distanceTo(const std::shared_ptr<NPC>& other) const {
    if (!other) return 0;
    int dx = x - other->x;
    int dy = y - other->y;
    return std::sqrt(dx * dx + dy * dy);
}