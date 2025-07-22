#include <iostream>    // Input/output operations
#include <fstream>     // File handling operations
#include <string>      // String handling
#include <vector>      // Dynamic array container
#include <ctime>       // Time and date functions
#include <iomanip>     // Output formatting
#include <algorithm>   // For algorithms like find_if
#include <sstream>     // String stream processing
using namespace std;

// Book structure to store book information
struct Book {
    int id;             // Unique identifier for each book
    string title;       // Title of the book
    int quantity;       // Current available quantity
    int og_quantity;    // Original/Total quantity
};

// Function to load books from file into memory
void loadBooks(vector<Book>& books) {
    ifstream infile("books.txt");  // Open books.txt for reading
    if (!infile) {
        cout << "Error: Could not open books.txt\n";
        return;
    }
    books.clear();  // Clear existing books from vector
    string line;
    
    // Read file line by line
    while (getline(infile, line)) {
        cout << "Read line: " << line << endl;  // Debug output
        stringstream ss(line);  // Create string stream for parsing
        
        // Variables to store parsed data
        string id_str, title, quantity_str, og_quantity_str;
        
        // Parse line into components
        getline(ss, id_str, ' ');         // Get ID before space
        getline(ss, title, ',');          // Get title before comma
        getline(ss, quantity_str, ',');   // Get quantity before comma
        getline(ss, og_quantity_str, ','); // Get original quantity
        
        // Check if any field is empty
        if (id_str.empty() || title.empty() || quantity_str.empty() || og_quantity_str.empty()) {
            cout << "Skipping invalid line: " << line << endl;
            continue;
        }
        
        // Convert string values to integers and add book to vector
        try {
            int id = stoi(id_str);
            int quantity = stoi(quantity_str);
            int og_quantity = stoi(og_quantity_str);
            books.push_back({id, title, quantity, og_quantity});
        } catch (const exception& e) {
            cout << "Error parsing line: " << line << endl;
        }
    }
    infile.close();  // Close the file
}

// Function to save books from memory back to file
void saveBooks(const vector<Book>& books) {
    ofstream outfile("books.txt");  // Open books.txt for writing
    if (!outfile) {
        cout << "Error: Could not open books.txt for writing\n";
        return;
    }
    
    // Write each book to file in specified format
    for (const auto& book : books) {
        outfile << book.id << " " << book.title << "," 
                << book.quantity << "," << book.og_quantity << endl;
    }
    outfile.close();  // Close the file
}

// Function to display all available books (quantity > 0)
void displayAvailableBooks(const vector<Book>& books) {
    cout << "\nAvailable Books:\n";
    // Format header with fixed width columns
    cout << left << setw(5) << "ID" << setw(30) << "Title" << setw(10) << "Quantity" << endl;
    cout << string(45, '-') << endl;  // Print separator line
    
    bool any = false;  // Track if any books are available
    // Display each available book
    for (const auto& book : books) {
        if (book.quantity > 0) {
            cout << left << setw(5) << book.id 
                 << setw(30) << book.title 
                 << setw(10) << book.quantity << endl;
            any = true;
        }
    }
    if (!any) cout << "No books available.\n";
}

// Function to display all borrowed books
void displayBorrowedBooks(const vector<Book>& books) {
    cout << "\nBorrowed Books:\n";
    // Format header with fixed width columns
    cout << left << setw(5) << "ID" << setw(30) << "Title" 
         << setw(15) << "Borrowed Qty" << endl;
    cout << string(50, '-') << endl;
    
    bool any = false;  // Track if any books are borrowed
    // Display each borrowed book
    for (const auto& book : books) {
        int borrowed = book.og_quantity - book.quantity;  // Calculate borrowed amount
        if (borrowed > 0) {
            cout << left << setw(5) << book.id 
                 << setw(30) << book.title 
                 << setw(15) << borrowed << endl;
            any = true;
        }
    }
    if (!any) cout << "No books have been borrowed.\n";
}

