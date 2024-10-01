#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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

int distanceRangeForAllTypes[2] = { 10, 50 };
int distanceRangeForAllTypesLongDistanse[2] = { 50, 100 };

int costRangeForAllTypes[2] = { 10, 20 };

class Swordsman {
private:
  int strength, durability, distance, cost;
  int role; // 0 - танк, 1 - значительный урон

public:
    /*
    * Вывод
    */
    void display() const {
        std::cout << "Swordsman: Strength: " << strength << ", Durability: " << durability << ", Distance: " << distance << ", Cost: " << cost << std::endl;
    }
    int globalType = 1;

    int getCost() {
        return cost;
    }

    int getDurability() {
        return durability;
    }
    int getDistance() {
        return distance;
    }

    int getStrength() {
        return strength;
    }
    
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

};

class Mage {
private:
    int strength, durability, distance, cost;
    int type; // 0 - средняя дистанция, 1 - большая дистанция

   public:
    int globalType = 2;
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
        std::cout << "Mage: Strength: " << strength << ", Durability: " << durability << ", Distance: " << distance << ", Cost: " << cost << std::endl;

    }
};

class Archer {
private:
    int strength, durability, distance, cost;
    int type; // 0 - средняя дистанция, 1 - большая дистанция

   public:
    int globalType = 3;
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
        std::cout << "Archer: Strength: " << strength << ", Durability: " << durability << ", Distance: " << distance << ", Cost: " << cost << std::endl;
    }
};

class Mercenary {
public:
    void* character = nullptr;
    size_t type = 0; // Types : 1 - Tank Swordsman, 2 - Mage, 3 - Archer

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

    /*
    * Проверка на то, является ли группа идеальной
    */
    bool checkForIdealGroup(std::vector<Swordsman*> mercsGroup, size_t minCountInGroup) {
        if(mercsGroup.size() < minCountInGroup) {
          return false;
        }
        size_t sumDurability = 0;
        size_t sumStrength = 0;
        size_t sumCost = 0;

        for (const auto& merc : mercsGroup) {
            sumDurability += merc->getDurability();
            sumStrength += merc->getStrength();
            sumCost += merc->getCost();
        }

        if (sumDurability < sumStrength) {
          return false;
        }
        return true;
    }

    /*
    * Вывод любой группы
    */
    void displayMercenaries(std::vector<Mercenary*> mercs) const {
        size_t number = 1;
        for (const auto& merc : mercs) {
            std::cout << number << ". ";
            merc->display();
            number++;
        }
    }
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

    
    /*
    * Вывод группы 
    */
    void displayGroup() const {
        displayMercenaries(group);
    }

    /*
    * Суммарная стоимость группы
    */
    size_t sumGroupCost(std::vector<Swordsman*> mercGroup) const {
        size_t sum = 0;
        for (const auto& merc : mercGroup) {
            sum += merc->getCost();
        }
        return sum;
    }

    /*
     * Нахождение группы с максимальной силой
     */
    std::vector<Swordsman*> findMaxSumStreingth(std::vector<Swordsman*> mercs1, std::vector<Swordsman*> mercs2) const {
        size_t sum1 = 0;
        size_t sum2 = 0;
        
        for (const auto& merc : mercs1) {
            sum1 += merc->getStrength();
        }
        for (const auto& merc : mercs2) {
            sum2 += merc->getStrength();
        }
        return sum1 > sum2 ? mercs1 : mercs2;
    }

