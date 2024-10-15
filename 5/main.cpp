#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <thread>
#include <math.h>

const size_t catsFatiguePlusOnPLay = 37;
const size_t catsSatietyMinusOnPlay = 45;

const size_t dogsFatiguePlusOnPLay = 35;
const size_t dogsSatietyMinusOnPlay = 30;

const size_t animalsFatiguePlusOnPLayWithContact = 10;

const size_t agesRange[2] = {1, 10};
const size_t countActionsRange[2] = {80, 145};

const size_t onEatFromPersonSataietyPlus[2] = {10, 20};

const size_t minimalSatietyToEatFromPerson = 80;

class Animal {
 protected:
    std::string name;

    size_t age;
    size_t satiety = 70;
    size_t fatigue = 0;

    std::vector<Animal*> contactsWith;

    void setFatigue(size_t newFatigue) {
        if(newFatigue > 100) {
            newFatigue = 100;
        }
        if(newFatigue < 0) {
            newFatigue = 0;
        }
        fatigue = newFatigue;
    }

    void setSatiety(size_t newSatiety) {
        if(newSatiety > 100) {
            newSatiety = 100;
        }
        if(newSatiety < 0) {
            newSatiety = 0;
        }
        satiety = newSatiety;
    }

   public:
    Animal(std::string name, size_t age) : 
        name(name), age(age) {}

    bool IsNeededToSleep() {
        return fatigue > 80;
    }
    bool IsNeededToEat() {
        return satiety < 30;
    }

    std::string GetName() {
        return name;    
    }
    /*
    * Метод спать
    */
    bool GoToSleep() {
        if(!IsNeededToSleep()) {
            std::cout << name << " can't sleep\n";
            return false;
        }
        if(contactsWith.size() > 0) {
            std::cout << name << " can't sleep because of contacts\n";
            return false;
        }
        std::cout << name << " is sleeping\n";
        setFatigue(0);
        return true;
    }
    /*
    * Получить с кем контактирует животное
    */
    std ::vector<Animal*>* GetContactsWith() {
        return &contactsWith;
    }
    /*
    * Метод играть с другими животными
    */
    void PlayWithAnother(Animal* another) {
        if(another == this) {
            return;
        }
        for(auto contact : *GetContactsWith()) {
            if(contact == another) {
                return;
            }
        }
        contactsWith.push_back(another);
        for(auto contact : contactsWith) {
            contact->PlayWithAnother(another);
        }
        another->PlayWithAnother(this);
        setFatigue(fatigue + animalsFatiguePlusOnPLayWithContact);
        std::cout << name << " is playing with " << another->GetName() << "\n";
    }
    /*
    * Метод отписаться от игры с другими животными
    */
    void GoOutFromPlayingWithAnother(Animal* another = nullptr) {
        if(another == nullptr && contactsWith.size() == 0 ) {
          return;
        }
        if (another != nullptr) {
            for(auto contact : contactsWith) {
                contact->GoOutFromPlayingWithAnother(this);
            }

            for (size_t i = 0; i < contactsWith.size(); ++i) {
                if (contactsWith[i] == another) {
                    contactsWith.erase(contactsWith.begin() + i);
                    std::cout << name << " is out of playing with" << another->name << "\n";
                    break;
                }
            }
        }
        

        if(another == nullptr && contactsWith.size() > 0) {
            std::cout << name << " is out of playing with another\n";
            contactsWith.clear();
        }
        
    }
    /*
    * Метод есть от человека
    */
    void EatFromPerson() {
        if(satiety > minimalSatietyToEatFromPerson) {
            std::cout << name << " can't eat from person\n";
            return;
        }
        if(contactsWith.size() > 0) {
            std::cout << name << " can't eat from person because of contacts\n";
            return;
        }
        std::cout << name << " is eating from person\n";
        size_t satietyPlus = rand() % onEatFromPersonSataietyPlus[1] + onEatFromPersonSataietyPlus[0];
        setSatiety(satiety + satietyPlus);
    }
    /*
    * Метод есть
    */
    bool Eat() {
        if(!IsNeededToEat()) {
            std::cout << name << " can't eat\n";
            return false;
        }

        if(contactsWith.size() > 0) {
            std::cout << name << " can't eat because of contacts\n";
            return false;
        }

        std::cout << name << " is eating\n";
        setSatiety(100);
        return true;
    }

    virtual void Play(float intensivety) = 0;
    virtual void display() const = 0;
};

