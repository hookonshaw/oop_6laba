#include <iostream>
#include <fstream>
#include <memory>
#include <set>
#include <random>
#include <string>
#include <sstream>

#include "npc.h"
#include "npc_factory.h"
#include "observer.h"
#include "fight_visitor.h"

using set_t = std::set<std::shared_ptr<NPC>>;

std::shared_ptr<NPC> factory(std::istream &is)
{
    return NPCFactory::create(is);
}

std::shared_ptr<NPC> factory(NpcType type, const std::string& name, int x, int y)
{
    std::cout << "Creating " << (int)type << " at (" << x << ", " << y << ")" << std::endl;
    return NPCFactory::create(type, name, x, y);
}

// save array to file
void save(const set_t &array, const std::string &filename)
{
    std::ofstream fs(filename);
    for (auto &n : array)
        NPCFactory::save(n, fs);
    fs.flush();
    fs.close();
    std::cout << "Saved " << array.size() << " NPCs to " << filename << std::endl;
}

set_t load(const std::string &filename)
{
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open())
    {
        std::string line;
        while (std::getline(is, line)) {
            std::istringstream iss(line);
            auto npc = factory(iss);
            if (npc) {
                result.insert(npc);
            }
        }
        is.close();
        std::cout << "Loaded " << result.size() << " NPCs from " << filename << std::endl;
    }
    else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const set_t &array)
{
    os << "NPCs count: " << array.size() << std::endl;
    for (auto &n : array) {
        os << n->getType() << " " << n->getName() 
           << " at (" << n->getX() << ", " << n->getY() << ")" 
           << " - " << (n->isAlive() ? "Alive" : "Dead") << std::endl;
    }
    return os;
}

set_t fight(const set_t &array, size_t distance, const std::shared_ptr<IFightObserver>& observer = nullptr)
{
    set_t dead_list;

    for (const auto &attacker : array) {
        if (!attacker->isAlive()) continue;
        
        for (const auto &defender : array) {
            if (!defender->isAlive()) continue;
            if (attacker == defender) continue;
            
            if (attacker->distanceTo(defender) <= distance) {
                auto visitor = std::make_shared<FightVisitor>(attacker, observer);
                bool success = defender->accept(visitor);
                
                if (success && defender->isAlive()) {
                    defender->kill();
                    dead_list.insert(defender);
                }
            }
        }
    }

    return dead_list;
}

std::string generateName(const std::string& type, int index) {
    return type + "_" + std::to_string(index);
}

int main()
{
    set_t array;
    auto text_observer = std::make_shared<TextObserver>();
    auto file_observer = std::make_shared<FileObserver>("battle_logs.txt");

    class CompositeObserver : public IFightObserver {
    private:
        std::vector<std::shared_ptr<IFightObserver>> observers;
    public:
        void addObserver(const std::shared_ptr<IFightObserver>& observer) {
            observers.push_back(observer);
        }
        
        void onFight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool success) override {
            for (auto& observer : observers) {
                observer->onFight(attacker, defender, success);
            }
        }
    };
    
    auto composite_observer = std::make_shared<CompositeObserver>();
    composite_observer->addObserver(text_observer);
    composite_observer->addObserver(file_observer);

    std::cout << "Generating ..." << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> type_dist(0, 2);
    std::uniform_int_distribution<> coord_dist(0, 100);
    
    for (size_t i = 0; i < 30; ++i) {
        NpcType type = static_cast<NpcType>(type_dist(gen));
        std::string type_name;
        switch (type) {
            case NpcType::Queen: type_name = "Queen"; break;
            case NpcType::Dragon: type_name = "Dragon"; break;
            case NpcType::KnightErrant: type_name = "Knight"; break;
        }
        
        array.insert(factory(type, generateName(type_name, i), 
                            coord_dist(gen), coord_dist(gen)));
    }

    std::cout << "Saving ..." << std::endl;
    save(array, "npc.txt");

    std::cout << "Loading ..." << std::endl;
    array = load("npc.txt");

    std::cout << "Initial state:" << std::endl << array << std::endl;

    std::cout << "Fighting ..." << std::endl;

    for (size_t distance = 20; (distance <= 100) && !array.empty(); distance += 10)
    {
        auto dead_list = fight(array, distance, composite_observer);
        for (auto &d : dead_list)
            array.erase(d);
            
        std::cout << "Fight stats ----------" << std::endl
                  << "distance: " << distance << std::endl
                  << "killed: " << dead_list.size() << std::endl
                  << "survivors: " << array.size() << std::endl
                  << std::endl;
    }

    std::cout << "Final survivors:" << std::endl << array;

    return 0;
}