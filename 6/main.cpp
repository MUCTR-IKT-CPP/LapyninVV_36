#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <cmath>
#include <string>
#include <map>

using namespace std;

// Constants
const int WARRIOR_HEALTH = 150;
const int ARCHER_HEALTH = 100;
const int MAGE_HEALTH = 80;
const int MIN_ARMOR = 1;
const int MAX_ARMOR = 20;
const int MIN_BONUS_DAMAGE = 1;
const int MAX_BONUS_DAMAGE = 8;
const int WARRIOR_MOVE_RANGE = 1;
const int ARCHER_MOVE_RANGE = 2;
const int MAGE_MOVE_RANGE = 2;
const int MIN_INITIATIVE = 1;
const int MAX_INITIATIVE = 20;
const int WARRIOR_ATTACK_RANGE = 1;
const int ARCHER_ATTACK_RANGE = 10;
const int MAGE_ATTACK_RANGE = 5;
const double WARRIOR_RATIO = 0.5;
const double ARCHER_RATIO = 0.3;
const int FIELD_SIZE = 10;
const int TEAM_SIZE = 10;

// Абстрактный класс бойца
class Fighter {
protected:
    int health;
    int maxHealth;
    int armor;
    int bonusDamage;
    int initiative;
    int moveRange;
    int x, y;  // Позиция на поле
    vector<pair<int, int>> battlePath;
    int damageDealt;
    int damageTaken;
    int kills;

public:
    /*
     * Конструктор класса Fighter
     *
     * @param health начальное здоровье бойца.
     * @param armor броня бойца.
     * @param bonusDamage бонусный урон бойца.
     * @param moveRange дальность передвижения бойца.
     */
    Fighter(int health, int armor, int bonusDamage, int moveRange)
        : health(health), maxHealth(health), armor(armor), bonusDamage(bonusDamage), moveRange(moveRange),
          damageDealt(0), damageTaken(0), kills(0) {
        initiative = rand() % (MAX_INITIATIVE - MIN_INITIATIVE + 1) + MIN_INITIATIVE;
        battlePath.push_back({x, y});
    }

    virtual ~Fighter() = default;

    /*
     * Виртуальный метод атаки
     *
     * @param target указатель на атакуемого бойца.
     */
    virtual void attack(Fighter* target) = 0;

    /*
     * Виртуальный метод получения дальности атаки
     *
     * @return возвращает дальность атаки бойца.
     */
    virtual int getAttackRange() const = 0;

    /*
     * Виртуальный метод получения типа бойца
     *
     * @return возвращает строку с типом бойца.
     */
    virtual string getType() const = 0;

    /*
     * Метод получения урона
     *
     * @param damage количество входящего урона.
     */
    void takeDamage(int damage) {
        int actualDamage = max(1, damage - armor);
        health = max(0, health - actualDamage);
        damageTaken += actualDamage;
    }

    /*
     * Проверка, жив ли боец
     *
     * @return возвращает true, если боец жив, иначе false.
     */
    bool isAlive() const { return health > 0; }

    /*
     * Получение значения инициативы бойца
     *
     * @return возвращает значение инициативы.
     */
    int getInitiative() const { return initiative; }

    /*
     * Установка новой позиции бойца
     *
     * @param newX новая координата X.
     * @param newY новая координата Y.
     */
    void setPosition(int newX, int newY) { 
        x = newX; 
        y = newY; 
        battlePath.push_back({x, y});
    }

    /*
     * Получение текущей позиции бойца
     *
     * @return возвращает пару координат (X, Y).
     */
    pair<int, int> getPosition() const { return {x, y}; }

    /*
     * Получение дальности передвижения бойца
     *
     * @return возвращает дальность передвижения.
     */
    int getMoveRange() const { return moveRange; }

    /*
     * Добавление нанесенного урона к статистике
     *
     * @param damage количество нанесенного урона.
     */
    void addDamageDealt(int damage) { damageDealt += damage; }

    /*
     * Увеличение счетчика убийств
     */
    void addKill() { kills++; }