    /*
    * Заполнение группы
    */
    void fillGroup() {
        size_t choice;

        do {
            std::cout << "\nSelect an action:\n";
            std::cout << "1. Print Group\n";
            std::cout << "2. Add mercenary to group\n";
            std::cout << "0. Exit\n";

            std::cin >> choice;

            if (choice == 1) {
                std::cout << "\nYour group: \n";
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
    * Генерация идеальной группы
    */
    void generateIdealGroup(size_t maxCost) {
        group.clear();
        const size_t currentMercsSize = mercenaries.size();
        const size_t minCountInGroup = 5;

        float horizontalHashes[currentMercsSize];
        Swordsman* verticalHashes[currentMercsSize];

        std::vector<Swordsman*> hashTable[currentMercsSize][currentMercsSize];

        for (int i = 0; i < currentMercsSize; i++) {
            horizontalHashes[i] = float(maxCost) / currentMercsSize * (i+1);
            verticalHashes[i] = static_cast<Swordsman*>(mercenaries.at(i)->character);
        } 

        
        for(int i = 0; i < currentMercsSize; i++) {
            for(int j = 0; j < currentMercsSize; j++) {
                std::vector<Swordsman*> tmpGroup = std::vector<Swordsman*> {verticalHashes[0]};

                if(i == 0 && j == 0) {
                    if(sumGroupCost(tmpGroup) <= maxCost) {
                        hashTable[i][j] = tmpGroup;
                    } else {
                      hashTable[i][j] = {};
                    }
                    continue;
                } else if (i!=0 && j==0) {
                    tmpGroup = hashTable[i-1][j];
                    tmpGroup.push_back(verticalHashes[i]);
                    if(sumGroupCost(tmpGroup) <= maxCost) {
                        hashTable[i][j] = tmpGroup;
                    } else {
                        hashTable[i][j] = hashTable[i-1][j];
                    }
                    tmpGroup.clear();
                    continue;
                } else if(i==0 && j!=0) {
                    if(hashTable[i][j].size() == 0 && sumGroupCost(tmpGroup)) {
                      hashTable[i][j] = tmpGroup;
                    } else {
                        hashTable[i][j] = hashTable[i][j-1];
                    }
                    continue;
                }
                tmpGroup = hashTable[i-1][j-1];
                tmpGroup.push_back(verticalHashes[i]);
                if(sumGroupCost(tmpGroup) <= maxCost) {
                    hashTable[i][j] = findMaxSumStreingth(hashTable[i-1][j], tmpGroup);
                } else {
                    tmpGroup = hashTable[i][j-1];
                    tmpGroup.push_back(verticalHashes[i]);
                    if(sumGroupCost(tmpGroup) <= maxCost) {
                        hashTable[i][j] = findMaxSumStreingth(hashTable[i][j-1], tmpGroup);
                    } else {
                        hashTable[i][j] = findMaxSumStreingth(hashTable[i-1][j], hashTable[i][j-1]);
                    }
                }
                tmpGroup.clear();
            }
        }

        
        if(!checkForIdealGroup(hashTable[currentMercsSize - 1][currentMercsSize - 1], minCountInGroup)) {
            std::cout << "Can't generate ideal group\n";
            return;
        } else {
            for(size_t i = 0; i < hashTable[currentMercsSize - 1][currentMercsSize - 1].size(); i++) {
                Swordsman* merc = hashTable[currentMercsSize - 1][currentMercsSize - 1].at(i);
                addMercenary(new Mercenary(merc, merc->globalType), &group);
            }
            std::cout << "Ideal group generated\n";
        }
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

/*
* Отобразить пользовательский сценарий
*/
void getActions(Guild * guild) {
    int choice;

    do {
        std::cout << "\nSelect an action:\n";
        std::cout << "1. Print all Mercenaries\n";
        std::cout << "2. Generate Ideal Group\n";
        std::cout << "3. Fill Group\n";
        std::cout << "4. Print Group\n";
        std::cout << "0. Exit\n";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "List of all mercenaries:" << std::endl;
            guild->displayMercenaries();
        } else if (choice == 2) {
            guild->generateIdealGroup(150);
        } else if (choice == 3) {
            guild->fillGroup();
        } else if (choice == 4) {
            std::cout << "Your group:\n";
            guild->displayGroup();
        }
    } while(choice != 0);
}

int main() {
    srand(time(0));

    Guild guild;
    guild.generateRandomMercenaries(); 

    getActions(&guild);
    return 0;
}