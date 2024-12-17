class Student {
  private:
    static size_t lastId;
    size_t id;
    std::string firstName;
    std::string lastName;
  public:
    Student(std::string firstName, std::string lastName) : id(++lastId), firstName(firstName), lastName(lastName) { }

    void Print() const { std::cout << firstName << " " << lastName << std::endl; }
    std::string GetFullName() { return firstName + " " + lastName; }
};

size_t Student::lastId = 0;