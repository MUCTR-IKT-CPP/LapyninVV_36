#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <ctime>
#include "include.h"
#include <map>
#include <math.h>
#include <sstream>
#include "StreamTable.h"

const size_t MAX_SUM_OF_CONTROL_POINTS_FOR_EXAM = 60;
const size_t MAX_SUM_OF_CONTROL_POINTS_FOR_TEST_WITH_MARK = 60;
const size_t MAX_SUM_OF_CONTROL_POINTS_FOR_TEST = 100;

const size_t MAX_EXAM_MARK = 40;

const size_t DEBAULT_COUNT_OF_CONTROL_POINTS = 3;

const size_t DOBOR_OF_CONTROL_POINTS = 30;

const size_t MIN_EXAM_MARK = 20;

const size_t MIN_MARK_FOR_TEST = 50;

const size_t EXAM_MARK_3[2] = {50, 74};
const size_t EXAM_MARK_4[2] = {75, 84};
const size_t EXAM_MARK_5[2] = {85, 100};


size_t GetMarkByPercents(size_t percent) { 
    if(percent >= EXAM_MARK_3[0] && percent <= EXAM_MARK_3[1]) {
        return 3;
    } else if(percent >= EXAM_MARK_4[0] && percent <= EXAM_MARK_4[1]) {
        return 4;
    } else if(percent >= EXAM_MARK_5[0] && percent <= EXAM_MARK_5[1]) {
        return 5;
    }
    return std::numeric_limits<size_t>::quiet_NaN();
}

class ControlPoint {
  private:
    int number;
    int maxScore;
  public:
    ControlPoint(int number, int maxScore): number(number), maxScore(maxScore) {}
    int GetNumber() { return number; }
    int GetMaxScore() { return maxScore; }
};

class JournalSubject {
  private:
    Subject* subject;
    std::vector<ControlPoint*> controlPoints;

    void _AddControlPoint(int maxScore) {
        TypeOfSubject type = subject->GetType();
        int currentSum = GetSumCurrentControlPoints();
        if (type == EXAM && MAX_SUM_OF_CONTROL_POINTS_FOR_EXAM < currentSum + maxScore) {
            return;
        } else if (type == TEST_WITH_MARK && MAX_SUM_OF_CONTROL_POINTS_FOR_TEST_WITH_MARK < currentSum + maxScore) {
            return;
        } else if (type == TEST && MAX_SUM_OF_CONTROL_POINTS_FOR_TEST < currentSum + maxScore) {
            return;
        }
        controlPoints.push_back(new ControlPoint(controlPoints.size() + 1, maxScore));
    }

  public:
    JournalSubject(Subject* subject): subject(subject) {
        if (subject->GetType() == EXAM || subject->GetType() == TEST_WITH_MARK) {
            for (size_t i = 0; i < DEBAULT_COUNT_OF_CONTROL_POINTS; i++) {
                _AddControlPoint(20);
            }
        } else {
            _AddControlPoint(20);
            _AddControlPoint(30);
            _AddControlPoint(50);
        }
    }

    bool CheckSubject(Subject* subjectForCheck) {
        return subjectForCheck == subject;
    }

    Subject* GetSubject() {return subject;}

    int GetSumCurrentControlPoints() {
        int sum = 0;
        for(auto point : controlPoints) {
            sum += point->GetMaxScore();
        }
        return sum;
    }

    std::vector<ControlPoint*> GetControlPoints() {return controlPoints; }

    int GetCountOfControlPoints() { return controlPoints.size(); }
};

class JournalItem {
  private:
    JournalSubject* subject;
    Student* student;
    std::vector<size_t> marks;
    size_t examMark = std::numeric_limits<size_t>::quiet_NaN();
  public:
    JournalItem(JournalSubject* subject, Student* student): subject(subject), student(student) {
        std::vector<ControlPoint*> controlPoints = subject->GetControlPoints();
        marks.resize(controlPoints.size());
        for(size_t i = 0; i < controlPoints.size(); i++) {
            marks[i] = rand() % (controlPoints[i]->GetMaxScore() + 1);
        }
    }

