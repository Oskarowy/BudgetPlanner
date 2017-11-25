#include <iostream>
#include <vector>

using namespace std;

class User {

private:
    int id;
    string login, password;
public:
    User(int dID = 0, string dLogin = "brak", string dPassword = "brak") {
        id = dID;
        this->login = dLogin;
        this->password = dPassword;
    }

    void setID(int newID);
    void setLogin(string newLogin);
    void setPassword(string newPassword);
    void setNewLogin();
    void setNewPassword();

    int getID();
    string getLogin();
    string getPassword();

    string convertToFileFormat();
};

int addNewUser(vector <User> &users, int numberOfUsers);
int readUsersFromFile(vector <User> &users);
bool isAnyUserRegistered(int numberOfUsers);
int getLoggedUserID(vector <User> &users, int numberOfUsers);
int login(int loggedUserID);
void saveInFile(vector <User> &users);

void confirmationOfChange();
void choosenOptionIsNotCorrect();
bool choosenMenu (bool firstMenu);
