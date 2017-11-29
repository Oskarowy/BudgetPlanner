#include <iostream>

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
    setDay(int d);
    setMonth(int m);
    setYear(int y);
    getDay();
    getMonth();
    getYear();
    void showFormattedDate();
    void addDays(int countDays);
    bool isDateCorrect();
    void setAsToday();
};

int whichDateIsEarlier(cDate firstDate, cDate secondDate);