    /*
     * Получение пути передвижения бойца
     *
     * @return возвращает вектор пар координат, представляющих путь бойца.
     */
    const vector<pair<int, int>>& getBattlePath() const { return battlePath; }

    /*
     * Получение общего нанесенного урона
     *
     * @return возвращает общее количество нанесенного урона.
     */
    int getDamageDealt() const { return damageDealt; }

    /*
     * Получение общего полученного урона
     *
     * @return возвращает общее количество полученного урона.
     */
    int getDamageTaken() const { return damageTaken; }

    /*
     * Получение количества убийств
     *
     * @return возвращает количество убийств.
     */
    int getKills() const { return kills; }

    /*
     * Получение текущего здоровья бойца
     *
     * @return возвращает текущее значение здоровья.
     */
    int getCurrentHealth() const { return health; }

    /*
     * Получение максимального здоровья бойца
     *
     * @return возвращает максимальное значение здоровья.
     */
    int getMaxHealth() const { return maxHealth; }
};

// Класс Воина (ближний бой)
class Warrior : public Fighter {
public:
    /*
     * Конструктор класса Warrior
     */
    Warrior() : Fighter(WARRIOR_HEALTH, rand() % (MAX_ARMOR - MIN_ARMOR + 1) + MIN_ARMOR, 
                        rand() % (MAX_BONUS_DAMAGE - MIN_BONUS_DAMAGE + 1) + MIN_BONUS_DAMAGE, WARRIOR_MOVE_RANGE) {}

    /*
     * Метод атаки воина
     *
     * @param target указатель на атакуемого бойца.
     */
    void attack(Fighter* target) override {
        int damage = rand() % (MAX_INITIATIVE - MIN_INITIATIVE + 1) + MIN_INITIATIVE + bonusDamage;
        target->takeDamage(damage);
        addDamageDealt(damage);
        if (!target->isAlive()) addKill();
    }

    /*
     * Получение дальности атаки воина
     *
     * @return возвращает дальность атаки воина.
     */
    int getAttackRange() const override { return WARRIOR_ATTACK_RANGE; }

    /*
     * Получение типа бойца
     *
     * @return возвращает строку "Warrior".
     */
    string getType() const override { return "Warrior"; }
};

// Класс Лучника (дальний бой)
class Archer : public Fighter {
public:
    /*
     * Конструктор класса Archer
     */
    Archer() : Fighter(ARCHER_HEALTH, rand() % (MAX_ARMOR - MIN_ARMOR + 1) + MIN_ARMOR, 
                       rand() % (MAX_BONUS_DAMAGE - MIN_BONUS_DAMAGE + 1) + MIN_BONUS_DAMAGE, ARCHER_MOVE_RANGE) {}

    /*
     * Метод атаки лучника
     *
     * @param target указатель на атакуемого бойца.
     */
    void attack(Fighter* target) override {
        int damage = rand() % (MAX_INITIATIVE - MIN_INITIATIVE + 1) + MIN_INITIATIVE + bonusDamage;
        target->takeDamage(damage);
        addDamageDealt(damage);
        if (!target->isAlive()) addKill();
    }

    /*
     * Получение дальности атаки лучника
     *
     * @return возвращает дальность атаки лучника.
     */
    int getAttackRange() const override { return ARCHER_ATTACK_RANGE; }

    /*
     * Получение типа бойца
     *
     * @return возвращает строку "Archer".
     */
    string getType() const override { return "Archer"; }
};

// Класс Мага (атака по области)
class Mage : public Fighter {
public:
    /*
     * Конструктор класса Mage
     */
    Mage() : Fighter(MAGE_HEALTH, rand() % (MAX_ARMOR - MIN_ARMOR + 1) + MIN_ARMOR, 
                     rand() % (MAX_BONUS_DAMAGE - MIN_BONUS_DAMAGE + 1) + MIN_BONUS_DAMAGE, MAGE_MOVE_RANGE) {}

