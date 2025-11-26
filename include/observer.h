#pragma once

#include <memory>
#include <iostream>
#include <fstream>

#include "npc.h"

class IFightObserver {
public:
    virtual ~IFightObserver() = default;
    virtual void onFight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool success) = 0;
};

class TextObserver : public IFightObserver {
public:
    void onFight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool success) override;
};

class FileObserver : public IFightObserver {
private:
    std::ofstream logfile;

public:
    FileObserver(const std::string& filename = "logs_of_battle.txt");
    ~FileObserver();
    
    void onFight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool success) override;
};