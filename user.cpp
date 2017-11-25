#include "user.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <windows.h>

using namespace std;

int convertStrToInt (string str) {
    int i;
    istringstream iss(str);
    iss >> i;
    return i;
}

string convertIntToStr(int i) {
    ostringstream ss;
    ss << i;
    string str = ss.str();
    return str;
}

string changeToLowerCase(string word) {
    transform(word.begin(), word.end(), word.begin(),::tolower);
    return word;
}

string fromCapitalLetter(string word) {
    transform(word.begin(), word.begin()+1, word.begin(),::toupper);
    return word;
}

int User::getID() {
    return id;
}

string User::getLogin() {
    return login;
}

string User::getPassword() {
    return password;
}

string User::getName() {
    return name;
}

string User::getSurname() {
    return surname;
}

void User::setID(int newID) {
    id = newID;
}

void User::setLogin() {
    string newLogin;
    cout << "Podaj login: ";
    cin.sync();
    getline(cin,newLogin);
    login = newLogin;
}

void User::setPassword() {
    string newPassword;
    string newPasswordConfirmation;
    cout << "Podaj haslo: ";
    cin.sync();
    getline(cin,newPassword);
    cout << "Podaj ponownie haslo: ";
    cin.sync();
    getline(cin,newPasswordConfirmation);

    if(newPassword == newPasswordConfirmation) password = newPassword;
    else cout << endl << "Wprowadzone hasla nie sa takie same!" << endl;
}

void User::setName() {
    string newName;
    cout << "Podaj imie: ";
    cin.sync();
    getline(cin,newName);
    name = newName;
}

void User::setSurname() {
    string newSurname;
    cout << "Podaj nazwisko: ";
    cin.sync();
    getline(cin,newSurname);
    surname = newSurname;
}

void User::setLogin(string newValue) {
    login = newValue;
}
void User::setPassword(string newValue) {
    password = newValue;
}
void User::setName(string newValue) {
    name = newValue;
}
void User::setSurname(string newValue) {
    surname = newValue;
}

/*string User::convertToFileFormat() {
    return (convertIntToStr(id) + '|' + login + '|' + password + '|' + "\n");
}

int readUsersFromFile(vector <User> &users) {

    int numberOfUsers = 0;
    User singleUserData;

    fstream file;

    string singleLine;
    string currentWord = "";
    int wordNumber = 1;

    file.open("Uzytkownicy.txt", ios::in);

    if(file.good() == false) cout << "Nie mozna otworzyc pliku!";

    while(getline(file, singleLine)) {
        for(int i = 0, end = singleLine.length(); i < end; i++) {
            if(singleLine[i] != '|') {
                currentWord += singleLine[i];
            } else {
                if(wordNumber == 1) singleUserData.setID(convertStrToInt(currentWord));
                if(wordNumber == 2) singleUserData.setLogin(currentWord);
                if(wordNumber == 3) singleUserData.setPassword(currentWord);
                if(wordNumber%3 == 0) users.push_back(singleUserData);
                currentWord = "";
                wordNumber++;
            }
        }
        wordNumber = 1;
        numberOfUsers++;
    }
    file.close();

    return numberOfUsers;
}

int addNewUser(vector <User> &users, int numberOfUsers) {

    User singleUserData;

    singleUserData.setID(numberOfUsers+1);
    singleUserData.setLogin();
    singleUserData.setPassword();

    if(singleUserData.getPassword() != "brak") {

        users.push_back(singleUserData);

        string fileFormatUserData = singleUserData.convertToFileFormat();

        fstream plik;
        plik.open("Uzytkownicy.txt",ios::out | ios::app);

        if(plik.good()) {
            plik << fileFormatUserData;
            plik.close();
            cout << "Dane nowego Uzytkownika zapisano pomyslnie" << endl;
            Sleep(1000);
        } else {
            cout << "Nie mozna otworzyc pliku Uzytkownicy.txt..." << endl;
            Sleep(1000);
        }
        numberOfUsers++;
    } else {
        cout << endl << "Dane Uzytkownika nie zostaly zapisane, sprobuj ponownie..." << endl;
        Sleep(1000);
    }
    return numberOfUsers;
}

int getLoggedUserID(vector <User> &users, int numberOfUsers) {

    int idOfLoggedUser = 0;

    if(isAnyUserRegistered(numberOfUsers) == true) {
        string loginToFind;
        string passwordToFind;

        cout << "Podaj login: ";
        cin.sync();
        getline(cin,loginToFind);

        cout << "Podaj haslo: ";
        cin.sync();
        getline(cin,passwordToFind);

        vector <User>::iterator itr;
        User singleUserData;
        int counter = 0;

        for(itr = users.begin(); itr != users.end(); itr++) {
            if(users[counter].getLogin() == loginToFind) {
                if(users[counter].getPassword() == passwordToFind) {
                    idOfLoggedUser = users[counter].getID();
                }
            }
            counter++;
        }
        if(idOfLoggedUser == 0) {
            cout << endl << "Nie znaleziono Uzytkownika z takimi danymi...";
            Sleep(1000);
        }
    }

    return idOfLoggedUser;
}

int login(int loggedUserID) {
    if(loggedUserID != 0) {
        cout << endl << "Uzytkownik o numerze ID " << loggedUserID << " zostal poprawnie zalogowany!" << endl;
        Sleep(1000);
    }
    return loggedUserID;
}

void saveInFile(vector <User> &users) {

    ofstream file("Uzytkownicy.txt");

    vector <User>::iterator itr;

    for(itr = users.begin(); itr < users.end(); itr++)
        file << itr->convertToFileFormat();
    file.close();
}
*/
bool isAnyUserRegistered(int numberOfUsers) {
    if(numberOfUsers == 0) {
        cout << "Brak zarejestrowanych Uzytkownikow..." << endl;
        Sleep(1000);
        return false;
    }
    return true;
}

void confirmationOfChange() {
    cout << endl << "Zmiany zapisano pomyslnie!" << endl;
    Sleep(1000);
}

void choosenOptionIsNotCorrect() {
    cout << endl << "Wybierz poprawna opcje z menu" << endl;
    Sleep(500);
}

bool choosenMenu (bool firstMenu) {
    if(firstMenu == true)return true;
    else return false;
}
