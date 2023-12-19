//2 вариант, про бибилотеку

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <string>
#include <cstdio>

using namespace std;


template <typename T1, typename T2>
class Pair {
public:
    Pair() {}
    Pair(const T1& first, const T2& second) : first(first), second(second) {}

    void displayPair() const {
        std::cout << first << ": " << second << std::endl;
    }

    void savePairToFile(std::ofstream& outFile) const {
        outFile << first << " " << second << " ";
    }

private:
    T1 first;
    T2 second;
};



class Book {
public:
    //Book(const string& title, const string& author, const string& genre) : title(title), author(author), genre(genre) {}
    Book(const string& title, const string& author, const string& genre) {
        this->title = title;
        this->author = author;
        this->genre = genre;
    }
    //~Book() {};

    /*void settitle(const string& newtitle) {
        title = newtitle;
    }*/

    virtual void displayInfo() const {
        cout << "Книга " << title << endl;
        cout << "Автор " << author << endl;
        cout << "Жанр " << genre << endl;
    }

    const string& gettitle() const {
        return title;
    }

    const string& getautor() const {
        return author;
    }

    const string& getgenre() const {
        return genre;
    }

    static bool compareByLastName(const Book* book1, const Book* book2) {
        return book1->getautor() < book2->getautor();
    }

private:
    string title;
    string author;
    string genre;
};


class Fiction : public Book {
public:
    Fiction(const string& title, const string& author) : Book(title,author,"фантатсика") { }
    
    void displayInfo() const override {
        cout << "Книга " << this->gettitle() << endl;
        cout << "Автор " << this->getautor() << endl;
        cout << "Жанр " << "фантатсика" << endl;
    }
};


class NoFiction : public Book {
public:
    NoFiction(const string& title, const string& author) : Book(title, author, "не фантатсика") { }

    void displayInfo() const override {
        cout << "Книга " << this->gettitle() << endl;
        cout << "Автор " << this->getautor() << endl;
        cout << "Жанр " << "не фантатсика" << endl;
    }
};


void addP(const Book& produks) {
    ofstream outFile("outfile.txt", ios::app);
    if (outFile.is_open()) {
        outFile << produks.gettitle() << "," << produks.getautor() << "," << produks.getgenre() << endl;
        outFile.close();
    }
    else {
        cerr << "Не удалось открыть файл для записи." << endl;
    }
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::vector<Book*> book;
    int choice;

    do {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить книгу" << std::endl;
        std::cout << "2. Поиск книги по названию" << std::endl;
        std::cout << "3. Сортировать книги по автору" << std::endl;
        std::cout << "4. Случайно удалить всю бд" << std::endl;
        std::cout << "5. Данные о книгах" << std::endl;
        std::cout << "6. Выход" << std::endl;

        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                string title, author, genre;
                cin.ignore();
                cout << "Название книги ";
                getline(cin, title);
                cout << "Автор ";
                getline(cin, author);
                cout << "Жанр ";
                getline(cin, genre);

                if (genre == "фантастика") {
                    book.push_back(new Fiction(title, author));
                    addP(Fiction(title, author));
                }
                else {
                    book.push_back(new NoFiction(title, author));
                    addP(NoFiction(title, author));
                }
                break;
            }
            
            case 2: {
                cin.ignore();
                cout << "Название книги ";
                string title;
                getline(cin, title);
                //cin >> title;
                /*auto it = find_if(book.begin(), book.end(), [&](const Book* book1) {
                    return book1->gettitle() == title;
                });

                if (it != book.end()) {
                    cout << "Книга существет";
                    it->displayInfo();
                }*/


                for (auto& i : book) {
                    if (i->gettitle() == title) {
                        i->displayInfo();
                        addP(Book(i->gettitle(), i->getautor(), i->getgenre()));
                    }
                }

                break;
            }

            case 3: {
                sort(book.begin(), book.end(),Book::compareByLastName);
                cout << "Книги отсортированы по автору" << endl;
                
                for (auto& i : book) {
                    addP(Book(i->gettitle(), i->getautor(), i->getgenre()));
                }
                
                break;
            }
            
            case 4: {
                cout << "Куда-то нажал и все пропало, а надо было бэкап делать" << endl;
                book.clear();
                if (remove("outfile.txt") != 0)
                    std::cout << "Ошибка удаления файлаn" << endl;
                else
                    std::cout << "Файл успешно удалёнn" << endl;
                break;
            }

            case 5: {
                for (auto& i : book) {
                    i->displayInfo();
                }
                break;
            }
            
        }
    } while (choice != 6);

    book.clear();
    return 0;
}
