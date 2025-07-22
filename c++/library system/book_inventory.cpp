#include <iostream>
#include <string>
#include <iomanip>  // For setw

using namespace std;

// maximum books
const int max_book = 10;

// structure of record
struct record {
    string name;
    int quantity;
};

// function that displays all books
void displaybooks(record data[], int count) {
    if (count == 0) {
        cout << "no records in the database.\n";
        return;
    }
    cout << "\nquantity\tname\n";
    cout << "-------------------------\n";
    for (int i = 0; i < count; i++) {
        cout << data[i].quantity << "\t\t" << data[i].name << endl;
    }
}

// function search
int searchbooks(record database[], int count, const string& name) {
    for (int i = 0; i < count; i++) {
        if (database[i].name == name) {
            return i; // returns record index
        }
    }
    return -1; // returns -1 if there is no record
}

// function delete
void deleterecord(record database[], int &count, const string& name) {
    int index = searchbooks(database, count, name);
    if (index == -1) {
        cout << "book \"" << name << "\" not found.\n";
        return;
    }
    // replaces the deleted record
    for (int i = index; i < count - 1; i++) {
        database[i] = database[i + 1];
    }
    count--; // reduce record
    cout << "book \"" << name << "\" has been deleted.\n";
}

int main() {
    // array of the records
    record data[max_book];
    int recordCount = 0; // tracks the number of record

    int choice;
    string searchName, deleteName; // variables outside the switch 
    int searchindex;

    do {
        // displays choices
        cout << "\n  Books\n";
        cout << "1. add books\n";
        cout << "2. view books\n";
        cout << "3. search books\n";
        cout << "4. delete books\n";
        cout << "5. exit\n";
        cout << "enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // adds record
                if (recordCount < max_book) {
                    cout << "enter name: ";
                    cin.ignore(); // clear the input
                    getline(cin, data[recordCount].name);
                    cout << "enter quantity: ";
                    cin >> data[recordCount].quantity;
                    recordCount++;
                    cout << "book has been recorded.\n";
                } else {
                    cout << "reached maximum. Cannot add more books.\n";
                }
                break;

            case 2: // view records
                displaybooks(data, recordCount);
                break;

            case 3: // search record
                cout << "enter name to search: ";
                cin.ignore(); // clear the input
                getline(cin, searchName);
                searchindex = searchbooks(data, recordCount, searchName);
                if (searchindex != -1) {
                    cout << "record found:\n";
                    cout << "name: " << data[searchindex].name
                         << ", quantity: " << data[searchindex].quantity << endl;
                } else {
                    cout << "book \"" << searchName << "\" not found.\n";
                }
                break;

            case 4: // deletes book
                cout << "enter name of the book to delete: ";
                cin.ignore(); // clear the input
                getline(cin, deleteName);
                deleterecord(data, recordCount, deleteName);
                break;

            case 5: // exit
                cout << "exiting!\n";
                break;

            default:
                cout << "invalid. please try again.\n";
        }
    } while (choice != 5);

    return 0; 
}