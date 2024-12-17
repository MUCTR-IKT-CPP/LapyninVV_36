class StudyGroup {
  private:
    std::string code;
    std::vector<Student*> students;
    std::vector<Subject*> requiredSubjects;
  public:
    StudyGroup(std::string code, std::vector<Student*> students, std::vector<Subject*> requiredSubjects) : code(code), students(students), requiredSubjects(requiredSubjects) {}
    void AddStudent(Student* student) { students.push_back(student); }
    void PrintStudents() const { for (auto student : students) student->Print(); }
    void FindStudent(size_t id) {}
    std::vector<Student*> GetStudents() { return students; }
    std::vector<Subject*> GetSubjects() { return requiredSubjects; }
};