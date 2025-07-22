#include <iostream>
#include <string>

using namespace std;

const int maximum = 10; // maximum number of books

// structure to store books
struct book {
    string title;
    int quantity;
};

// function to input book title and its quantity
void addbook(book books[], int &size) {
    cout << "Enter the number of books (max 10): ";
    cin >> size;
    cin.ignore(); // ignores the newline after integer input

    if (size > maximum) size = maximum;

    for (int i = 0; i < size; i++) {
        cout << "Enter book title " << i + 1 << ": ";
        getline(cin, books[i].title);
        cout << "Enter quantity: ";
        while (!(cin >> books[i].quantity) || books[i].quantity < 0) {
            cout << "Invalid input. Enter a valid quantity: ";
            cin.clear();
            cin.ignore(10000, '\n'); // ignores up to 10000 characters or until newline
        }
        cin.ignore(); // ignores the newline character after integer input
    }
}

// function to display all book titles and quantities
void displaybook(const book books[], int size) {
    if (size == 0) {
        cout << "No books recorded yet." << endl;
        return;
    }
    cout << "\nBook Titles and Quantities:\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << books[i].title << " (Quantity: " << books[i].quantity << ")" << endl;
    }
}

// function to search for a book
bool searchbook(const book books[], int size, const string &title) {
    for (int i = 0; i < size; i++) {
        if (books[i].title == title) {
            cout << "Book found: " << books[i].title << " (Quantity: " << books[i].quantity << ")" << endl;
            return true;
        }
    }
    cout << "Book not found!" << endl;
    return false;
}

// function to delete a book
void deletebook(book books[], int &size, const string &title) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (books[i].title == title) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Book not found!" << endl;
        return;
    }
    for (int i = index; i < size - 1; i++) {
        books[i] = books[i + 1];
    }
    size--;
    cout << "Book deleted successfully!" << endl;
}

// function to sort books alphabetically
void sortbook(book books[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (books[i].title > books[j].title) {
                swap(books[i], books[j]);
            }
        }
    }
}

int main() {
    book books[maximum];
    int size = 0;
    int choice;

    do {
        cout << "\nBook Keeping System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display Books" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Delete Book" << endl;
        cout << "5. Sort Books" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 6) {
            cout << "Invalid choice. Enter a valid choice: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore();

        switch (choice) {
            case 1:
                addbook(books, size);
                break;

            case 2:
                displaybook(books, size);
                break;

            case 3: {
                string title;
                cout << "Enter book title to search: ";
                getline(cin, title);
                searchbook(books, size, title);
                break;
            }

            case 4: {
                string title;
                cout << "Enter book title to delete: ";
                getline(cin, title);
                deletebook(books, size, title);
                break;
            }

            case 5:
                if (size == 0) {
                    cout << "No books available to sort." << endl;
                } else {
                    sortbook(books, size);
                    cout << "Books sorted." << endl;
                    displaybook(books, size);
                }
                break;

            case 6:
                cout << "Exiting program..." << endl;
                break;
        }
    } while (choice != 6);

    return 0;
}