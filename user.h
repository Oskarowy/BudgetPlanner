#include <iostream>
#include <vector>

using namespace std;

class User {

private:
    int id;
    string login, password, name, surname;

public:
    User( int dID = 0, string dLogin = "login", string dPassword = "haslo", string dName = "imie", string dSurname = "nazwisko" ) {
        id = dID;
        this->login = dLogin;
        this->password = dPassword;
        this->name = dName;
        this->surname = dSurname;
    }

    int getID();
    string getLogin();
    string getPassword();
    string getName();
    string getSurname();

    void setID(int newID);
    void setLogin();
    void setPassword();
    void setName();
    void setSurname();
    void setLogin(string newValue);
    void setPassword(string newValue);
    void setName(string newValue);
    void setSurname(string newValue);

    //string convertToFileFormat();
};

// konwersja tekstu
int convertStrToInt (string str);
string convertIntToStr(int i);
string changeToLowerCase(string word);
string fromCapitalLetter(string word);


int addNewUser(vector <User> &users, int numberOfUsers);
int readUsersFromFile(vector <User> &users);
bool isAnyUserRegistered(int numberOfUsers);
int getLoggedUserID(vector <User> &users, int numberOfUsers);
int login(int loggedUserID);
void saveInFile(vector <User> &users);

void confirmationOfChange();
void choosenOptionIsNotCorrect();
bool choosenMenu (bool firstMenu);
