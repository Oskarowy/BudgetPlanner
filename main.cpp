#include "user.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    vector <User> users;
    int numberOfUsers = 0;
    int loggedUserID = 0;
    string loggedUserLogin = "";

    //vector <Person> people;
    //int numberOfPeopleInTelebook = 0;

    numberOfUsers = readUsersFromFile(users);

    bool firstMenu = true;
    char choosenMenuOption;

    while(true) {
        if(choosenMenu(firstMenu)) {
            system("cls");
            cout << "--------------------------------------------------------" << endl;
            cout << "--------- Witaj w aplikacji Budget Planner! ----------" << endl;
            cout << "---- Zaloguj sie lub zarejestruj nowego Uzytkownika!----" << endl;
            cout << "--------------------------------------------------------" << endl<< endl;
            cout << "1. Rejestracja nowego Uzytkownika" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;

            cin >> choosenMenuOption;

            switch (choosenMenuOption) {
            case '1':
                numberOfUsers = addNewUser(users, numberOfUsers);
                break;
            case '2':
                loggedUserID = login(getLoggedUserID(users, numberOfUsers));
                if(loggedUserID != 0) {
                    loggedUserLogin = users[loggedUserID-1].getLogin();
                    //numberOfPeopleInTelebook = readFromFile(people,loggedUserID);
                    firstMenu = false;
                }
                break;
            case '9':
                cout << "Do zobaczenia!" << endl;
                exit(0);
                break;
            default:
                choosenOptionIsNotCorrect();
            }
        } else {
            system("cls");
            cout << "--------------------------------------------------------" << endl;
            cout << "------------- Dane zalogowanego Uzytkownika ------------" << endl << endl;
            cout << "                   Login: " << loggedUserLogin << endl;
            cout << "                   Numer ID: " << loggedUserID << endl << endl;
            cout << "--------------------------------------------------------" << endl<< endl;
            cout << "1. Dodaj nowa osobe do Ksiazki" << endl;
            cout << "2. Wyszukiwanie po imieniu" << endl;
            cout << "3. Wyszukiwanie po nazwisku" << endl;
            cout << "4. Wyswietl wszystkie osoby z Ksiazki" << endl;
            cout << "5. Usun osobe z Ksiazki" << endl;
            cout << "6. Edytuj dane osoby" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj sie" << endl;

            cin >> choosenMenuOption;

            switch (choosenMenuOption) {
            case '1':
                //numberOfPeopleInTelebook = addNewPerson(people, numberOfPeopleInTelebook, loggedUserID);
                break;
            case '2':
                //searchByName(people);
                break;
            case '3':
                //searchBySurname(people);
                break;
           /* case '4':
                /*if(isTelebookEmpty(numberOfPeopleInTelebook) == false) {
                    if(people.empty() == false) showAllPeopleData(people);
                    else {
                        cout << endl << "Ten Uzytkownik nie ma zapisanych zadnych osob w Ksiazce!" << endl;
                        Sleep(1500);
                    }
                }
                break;
            case '5':
                if(isTelebookEmpty(numberOfPeopleInTelebook) == false) {
                    system("cls");
                    cout << "--------------------------------------------------------" << endl;
                    cout << "------------ Usuwanie danych osoby z ksiazki -----------" << endl;
                    cout << "--------------------------------------------------------" << endl<< endl;
                    cout << "Za chwile wyswietlona zostanie cala zawartosc Ksiazki Adresowej." << endl;
                    cout << "Wyszukaj w niej odpowiednie ID, aby usunac przypisana do tego numeru ID osobe..." << endl << endl;
                    cout << "Aby rozpoczac wyszukiwanie, wcisnij dowolny przycisk" << endl;
                    getch();
                    system("cls");
                    showAllPeopleData(people);
                    removePerson(people);
                    numberOfPeopleInTelebook = updateNumberOfPeopleInTelebook(people,numberOfPeopleInTelebook, loggedUserID);
                }
                break;
            case '6':
                if(isTelebookEmpty(numberOfPeopleInTelebook)==false) {
                    if(people.empty()==true) {
                        cout << endl << "Ten Uzytkownik nie ma zapisanych zadnych osob w Ksiazce!" << endl;
                        Sleep(1500);
                    } else {
                        system("cls");
                        cout << "--------------------------------------------------------" << endl;
                        cout << "----------------- Edycja danych osoby ------------------" << endl;
                        cout << "--------------------------------------------------------" << endl<< endl;
                        cout << "Za chwile wyswietlona zostanie cala zawartosc Ksiazki Adresowej." << endl;
                        cout << "Wyszukaj w niej odpowiednie ID, aby edytowac dane przypisanej do tego numeru osoby..." << endl << endl;
                        cout << "Aby rozpoczac wyszukiwanie, wcisnij dowolny przycisk" << endl;
                        getch();
                        system("cls");
                        showAllPeopleData(people);
                        rewriteFile(editPersonData(people));
                        numberOfPeopleInTelebook = updateNumberOfPeopleInTelebook(people,numberOfPeopleInTelebook, loggedUserID);
                    }
                }
                break;
            case '7':
                users[loggedUserID-1].setNewPassword();
                saveInFile(users);
                confirmationOfChange();
                break;
           */ case '8':
                loggedUserID = 0;
                loggedUserLogin = "";
                //people.clear();
                firstMenu = true;
                break;
            default:
                choosenOptionIsNotCorrect();
            }
        }
    }
    return 0;
}
