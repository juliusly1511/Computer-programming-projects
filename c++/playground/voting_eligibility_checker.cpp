#include <iostream>
#include <vector>
using namespace std;

int main() {
    int count, age;
    string name, gender;
    int eligibleCount = 0;
    int notEligibleCount = 0;
    int maleEligible = 0, femaleEligible = 0;
    int maleNotEligible = 0, femaleNotEligible = 0;

    vector<string> results;

    cout << "Enter the number of people: ";
    cin >> count;
    cin.ignore();

    for (int i = 0; i < count; i++) {
        cout << "Enter name: ";
        getline(cin, name);

        cout << "Enter age: ";
        cin >> age;
        cin.ignore();

        cout << "Enter gender (M/F): ";
        getline(cin, gender);

        if (age <= 0) {
            cout << "Age should be 1 and above." << endl;
            continue;
        }

        string pronoun = (gender == "F" || gender == "f") ? "She" : "He";
        string message;

        if (age < 18) {
            message = name + " (" + pronoun + ") is not eligible to vote.";
            notEligibleCount++;
            if (gender == "F" || gender == "f") femaleNotEligible++;
            else maleNotEligible++;
        } else {
            message = name + " (" + pronoun + ") is eligible to vote.";
            eligibleCount++;
            if (gender == "F" || gender == "f") femaleEligible++;
            else maleEligible++;
        }

        cout << message << endl;
        results.push_back(message);
    }

    // Output Results Table
    cout << "\n--- Voting Eligibility Table ---\n";
    for (const string& result : results) {
        cout << result << '\n';
    }

    // Output Summary
    cout << "\nSummary:\n";
    cout << "Total Eligible: " << eligibleCount << '\n';
    cout << "  Males: " << maleEligible << "\n  Females: " << femaleEligible << '\n';
    cout << "Total Not Eligible: " << notEligibleCount << '\n';
    cout << "  Males: " << maleNotEligible << "\n  Females: " << femaleNotEligible << '\n';

    return 0;
}