    /*
     * Метод атаки мага
     *
     * @param target указатель на атакуемого бойца.
     */
    void attack(Fighter* target) override {
        int damage = rand() % (MAX_INITIATIVE - MIN_INITIATIVE + 1) + MIN_INITIATIVE + bonusDamage;
        target->takeDamage(damage);
        addDamageDealt(damage);
        if (!target->isAlive()) addKill();
        // Здесь можно добавить логику атаки по области
    }

    /*
     * Получение дальности атаки мага
     *
     * @return возвращает дальность атаки мага.
     */
    int getAttackRange() const override { return MAGE_ATTACK_RANGE; }

    /*
     * Получение типа бойца
     *
     * @return возвращает строку "Mage".
     */
    string getType() const override { return "Mage"; }
};

class Battlefield {
private:
    int fieldSize;
    vector<Fighter*> team1;
    vector<Fighter*> team2;
    vector<Fighter*> allFighters;
    int totalRounds;
    map<string, int> fighterTypeCount;

    /*
     * Вычисление расстояния между двумя бойцами
     *
     * @param f1 указатель на первого бойца.
     * @param f2 указатель на второго бойца.
     * @return возвращает манхэттенское расстояние между бойцами.
     */
    int calculateDistance(const Fighter* f1, const Fighter* f2) const {
        auto [x1, y1] = f1->getPosition();
        auto [x2, y2] = f2->getPosition();
        return abs(x1 - x2) + abs(y1 - y2);  // Манхэттенское расстояние
    }

    /*
     * Поиск ближайшего врага
     *
     * @param attacker указатель на атакующего бойца.
     * @param enemies вектор указателей на вражеских бойцов.
     * @return возвращает указатель на ближайшего врага или nullptr, если врагов нет.
     */
    Fighter* findNearestEnemy(Fighter* attacker, const vector<Fighter*>& enemies) const {
        Fighter* nearest = nullptr;
        int minDistance = INT_MAX;

        for (auto enemy : enemies) {
            if (enemy->isAlive()) {
                int distance = calculateDistance(attacker, enemy);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearest = enemy;
                }
            }
        }

        return nearest;
    }

    /*
     * Симуляция одного раунда битвы
     */
    void simulateBattleRound() {
        // Сортировка бойцов по инициативе
        sort(allFighters.begin(), allFighters.end(), [](const Fighter* a, const Fighter* b) {
            return a->getInitiative() > b->getInitiative();
        });

        for (auto fighter : allFighters) {
            if (!fighter->isAlive()) continue;

            vector<Fighter*>& enemyTeam = (find(team1.begin(), team1.end(), fighter) != team1.end()) ? team2 : team1;
            Fighter* target = findNearestEnemy(fighter, enemyTeam);

            if (target) {
                int distance = calculateDistance(fighter, target);
                if (distance <= fighter->getAttackRange()) {
                    fighter->attack(target);
                } else {
                    // Движение к цели
                    auto [targetX, targetY] = target->getPosition();
                    auto [fighterX, fighterY] = fighter->getPosition();
                    int dx = (targetX > fighterX) ? 1 : (targetX < fighterX) ? -1 : 0;
                    int dy = (targetY > fighterY) ? 1 : (targetY < fighterY) ? -1 : 0;
                    fighter->setPosition(fighterX + dx * fighter->getMoveRange(), fighterY + dy * fighter->getMoveRange());
                }
            }
        }
    }

    /*
     * Проверка окончания битвы
     *
     * @return возвращает true, если битва окончена, иначе false.
     */
    bool isBattleOver() const {
        auto teamAlive = [](const vector<Fighter*>& team) {
            return any_of(team.begin(), team.end(), [](const Fighter* f) { return f->isAlive(); });
        };
        return !teamAlive(team1) || !teamAlive(team2);
    }

