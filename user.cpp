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

int readUsersFromFile(vector <User> &users) {

    int numberOfUsers = 0;
    User singleUserData;

    CMarkup xmlFile;
    xmlFile.Load("users.xml");

    while(xmlFile.FindElem("USER")){
        xmlFile.IntoElem();
            xmlFile.FindElem("ID");
            singleUserData.setID(convertStrToInt(xmlFile.GetData()));
            xmlFile.FindElem("LOGIN");
            singleUserData.setLogin( xmlFile.GetData());
            xmlFile.FindElem("PASSWORD");
            singleUserData.setPassword(xmlFile.GetData());
            xmlFile.FindElem("NAME");
            singleUserData.setName( xmlFile.GetData());
            xmlFile.FindElem("SURNAME");
            singleUserData.setSurname(xmlFile.GetData());
        xmlFile.OutOfElem();
        users.push_back( singleUserData );
        numberOfUsers++;
    }
    return numberOfUsers;
}

int addNewUser(vector <User> &users, int numberOfUsers) {

    User singleUserData;

    singleUserData.setID(numberOfUsers+1);
    singleUserData.setName();
    singleUserData.setSurname();
    singleUserData.setLogin();
    singleUserData.setPassword();

    if(singleUserData.getPassword() != "haslo") {

        users.push_back(singleUserData);

        CMarkup xmlFile;
        xmlFile.Load("users.xml");

        xmlFile.AddElem("USER");
        xmlFile.IntoElem();
            xmlFile.AddElem("ID", singleUserData.getID());
            xmlFile.AddElem("LOGIN", singleUserData.getLogin());
            xmlFile.AddElem("PASSWORD", singleUserData.getPassword());
            xmlFile.AddElem("NAME", singleUserData.getName());
            xmlFile.AddElem("SURNAME", singleUserData.getSurname());
        xmlFile.OutOfElem();;

        cout << "Dane nowego Uzytkownika zapisano pomyslnie" << endl;
        Sleep(1000);
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

    User singleUserData;
    vector <User>::iterator itr;
    int counter = 0;
    CMarkup xmlFile;

    for(itr = users.begin(); itr < users.end(); itr++){
    singleUserData = users[counter];

    xmlFile.AddElem("USER");
    xmlFile.IntoElem();
        xmlFile.AddElem("ID", singleUserData.getID());
        xmlFile.AddElem("LOGIN", singleUserData.getLogin());
        xmlFile.AddElem("PASSWORD", singleUserData.getPassword());
        xmlFile.AddElem("NAME", singleUserData.getName());
        xmlFile.AddElem("SURNAME", singleUserData.getSurname());
    xmlFile.OutOfElem();
    counter++;
    }
    xmlFile.Save("users.xml");
}

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
