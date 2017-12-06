#include "cashflow.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <windows.h>
#include <iomanip>

int CashFlow::getUserID() {
    return userID;
}

string CashFlow::getDate() {
    return flowDate;
}

cDate getDateAsObject(string dateAsString) {

    cDate dateOfCashFlow;
    dateAsString+="-";

    string extractedNumber = "";
    int counter = 1;

    for(int i = 0, end = dateAsString.length(); i < end; i++) {
        if(dateAsString[i] == '-') {
            if(counter == 1) dateOfCashFlow.setYear(convertStrToInt(extractedNumber));
            if(counter == 2) dateOfCashFlow.setMonth(convertStrToInt(extractedNumber));
            if(counter == 3) dateOfCashFlow.setDay(convertStrToInt(extractedNumber));
            counter++;
            extractedNumber = "";
        } else extractedNumber+=dateAsString[i];
    }
    return dateOfCashFlow;
}

string CashFlow::getItem() {
    return item;
}

double CashFlow::getAmount() {
    return amount;
}

void CashFlow::setUserID(int loggedUserID) {
    userID = loggedUserID;
}

void CashFlow::setDate(string newValue) {
    flowDate = newValue;
}

void CashFlow::setDate() {
    cDate dateOfCashFlow;
    string formattedDate;

    cout << "Czy dodac rekord z data dzisiejsza? (T/N)" << endl;
    cout << "Twoj wybor: ";
    char userChoose;
    cin >> userChoose;

    switch(userChoose) {
    case 'T':
    case 't':
        dateOfCashFlow.setAsToday();
        break;
    case 'N':
    case 'n':
        do {
            dateOfCashFlow.setYear();
            dateOfCashFlow.setMonth();
            dateOfCashFlow.setDay();
            if(dateOfCashFlow.isDateCorrect()== false) {
                cout << endl << "Wprowadzono niepoprawna date..." << endl;
                cout << "UWAGA: Data nie moze byc wczesniejsza niz 2000-01-01..." << endl << endl;
                Sleep(500);
            }
        } while (dateOfCashFlow.isDateCorrect()!=true);
        break;
    default:
        choosenOptionIsNotCorrect();
    }
    if(dateOfCashFlow.isDateCorrect()) {
        formattedDate = dateOfCashFlow.formatDate();
        flowDate = formattedDate;
        cout << "Data ustawiona na " << flowDate << endl;
        Sleep(500);
    }
}

void CashFlow::setItem() {
    string newItem;
    cout << "Podaj czego dotyczy: ";
    cin.sync();
    getline(cin,newItem);
    item = newItem;
}

void CashFlow::setAmount() {
    string newValue;
    cout << "Podaj kwote: ";
    cin.sync();
    getline(cin,newValue);
    amount = convertToCorrectDoubleFormat(newValue);
}

void CashFlow::setItem(string newValue) {
    item = newValue;
}

void CashFlow::setAmount(double newValue) {
    amount = newValue;
}

double convertToCorrectDoubleFormat(string doubleValueAsString) {
    doubleValueAsString+= ".";
    double correctValue = 0.0;
    double fraction = 0.0;
    string extractedNumber = "";
    int counter = 1;

    for(int i = 0, end = doubleValueAsString.length(); i < end; i++) {
        if((doubleValueAsString[i] == ',')||(doubleValueAsString[i] == '.')) {
            if(counter == 1) correctValue+=convertStrToInt(extractedNumber);
            if(counter == 2) {
                fraction = convertStrToInt(extractedNumber);
                fraction/=100;
                correctValue+=fraction;
            }
            counter++;
            extractedNumber = "";
        } else extractedNumber+=doubleValueAsString[i];
    }
    return correctValue;
}
string convertDoubleToXMLStringFormat(double value) {

    int moreThanOne = value;
    double theRest = value-moreThanOne;

    string amountAsStr = "";
    amountAsStr+=convertIntToStr(moreThanOne);
    amountAsStr+=".";
    amountAsStr+=convertIntToStr((theRest)*100);

    return amountAsStr;
}

