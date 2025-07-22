#include <iostream>
#include <string>

using namespace std;

// checks if it has a digit
bool digit(char ch) {
    return ch >= '0' && ch <= '9';
}

// checks if it has a capital letter
bool uppercase(char ch) {
    return ch >= 'A' && ch <= 'Z';
}

// checks if it has a small letter
bool lowercase(char ch) {
    return ch >= 'a' && ch <= 'z';
}

// checks if it has a special character
bool specialchar(char ch) {
    string specialchars = "!@#$%^&*()-_=+[]{}|;:',.<>/?`~ ";
    return specialchars.find(ch) != string::npos;
}

// checks password
bool validpassword(const string& password) {
    if (password.length() < 8) {
        cout << "password should be 8 characters long and above." << endl;
        return false;
    }

    bool hasdigit = false;
    bool hasspecialchar = false;
    bool hasuppercase = false;
    bool haslowercase = false;

    for (char ch : password) {
        if (digit(ch)) hasdigit = true;
        else if (uppercase(ch)) hasuppercase = true;
        else if (lowercase(ch)) haslowercase = true;
        else if (specialchar(ch)) hasspecialchar = true;
    }

    if (!hasdigit) {
        cout << "password has no digit." << endl;
        return false;
    }

    if (!hasspecialchar) {
        cout << "password has no special character." << endl;
        return false;
    }

    if (!hasuppercase) {
        cout << "password has no uppercase letter." << endl;
        return false;
    }

    if (!haslowercase) {
        cout << "password has no lowercase letter." << endl;
        return false;
    }

    return true;
}

int main() {
    string user, pass, confirm;

    // create a username and password
    cout << "create username: ";
    getline(cin, user);
    cout << "create password: ";
    getline(cin, pass);

    while (!validpassword(pass)) {
        cout << "try again: ";
        getline(cin, pass);
    }

    cout << "confirm password: ";
    getline(cin, confirm);

    if (pass == confirm) {
        cout << "done!" << endl;
    } else {
        cout << "wrong password, try again" << endl;
        return 1;
    }

    // login system
    string inputuser, inputpass;
    cout << "\nwelcome" << endl;

    int attempts = 0;
    const int max_attempts = 3;

    while (attempts < max_attempts) {
        cout << "enter username: ";
        getline(cin, inputuser);

        cout << "enter password: ";
        getline(cin, inputpass);

        if (inputuser == user && inputpass == pass) {
            cout << "welcome, " << user;
            system("start chrome https://youtu.be/oHg5SJYRHA0?si=Abo0EtnvDd2He5Ft"); // rickroll 🤣
            return 0;
        } else {
            attempts++;
            int remaining_attempts = max_attempts - attempts;

            if (remaining_attempts > 0) {
                cout << "wrong username or password. " << remaining_attempts << " attempts remaining." << endl;

                if (attempts == 2) {
                    cout << "hint: the password starts with '" << pass[0] << "' and ends with '" << pass[pass.length() - 1] << "'" << endl << "warning! this pc will shutdown!" << endl;
                }
            }
        }
    }

    cout << "too many failed attempts. system will shut down." << endl;
    system("shutdown -s");
    return 0;
}