public:
    /*
     * Конструктор класса Battlefield
     *
     * @param size размер поля битвы.
     * @param teamSize размер каждой команды.
     */
    Battlefield(int size, int teamSize) : fieldSize(size), totalRounds(0) {
        // Создание команд
        for (int i = 0; i < teamSize; ++i) {
            Fighter* fighter1;
            Fighter* fighter2;
            if (i < teamSize * WARRIOR_RATIO) {
                fighter1 = new Warrior();
                fighter2 = new Warrior();
                fighterTypeCount["Warrior"] += 2;
            } else if (i < teamSize * (WARRIOR_RATIO + ARCHER_RATIO)) {
                fighter1 = new Archer();
                fighter2 = new Archer();
                fighterTypeCount["Archer"] += 2;
            } else {
                fighter1 = new Mage();
                fighter2 = new Mage();
                fighterTypeCount["Mage"] += 2;
            }
            team1.push_back(fighter1);
            team2.push_back(fighter2);
        }

        allFighters.insert(allFighters.end(), team1.begin(), team1.end());
        allFighters.insert(allFighters.end(), team2.begin(), team2.end());

        // Расстановка бойцов на поле
        for (int i = 0; i < teamSize; ++i) {
            team1[i]->setPosition(0, i);
            team2[i]->setPosition(fieldSize - 1, i);
        }
    }

    /*
     * Деструктор класса Battlefield
     */
    ~Battlefield() {
        for (auto fighter : allFighters) {
            delete fighter;
        }
    }

    /*
     * Симуляция всей битвы
     */
    void simulateBattle() {
        while (!isBattleOver()) {
            simulateBattleRound();
            totalRounds++;
        }

        // Вывод результатов
        cout << "Battle ended on round " << totalRounds << "." << endl;
        if (all_of(team1.begin(), team1.end(), [](const Fighter* f) { return !f->isAlive(); })) {
            cout << "Team 2 wins!" << endl;
        } else {
            cout << "Team 1 wins!" << endl;
        }

        printBattleStatistics();
    }

    /*
     * Вывод статистики битвы
     */
    void printBattleStatistics() {
        cout << "\nBattle Statistics:" << endl;
        cout << "Total Rounds: " << totalRounds << endl;

        auto printTeamStats = [this](const vector<Fighter*>& team, const string& teamName) {
            cout << "\n" << teamName << " Statistics:" << endl;
            int totalDamageDealt = 0, totalDamageTaken = 0, totalKills = 0;
            int survivingFighters = 0;

            for (const auto& fighter : team) {
                cout << "\n" << fighter->getType() << " at position " << fighter->getPosition().first << "," << fighter->getPosition().second << ":" << endl;
                cout << "  Battle Path: ";
                for (const auto& pos : fighter->getBattlePath()) {
                    cout << "(" << pos.first << "," << pos.second << ") ";
                }
                cout << "\n  Damage Dealt: " << fighter->getDamageDealt() << endl;
                cout << "  Damage Taken: " << fighter->getDamageTaken() << endl;
                cout << "  Kills: " << fighter->getKills() << endl;
                cout << "  Final Health: " << fighter->getCurrentHealth() << "/" << fighter->getMaxHealth() << endl;

                totalDamageDealt += fighter->getDamageDealt();
                totalDamageTaken += fighter->getDamageTaken();
                totalKills += fighter->getKills();
                if (fighter->isAlive()) survivingFighters++;
            }

            cout << "\nTeam Summary:" << endl;
            cout << "  Total Damage Dealt: " << totalDamageDealt << endl;
            cout << "  Total Damage Taken: " << totalDamageTaken << endl;
            cout << "  Total Kills: " << totalKills << endl;
            cout << "  Surviving Fighters: " << survivingFighters << "/" << team.size() << endl;
        };

        printTeamStats(team1, "Team 1");
        printTeamStats(team2, "Team 2");

        cout << "\nFighter Type Distribution:" << endl;
        for (const auto& [type, count] : fighterTypeCount) {
            cout << "  " << type << ": " << count << endl;
        }
    }
};

int main() {
    srand(time(nullptr));
    Battlefield battlefield(FIELD_SIZE, TEAM_SIZE);
    battlefield.simulateBattle();
    return 0;
}
