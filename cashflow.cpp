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

double CashFlow::convertToCorrectDoubleFormat(string doubleValueAsString) {
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

int Income::getID() {
    return id;
}

void Income::setID(int newIncomeID){
    id = newIncomeID;
}

int Expense::getID() {
    return id;
}

void Expense::setID(int newExpenseID){
    id = newExpenseID;
}

int addNewIncome(vector <Income> &incomes, int numberOfIncomes, int loggedUserID){
    Income singleIncomeData;

    singleIncomeData.setID(numberOfIncomes+1);
    singleIncomeData.setUserID(loggedUserID);
    //singleIncomeData.setDate();
    singleIncomeData.setItem();
    singleIncomeData.setAmount();

    //if(singleIncomeData.getDate() != MINIMALNA DATA) {

    ///// konwersja na poprawny zapis kwoty do pliku xml /////
    double amount = singleIncomeData.getAmount();
    int moreThanOne = amount;
    double lessThanOne = amount-moreThanOne;

    string amountAsStr = "";
    amountAsStr+=convertIntToStr(moreThanOne);
    amountAsStr+=".";
    amountAsStr+=convertIntToStr((lessThanOne)*100);


        incomes.push_back(singleIncomeData);

        CMarkup xmlFile;
        xmlFile.Load("incomes.xml");

        xmlFile.AddElem("INCOME");
        xmlFile.IntoElem();
            xmlFile.AddElem("ID", singleIncomeData.getID());
            xmlFile.AddElem("USER ID", singleIncomeData.getUserID());
            xmlFile.AddElem("DATE", singleIncomeData.getDate());
            xmlFile.AddElem("ITEM", singleIncomeData.getItem());
            xmlFile.AddElem("AMOUNT", amountAsStr);
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