int Income::getID() {
    return id;
}

void Income::setID(int newIncomeID) {
    id = newIncomeID;
}

int readAllIncomesFromFile() {

    int numberOfIncomes = 0;

    CMarkup xmlFile;
    xmlFile.Load("incomes.xml");

    while(xmlFile.FindElem("INCOME")) {
        xmlFile.IntoElem();
        xmlFile.OutOfElem();
        numberOfIncomes++;
    }

    return numberOfIncomes;
}

int addNewIncome(vector <Income> &incomes, int numberOfIncomes, int loggedUserID) {
    Income singleIncomeData;
    cDate minDate,dateToCheck;

    singleIncomeData.setID(numberOfIncomes+1);
    singleIncomeData.setUserID(loggedUserID);
    singleIncomeData.setDate();
    singleIncomeData.setItem();
    singleIncomeData.setAmount();

    dateToCheck = getDateAsObject(singleIncomeData.getDate());

    if(whichDateIsEarlier(dateToCheck, minDate)>=0) {

        incomes.push_back(singleIncomeData);

        CMarkup xmlFile;
        xmlFile.Load("incomes.xml");

        xmlFile.AddElem("INCOME");
        xmlFile.IntoElem();
        xmlFile.AddElem("ID", singleIncomeData.getID());
        xmlFile.AddElem("USER", singleIncomeData.getUserID());
        xmlFile.AddElem("DATE", singleIncomeData.getDate());
        xmlFile.AddElem("ITEM", singleIncomeData.getItem());
        xmlFile.AddElem("AMOUNT", convertDoubleToXMLStringFormat(singleIncomeData.getAmount()));
        xmlFile.OutOfElem();
        xmlFile.Save("incomes.xml");

        cout << "Dane nowego przychodu zapisano pomyslnie" << endl;
        Sleep(1000);
        numberOfIncomes++;
    } else {
        cout << "Dane przychodu nie zostaly zapisane, sprobuj ponownie..." << endl;
        Sleep(1000);
    }

    return numberOfIncomes;
}

void readUserIncomesFromFile(vector <Income> &incomes, int loggedUserID) {

    Income singleIncomeData;

    CMarkup xmlFile;
    xmlFile.Load("incomes.xml");

    while(xmlFile.FindElem("INCOME")) {
        xmlFile.IntoElem();
        xmlFile.FindElem("ID");
        singleIncomeData.setID(convertStrToInt(xmlFile.GetData()));
        xmlFile.FindElem("USER");
        singleIncomeData.setUserID(convertStrToInt(xmlFile.GetData()));
        xmlFile.FindElem("DATE");
        singleIncomeData.setDate(xmlFile.GetData());
        xmlFile.FindElem("ITEM");
        singleIncomeData.setItem(xmlFile.GetData());
        xmlFile.FindElem("AMOUNT");
        singleIncomeData.setAmount(convertToCorrectDoubleFormat(xmlFile.GetData()));
        xmlFile.OutOfElem();

        if(singleIncomeData.getUserID() == loggedUserID) incomes.push_back(singleIncomeData);
    }
}

int Expense::getID() {
    return id;
}

void Expense::setID(int newExpenseID) {
    id = newExpenseID;
}

int readAllExpensesFromFile() {

    int numberOfExpenses = 0;

    CMarkup xmlFile;
    xmlFile.Load("expenses.xml");

    while(xmlFile.FindElem("EXPENSE")) {
        xmlFile.IntoElem();
        xmlFile.OutOfElem();
        numberOfExpenses++;
    }

    return numberOfExpenses;
}

