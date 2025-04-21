#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
using namespace std;

struct User
{
    string name; string surname; string family_name; string mothers_name; string mothers_surname; string fathers_name; string fathers_surname; 
    string citizenship; string ID_NUMBER; string PESEL_NUMBER; string date_of_birth; string phone_number; string Login;
};

User user;

void loginToFile(string login)
{
    fstream file;
    file.open("logins.txt", ios::in | ios::app);
    if(file.is_open())
    {
        file << login << endl;
        file.close();
    }
}

void passToFile(string pass)
{
    fstream file;
    file.open("pass.txt", ios::in | ios::app);
    if(file.is_open())
    {
        file << pass << endl;
        file.close();
    }
}


void dataToFile(string name, string surname, string mothername, string mothersurname, string fathername, string fathersurname, string family_name, string citizenship, string ID_NUMBER, string PESEL_NUMBER, string date_of_birth, string phone_number)
{
    printf("Prosze podac dane niezbedne do zalozenia konta:\n");
    printf("Imie:\n");
    cin >> name;
    printf("Nazwisko:\n");
    cin >> surname;
    cin.ignore();
    printf("Nazwisko rodowe:\n");
    getline(cin, family_name);
    printf("Imie matki:\n");
    cin >> mothername;
    printf("Nazwisko matki:\n");
    cin >> mothersurname;
    printf("Imie ojca:\n");
    cin >> fathername;
    printf("Nazwisko ojca:\n");
    cin >> fathersurname;
    cin.ignore();
    printf("Narodowosc:\n");
    getline(cin, citizenship);
    printf("Nr. dowodu:\n");
    cin >> ID_NUMBER;
    printf("Numer PESEL:\n");
    cin >> PESEL_NUMBER;
    cin.ignore();
    printf("Data urodzenia:\n");
    while(true)
    {
        cout << "Data w formacie: (dd.mm.rrrr)" << endl;
        getline(cin, date_of_birth);
        if(date_of_birth.length() == 10 && date_of_birth[2] == '.' && date_of_birth[5] == '.')
        break;
        else
        cout << "Nieprawidłowy format. Prosze sprobowac ponownie.\n";
    }
    printf("Nr. telefonu:\n");
    getline(cin, phone_number);

    fstream file;
    if(file.is_open())
    {
    file.open("data.txt", ios::in | ios::app);
    file << "Imie: " << name << endl;
    file << "Nazwisko: " << surname << endl;
    file << "Nazwisko rodowe: " << family_name << endl;
    file << "Imie matki: " << mothername << endl;
    file << "Naziwsko matki: " << mothersurname << endl;
    file << "Imie ojca: " << fathername << endl;
    file << "Nazwisko ojca: " << fathersurname << endl;
    file << "Narodowosc: " << citizenship << endl;
    file << "Nr. dowodu: " << ID_NUMBER << endl;
    file << "PESEL: " << PESEL_NUMBER << endl;
    file << "Data urodzenia: " << date_of_birth << endl;
    file << "Nr. telefonu: " << phone_number << endl;
    file.close();
    }
}


void registerUser(void (*dataToFile)(string, string, string, string, string, string, string, string, string, string, string, string))
{
    string name, surname, family_name, mothername, mothersurname, fathername, fathersurname, citizenship, ID_NUMBER, PESEL_NUMBER, date_of_birth, phone_number;
    dataToFile(name, surname, family_name, mothername, mothersurname, fathername, fathersurname, citizenship, ID_NUMBER, PESEL_NUMBER, date_of_birth, phone_number);
}

void LoginUser(string loginInput, string passInput)
{
    cout << "Give login: " << endl;
    getline(cin,loginInput);
    ifstream file("logins.txt");
    if(!file.is_open())
    {
        cout << "Nie otworzono pliku logins.txt! " << endl;
        return;
    }
    string loginFromFile;
    bool found = false;
    while(getline(file, loginFromFile))
    {
        if(loginFromFile == loginInput)
        {
            found = true;
            break;
        }
    }
    file.close();
    if(found)
    {
        cout << "Login successful! " << endl;
    }
    else
    {
        cout << "Login failed! Left 2 tries" << endl;
    }

    cout << "Give password: " << endl;
    getline(cin, passInput);
    ifstream file("pass.txt");
    if(!file.is_open())
    {
        cout << "Nie otworzono pliku pass.txt! " << endl;
        return;
    }
    string passFromFile;
    bool found1 = false;
    while(getline(file,passFromFile))
    {
        if(passFromFile == passInput)
        {
            found1 = true;
            break;
        }
    }
    file.close();
    if(found1)
    {
        cout << "Login successful! " << endl;
    }
    else
    {
        cout << "Login failed! Left 2 tries" << endl;
    }
}
int main()
{

    return 0;
}