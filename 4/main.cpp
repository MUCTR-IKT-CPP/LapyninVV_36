#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Character {
public:
    virtual void display() const = 0;
};

int stengthRangeForArcher[2] = { 7, 12 };
int durabilityRangeForArcher[2] = { 10, 20 };

int strengthRangeForMage[2] = { 10, 20 };
int durabilityRangeForMage[2] = { 5, 10 };

int stengthRangeForSwordsmanTank[2] = { 5, 10 };
int streigthRangeForSwordsmanUron[2] = { 7, 12 };
int durabilityRangeForSwordsman[2] = { 5, 10 };

int distanceRangeForAllTypes[2] = { 25, 50 };
int distanceRangeForAllTypesLongDistanse[2] = { 10, 30 };

int costRangeForAllTypes[2] = { 10, 20 };

class Swordsman {
private:
  int strength, durability, distance, cost;
  int role; // 0 - танк, 1 - значительный урон

public:
    Swordsman(int role) {
        if(role == 0) {
            strength = rand() % (stengthRangeForSwordsmanTank[1] - stengthRangeForSwordsmanTank[0] + 1) + stengthRangeForSwordsmanTank[0];
        } else {
            strength = rand() % (streigthRangeForSwordsmanUron[1] - streigthRangeForSwordsmanUron[0] + 1) + streigthRangeForSwordsmanUron[0];
        }
        durability = rand() % (durabilityRangeForSwordsman[1] - durabilityRangeForSwordsman[0] + 1) + durabilityRangeForSwordsman[0];
        distance = rand() % (distanceRangeForAllTypes[1] - distanceRangeForAllTypes[0] + 1) + distanceRangeForAllTypes[0];
        cost = rand() % (costRangeForAllTypes[1] - costRangeForAllTypes[0] + 1) + costRangeForAllTypes[0];
        role = role;
    }

    /*
    * Вывод
    */
    void display() const {
        std::cout << "Swordsman: Strength: " << strength << ", Durability: " << durability << ", Distance: " << distance << std::endl;
    }
};

class Mage {
private:
    int strength, durability, distance, cost;
    int type; // 0 - средняя дистанция, 1 - большая дистанция

   public:
    Mage(int type) {
        if(type == 0) {
            distance = rand() % (distanceRangeForAllTypes[1] - distanceRangeForAllTypes[0] + 1) + distanceRangeForAllTypes[0];
        } else {
            distance = rand() % (distanceRangeForAllTypesLongDistanse[1] - distanceRangeForAllTypesLongDistanse[0] + 1) + distanceRangeForAllTypesLongDistanse[0];
        }
        durability = rand() % (durabilityRangeForMage[1] - durabilityRangeForMage[0] + 1) + durabilityRangeForMage[0];
        strength = rand() % (strengthRangeForMage[1] - strengthRangeForMage[0] + 1) + strengthRangeForMage[0];
        cost = rand() % (costRangeForAllTypes[1] - costRangeForAllTypes[0] + 1) + costRangeForAllTypes[0];
        type = type;
    }

    /*
    * Вывод
    */
    void display() const{
        std::cout << "Mage: Strength: " << strength << ", Durability: " << durability << ", Distance: " << distance << std::endl;

    }
};

class Archer {
private:
    int strength, durability, distance, cost;
    int type; // 0 - средняя дистанция, 1 - большая дистанция

   public:
    Archer(int type) {
        if(type = 0) {
            distance = rand() % (distanceRangeForAllTypes[1] - distanceRangeForAllTypes[0] + 1) + distanceRangeForAllTypes[0];
        } else {
            distance = rand() % (distanceRangeForAllTypesLongDistanse[1] - distanceRangeForAllTypesLongDistanse[0] + 1) + distanceRangeForAllTypesLongDistanse[0];
        }
        durability = rand() % (durabilityRangeForArcher[1] - durabilityRangeForArcher[0] + 1) + durabilityRangeForArcher[0];
        strength = rand() % (stengthRangeForArcher[1] - stengthRangeForArcher[0] + 1) + stengthRangeForArcher[0];
        cost = rand() % (costRangeForAllTypes[1] - costRangeForAllTypes[0] + 1) + costRangeForAllTypes[0];

        type = type;
    }