int addNewExpense(vector <Expense> &expenses, int numberOfExpenses, int loggedUserID) {
    Expense singleExpenseData;
    cDate minDate,dateToCheck;

    singleExpenseData.setID(numberOfExpenses+1);
    singleExpenseData.setUserID(loggedUserID);
    singleExpenseData.setDate();
    singleExpenseData.setItem();
    singleExpenseData.setAmount();

    dateToCheck = getDateAsObject(singleExpenseData.getDate());

    if(whichDateIsEarlier(dateToCheck, minDate)>=0) {

        expenses.push_back(singleExpenseData);

        CMarkup xmlFile;
        xmlFile.Load("expenses.xml");

        xmlFile.AddElem("EXPENSE");
        xmlFile.IntoElem();
        xmlFile.AddElem("ID", singleExpenseData.getID());
        xmlFile.AddElem("USER", singleExpenseData.getUserID());
        xmlFile.AddElem("DATE", singleExpenseData.getDate());
        xmlFile.AddElem("ITEM", singleExpenseData.getItem());
        xmlFile.AddElem("AMOUNT", convertDoubleToXMLStringFormat(singleExpenseData.getAmount()));
        xmlFile.OutOfElem();
        xmlFile.Save("expenses.xml");

        cout << "Dane nowego wydatku zapisano pomyslnie" << endl;
        Sleep(1000);
        numberOfExpenses++;
    } else {
        cout << "Dane wydatku nie zostaly zapisane, sprobuj ponownie..." << endl;
        Sleep(1000);
    }

    return numberOfExpenses;
}

void readUserExpensesFromFile(vector <Expense> &expenses, int loggedUserID) {

    Expense singleExpenseData;

    CMarkup xmlFile;
    xmlFile.Load("expenses.xml");

    while(xmlFile.FindElem("EXPENSE")) {
        xmlFile.IntoElem();
        xmlFile.FindElem("ID");
        singleExpenseData.setID(convertStrToInt(xmlFile.GetData()));
        xmlFile.FindElem("USER");
        singleExpenseData.setUserID(convertStrToInt(xmlFile.GetData()));
        xmlFile.FindElem("DATE");
        singleExpenseData.setDate(xmlFile.GetData());
        xmlFile.FindElem("ITEM");
        singleExpenseData.setItem(xmlFile.GetData());
        xmlFile.FindElem("AMOUNT");
        singleExpenseData.setAmount( convertToCorrectDoubleFormat(xmlFile.GetData()));
        xmlFile.OutOfElem();

        if(singleExpenseData.getUserID()==loggedUserID) expenses.push_back( singleExpenseData );
    }
}

