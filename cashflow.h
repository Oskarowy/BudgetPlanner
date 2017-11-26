#include <iostream>
#include <vector>
#include <time.h>
#include "Markup.h"
#include "user.h"

using namespace std;

/*class Date {

protected:
    unsigned int year;
    unsigned int month;
    unsigned int day;

public:
    Date(int y=2000, int m=1, int d=1) {
        this->year = y;
        this->month = m;
        this->day = d;
    }

    friend class CashFlow;

    void getDate() {
        cout << year << "-" << month << "-" << day;
    }

    void setDate() {
        unsigned int y,m,d;
        cout << "Podaj rok: ";
        cin >> y;
        cout << "Podaj miesiac: ";
        cin >> m;
        cout << "Podaj dzien: ";
        cin >> d;

        if((year<2000)||(month>12)||(day>31)) cout << "Data niepoprawna, wprowadz date wieksza niz 2000-01-01!" << endl;
        else {
            year = y;
            month = m;
            day = d;
        }
    }
};*/

class CashFlow {

protected:
    int id, userID;
    string flowDate;
    string item;
    double amount;

public:
    CashFlow( int dID = 0, int dUserID = 0, string dFlowDate = "2000-01-01", string dItem = "brak", double dAmount = 0.0 ) {
        id = dID;
        userID = dUserID;
        this->flowDate = dFlowDate;
        this->item = dItem;
        this->amount = dAmount;
    }

    virtual int getID() = 0;
    int getUserID();
    string getDate();
    string getItem();
    double getAmount();

    virtual void setID(int newID) = 0;
    void setUserID(int loggedUserID);
    void setDate();
    void setItem();
    void setAmount();
    void setItem(string newValue);
    void setAmount(double newValue);
};

double convertToCorrectDoubleFormat(string newValue);

class Income : public CashFlow {
public:
    int getID();
    void setID(int newIncomeID);

};

int addNewIncome(vector <Income> &incomes, int numberOfIncomes, int loggedUserID);
int readIncomesFromFile(vector <Income> &incomes, int loggedUserID);

class Expense : public CashFlow {
public:
    int getID();
    void setID(int newExpenseID);
};

int addNewExpense(vector <Expense> &expenses, int numberOfExpenses, int loggedUserID);
int readExpensesFromFile(vector <Expense> &expenses, int loggedUserID);



