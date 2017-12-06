#include <iostream>
#include "user.h"

using namespace std;

class cDate {
private:
    int month;
    int day;
    int year;
    static const int days[];
    void increaseDay();
    bool isLeapYear( int yearToCheck ) const;
    bool isEndOfMonth( int daysNumber ) const;
public:
    cDate();
    cDate( int y, int m, int d);
    setDay();
    setMonth();
    setYear();
    setDay(int d);
    setMonth(int m);
    setYear(int y);
    getDay();
    getMonth();
    getYear();
    string formatDate();
    long long int getDateAsLongInt();
    void addDays(int countDays);
    bool isDateCorrect();
    void setAsToday();
};

int whichDateIsEarlier(cDate firstDate, cDate secondDate);
string changeDateToStr(long long int date);