class Cat : public Animal {
   public:
    Cat(std::string name, size_t age) : Animal(name, age) {}
    /*
    * Метод играть
    */
    void Play(float intensivety) override {
        if(IsNeededToSleep() || IsNeededToEat()) {
            std::cout << name << " can't play\n";
            return;
        }

        if(contactsWith.size() > 0) {
            std::cout << name << " can't play because of contacts\n";
            return;
        }

        setFatigue(fatigue + floor(intensivety*catsFatiguePlusOnPLay));
        setSatiety(satiety - floor(intensivety*catsSatietyMinusOnPlay));
        std::cout << name << " is playing\n";
    }
    void display() const override {
        std::cout << "Cat: " << name << ", age: " << age << ", satiety: " << satiety << ", fatigue: " << fatigue << std::endl;
    }
};

class Dog : public Animal {
   public:
    Dog(std::string name, size_t age) : Animal(name, age) {}


    /*
    * Метод играть
    */
    void Play(float intensivety) override {
        if(IsNeededToSleep() || IsNeededToEat()) {
            std::cout << name << " can't play\n";
            return;
        }

        if(contactsWith.size() > 0) {
            std::cout << name << " can't play because of contacts\n";
            return;
        }

        setFatigue(fatigue + floor(intensivety*dogsFatiguePlusOnPLay));
        setSatiety(satiety - floor(intensivety*dogsSatietyMinusOnPlay));
        std::cout << name << " is playing\n";
    }

    void display() const override {
        std::cout << "Dog: " << name << ", age: " << age << ", satiety: " << satiety << ", fatigue: " << fatigue << std::endl;
    }
};

class ContactZoo {
 private:
    std::vector<Animal*> animals;
    std::vector<Animal*> catsRoom;
    std::vector<Animal*> dogsRoom;

    std::vector<Animal*> sleepingRoom;
    std::vector<Animal*> eatingRoom;

    float intensivety = 0.2;

    /*
    * Метод заполнения зоопарка
    */
    void FillZoo(size_t countAnimals) {
        for (size_t i = 0; i < countAnimals; ++i) {
            size_t animalAge = agesRange[0] + rand() % (agesRange[1] - agesRange[0]);
            if(i % 2 == 0) {
                AddAnimal(new Cat("Cat" + std::to_string(i), animalAge));
            } else {
                AddAnimal(new Dog("Dog" + std::to_string(i), animalAge));
            }
        }
    }
    /*
    * Метод изменения интенсивности посещения зоопарка
    */
    void SetIntensivety(float intensivety) {
        if(intensivety > 1) {
            intensivety = 1;
        } else if (intensivety < 0) {
            intensivety = 0;
        }
        this->intensivety = intensivety;
        std::cout << "Intensivety: " << intensivety << std::endl;
    }

    /*
    * Метод возвращения животного из специального вольера
    */
    void BackToOwnRoom(Animal* animal) {
        std::cout << animal->GetName() << " is back to own room" << std::endl;
        AddAnimal(animal);
    }

    /*
    * Эмуляция работы посетителя
    */
    void PersonAction(Animal* animal) {
        size_t action = rand() % 100;
        if(action > 80) {
            animal->EatFromPerson();
        } else {
            animal->Play(intensivety);
        }
    }

    /*
    * Эмулировать рандомную работу игры между животными
    */
    void AnimalsPlayWithAnother() {
        std::cout << "Animals play with another" << std::endl;
        size_t countActions = rand() % 3;
        // for dogs
        while (countActions > 0) {
            size_t actionPlay = rand() % 100; // < 60 - plays, >=60 - don't plays with another 
            if(actionPlay < 60) {
                size_t index = rand() % dogsRoom.size();
                Animal* animal = dogsRoom[index];
                size_t anotherIndex = rand() % dogsRoom.size();
                Animal* another = dogsRoom[anotherIndex];
                animal->PlayWithAnother(another);
                --countActions;
            } else {
                size_t index = rand() % dogsRoom.size();
                Animal* animal = dogsRoom[index];
                animal->GoOutFromPlayingWithAnother();
                --countActions;
            }
            
        }

        // for cats
        countActions = rand() % 3;
        while (countActions > 0) {
            size_t actionPlay = rand() % 100; // < 60 - plays, >=60 - don't plays with another 
            if(actionPlay < 60) {
                size_t index = rand() % catsRoom.size();
                Animal* animal = catsRoom[index];
                size_t anotherIndex = rand() % catsRoom.size();
                Animal* another = catsRoom[anotherIndex];
                animal->PlayWithAnother(another);
                --countActions;
            } else {
                size_t index = rand() % catsRoom.size();
                Animal* animal = catsRoom[index];
                animal->GoOutFromPlayingWithAnother();
                --countActions;
            }
        }

    }

