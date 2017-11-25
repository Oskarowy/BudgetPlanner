#include <iostream>
#include <vector>
#include "Markup.h"
#include "user.h"

using namespace std;

class CashFlow {

protected:
    int id, userID;
    string date;
    string item;
    double amount;

public:
    CashFlow( int dID = 0, int dUserID = 0, string dDate = "2000-01-01", string dItem = "brak", double dAmount = 0.0 ) {
        id = dID;
        userID = dUserID;
        this->date = dDate;
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