// Function to log borrowing transaction
void logBorrow(const Book& book, int amount) {
    ofstream outfile("borrowed.txt", ios::app);  // Open in append mode
    time_t now = time(0);  // Get current time
    tm* ltm = localtime(&now);  // Convert to local time
    
    // Write transaction details with timestamp
    outfile << "ID: " << book.id << ", Title: " << book.title
            << ", Quantity: " << amount
            << ", Date: " << 1900 + ltm->tm_year << "-"
            << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
            << setw(2) << setfill('0') << ltm->tm_mday << " "
            << setw(2) << setfill('0') << ltm->tm_hour << ":"
            << setw(2) << setfill('0') << ltm->tm_min << ":"
            << setw(2) << setfill('0') << ltm->tm_sec << endl;
    outfile.close();
}

// Function to log return transaction
void logReturn(const Book& book, int amount) {
    ofstream outfile("borrowed.txt", ios::app);  // Open in append mode
    time_t now = time(0);  // Get current time
    tm* ltm = localtime(&now);  // Convert to local time
    
    // Write return transaction details with timestamp
    outfile << "RETURNED - ID: " << book.id << ", Title: " << book.title
            << ", Quantity: " << amount
            << ", Date: " << 1900 + ltm->tm_year << "-"
            << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
            << setw(2) << setfill('0') << ltm->tm_mday << " "
            << setw(2) << setfill('0') << ltm->tm_hour << ":"
            << setw(2) << setfill('0') << ltm->tm_min << ":"
            << setw(2) << setfill('0') << ltm->tm_sec << endl;
    outfile.close();
}

// Function to handle book borrowing process
void borrowBook(vector<Book>& books) {
    displayAvailableBooks(books);  // Show available books
    cout << "\nEnter the ID of the book to borrow: ";
    int id, amount;
    cin >> id;
    
    // Find book with matching ID
    auto it = find_if(books.begin(), books.end(), 
                     [id](const Book& b){ return b.id == id; });
    
    // Check if book exists and is available
    if (it == books.end() || it->quantity == 0) {
        cout << "Book not found or not available.\n";
        return;
    }
    
    // Get borrow quantity
    cout << "Enter quantity to borrow (max " << it->quantity << "): ";
    cin >> amount;
    
    // Validate quantity
    if (amount <= 0 || amount > it->quantity) {
        cout << "Invalid quantity.\n";
        return;
    }
    
    // Update book quantity and save changes
    it->quantity -= amount;
    cout << "Successfully borrowed " << amount << " copy/copies of \"" 
         << it->title << "\".\n";
    logBorrow(*it, amount);
    saveBooks(books);
    loadBooks(books);  // Reload to ensure sync
}

// Function to handle book return process
void returnBook(vector<Book>& books) {
    displayBorrowedBooks(books);  // Show borrowed books
    cout << "\nEnter the ID of the book to return: ";
    int id, amount;
    cin >> id;
    
    // Find book with matching ID
    auto it = find_if(books.begin(), books.end(), 
                     [id](const Book& b){ return b.id == id; });
    
    // Check if book exists
    if (it == books.end()) {
        cout << "Book not found.\n";
        return;
    }
    
    // Calculate borrowed quantity
    int borrowed = it->og_quantity - it->quantity;
    if (borrowed == 0) {
        cout << "No borrowed copies for this book.\n";
        return;
    }
    
    // Get return quantity
    cout << "Enter quantity to return (max " << borrowed << "): ";
    cin >> amount;
    
    // Validate quantity
    if (amount <= 0 || amount > borrowed) {
        cout << "Invalid quantity.\n";
        return;
    }
    
    // Update book quantity and save changes
    it->quantity += amount;
    cout << "Successfully returned " << amount << " copy/copies of \"" 
         << it->title << "\".\n";
    saveBooks(books);
    logReturn(*it, amount);
    loadBooks(books);  // Reload to ensure sync
}

// Main function - program entry point
int main() {
    vector<Book> books;  // Vector to store all books
    loadBooks(books);    // Load books from file
    
    int choice;
    // Main program loop
    do {
        // Display menu
        cout << "\nLibrary System Menu\n";
        cout << string(20, '=') << endl;
        cout << "1. View Available Books\n";
        cout << "2. Borrow Book\n";
        cout << "3. Return Book\n";
        cout << "4. View Borrowed Books\n";
        cout << "5. Exit\n";
        cout << string(20, '=') << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Clear input buffer
        
        // Process user choice
        switch (choice) {
            case 1: displayAvailableBooks(books); break;
            case 2: borrowBook(books); break;
            case 3: returnBook(books); break;
            case 4: displayBorrowedBooks(books); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);  // Continue until user chooses to exit

    return 0;
}