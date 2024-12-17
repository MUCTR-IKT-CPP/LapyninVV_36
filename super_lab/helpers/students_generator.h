const std::vector<std::string> MOCK_MALE_LASTNAMES = {"Pipkin", "Petkin", "Grishin", "Fedorov", "Sidorov"};
const std::vector<std::string> MOCK_FEMALE_LASTNAMES = {"Pipkina", "Petkina", "Grishina", "Fedorova", "Sidorova"};
const std::vector<std::string> MOCK_MALE_FIRSTNAMES = {"Vasya", "Petya", "Grisha", "Kesha", "Fedya"};
const std::vector<std::string> MOCK_FEMALE_FIRSTNAMES = {"Masha", "Genya", "Sasha", "Ksusha", "Vera"};

class StudentsGenerator {
  public:
    static std::vector<Student*> Generate(const int count) {
        std::vector<Student*> students;
        for (int i = 0; i < count; i++) {
            int sex = rand() % 2; // male = 0, female = 1
            std::string firstName = sex == 0 ? MOCK_MALE_FIRSTNAMES[rand() % MOCK_MALE_FIRSTNAMES.size()] : MOCK_FEMALE_FIRSTNAMES[rand() % MOCK_FEMALE_FIRSTNAMES.size()];
            std::string lastName = sex == 0 ? MOCK_MALE_LASTNAMES[rand() % MOCK_MALE_LASTNAMES.size()] : MOCK_FEMALE_LASTNAMES[rand() % MOCK_FEMALE_LASTNAMES.size()];
            students.push_back(new Student(firstName, lastName));
        }
        return students;
    }
};