#include <iostream>
#include <vector>
#include <time.h>
#include "Markup.h"
#include "cDate.h"

using namespace std;

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
    void setDate(string newValue);
    void setAmount(double newValue);

};

double convertToCorrectDoubleFormat(string newValue);
string convertDoubleToXMLStringFormat(double value);
cDate getDateAsObject(string dateAsString);

class Income : public CashFlow {
public:
    int getID();
    void setID(int newIncomeID);
};

int readAllIncomesFromFile();
int addNewIncome(vector <Income> &incomes, int numberOfIncomes, int loggedUserID);
void readUserIncomesFromFile(vector <Income> &incomes, int loggedUserID);

class Expense : public CashFlow {
public:
    int getID();
    void setID(int newExpenseID);
};

int readAllExpensesFromFile();
int addNewExpense(vector <Expense> &expenses, int numberOfExpenses, int loggedUserID);
void readUserExpensesFromFile(vector <Expense> &expenses, int loggedUserID);

void showUserBalanceForCurrentMonth(vector <Income> &incomes, vector <Expense> &expenses);
void showUserBalanceForPreviousMonth(vector <Income> &incomes, vector <Expense> &expenses);
void showUserBalanceForSpecifiedPeriod(vector <Income> &incomes, vector <Expense> &expenses);

void sortVectorsAndRemoveDoubles(vector <long long int> &incSorter, vector <long long int> &expSorter);
void showSortedIncomesAndExpenses( vector <Income> &matchedIncomes, vector <Expense> &matchedExpenses ,vector <long long int> &incSorter, vector <long long int> &expSorter);

void thisUserHasGotNoIncomes();
void thisUserHasGotNoExpenses();
void checkUserBalance(double incomesSum, double expensesSum);
void pressAnyButtonMesage();