void showUserBalanceForCurrentMonth(vector <Income> &incomes, vector <Expense> &expenses) {
    cDate today, dateToCheck;
    today.setAsToday();
    int currentYear = today.getYear();
    int currentMonth = today.getMonth();

    double incomesSum = 0.0;
    double expensesSum = 0.0;
    int noIncomes = 0;
    int noExpenses = 0;

    vector <Income>::iterator incItr;
    int counter = 0;

    vector <Income> matchedIncomes;
    vector <long long int> incSorter;
    long long int dateToSort;

    if(!incomes.empty()) {
        for(incItr = incomes.begin(); incItr != incomes.end(); incItr++) {
            dateToCheck = getDateAsObject(incomes[counter].getDate());
            dateToSort = dateToCheck.getDateAsLongInt();

            if((dateToCheck.getYear()==currentYear)&&(dateToCheck.getMonth()==currentMonth)) {
                incSorter.push_back(dateToSort);
                matchedIncomes.push_back(incomes[counter]);
                noIncomes++;
                incomesSum+=incomes[counter].getAmount();
            }
            counter++;
        } if(noIncomes == 0) thisUserHasGotNoIncomes();
    } else thisUserHasGotNoIncomes();

    vector <Expense>::iterator expItr;
    counter = 0;

    vector <Expense> matchedExpenses;
    vector <long long int> expSorter;
    dateToSort = 0;

    if(!expenses.empty()) {
        for(expItr = expenses.begin(); expItr != expenses.end(); expItr++) {
            dateToCheck = getDateAsObject(expenses[counter].getDate());
            dateToSort = dateToCheck.getDateAsLongInt();

            if((dateToCheck.getYear()==currentYear)&&(dateToCheck.getMonth()==currentMonth)) {

                expSorter.push_back(dateToSort);
                matchedExpenses.push_back(expenses[counter]);
                noExpenses++;
                expensesSum+=expenses[counter].getAmount();
            }
            counter++;
        } if(noExpenses == 0) thisUserHasGotNoExpenses();
    } else  thisUserHasGotNoExpenses();

    stable_sort(incSorter.begin(), incSorter.end());
    stable_sort(expSorter.begin(), expSorter.end());

    system("cls");

    cout << endl << "---------------------- PRZYCHODY ----------------------" << endl;

    for(int i = 0; i < incSorter.size(); i++){

        string sortingDate = changeDateToStr(incSorter[i]);
        counter = 0;

        for(incItr = matchedIncomes.begin(); incItr != matchedIncomes.end(); incItr++){

            if(matchedIncomes[counter].getDate()==sortingDate){
                cout << endl << "ID przychodu: " << matchedIncomes[counter].getID() << endl;
                cout << "Data przychodu: " << matchedIncomes[counter].getDate() << endl;
                cout << "Czego dotyczy: " << matchedIncomes[counter].getItem() << endl;
                cout << "Kwota przychodu: " << matchedIncomes[counter].getAmount() << endl;
                cout << "--------------------------------------------------------" << endl;
            } counter++;
        }
    }

    cout << endl << "----------------------- WYDATKI -----------------------" << endl;

    for(int i = 0; i < expSorter.size(); i++) {

        string sortingDate = changeDateToStr(expSorter[i]);
        counter = 0;

        for(expItr = matchedExpenses.begin(); expItr != matchedExpenses.end(); expItr++){

            if(matchedExpenses[counter].getDate() == sortingDate){

                cout << endl << "ID wydatku: " << matchedExpenses[counter].getID() << endl;
                cout << "Data wydatku: " << matchedExpenses[counter].getDate() << endl;
                cout << "Czego dotyczy: " << matchedExpenses[counter].getItem() << endl;
                cout << "Kwota wydatku: " << matchedExpenses[counter].getAmount() << endl;
                cout << "--------------------------------------------------------" << endl;
            } counter++;

        }
    }

    checkUserBalance(incomesSum,expensesSum);
    pressAnyButtonMesage();
}

