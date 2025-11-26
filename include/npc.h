#pragma once

#include <memory>
#include <string>

class FightVisitor;
class IFightObserver;

class NPC {
protected:
    std::string name;
    int x, y;
    bool alive;

public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;

    virtual bool accept(const std::shared_ptr<FightVisitor>& attacker) = 0;
    
    virtual bool fight(const std::shared_ptr<class Queen>& other) = 0;
    virtual bool fight(const std::shared_ptr<class Dragon>& other) = 0;
    virtual bool fight(const std::shared_ptr<class KnightErrant>& other) = 0;

    std::string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    bool isAlive() const { return alive; }
    void kill() { alive = false; }

    double distanceTo(const std::shared_ptr<NPC>& other) const;

    virtual std::string getType() const = 0;
};

using NPCPtr = std::shared_ptr<NPC>;