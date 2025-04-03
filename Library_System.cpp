
#include <iostream>
#include <cstring>
#include <limits>
#include <cctype>
using namespace std;

class Book {
private:
    char id[20], isbn[20], title[50], author[50], edition[20], publication[50], category[20];

public:
    Book() {
        strcpy(id, "");
        strcpy(isbn, "");
        strcpy(title, "");
        strcpy(author, "");
        strcpy(edition, "");
        strcpy(publication, "");
        strcpy(category, "");
    }

    void setBook(const char* id, const char* isbn, const char* title, const char* author, const char* edition, const char* publication, const char* category) {
        strcpy(this->id, id);
        strcpy(this->isbn, isbn);
        strcpy(this->title, title);
        strcpy(this->author, author);
        strcpy(this->edition, edition);
        strcpy(this->publication, publication);
        strcpy(this->category, category);
    }

    const char* getId() { return id; }
    const char* getCategory() { return category; }

    void display() {
        cout << "ID: " << id << "\tISBN: " << isbn << "\tTitle: " << title << "\tAuthor: " << author
             << "\tEdition: " << edition << "\tPublication: " << publication << "\tCategory: " << category << "\n";
    }

    void editBook(const char* isbn, const char* title, const char* author, const char* edition, const char* publication, const char* category) {
        strcpy(this->isbn, isbn);
        strcpy(this->title, title);
        strcpy(this->author, author);
        strcpy(this->edition, edition);
        strcpy(this->publication, publication);
        strcpy(this->category, category);
    }
};

class Library {
private:
    Book books[100];
    int bookCount;

public:
    Library() { bookCount = 0; }

    bool isDuplicateId(const char* id) {
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i].getId(), id) == 0) return true;
        }
        return false;
    }

    bool isInteger(const string& input) {
        for (char c : input) {
            if (!isdigit(c) && c != '-') return false;
        }
        return true;
    }

    bool isValidChoice(int choice) {
        return choice >= 1 && choice <= 7;
    }

    bool isValidISBN(const char* isbn) {
        for (int i = 0; isbn[i] != '\0'; i++) {
            if (!(isdigit(isbn[i]) || isbn[i] == '-')) {
                return false;
            }
        }
        return true;
    }

    bool isValidEdition(const char* edition) {
        for (int i = 0; edition[i] != '\0'; i++) {
            if (edition[i] == '.' || edition[i] == '-' || !isalnum(edition[i])) {
                return false;
            }
        }
        return true;
    }

    void addBook();
    void editBook();
    void searchBook();
    void deleteBook();
    void viewBooksByCategory();
    void viewAllBooks();
};

void Library::addBook() {
    char id[20], isbn[20], title[50], author[50], edition[20], publication[50], category[20];

    cout << "Enter Category (e.g., Fiction, Non-Fiction, etc.): ";
    cin.ignore();
    cin.getline(category, 20);

    bool validId = false;
    while (!validId) {
        cout << "Enter Book ID: "; 
        cin >> id;
        if (isDuplicateId(id)) {
            cout << "Duplicate ID! Please enter a valid one.\n";
        } else {
            validId = true;  // ID is valid, break out of the loop
        }
    }

    cout << "Enter ISBN: "; cin >> isbn;
    while (!isValidISBN(isbn)) {
        cout << "Invalid ISBN. Please enter a valid ISBN (numbers and dashes only): ";
        cin >> isbn;
    }

    cout << "Enter Title: "; cin.ignore(); cin.getline(title, 50);
    cout << "Enter Author: "; cin.getline(author, 50);
    cout << "Enter Edition: "; cin.getline(edition, 20);
    while (!isValidEdition(edition)) {
        cout << "Invalid Edition. Please enter a valid edition (alphanumeric characters only): ";
        cin.getline(edition, 20);
    }

    cout << "Enter Publication: "; cin.getline(publication, 50);

    books[bookCount].setBook(id, isbn, title, author, edition, publication, category);
    bookCount++;
    cout << "Book added successfully!\nPress Enter to continue...";
    cin.get();
}

void Library::viewBooksByCategory() {
    char category[20];
    bool validCategory = false;
    while (!validCategory) {
        cout << "Enter Category: ";
        cin >> category;
        bool found = false;
        cout << "\nID\tISBN\tTitle\tAuthor\tEdition\tPublication\tCategory\n";
        cout << "------------------------------------------------------------\n";
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i].getCategory(), category) == 0) {
                books[i].display();
                found = true;
            }
        }
        if (found) {
            validCategory = true;
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        } else {
            cout << "Category not found! Please try again.\n";
        }
    }
}

void Library::editBook() {
    char id[20];
    cout << "Enter Book ID to edit: ";
    cin >> id;
    
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].getId(), id) == 0) {
            char isbn[20], title[50], author[50], edition[20], publication[50], category[20];
            cin.ignore();
            cout << "Enter new ISBN: "; cin.getline(isbn, 20);
            cout << "Enter new Title: "; cin.getline(title, 50);
            cout << "Enter new Author: "; cin.getline(author, 50);
            cout << "Enter new Edition: "; cin.getline(edition, 20);
            cout << "Enter new Publication: "; cin.getline(publication, 50);
            cout << "Enter new Category: "; cin.getline(category, 20);
            books[i].editBook(isbn, title, author, edition, publication, category);
            cout << "Book edited successfully!\nPress Enter to continue...";
            cin.get();
            return;
        }
    }
    cout << "Book not found!\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void Library::searchBook() {
    char id[20];
    cout << "Enter Book ID to search: ";
    cin >> id;
    
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].getId(), id) == 0) {
            books[i].display();
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            return;
        }
    }
    cout << "Book not found!\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void Library::deleteBook() {
    char id[20];
    cout << "Enter Book ID to delete: ";
    cin >> id;
    
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].getId(), id) == 0) {
            books[i].display();
            cout << "Do you want to delete this book? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                for (int j = i; j < bookCount - 1; j++) {
                    books[j] = books[j + 1];
                }
                bookCount--;
                cout << "Book deleted successfully!\nPress Enter to continue...";
            }
            cin.ignore();
            cin.get();
            return;
        }
    }
    cout << "Book not found!\nPress Enter to continue..";
    cin.ignore();
    cin.get();
}

void Library::viewAllBooks() {
    cout << "\nAll Available Books:\n";
    cout << "ID\tISBN\tTitle\tAuthor\tEdition\tPublication\tCategory\n";
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < bookCount; i++) {
        books[i].display();
    }
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

int main() {
    Library lib;
    bool running = true;
    while (running) {
        string input;
        int choice = 0;
        bool validChoice = false;
        
        while (!validChoice) {
            cout << "\n1. Add Book\n2. Edit Book\n3. Search Book\n4. Delete Book\n5. View Books by Category\n6. View All Books\n7. Exit\nChoice: ";
            cin >> input;

            if (lib.isInteger(input)) {
                choice = stoi(input);
                if (lib.isValidChoice(choice)) {
                    validChoice = true;
                } else {
                    cout << "Invalid choice! Please enter a valid choice (1-7).\n";
                }
            } else {
                cout << "Invalid input! Please enter a valid choice (1-7).\n";
            }
        }

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.editBook(); break;
            case 3: lib.searchBook(); break;
            case 4: lib.deleteBook(); break;
            case 5: lib.viewBooksByCategory(); break;
            case 6: lib.viewAllBooks(); break;
            case 7: cout << "Exiting..." << endl; running = false; break;
        }
    }
    return 0;
}