    void UpsertMark(size_t index, size_t mark) {
        marks[index] = mark;
    }

    void UpsertExamMark(size_t mark) {
        if(subject->GetSumCurrentControlPoints() < DOBOR_OF_CONTROL_POINTS || mark < MIN_EXAM_MARK) {
            std::cout << "You can't give this mark\n";
            return;
        };
        if(subject->GetSubject()->GetType() == TEST) return;
        if(mark > MAX_EXAM_MARK) return;

        examMark = mark;
    }

    size_t GetItogMark() const {
        size_t sum = 0;
        for(auto mark : marks) {
            sum += mark;
        }
        if(!std::isnan(examMark)) {
            sum += examMark;
        }
        return sum;
    }

    Student* GetStudent() const { return student; }
    JournalSubject* GetSubject() { return subject; }
    std::vector<size_t> GetMarks() { return marks; }
    size_t GetExamMark() { return examMark; }
};

class Journal {
  private:
    std::map<StudyGroup*, std::vector<JournalItem*>> journalGroups;

  public:
    Journal() {
        journalGroups = std::map<StudyGroup*, std::vector<JournalItem*>>();
    }
    void AddGroup(StudyGroup* group) {
        journalGroups[group] = std::vector<JournalItem*>();
        for(Student* student : group->GetStudents()) {
            for(Subject* subject : group->GetSubjects()) {
                JournalItem * newItem =  new JournalItem(new JournalSubject(subject), student);
                journalGroups[group].push_back(newItem);
            }
        }
    }

    void GiveRating(JournalItem* item, size_t numberOfControlPoint, size_t mark) {
        item->UpsertMark(numberOfControlPoint, mark);
    }

    JournalItem* GetItem(StudyGroup* group, Student* student, Subject* subject) {
        for(auto item : journalGroups.at(group)) {
            if(item->GetStudent() == student && item->GetSubject()->GetSubject() == subject) {
                return item;
            }
        }
        return nullptr;
    }

    void PrintByGroupAndSubject(StudyGroup* group, Subject* subject) const {
        StreamTable st(std::cout);
        st.AddCol(5);
        st.AddCol(25);
        st.AddCol(15);

        std::vector<ControlPoint*> controlPoints ;

        TypeOfSubject typeOfSubject = subject->GetType();

        for(auto item : journalGroups.at(group)) {
            if(item->GetSubject()->CheckSubject(subject)) {
                controlPoints = item->GetSubject()->GetControlPoints();
                break;
            }
        }
        for(size_t i = 0; i < controlPoints.size(); i++) {
            st.AddCol(10);
        }
        st.AddCol(10);
        st.AddCol(10);
        st.AddCol(20);

        st.MakeBorderExt(true);
        st.SetDelimRow(true, '-');
        st.SetDelimCol(true, '|');

        st << "No" << "Student" << "Subject";
        for(auto controlPoint : controlPoints) {
            std::string formatStr = "CR" + std::to_string(controlPoint->GetNumber()); 
            st << formatStr;
        }
        st << "Exam" << "Itog" << "Mark";
        std::vector<JournalItem*> items = journalGroups.at(group);
        std::sort(items.begin(), items.end(), [](const JournalItem* a, const JournalItem* b) {
            return a->GetStudent()->GetFullName() < b->GetStudent()->GetFullName();
        });
        size_t number = 1;
        for(size_t i = 0; i < items.size(); i++) {
            JournalItem* item = items.at(i);
            if(item->GetSubject()->CheckSubject(subject)) {
                st << number << item->GetStudent()->GetFullName() << item->GetSubject()->GetSubject()->GetName();
                for(size_t i = 0; i < controlPoints.size(); i++) {
                    st << item->GetMarks()[i];
                }
                st <<( item->GetExamMark() ? std::to_string(item->GetExamMark()) : "-");
                st << item->GetItogMark();

                std::string itogMark;
                if(typeOfSubject == EXAM || typeOfSubject == TEST_WITH_MARK) {
                    if(!item->GetExamMark()) {
                        itogMark = "Not Passed";
                    } else {
                        size_t itogMarkPercent = GetMarkByPercents(item->GetItogMark());
                        itogMark = itogMarkPercent ? std::to_string(itogMarkPercent) : "Not Passed";
                    }
                } else {
                    itogMark = item->GetItogMark() > MIN_MARK_FOR_TEST ? "Passed" : "Not Passed";
                }
                
                st << itogMark;
                number++;
            }
        }
    }
};

