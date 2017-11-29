#include "cashflow.h"
#include "cDate.h"
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
    string loggedUserName = "";
    string loggedUserSurname = "";

    numberOfUsers = readUsersFromFile(users);

    vector <Income> incomes;
    int numberOfIncomes = 0;
    numberOfIncomes = readAllIncomesFromFile();


    vector <Expense> expenses;
    int numberOfExpenses = 0;
    numberOfExpenses = readAllExpensesFromFile();

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
                    loggedUserName = users[loggedUserID-1].getName();
                    loggedUserSurname = users[loggedUserID-1].getSurname();
                    readUserIncomesFromFile(incomes,loggedUserID);
                    readUserExpensesFromFile(expenses,loggedUserID);
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
            cout << "              Imie: " << loggedUserName << endl;
            cout << "              Nazwisko: " << loggedUserSurname << endl << endl;
            cout << "--------------------------------------------------------" << endl<< endl;
            cout << "1. Dodaj przychod" << endl;
            cout << "2. Dodaj wydatek" << endl;
            cout << "3. Bilans z biezacego miesiaca" << endl;
            cout << "4. Bilans z poprzedniego miesiaca" << endl;
            cout << "5. Bilans z wybranego okresu" << endl;
            cout << "6. Zmien haslo" << endl;
            cout << "7. Wyloguj sie" << endl;

            cin >> choosenMenuOption;

            switch (choosenMenuOption) {
            case '1':
                numberOfIncomes = addNewIncome(incomes, numberOfIncomes,loggedUserID);
                break;
            case '2':
                numberOfExpenses = addNewExpense(expenses, numberOfExpenses, loggedUserID);
                break;
            case '3':
                showUserIncomesAndExpensesBalance(incomes, expenses);
                break;
           case '4':
                ;
                break;
            case '5':
                ;
                break;
            case '6':
                users[loggedUserID-1].setPassword();
                saveInFile(users);
                confirmationOfChange();
                break;
            case '7':
                loggedUserID = 0;
                loggedUserName = "";
                loggedUserSurname = "";
                incomes.clear();
                expenses.clear();
                firstMenu = true;
                break;
            default:
                choosenOptionIsNotCorrect();
            }
        }
    }
    return 0;
}