void showUserBalanceForPreviousMonth(vector <Income> &incomes, vector <Expense> &expenses) {
    cDate today, dateToCheck;
    today.setAsToday();
    int currentYear = today.getYear();
    int previousMonth = today.getMonth()-1;

    double incomesSum = 0.0;
    double expensesSum = 0.0;
    int noIncomes = 0;
    int noExpenses = 0;

    vector <Income>::iterator incItr;
    int counter = 0;

    vector <Income> matchedIncomes;
    vector <long long int> incSorter;
    long long int dateToSort;

    if(!incomes.empty()) {
        for(incItr = incomes.begin(); incItr != incomes.end(); incItr++) {
            dateToCheck = getDateAsObject(incomes[counter].getDate());
            dateToSort = dateToCheck.getDateAsLongInt();

            if(((dateToCheck.getYear()==currentYear)&&(dateToCheck.getMonth()==previousMonth)) || ((dateToCheck.getYear()+1==currentYear)&&(dateToCheck.getMonth()==12))) {
                incSorter.push_back(dateToSort);
                matchedIncomes.push_back(incomes[counter]);
                noIncomes++;
                incomesSum+=incomes[counter].getAmount();
            }
            counter++;
        } if(noIncomes == 0) thisUserHasGotNoIncomes();
    } else thisUserHasGotNoIncomes();

    vector <Expense>::iterator expItr;
    counter = 0;

    vector <Expense> matchedExpenses;
    vector <long long int> expSorter;
    dateToSort = 0;

    if(!expenses.empty()) {
        for(expItr = expenses.begin(); expItr != expenses.end(); expItr++) {
            dateToCheck = getDateAsObject(expenses[counter].getDate());
            dateToSort = dateToCheck.getDateAsLongInt();

            if(((dateToCheck.getYear()==currentYear)&&(dateToCheck.getMonth()==previousMonth)) || ((dateToCheck.getYear()+1==currentYear)&&(dateToCheck.getMonth()==12))) {

                expSorter.push_back(dateToSort);
                matchedExpenses.push_back(expenses[counter]);
                noExpenses++;
                expensesSum+=expenses[counter].getAmount();
            }
            counter++;
        } if(noExpenses == 0) thisUserHasGotNoExpenses();
    } else  thisUserHasGotNoExpenses();

    stable_sort(incSorter.begin(), incSorter.end());
    stable_sort(expSorter.begin(), expSorter.end());

    system("cls");

    cout << endl << "---------------------- PRZYCHODY ----------------------" << endl;

    for(int i = 0; i < incSorter.size(); i++){

        string sortingDate = changeDateToStr(incSorter[i]);
        counter = 0;

        for(incItr = matchedIncomes.begin(); incItr != matchedIncomes.end(); incItr++){

            if(matchedIncomes[counter].getDate()==sortingDate){
                cout << endl << "ID przychodu: " << matchedIncomes[counter].getID() << endl;
                cout << "Data przychodu: " << matchedIncomes[counter].getDate() << endl;
                cout << "Czego dotyczy: " << matchedIncomes[counter].getItem() << endl;
                cout << "Kwota przychodu: " << matchedIncomes[counter].getAmount() << endl;
                cout << "--------------------------------------------------------" << endl;
            } counter++;
        }
    }

    cout << endl << "----------------------- WYDATKI -----------------------" << endl;

    for(int i = 0; i < expSorter.size(); i++) {

        string sortingDate = changeDateToStr(expSorter[i]);
        counter = 0;

        for(expItr = matchedExpenses.begin(); expItr != matchedExpenses.end(); expItr++){

            if(matchedExpenses[counter].getDate() == sortingDate){

                cout << endl << "ID wydatku: " << matchedExpenses[counter].getID() << endl;
                cout << "Data wydatku: " << matchedExpenses[counter].getDate() << endl;
                cout << "Czego dotyczy: " << matchedExpenses[counter].getItem() << endl;
                cout << "Kwota wydatku: " << matchedExpenses[counter].getAmount() << endl;
                cout << "--------------------------------------------------------" << endl;
            } counter++;

        }
    }

    checkUserBalance(incomesSum,expensesSum);
    pressAnyButtonMesage();
}

