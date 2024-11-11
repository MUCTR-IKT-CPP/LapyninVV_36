#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <algorithm>
#include <chrono>

// Константы для генерации
const int MIN_PAGES = 50;
const int MAX_PAGES = 800;
const int MIN_AGE_RESTRICTION = 0;
const int MAX_AGE_RESTRICTION = 18;
const int NUM_GENRES = 4;
const int NUM_SIZES = 3;
const int MIN_DAILY_VISITORS = 1;
const int MAX_DAILY_VISITORS = 5;
const int MAX_VISITORS = 20;
const int BASE_VISITOR_AGE = 20;
const int BASE_READING_SPEED = 30;
const int READING_SPEED_INCREMENT = 10;
const int MIN_RATING = 1;
const int MAX_RATING = 5;
const int CATALOG_SIZE = 30;

// Перечисление жанров книг
enum class Genre {
    Detective,
    Romance,
    Fantasy,
    SciFi
};

enum class Size {
    Small,
    Medium,
    Large
};

// Класс для представления автора
class Author {
private:
    std::string name;
    
public:
    /*
     * Конструктор автора
     *
     * @param name имя автора.
     */
    Author(const std::string& name) : name(name) {}
    
    /*
     * Получение имени автора
     *
     * @return возвращает имя автора.
     */
    std::string getName() const { return name; }

    /*
     * Оператор вывода автора в поток
     *
     * @param os поток вывода.
     * @param author автор для вывода.
     * @return возвращает поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& os, const Author& author) {
        os << "Author {name: " << author.name << "}";
        return os;
    }
};

// Класс для представления книги
class Book {
private:
    std::string title;
    int pages;
    int ageRestriction;
    Genre genre;
    Size size;
    Author* author;
    int timesBorrowed;

public:
    /*
     * Конструктор книги
     *
     * @param title название книги.
     * @param pages количество страниц.
     * @param ageRestriction возрастное ограничение.
     * @param genre жанр книги.
     * @param author указатель на автора книги.
     */
    Book(const std::string& title, int pages, int ageRestriction, 
        Genre genre, Author* author)
        : title(title), pages(pages), ageRestriction(ageRestriction),
          genre(genre), author(author), timesBorrowed(0) {
            if (pages < 100) size = Size::Small;
            else if (pages >= 100 && pages <= 500) size = Size::Medium;
            else size = Size::Large;
          }

    /*
     * Увеличение счетчика заимствований книги
     */
    void incrementBorrows() {
        timesBorrowed++;
    }

    /*
     * Получение названия книги
     *
     * @return возвращает название книги.
     */
    std::string getTitle() const { return title; }

    /*
     * Получение количества страниц
     *
     * @return возвращает количество страниц.
     */
    int getPages() const { return pages; }

    /*
     * Получение возрастного ограничения
     *
     * @return возвращает возрастное ограничение.
     */
    int getAgeRestriction() const { return ageRestriction; }

    /*
     * Получение жанра книги
     *
     * @return возвращает жанр книги.
     */
    Genre getGenre() const { return genre; }

    /*
     * Получение размера книги
     *
     * @return возвращает размер книги.
     */
    Size getSize() const { return size; }

    /*
     * Получение автора книги
     *
     * @return возвращает указатель на автора книги.
     */
    Author* getAuthor() const { return author; }

    /*
     * Получение количества заимствований
     *
     * @return возвращает количество раз, когда книга была взята.
     */
    int getTimesBorrowed() const { return timesBorrowed; }

    /*
     * Оператор вывода книги в поток
     *
     * @param os поток вывода.
     * @param book книга для вывода.
     * @return возвращает поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << "Book {title: " << book.title 
           << ", pages: " << book.pages
           << ", age restriction: " << book.ageRestriction
           << ", genre: " << static_cast<int>(book.genre)
           << ", size: " << static_cast<int>(book.size)
           << ", author: " << *book.author
           << ", times borrowed: " << book.timesBorrowed
           << "}";
        return os;
    }
};

// Класс для представления посетителя
class Visitor {
private:
    std::string name;
    int age;
    int readingSpeed;
    std::vector<Book*> readBooks;
    Book* currentBook;
    int remainingReadingDays;
    Genre preferredGenre;
    int preferredSize;

public:
    /*
     * Конструктор посетителя
     *
     * @param name имя посетителя.
     * @param age возраст посетителя.
     * @param readingSpeed скорость чтения (страниц в день).
     */
    Visitor(const std::string& name, int age, int readingSpeed)
        : name(name), age(age), readingSpeed(readingSpeed), 
          currentBook(nullptr), remainingReadingDays(0) {}

    /*
     * Установка предпочтений посетителя
     *
     * @param genre предпочитаемый жанр.
     * @param size предпочитаемый размер книги.
     */
    void setPreferences(Genre genre, int size) {
        preferredGenre = genre;
        preferredSize = size;
    }

