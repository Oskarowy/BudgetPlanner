#include "cashflow.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <windows.h>

int CashFlow::getUserID() {
    return userID;
}

string CashFlow::getDate() {
    return date;
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
    string extractedNumber = "";
    int counter = 1;

    for(int i = 0, end = doubleValueAsString.length(); i < end; i++) {
        if((doubleValueAsString[i] != ',')&&(doubleValueAsString[i] != '.')) {
            extractedNumber+=doubleValueAsString[i];
        } else {
            if(counter == 1) correctValue+=convertStrToInt(extractedNumber);
            if(counter == 2) {
                double fraction = convertStrToInt(extractedNumber)/100;
                correctValue+=fraction;
            }
            counter++;
        }
    }
    return correctValue;
}
