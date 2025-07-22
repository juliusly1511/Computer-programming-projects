#include <iostream>
#include <string>
using namespace std;

// maximum record that can be stored
const int Max = 100;

// strcuture of record
struct record {
    int id;
    string name;
    int age;
};

// function that displays all records
void displayrecords(record database[], int count) {
    if (count == 0) {
        cout << "no records in the database.\n";
        return;
    }
    cout << "\nid\tname\tage\n";
    for (int i = 0; i < count; i++) {
        cout << database[i].id << "\t" << database[i].name << "\t" << database[i].age << endl;
    }
}

// function search
int searchrecord(record database[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (database[i].id == id) {
            return i;//returns record
        }
    }
    return -1; // returns -1 if their is no record
}

// function delete
void deleterecord(record database[], int &count, int id) {
    int index = searchrecord(database, count, id);
    if (index == -1) {
        cout << "id no. " << id << " not found.\n";
        return;
    }
    // replaces the deleted record
    for (int i = index; i < count - 1; i++) {
        database[i] = database[i + 1];
    }
    count--; // reduce record
    cout << "id no. " << id << " has been deleted.\n";
}

int main() {
    // array of the records
    record database[Max];
    int recordCount = 0; // tracks the number of record

    int choice;
    int searchid, deleteid; // variables oustide the switch 
    int searchindex;

    do {
       //displays chhhoices
        cout << "\ndata base management system\n";
        cout << "1. add record\n";
        cout << "2. view record\n";
        cout << "3. search record\n";
        cout << "4. delete record\n";
        cout << "5. exit\n";
        cout << "enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: //adds record
                if (recordCount < Max) {
                    cout << "enter id: ";
                    cin >> database[recordCount].id;
                    cout << "enter name: ";
                    cin.ignore(); //clear the input
                    getline(cin, database[recordCount].name);
                    cout << "enter age: ";
                    cin >> database[recordCount].age;
                    recordCount++;
                    cout << "record has been recorded.\n";
                } else {
                    cout << "Database is full. Cannot add more records.\n";
                }
                break;

            case 2: // view records
                displayrecords(database, recordCount);
                break;

            case 3: // search record
                cout << "enter id to search: ";
                cin >> searchid;
                searchindex = searchrecord(database, recordCount, searchid);
                if (searchindex != -1) {
                    cout << "record found:\n";
                    cout << "id: " << database[searchindex].id << ", name: " << database[searchindex].name
                         << ", age: " << database[searchindex].age << endl;
                } else {
                    cout << "record no. " << searchid << " not found.\n";
                }
                break;

            case 4: // deletes Record
                cout << "enter id to delete: ";
                cin >> deleteid;
                deleterecord(database, recordCount, deleteid);
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