    /*
     * Проверка возможности чтения книги
     *
     * @param book указатель на проверяемую книгу.
     * @return возвращает true, если посетитель может читать книгу.
     */
    bool canReadBook(const Book* book) const {
        return age >= book->getAgeRestriction() && 
               std::find(readBooks.begin(), readBooks.end(), book) == readBooks.end();
    }

    /*
     * Проверка, читает ли посетитель книгу
     *
     * @return возвращает true, если посетитель читает книгу.
     */
    bool isReading() const {
        return currentBook != nullptr;
    }

    /*
     * Начало чтения книги
     *
     * @param book указатель на книгу для чтения.
     */
    void startReading(Book* book) {
        currentBook = book;
        remainingReadingDays = std::ceil(static_cast<double>(book->getPages()) / readingSpeed);
        book->incrementBorrows();
    }

    /*
     * Обновление процесса чтения
     */
    void updateReading() {
        if (currentBook && remainingReadingDays > 0) {
            remainingReadingDays--;
            if (remainingReadingDays == 0) {
                finishBook();
            }
        }
    }

    /*
     * Завершение чтения книги
     */
    void finishBook() {
        if (currentBook) {
            readBooks.push_back(currentBook);
            currentBook = nullptr;
        }
    }

    /*
     * Получение имени посетителя
     *
     * @return возвращает имя посетителя.
     */
    std::string getName() const { return name; }

    /*
     * Получение возраста посетителя
     *
     * @return возвращает возраст посетителя.
     */
    int getAge() const { return age; }

    /*
     * Получение предпочитаемого жанра
     *
     * @return возвращает предпочитаемый жанр.
     */
    Genre getPreferredGenre() const { return preferredGenre; }

    /*
     * Получение предпочитаемого размера книги
     *
     * @return возвращает предпочитаемый размер.
     */
    int getPreferredSize() const { return preferredSize; }

    /*
     * Получение скорости чтения
     *
     * @return возвращает скорость чтения (страниц в день).
     */
    int getReadingSpeed() const { return readingSpeed; }

    /*
     * Получение текущей читаемой книги
     *
     * @return возвращает указатель на текущую книгу.
     */
    Book* getCurrentBook() const { return currentBook; }

    /*
     * Оператор вывода посетителя в поток
     *
     * @param os поток вывода.
     * @param visitor посетитель для вывода.
     * @return возвращает поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& os, const Visitor& visitor) {
        os << "Visitor {name: " << visitor.name
           << ", age: " << visitor.age
           << ", reading speed: " << visitor.readingSpeed
           << ", read books: " << visitor.readBooks.size()
           << ", current book: " << (visitor.currentBook ? visitor.currentBook->getTitle() : "none")
           << ", remaining days: " << visitor.remainingReadingDays
           << ", preferred genre: " << static_cast<int>(visitor.preferredGenre)
           << ", preferred size: " << visitor.preferredSize
           << "}";
        return os;
    }
};

// Класс библиотеки
class Library {
private:
    std::vector<Book*> catalog;
    std::vector<Author*> authors;
    std::vector<Visitor*> visitors;
    int currentDay;
    const int SIMULATION_DAYS = 30;
    
    std::map<Book*, std::vector<int>> bookRatings;
    std::map<Book*, std::vector<int>> bookReadingTimes;
    
    /*
     * Генерация случайного рейтинга
     *
     * @return возвращает случайный рейтинг от MIN_RATING до MAX_RATING.
     */
    int generateRandomRating() {
        return MIN_RATING + (rand() % (MAX_RATING - MIN_RATING + 1));
    }
    
    /*
     * Обновление статистики книги
     *
     * @param book указатель на книгу.
     * @param visitor указатель на посетителя.
     */
    void updateBookStatistics(Book* book, Visitor* visitor) {
        if (!book) return;
        
        bookRatings[book].push_back(generateRandomRating());
        
        int readingTime = std::ceil(static_cast<double>(book->getPages()) / visitor->getReadingSpeed());
        bookReadingTimes[book].push_back(readingTime);
    }

public:
    /*
     * Конструктор библиотеки
     */
    Library() : currentDay(0) {
        srand(time(0));
        generateCatalog();
        
        generateVisitors();
    }

    /*
     * Деструктор библиотеки
     */
    ~Library() {
        for (auto book : catalog) delete book;
        for (auto author : authors) delete author;
        for (auto visitor : visitors) delete visitor;
    }

    /*
     * Генерация посетителей библиотеки
     */
    void generateVisitors() {
        for (int i = 0; i < MAX_VISITORS; i++) {
            visitors.push_back(new Visitor("Visitor " + std::to_string(i + 1), BASE_VISITOR_AGE + i, BASE_READING_SPEED + i * READING_SPEED_INCREMENT));
        }
    }