    void DropFromRoom(Animal* animal, std::vector<Animal*> *room = nullptr) {
        if(!room) {
            for(size_t i = 0; i < animals.size(); ++i) {
                if(animals[i] == animal) {
                    animals.erase(animals.begin() + i);
                    break;
                }
            }
            std::vector<Animal*>* neededRoom;
            if(typeid(*animal) == typeid(Cat)) {
                neededRoom = &catsRoom;
            } else {
                neededRoom = &dogsRoom;
            }
            return DropFromRoom(animal, neededRoom);
        }
        
        for(size_t i = 0; i < room->size(); ++i) {
            if(room->at(i) == animal) {
                room->erase(room->begin() + i);
                break;
            }
        }
    }

 public:
    ContactZoo(size_t countAnimals) { FillZoo(countAnimals); }

    ~ContactZoo() {
        for (auto animal : animals) {
            delete animal;
        }
    }

    /*
    * Метод добавления животных
    */
    void AddAnimal(Animal* animal) {
        if(typeid(*animal) == typeid(Cat)) {
            catsRoom.push_back(static_cast<Cat*>(animal));
        } else if(typeid(*animal) == typeid(Dog)) {
            dogsRoom.push_back(static_cast<Dog*>(animal));
        }
        animals.push_back(animal);
    }

    /*
    * Отобразить список животных
    */
    void PrintAnimals() {
        for (auto animal : animals) {
            animal->display();
        }
    }

    /*
    * Метод для проведения инспекции зоопарка
    */
    void ConductAnInspection() {
        std::cout << "Zoo inspection" << std::endl;

        for (size_t i = 0; i < sleepingRoom.size(); ++i) {
            Animal* animal = sleepingRoom[i];
            // something checks
            BackToOwnRoom(animal);
            DropFromRoom(animal, &sleepingRoom);
        }

        for (size_t i = 0; i < eatingRoom.size(); ++i) {
            Animal* animal = eatingRoom[i];
            // something checks
            BackToOwnRoom(animal);
            DropFromRoom(animal, &eatingRoom);
        }

        for (size_t i = 0; i < animals.size(); ++i) {
            Animal* animal = animals[i];
            if(animal->IsNeededToEat()) {
                if(animal->Eat()) {
                    eatingRoom.push_back(animal);
                    DropFromRoom(animal);
                }
            } else if(animal->IsNeededToSleep()) {
                if(animal->GoToSleep()) {
                    sleepingRoom.push_back(animal);
                    DropFromRoom(animal);
                }
            } 
        }
    }

    /*
    * Эмулировать работу зоопарка
    */
    void WorkZoo() {
        size_t countActions = countActionsRange[0] + rand() % (countActionsRange[1] - countActionsRange[0]);
        
        while(countActions>0) {
            int action = rand() % 100; // 0-60 - person play with animal, 60-70 - set intensivety, 70-80 - animal play with another, >=80 - conduct an inspection
            if(action <60) {
                size_t animalIndex = rand() % animals.size();
                PersonAction(animals[animalIndex]);
            } else if(action>= 60 && action < 70) {
              float newIntensivityKoef = (action/(countActions/1.0));
              std::cout << "newIntensivityKoef = " << newIntensivityKoef << std::endl;
              if(countActions/2 > action) {
                SetIntensivety(intensivety + intensivety * newIntensivityKoef);
              } else {
                SetIntensivety(intensivety - intensivety * newIntensivityKoef);
              }
            } else if(action >= 70 && action < 80) {
                AnimalsPlayWithAnother();
            } else {
                ConductAnInspection();
            }
            std::thread([&]() {
              std::this_thread::sleep_for(std::chrono::seconds(2));
            }).join();

            --countActions;
        }
    }
};

/*
* Отобразить пользовательский сценарий
*/
void GetActions(ContactZoo* zoo) {
    int choice;
    do {
        std::cout << "\nSelect an action:\n";
        std::cout << "1. Print all animals\n";
        std::cout << "2. Conduct an inspection\n";
        std::cout << "3. Work zoo\n";
        std::cout << "0. Exit\n";
        std::cin >> choice;

        switch (choice) {
        case 1:
            zoo->PrintAnimals();
            break;
        case 2:
            zoo->ConductAnInspection();
            break;
        case 3:
            zoo->WorkZoo();
            break;
        default:
            break;
        }
    } while (choice != 0);
}

int main() {
    srand(time(nullptr));
    int countAnimals;
    std::cout << "Type count of animals: ";
    std::cin >> countAnimals;

    ContactZoo zoo = ContactZoo(countAnimals);

    GetActions(&zoo);

}