void showUserBalanceForSpecifiedPeriod(vector <Income> &incomes, vector <Expense> &expenses) {
    cDate periodStart, periodEnd, dateToCheck;

    cout << "Ustaw okres, za jaki ma byc wyswietlony bilans." << endl;

    cout << endl << "Ustawienie daty poczatkowej:" << endl;
    do {
        periodStart.setYear();
        periodStart.setMonth();
        periodStart.setDay();
        if(periodStart.isDateCorrect()== false) {
            cout << endl << "Wprowadzono niepoprawna date..." << endl;
            cout << "UWAGA: Data nie moze byc wczesniejsza niz 2000-01-01..." << endl << endl;
            Sleep(500);
        }
    } while (periodStart.isDateCorrect()!=true);
    if(periodStart.isDateCorrect()) {
        string formattedDate = periodStart.formatDate();
        cout << "Data poczatku bilansu ustawiona na " << formattedDate << endl;
        Sleep(500);
    }

    cout << endl <<"Ustawienie daty koncowej:" << endl;
    cout << "Czy ustawic na date dzisiejsza? (T/N)" << endl;
    char userChoice;
    cin >> userChoice;

    if(userChoice == 'T' || userChoice == 't') periodEnd.setAsToday();
    else {
        do {
            periodEnd.setYear();
            periodEnd.setMonth();
            periodEnd.setDay();
            if(periodEnd.isDateCorrect()== false) {
                cout << endl << "Wprowadzono niepoprawna date..." << endl;
                cout << "UWAGA: Data nie moze byc wczesniejsza niz 2000-01-01..." << endl << endl;
                Sleep(500);
            }
        } while (periodEnd.isDateCorrect()!=true);
    }
    if(periodEnd.isDateCorrect()) {
        string formattedDate = periodEnd.formatDate();
        cout << "Data konca bilansu ustawiona na " << formattedDate << endl;
        Sleep(500);
    }

    double incomesSum = 0.0;
    double expensesSum = 0.0;

    int noIncomes = 0;
    int noExpenses = 0;

    vector <Income>::iterator incItr;
    int counter = 0;

    system("cls");

    cout << endl << "---------------------- PRZYCHODY ----------------------" << endl;

    if(!incomes.empty()) {
        for(incItr = incomes.begin(); incItr != incomes.end(); incItr++) {
            dateToCheck = getDateAsObject(incomes[counter].getDate());

            if(((whichDateIsEarlier(periodStart,dateToCheck))<=0)&&(whichDateIsEarlier(dateToCheck, periodEnd))<=0) {
                cout << endl << "ID przychodu: " << incomes[counter].getID() << endl;
                cout << "Data przychodu: " << incomes[counter].getDate() << endl;
                cout << "Czego dotyczy: " << incomes[counter].getItem() << endl;
                cout << "Kwota przychodu: " << incomes[counter].getAmount() << endl;
                cout << "--------------------------------------------------------" << endl;
                noIncomes++;
                incomesSum+=incomes[counter].getAmount();
            } counter++;
        } if(noIncomes == 0) thisUserHasGotNoIncomes();
    } else thisUserHasGotNoIncomes();

    cout << endl << "----------------------- WYDATKI -----------------------" << endl;

    vector <Expense>::iterator expItr;
    counter = 0;

    if(!expenses.empty()) {
        for(expItr = expenses.begin(); expItr != expenses.end(); expItr++) {
            dateToCheck = getDateAsObject(expenses[counter].getDate());

            if(((whichDateIsEarlier(periodStart,dateToCheck))<=0)&&(whichDateIsEarlier(dateToCheck, periodEnd))<=0) {
                cout << endl << "ID wydatku: " << expenses[counter].getID() << endl;
                cout << "Data wydatku: " << expenses[counter].getDate() << endl;
                cout << "Czego dotyczy: " << expenses[counter].getItem() << endl;
                cout << "Kwota wydatku: " << expenses[counter].getAmount() << endl;
                cout << "--------------------------------------------------------" << endl;
                noExpenses++;
                expensesSum+=expenses[counter].getAmount();
            } counter++;
        } if(noExpenses == 0) thisUserHasGotNoExpenses();
    } else  thisUserHasGotNoExpenses();

    checkUserBalance(incomesSum,expensesSum);
    pressAnyButtonMesage();
}

void thisUserHasGotNoIncomes() {
    cout << endl << "Lista przychodow tego Uzytkownika jest pusta." << endl;
    cout << "Najpierw dodaj jakis przychod..." << endl << endl;
    cout << "--------------------------------------------------------" << endl;
}
void thisUserHasGotNoExpenses() {
    cout << endl << "Lista wydatkow tego Uzytkownika jest pusta." << endl;
    cout << "Najpierw dodaj jakis wydatek..." << endl << endl;
    cout << "--------------------------------------------------------" << endl;
}

void checkUserBalance(double incomesSum, double expensesSum) {

    double balance = incomesSum - expensesSum;
    double zeroBalance = 0.0;

    if((balance<0.01)&&(balance>-0.01)) balance = zeroBalance;

    cout << endl << "--------------------------------------------------------" << endl;
    cout << "            Suma przychodow: " << incomesSum << endl;
    cout << "            Suma wydatkow: " << expensesSum  << endl;
    if(balance > 0)
        cout << endl << "            Wygenerowane oszczednosci: " << balance << endl;
    else if(balance < 0)
        cout << endl << "            Wygenerowane straty: " << (balance*-1) << endl;
    else if(balance == 0)
        cout << endl << "      W tym okresie przychody bilansuja wydatki..." << endl;

    cout << "--------------------------------------------------------" << endl << endl;
}

void pressAnyButtonMesage() {
    cout << "-------------- Wcisnij dowolny przycisk! ---------------" << endl;
    getch();
}
