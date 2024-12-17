class SubjectsRepository: public CRUDRepository<Subject> {
  private:
    static SubjectsRepository* instance;
    SubjectsRepository() : CRUDRepository<Subject>() {}
  public:
    SubjectsRepository(const SubjectsRepository& other) = delete;

    static SubjectsRepository* GetInstance() { 
        if (instance == nullptr) {
            instance = new SubjectsRepository();
        }
        return instance;
    }
};

class StudentsRepository: public CRUDRepository<Student> {
  private:
    static StudentsRepository* instance;
    StudentsRepository() : CRUDRepository<Student>() {}
  public:
    StudentsRepository(const StudentsRepository& other) = delete;

    static StudentsRepository* GetInstance() {
        if (instance == nullptr) {
            instance = new StudentsRepository();
        }
        return instance;
    }
};

SubjectsRepository* SubjectsRepository::instance = nullptr;
StudentsRepository* StudentsRepository::instance = nullptr;