void GetChoices() {
    size_t choice;
	std::cout << "\nSelect an action:\n";
	std::cout << "1 - Print group by subject\n";
	std::cout << "2 - Insert mark\n";
	std::cout << "3 - Insert exam mark\n";
	std::cout << "0 - to exit\n";

    Subject* math = new Subject("Math", static_cast<TypeOfSubject>(EXAM));
    Subject* physics = new Subject("Physics", static_cast<TypeOfSubject>(TEST));

    std::vector<Subject*> subjects = {math, physics};

    SubjectsRepository* subjectsRepository = SubjectsRepository::GetInstance();

    subjectsRepository->Insert(math);
    subjectsRepository->Insert(physics);

    StudentsRepository* studentsRepository = StudentsRepository::GetInstance();
    std::vector<Student*> students = StudentsGenerator::Generate(10);

    std::sort(students.begin(), students.end(), [](Student* a, Student* b) {
        return a->GetFullName() < b->GetFullName();
    });

    studentsRepository->BulkInsert(students);

    StudyGroup* group = new StudyGroup("KS-36", studentsRepository->GetAll(), subjectsRepository->GetAll());  
    Journal journal;

    journal.AddGroup(group);
    size_t subjectNumber;
    size_t studentNumber;
    size_t controlPointNumber;
    int mark;

    do {
        std::cin >> choice;
        if(choice == 1) {
            std::cout << "List of subjects: " << std::endl;
            for(size_t i = 0; i < subjects.size(); i++) {
                std::cout << "\t" << i + 1 << ". " << subjects.at(i)->GetName() << std::endl; 
            }
            std::cout << "Type subject number: ";
            std::cin >> subjectNumber;
            journal.PrintByGroupAndSubject(group, subjects.at(subjectNumber - 1));
        } else if(choice == 2) {
            std::cout << "List of subjects: " << std::endl;
            for(size_t i = 0; i < subjects.size(); i++) {
                std::cout << "\t" << i + 1 << ". " << subjects.at(i)->GetName() << std::endl; 
            }
            std::cout << "Type subject number: ";
            std::cin >> subjectNumber;
            journal.PrintByGroupAndSubject(group, subjects.at(subjectNumber - 1));
            std::cout << "Type student number: ";
            std::cin >> studentNumber;
            journal.PrintByGroupAndSubject(group, subjects.at(subjectNumber - 1));
            std::cout << "Type control point number: ";
            std::cin >> controlPointNumber;

            std::cout << "Type mark: ";
            std::cin >> mark;

            JournalItem* item = journal.GetItem(group, students.at(studentNumber - 1), subjects.at(subjectNumber - 1));
            journal.GiveRating(item, controlPointNumber - 1, mark);
            journal.PrintByGroupAndSubject(group, subjects.at(subjectNumber - 1));
        } else {
            std::cout << "List of subjects: " << std::endl;
            for(size_t i = 0; i < subjects.size(); i++) {
                std::cout << "\t" << i + 1 << ". " << subjects.at(i)->GetName() << std::endl; 
            }
            std::cout << "Type subject number: ";
            std::cin >> subjectNumber;
            journal.PrintByGroupAndSubject(group, subjects.at(subjectNumber - 1));
            std::cout << "Type student number: ";
            std::cin >> studentNumber;
            journal.PrintByGroupAndSubject(group, subjects.at(subjectNumber - 1));
            std::cout << "Type mark: ";
            std::cin >> mark;
            JournalItem* item = journal.GetItem(group, students.at(studentNumber - 1), subjects.at(subjectNumber - 1));
            item->UpsertExamMark(mark);
            journal.PrintByGroupAndSubject(group, subjects.at(subjectNumber - 1));
        }
    } while(choice != 0);
}


int main() {
    srand(time(0));
    GetChoices();
    return 0;
}