    /*
    * Вывод
    */
    void display() const {
        std::cout << "Archer: Strength: " << strength << ", Durability: " << durability << ", Distance: " << distance << std::endl;
    }
};

class Mercenary {
public:
    void* character = nullptr;
    size_t type = 0; // Types : 1 - Tank Swordsman, 2 - Uron Swordman, 2 - Mage, 3 - Archer

    Mercenary(void* charPtr, size_t type) : character(charPtr), type(type) {};

    ~Mercenary() {
        delete character;
    }

    /*
    * Вывод
    */
    void display() const {
        if (type == 1) {
            static_cast<Swordsman*>(character)->display();
        } else if (type == 2) {
            static_cast<Mage*>(character)->display();
        } else {
            static_cast<Archer*>(character)->display();
        }
    }
};

class Guild {
private:
    std::vector<Mercenary*> mercenaries;
    std::vector<Mercenary*> group;
public:

    ~Guild() {
        for (auto merc : mercenaries) {
            delete merc;
        }
    }

    /*
    * Добавить наемника
    */
    void addMercenary(Mercenary* merc) {
        mercenaries.push_back(merc);
    }

    void addMercenary(Mercenary* merc, std::vector<Mercenary*> *mercsGroup) {
        mercsGroup->push_back(merc);
    }

    /*
    * Вывод наемников
    */
    void displayMercenaries() const {
      size_t number = 1;
      for (const auto& merc : mercenaries) {
        std::cout << number << ". ";
        merc->display();
        number++;
      }
    }

    void displayMercenaries(std::vector<Mercenary*> mercs) const {
        size_t number = 1;
        for (const auto& merc : mercs) {
            std::cout << number << ". ";
            merc->display();
            number++;
        }
    }

    void fillGroup() {
        size_t choice;

        do {
            std::cout << "\nSelect an action:\n";
            std::cout << "1. Print Group\n";
            std::cout << "2. Add mercenary to group\n";
            std::cout << "0. Exit\n";

            std::cin >> choice;

            if (choice == 1) {
                std::cout << "\nGroup: \n";
                displayMercenaries(group);
            } else if (choice == 2) {
                size_t mercNumber;
                std::cout << "Number of mercenary: ";
                std::cin >> mercNumber;
                addMercenary(mercenaries.at(mercNumber - 1), &group);
                std::cout << "Mercenary added to group\n";
            }
        } while (choice != 0);
    }

    /*
    * Генерация наемников
    */
    void generateRandomMercenaries() {
        addMercenary(new Mercenary(new Swordsman(0), 1)); 
        addMercenary(new Mercenary(new Swordsman(1), 1));
        addMercenary(new Mercenary(new Mage(0), 2)); 
        addMercenary(new Mercenary(new Mage(1), 2));
        addMercenary(new Mercenary(new Archer(0), 3));
        addMercenary(new Mercenary(new Archer(1), 3));

        for (int i = 0; i < 10; ++i) { 
            int type = rand() % 4 + 1; 
            if (type == 1) {
                addMercenary(new Mercenary(new Swordsman(rand() % 2), 1));
            } else if (type == 2) { 
                addMercenary(new Mercenary(new Mage(rand() % 2), 2));
            } else { 
                addMercenary(new Mercenary(new Archer(rand() % 2), 3));
            }
        }
    }
};

int main() {
    srand(time(0));

    Guild guild;
    guild.generateRandomMercenaries(); 

    std::cout << "List of all mercenaries:" << std::endl;
    guild.displayMercenaries();
    guild.fillGroup();
    return 0;
}