    /*
     * Генерация каталога книг
     */
    void generateCatalog() {
        authors = {
            new Author("John Smith"),
            new Author("Maria Petrova"),
            new Author("Alex Brown"),
            new Author("Elena Ivanova")
        };

        for (int i = 0; i < CATALOG_SIZE; i++) {
            int pages = MIN_PAGES + (rand() % (MAX_PAGES - MIN_PAGES + 1));
            int age = MIN_AGE_RESTRICTION + (rand() % (MAX_AGE_RESTRICTION - MIN_AGE_RESTRICTION + 1));
            int genre = rand() % NUM_GENRES;
            
            catalog.push_back(new Book(
                "Book " + std::to_string(i + 1),
                pages,
                age,
                static_cast<Genre>(genre),
                authors[i % authors.size()]
            ));
        }
    }

    /*
     * Поиск подходящей книги для посетителя
     *
     * @param visitor указатель на посетителя.
     * @return возвращает указатель на найденную книгу или nullptr.
     */
    Book* findBook(const Visitor* visitor) {
        for (auto book : catalog) {
            if (!visitor->canReadBook(book)) continue;

            bool sizeMatch = false;
            int pages = book->getPages();
            switch (visitor->getPreferredSize()) {
                case 0: sizeMatch = pages < 100; break;
                case 1: sizeMatch = pages >= 100 && pages <= 500; break;
                case 2: sizeMatch = pages > 500; break;
            }

            if (sizeMatch && book->getGenre() == visitor->getPreferredGenre()) {
                return book;
            }
        }
        return nullptr;
    }

    /*
     * Симуляция одного дня работы библиотеки
     */
    void simulateDay() {
        for (auto visitor : visitors) {
            if (visitor->isReading() && visitor->getCurrentBook()) {
                Book* currentBook = visitor->getCurrentBook();
                visitor->updateReading();
                if (!visitor->isReading()) {
                    updateBookStatistics(currentBook, visitor);
                }
            }
        }

        for (auto visitor : visitors) {
            if (!visitor->isReading()) {
                visitor->setPreferences(
                    static_cast<Genre>(rand() % NUM_GENRES),
                    rand() % NUM_SIZES
                );
                Book* book = findBook(visitor);
                if (book) {
                    visitor->startReading(book);
                }
            }
        }

        int newVisitorsCount = MIN_DAILY_VISITORS + (rand() % MAX_DAILY_VISITORS);
        for (int i = 0; i < newVisitorsCount; i++) {
            int visitorId = visitors.size() + 1;
            visitors.push_back(new Visitor(
                "Visitor " + std::to_string(visitorId),
                BASE_VISITOR_AGE + visitorId,
                BASE_READING_SPEED + visitorId * READING_SPEED_INCREMENT
            ));
        }

        currentDay++;
    }

    /*
     * Получение среднего рейтинга книги
     *
     * @param book указатель на книгу.
     * @return возвращает средний рейтинг книги.
     */
    double getAverageRating(const Book* book) const {
        auto it = bookRatings.find(const_cast<Book*>(book));
        if (it == bookRatings.end() || it->second.empty()) return 0;
        return static_cast<double>(std::accumulate(it->second.begin(), it->second.end(), 0)) / it->second.size();
    }

    /*
     * Получение среднего времени чтения книги
     *
     * @param book указатель на книгу.
     * @return возвращает среднее время чтения книги в днях.
     */
    double getAverageReadingTime(const Book* book) const {
        auto it = bookReadingTimes.find(const_cast<Book*>(book));
        if (it == bookReadingTimes.end() || it->second.empty()) return 0;
        return static_cast<double>(std::accumulate(it->second.begin(), it->second.end(), 0)) / it->second.size();
    }

    /*
     * Вывод статистики библиотеки
     */
    void printStatistics() const {
        std::cout << "\nLibrary Statistics:\n\n";

        for (const auto& book : catalog) {
            std::cout << *book << "\n";
            std::cout << "Average rating: " << getAverageRating(book) << "\n";
            std::cout << "Average reading time (days): " << getAverageReadingTime(book) << "\n\n";
        }

        std::map<std::string, int> authorStats;
        for (const auto& book : catalog) {
            authorStats[book->getAuthor()->getName()] += book->getTimesBorrowed();
        }

        std::cout << "\nAuthor Statistics:\n";
        for (const auto& [author, count] : authorStats) {
            std::cout << author << ": " << count << " borrows\n";
        }
    }

    /*
     * Запуск симуляции работы библиотеки
     */
    void simulate() {
        while (currentDay < SIMULATION_DAYS) {
            simulateDay();
        }
        
        for (auto visitor : visitors) {
            if (visitor->isReading()) {
                Book* currentBook = visitor->getCurrentBook();
                visitor->finishBook();
                updateBookStatistics(currentBook, visitor);
            }
        }
        
        printStatistics();
    }

    /*
     * Оператор вывода библиотеки в поток
     *
     * @param os поток вывода.
     * @param library библиотека для вывода.
     * @return возвращает поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& os, const Library& library) {
        os << "Library {current day: " << library.currentDay
           << ", catalog size: " << library.catalog.size()
           << ", authors count: " << library.authors.size()
           << ", visitors count: " << library.visitors.size()
           << "}";
        return os;
    }
};

/*
 * Точка входа в программу
 *
 * @return возвращает код завершения программы.
 */
int main() {
    Library library;
    library.simulate();
    return 0;
}
