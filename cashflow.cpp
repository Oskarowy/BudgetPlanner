#include "cashflow.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <windows.h>
#include <time.h>

int CashFlow::getUserID() {
    return userID;
}

string CashFlow::getDate() {
    return flowDate;
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

void CashFlow::setDate() {
    ;
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

    while(xmlFile.FindElem("INCOME"))
    {
        xmlFile.IntoElem();
        xmlFile.OutOfElem();
        numberOfIncomes++;
    }

    return numberOfIncomes;
}

int addNewIncome(vector <Income> &incomes, int numberOfIncomes, int loggedUserID) {
    Income singleIncomeData;

    singleIncomeData.setID(numberOfIncomes+1);
    singleIncomeData.setUserID(loggedUserID);
    //singleIncomeData.setDate();
    singleIncomeData.setItem();
    singleIncomeData.setAmount();

    //if(singleIncomeData.getDate() != MINIMALNA DATA) {

    incomes.push_back(singleIncomeData);

    CMarkup xmlFile;
    xmlFile.Load("incomes.xml");

    xmlFile.AddElem("INCOME");
    xmlFile.IntoElem();
    xmlFile.AddElem("ID", singleIncomeData.getID());
    xmlFile.AddElem("USER ID", singleIncomeData.getUserID());
    xmlFile.AddElem("DATE", singleIncomeData.getDate());
    xmlFile.AddElem("ITEM", singleIncomeData.getItem());
    xmlFile.AddElem("AMOUNT", convertDoubleToXMLStringFormat(singleIncomeData.getAmount()));
    xmlFile.OutOfElem();
    xmlFile.Save("incomes.xml");

    cout << "Dane nowego przychodu zapisano pomyslnie" << endl;
    Sleep(1000);
    numberOfIncomes++;
    /*} else {
        cout << endl << "Dane przychodu nie zostaly zapisane, sprobuj ponownie..." << endl;
        Sleep(1000);
    }*/

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
        xmlFile.FindElem("USER ID");
        singleIncomeData.setUserID(convertStrToInt(xmlFile.GetData()));
        //xmlFile.FindElem("DATE");
        //singleIncomeData.setDate(xmlFile.GetData());
        xmlFile.FindElem("ITEM");
        singleIncomeData.setItem(xmlFile.GetData());
        xmlFile.FindElem("AMOUNT");
        singleIncomeData.setAmount(convertToCorrectDoubleFormat(xmlFile.GetData()));
        xmlFile.OutOfElem();

        if(singleIncomeData.getUserID()==loggedUserID) incomes.push_back(singleIncomeData);
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

    while(xmlFile.FindElem("EXPENSE"))
    {
        xmlFile.IntoElem();
        xmlFile.OutOfElem();
        numberOfExpenses++;
    }

    return numberOfExpenses;
}

int addNewExpense(vector <Expense> &expenses, int numberOfExpenses, int loggedUserID) {
    Expense singleExpenseData;

    singleExpenseData.setID(numberOfExpenses+1);
    singleExpenseData.setUserID(loggedUserID);
    //singleExpenseData.setDate();
    singleExpenseData.setItem();
    singleExpenseData.setAmount();

    //if(singleExpenseData.getDate() != MINIMALNA DATA) {

    expenses.push_back(singleExpenseData);

    CMarkup xmlFile;
    xmlFile.Load("expenses.xml");

    xmlFile.AddElem("EXPENSE");
    xmlFile.IntoElem();
    xmlFile.AddElem("ID", singleExpenseData.getID());
    xmlFile.AddElem("USER ID", singleExpenseData.getUserID());
    xmlFile.AddElem("DATE", singleExpenseData.getDate());
    xmlFile.AddElem("ITEM", singleExpenseData.getItem());
    xmlFile.AddElem("AMOUNT", convertDoubleToXMLStringFormat(singleExpenseData.getAmount()));
    xmlFile.OutOfElem();
    xmlFile.Save("expenses.xml");

    cout << "Dane nowego wydatku zapisano pomyslnie" << endl;
    Sleep(1000);
    numberOfExpenses++;
    /*} else {
        cout << endl << "Dane wydatku nie zostaly zapisane, sprobuj ponownie..." << endl;
        Sleep(1000);
    }*/

    return numberOfExpenses;
}

void readUserExpensesFromFile(vector <Expense> &expenses, int loggedUserID) {

    Expense singleExpenseData;

    CMarkup xmlFile;
    xmlFile.Load("expenses.xml");

    while(xmlFile.FindElem("INCOME")) {
        xmlFile.IntoElem();
        xmlFile.FindElem("ID");
        singleExpenseData.setID(convertStrToInt(xmlFile.GetData()));
        xmlFile.FindElem("USER ID");
        singleExpenseData.setUserID(convertStrToInt(xmlFile.GetData()));
        //xmlFile.FindElem("DATE");
        //singleExpenseData.setDate(xmlFile.GetData());
        xmlFile.FindElem("ITEM");
        singleExpenseData.setItem(xmlFile.GetData());
        xmlFile.FindElem("AMOUNT");
        singleExpenseData.setAmount( convertToCorrectDoubleFormat(xmlFile.GetData()));
        xmlFile.OutOfElem();

        if(singleExpenseData.getUserID()==loggedUserID) expenses.push_back( singleExpenseData );
    }
}
