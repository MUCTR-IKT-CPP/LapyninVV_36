class Subject {
  private:
    std::string name;
    TypeOfSubject typeOfSubject;
  public:
    Subject(std::string name, TypeOfSubject typeOfSubject) : name(name), typeOfSubject(typeOfSubject) {}
    std::string GetName() const { return name; }
    TypeOfSubject GetType() { return typeOfSubject; }
};