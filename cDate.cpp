#include <iostream>
#include <windows.h>
#include "cDate.h"


using namespace std;

const int cDate::days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

cDate::cDate() {
    this->year = 2000;
    this->month = 1;
    this->day = 1;
}

cDate::cDate( int y, int m, int d) {

    this->year = y;
    this->month = m;
    this->day = d;
}

cDate::setDay() {
    cout << "Podaj dzien:";
    int d;
    cin >> d;
    this->day = d;
}

cDate::setMonth() {
    cout << "Podaj miesiac:";
    int m;
    cin >> m;
    this->month = m;
}

cDate::setYear() {
    cout << "Podaj rok:";
    int y;
    cin >> y;
    this->year = y;
}

cDate::setDay(int d) {
    this->day = d;
}

cDate::setMonth(int m) {
    this->month = m;
}

cDate::setYear(int y) {
    this->year = y;
}

cDate::getDay() {
    return day;
}
cDate::getMonth() {
    return month;
}
cDate::getYear() {
    return year;
}

bool cDate::isLeapYear( int yearToCheck ) const {
    if ( yearToCheck % 400 == 0 || ( yearToCheck % 100 != 0 && yearToCheck % 4 == 0))
        return true;

    return false;
}

bool cDate::isEndOfMonth( int daysNumber ) const {
    if ( month == 2 && isLeapYear( year ))
        return daysNumber == 29;

    return daysNumber == days[ month ];
}

void cDate::addDays(int countDays) {
    for(int i = 0; i < countDays; i++) {
        increaseDay();
    }
}

void cDate::increaseDay() {
    if (!isEndOfMonth( day )) ++day;
    else if ( month < 12 ) {
        ++month;
        day = 1;
    } else {
        ++year;
        month = 1;
        day = 1;
    }
}

bool cDate::isDateCorrect() {

    cDate minDate,today;
    today.setAsToday();

    if((year < minDate.getYear()) || (year > today.getYear())) return false;
    else if(month < minDate.getMonth() || month > 12) return false;
    else if(month == 2 && isLeapYear( year )) {
        if (day <= 29) return true;
        else return false;
    } else if(day > days[month] || day < minDate.getDay()) return false;
    else if((year == today.getYear()) && (month > today.getMonth())) return false;
    else return true;
}

string cDate::formatDate() {
    string formattedDate = "";

    formattedDate = convertIntToStr(year)+ "-" + convertIntToStr(month) + "-" + convertIntToStr(day);

    return formattedDate;
}

void cDate::setAsToday() {

    SYSTEMTIME winDate;
    GetLocalTime(&winDate);

    setDay(winDate.wDay);
    setMonth(winDate.wMonth);
    setYear(winDate.wYear);
}

int whichDateIsEarlier(cDate firstDate, cDate secondDate) {

    const int valueOfEquality = 0;
    const int firstIsEarlier = -1;
    const int secondIsEarlier = 1;

    int theAnswer;

    int yearOf1, yearOf2;
    int monthOf1, monthOf2;
    int dayOf1, dayOf2;

    yearOf1 = firstDate.getYear();
    monthOf1 = firstDate.getMonth();
    dayOf1 = firstDate.getDay();

    yearOf2 = secondDate.getYear();
    monthOf2 = secondDate.getMonth();
    dayOf2 = secondDate.getDay();

    if(yearOf1==yearOf2){
        if(monthOf1==monthOf2){
            if(dayOf1==dayOf2) theAnswer = valueOfEquality;
            else if(dayOf1 < dayOf2) theAnswer = firstIsEarlier;
            else theAnswer = secondIsEarlier;
        } else if(monthOf1 < monthOf2) theAnswer = firstIsEarlier;
        else theAnswer = secondIsEarlier;
    } else if(yearOf1 < yearOf2) theAnswer = firstIsEarlier;
    else theAnswer = secondIsEarlier;

    return theAnswer;
}

