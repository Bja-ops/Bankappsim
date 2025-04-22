#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <vector>
#include <locale.h>
using namespace std;


struct User
{
    string name; string surname; string family_name; string mothers_name; string mothers_surname; string fathers_name; string fathers_surname; 
    string citizenship; string ID_NUMBER; string PESEL_NUMBER; string date_of_birth; string phone_number; string Login;
};

User user;


void saveUserCredentials(const string &login, const string &password, const string &role)
{
    ofstream file("users.txt", ios::app);
    if (file.is_open())
    {
        file << login << ";" << password << ";" << role << endl;
        file.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku users.txt!" << endl;
    }
}


void loginToFile(string login)
{
    fstream file;
    file.open("logins.txt", ios::in | ios::app);
    if(file.is_open())
    {
        file << login << endl;
        file.close();
    }
    cout << "Login zapisany do pliku logins.txt\n";
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


void dataToFile(const User &user)
{
    ofstream file("data.txt", ios::app);
    if (file.is_open())
    {
        file << "Imie: " << user.name << endl;
        file << "Nazwisko: " << user.surname << endl;
        file << "Nazwisko rodowe: " << user.family_name << endl;
        file << "Imie matki: " << user.mothers_name << endl;
        file << "Nazwisko matki: " << user.mothers_surname << endl;
        file << "Imie ojca: " << user.fathers_name << endl;
        file << "Nazwisko ojca: " << user.fathers_surname << endl;
        file << "Narodowosc: " << user.citizenship << endl;
        file << "Nr. dowodu: " << user.ID_NUMBER << endl;
        file << "PESEL: " << user.PESEL_NUMBER << endl;
        file << "Data urodzenia: " << user.date_of_birth << endl;
        file << "Nr. telefonu: " << user.phone_number << endl;
        file << endl;
        file.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku data.txt!\n";
    }
}

void fillUserData(User &user)
{
    cout << "Prosze podac dane niezbedne do zalozenia konta:\n";

    cout << "Imie: ";
    cin >> user.name;

    cout << "Nazwisko: ";
    cin >> user.surname;
    cin.ignore();

    cout << "Nazwisko rodowe: ";
    getline(cin, user.family_name);

    cout << "Imie matki: ";
    cin >> user.mothers_name;

    cout << "Nazwisko matki: ";
    cin >> user.mothers_surname;

    cout << "Imie ojca: ";
    cin >> user.fathers_name;

    cout << "Nazwisko ojca: ";
    cin >> user.fathers_surname;
    cin.ignore();

    cout << "Narodowosc: ";
    getline(cin, user.citizenship);

    cout << "Nr. dowodu: ";
    cin >> user.ID_NUMBER;

    cout << "Numer PESEL: ";
    cin >> user.PESEL_NUMBER;
    cin.ignore();

    while (true)
    {
        cout << "Data urodzenia (dd.mm.rrrr): ";
        getline(cin, user.date_of_birth);
        if (user.date_of_birth.length() == 10 && user.date_of_birth[2] == '.' && user.date_of_birth[5] == '.')
            break;
        else
            cout << "Nieprawidlowy format. Prosze sprobowac ponownie.\n";
    }

    cout << "Nr. telefonu: ";
    getline(cin, user.phone_number);
}

void registerUser()
{
    User newUser;
    fillUserData(newUser);
    dataToFile(newUser);

    string login, password, role;
    cout << "Podaj login: ";
    getline(cin, login);
    cout << "Podaj haslo: ";
    getline(cin, password);

    cout << "Wybierz rolę (admin/user): ";
    getline(cin, role);

    while (role != "admin" && role != "user")
    {
        cout << "Nieprawidłowa rola. Wpisz 'admin' lub 'user': ";
        getline(cin, role);
    }

    saveUserCredentials(login, password, role);
}

bool isAccountBlocked(const string &login)
{
    ifstream file("blocked.txt");
    if (!file.is_open()) return false;

    string blockedLogin;
    while (getline(file, blockedLogin))
    {
        if (blockedLogin == login)
        {
            return true;
        }
    }
    return false;
}

void blockAccount(const string &login)
{
    ofstream file("blocked.txt", ios::app);
    if (file.is_open())
    {
        file << login << endl;
        file.close();
    }
}

void LoginUser()
{
    string loginInput, passInput;
    cout << "Podaj login: ";
    getline(cin, loginInput);

    if (isAccountBlocked(loginInput))
    {
        cout << "To konto jest zablokowane. Skontaktuj się z administratorem." << endl;
        return;
    }

    int attempts = 3;
    while (attempts--)
    {
        cout << "Podaj hasło: ";
        getline(cin, passInput);

        string role = getUserRole(loginInput, passInput);
        if (!role.empty())
        {
            cout << "Logowanie udane! Twoja rola: " << role << endl;
            if (role == "admin")
            {
                // Możemy tu dodać menu admina
                cout << "Masz dostęp do panelu administratora." << endl;
            }
            else
            {
                cout << "Zalogowano jako zwykły użytkownik." << endl;
            }
            return;
        }

        if (attempts > 0)
            cout << "Nieprawidłowe dane. Pozostało prób: " << attempts << endl;
    }

    cout << "Trzykrotnie podano nieprawidłowe dane. Konto zostało zablokowane!" << endl;
    blockAccount(loginInput);
}

void unblockAccount()
{
    string adminPass;
    cout << "Podaj haslo administratora: ";
    getline(cin, adminPass);

    const string correctPass = "admin123";

    if (adminPass != correctPass)
    {
        cout << "Błędne hasło. Dostęp zabroniony!" << endl;
        return;
    }

    ifstream file("blocked.txt");
    if (!file.is_open())
    {
        cout << "Nie mozna otworzyc pliku blocked.txt!" << endl;
        return;
    }

    vector<string> blockedUsers;
    string line;
    while (getline(file, line))
    {
        blockedUsers.push_back(line);
    }
    file.close();

    if (blockedUsers.empty())
    {
        cout << "Brak zablokowanych kont." << endl;
        return;
    }

    cout << "Zablokowane konta:\n";
    for (size_t i = 0; i < blockedUsers.size(); ++i)
    {
        cout << i + 1 << ". " << blockedUsers[i] << endl;
    }

    int choice;
    cout << "Wybierz numer konta do odblokowania (0 aby anulować): ";
    cin >> choice;
    cin.ignore();

    if (choice > 0 && choice <= static_cast<int>(blockedUsers.size()))
    {
        blockedUsers.erase(blockedUsers.begin() + choice - 1);

        ofstream outFile("blocked.txt");
        for (const auto &user : blockedUsers)
        {
            outFile << user << endl;
        }
        outFile.close();

        cout << "Konto odblokowane." << endl;
    }
    else
    {
        cout << "Anulowano lub błędny wybór." << endl;
    }
}

string getUserRole(const string &loginInput, const string &passInput)
{
    ifstream file("users.txt");
    if (!file.is_open())
        return "";

    string line;
    while (getline(file, line))
    {
        size_t pos1 = line.find(';');
        size_t pos2 = line.rfind(';');
        if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2)
        {
            string fileLogin = line.substr(0, pos1);
            string filePass = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string role = line.substr(pos2 + 1);

            if (fileLogin == loginInput && filePass == passInput)
                return role;
        }
    }

    return "";
}

int main()
{
    setlocale(LC_ALL, "");
    return 0;
}
