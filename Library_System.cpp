#include <iostream>
#include <cstring>
#include <limits>
#include <cctype>
#include <sstream> 
using namespace std;

class BookBase {
public:
    virtual void display() const = 0;
    virtual const char* getId() const = 0;
    virtual const char* getCategory() const = 0;
    virtual void editBook(const char*, const char*, const char*, const char*, const char*, const char*) = 0;
    virtual ~BookBase() {}
};

class Book : public BookBase {
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
    const char* getId() const override { return id; }
    const char* getCategory() const override { return category; }
    void display() const override {
        cout << id << "\t" << isbn << "\t" << title << "\t" << author << "\t" << edition << "\t" << publication << "\t" << category << "\n";
    }
    void editBook(const char* isbn, const char* title, const char* author, const char* edition, const char* publication, const char* category) override {
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
    bool isValidISBN(const char* isbn) {
        for (int i = 0; isbn[i] != '\0'; i++) {
            if (!(isdigit(isbn[i]) || isbn[i] == '-')) return false;
        }
        return true;
    }
    bool isValidEdition(const char* edition) {
        for (int i = 0; edition[i] != '\0'; i++) {
            if (!isalnum(edition[i]) && edition[i] != ' ') return false;
        }
        return true;
    }
    bool isValidCategory(const char* category) {
        return (strcmp(category, "Fiction") == 0 || strcmp(category, "Non-Fiction") == 0);
    }
    void addBook();
    void editBook();
    void searchBook();
    void deleteBook();
    void viewBooksByCategory();
    void viewAllBooks();
    bool isEmpty() {
        return bookCount == 0;
    }
    bool isInteger(const string& str) {
        stringstream ss(str);
        int num;
        ss >> num;
        return ss.eof() && !str.empty() && num == stoi(str);
    }
};

void Library::addBook() {
    char id[20], isbn[20], title[50], author[50], edition[20], publication[50], category[20];
    bool validId = false;
    while (!validId) {
        cout << "Enter Book ID: "; cin >> id;
        if (isDuplicateId(id)) {
            cout << "Duplicate ID! Please enter a valid one.\n";
        } else {
            validId = true;
        }
    }

    bool validCategory = false;
    while (!validCategory) {
        cout << "Enter Category (Fiction/Non-Fiction): "; cin >> category;
        if (isValidCategory(category)) {
            validCategory = true;
        } else {
            cout << "Invalid category! Please enter either 'Fiction' or 'Non-Fiction'.\n";
        }
    }

    bool validIsbn = false;
    while (!validIsbn) {
        cout << "Enter ISBN (Numbers and dashes only): "; cin >> isbn;
        if (isValidISBN(isbn)) {
            validIsbn = true;
        } else {
            cout << "Invalid ISBN! Please enter numbers and dashes only.\n";
        }
    }

    cout << "Enter Title: "; cin.ignore(); cin.getline(title, 50);
    cout << "Enter Author: "; cin.getline(author, 50);

    bool validEdition = false;
    while (!validEdition) {
        cout << "Enter Edition (Numbers and letters only): "; cin.getline(edition, 20);
        if (isValidEdition(edition)) {
            validEdition = true;
        } else {
            cout << "Invalid Edition! Please enter numbers and letters only.\n";
        }
    }

    cout << "Enter Publication: "; cin.getline(publication, 50);
    books[bookCount].setBook(id, isbn, title, author, edition, publication, category);
    bookCount++;
    cout << "Book added successfully!\nPress Enter to continue...";
    cin.get();
}

void Library::editBook() {
    if (isEmpty()) {
        cout << "There's no book added yet.\n";
        cout << "Press Enter to return to the menu.";
        cin.get();
        return;
    }

    char id[20];
    bool found = false;
    while (!found) {
        cout << "Enter Book ID to edit: "; cin >> id;
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i].getId(), id) == 0) {
                found = true;
                char isbn[20], title[50], author[50], edition[20], publication[50], category[20];
                cout << "Editing Book: " << books[i].getId() << endl;
                cout << "Enter New ISBN: "; cin >> isbn;
                cout << "Enter New Title: "; cin.ignore(); cin.getline(title, 50);
                cout << "Enter New Author: "; cin.getline(author, 50);
                cout << "Enter New Edition: "; cin.getline(edition, 20);
                cout << "Enter New Publication: "; cin.getline(publication, 50);
                cout << "Enter New Category: "; cin >> category;
                books[i].editBook(isbn, title, author, edition, publication, category);
                cout << "Book updated successfully!\nPress Enter to continue...";
                cin.get();
                break;
            }
        }
        if (!found) {
            cout << "Book ID not found. Please try again.\n";
        }
    }
}

void Library::searchBook() {
    if (isEmpty()) {
        cout << "There's no book added yet.\n";
        cout << "Press Enter to return to the menu.";
        cin.get();
        return;
    }

    char id[20];
    bool found = false;
    while (!found) {
        cout << "Enter Book ID to search: "; cin >> id;
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i].getId(), id) == 0) {
                found = true;
                books[i].display();
                break;
            }
        }
        if (!found) {
            cout << "Book ID not found. Please try again.\n";
        }
    }
}

void Library::deleteBook() {
    if (isEmpty()) {
        cout << "There's no book added yet.\n";
        cout << "Press Enter to return to the menu.";
        cin.get();
        return;
    }

    char id[20];
    bool found = false;
    while (!found) {
        cout << "Enter Book ID to delete: "; cin >> id;
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i].getId(), id) == 0) {
                found = true;
                for (int j = i; j < bookCount - 1; j++) {
                    books[j] = books[j + 1]; 
                }
                bookCount--;
                cout << "Book deleted successfully!\nPress Enter to continue...";
                cin.get();
                break;
            }
        }
        if (!found) {
            cout << "Book ID not found. Please try again.\n";
        }
    }
}

void Library::viewBooksByCategory() {
    if (isEmpty()) {
        cout << "There's no book added yet.\n";
        cout << "Press Enter to return to the menu.";
        cin.get();
        return;
    }

    char category[20];
    bool found = false;
    while (!found) {
        cout << "Enter Category: ";
        cin >> category;
        cout << "\nBooks in Category: " << category << "\n";
        cout << "ID\tISBN\tTitle\tAuthor\tEdition\tPublication\tCategory\n";
        cout << "--------------------------------------------------------------------\n";
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i].getCategory(), category) == 0) {
                books[i].display();
                found = true;
            }
        }
        if (!found) {
            cout << "Category not found! Try again.\n";
        }
    }
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void Library::viewAllBooks() {
    if (isEmpty()) {
        cout << "There's no book added yet.\n";
        cout << "Press Enter to return to the menu.";
        cin.get();
        return;
    }

    cout << "\nAll Available Books:\n";
    cout << "ID\tISBN\tTitle\tAuthor\tEdition\tPublication\tCategory\n";
    cout << "--------------------------------------------------------------------\n";
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
        int choice;
        bool validChoice = false;
        while (!validChoice) {
            cout << "\n1. Add Book\n2. Edit Book\n3. Search Book\n4. Delete Book\n5. View Books by Category\n6. View All Books\n7. Exit\nChoice: ";
            string input;
            cin >> input;
            if (lib.isInteger(input) && stoi(input) >= 1 && stoi(input) <= 7) {
                choice = stoi(input);
                validChoice = true;
            } else {
                cout << "Invalid choice! Please enter a whole number between 1 and 7.\n";
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
