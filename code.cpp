#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

class LoginManager
{
    string userNameAttempt;
    string passwordAttempt;
    bool accessGranted;

    int getLastID()
    {
        fstream file;
        file.open("user.dat", ios::in);

        string s;

        for(int i = -1; s.find("#") == string::npos; i--)
        {
            file.seekg(i, ios::end);
            file >> s;
        }

        file.close();
        s.erase(0, 4);

        int id;
        istringstream(s) >> id;

        return id;
    }

    int checkFile(string attempt, const char* p_fileName)
    {
        string line;
        fstream file;

        string currentChar;
        long long eChar;

        file.open(p_fileName, ios::in);

        while(1)
        {
            file >> currentChar;
            if(currentChar.find("#ID:") != string::npos)
            {
                if(attempt == line)
                {
                    file.close();
                    currentChar.erase(0, 4);
                    int id;
                    istringstream(currentChar) >> id;
                    return id;
                }
                else
                {
                    line.erase(line.begin(), line.end());
                }
            }
            else

            {
                istringstream(currentChar) >> eChar;
                line += (char)decrypt(eChar);
                currentChar = "";
            }

            if(file.peek() == EOF)
            {
                file.close();
                return 0;
            }
        }
    }

    void saveFile(string p_line, const char* p_fileName, const int& id)
    {
        fstream file;
        file.open(p_fileName, ios::app);
        file.seekg(0, ios::end);

        if(file.tellg() != 0)
            file << "\n";

        for(int i = 0; i < p_line.length(); i++)
        {
            file << encrypt(p_line[i]);
            file << "\n";
        }

        file << "#ID:" << id;
        file.close();
    }

    long long encrypt(int p_letter)
    {
        return powf(p_letter, 5) * 4 - 14;
    }
    int decrypt(long long p_letter)
    {
        return powf((p_letter + 14) / 4, 1/5.f);
    }



    public:
    int attempt=1;
    LoginManager()
    {
        accessGranted = 0;
    }
    bool login()
    {
        cout << "Enter your Details Here... \n\nUsername:";
        cin >> userNameAttempt;

        int usrID = checkFile(userNameAttempt, "user.dat");
        if(usrID != 0)
        {
            cout << "\nPassword:";
            cin >> passwordAttempt;

            int pwdID = checkFile(passwordAttempt, "pswd.dat");
            if(usrID == pwdID)
            {
                return true;
            }
            else if(attempt>2)
            {
                cout<<"\nToo Many tries. Please go outside\n"<<endl;
                return false;
            }
            else
            {
                cout << "\nWrong Password...\n\nTry again.\n" << endl;
                attempt++;
                login();
            }
        }
        else
        {
            if(attempt>2)
            {
                cout<<"\nToo Many tries. Please go outside"<<endl;
                return false;
            }
            cout << "User Name doesn't exist...\n\nTry again.\n" << endl;
            attempt++;
            login();
        }
    }

    void addUser(const string username, const string password)
    {
        if(checkFile(username, "user.dat") != 0)
        {
            cout << "That username is not availble." << endl;
            return;
        }

        int id = 1 + getLastID();
        saveFile(username, "user.dat", id);
        saveFile(password, "pswd.dat", id);
        cout<<"\nNew User Added\n"<<endl;
    }
friend void choice(int c);
};

void printdash(){
for (int i=0;i<25;i++)
    cout<<"--";
cout<<"\n";
}
void choice(LoginManager app)
{
    cout<<"Enter your choice:";
    int c;cin>>c;
    switch(c)
    {
    case 1:
        {
            app.login();
            break;
        }
    case 2:
        {
            cout<<"\nEnter details of an Authorized Person\n";
            if(app.login())
            {
                string usr,pwd;
                printdash();
                cout<<"\n New User's data...\n";
                printdash();
                cout<<"\nEnter a new user name:";
                cin>>usr;
                cout<<"\nEnter a new password:";
                cin>>pwd;
                app.addUser(usr,pwd);
            }
            break;
        }
    default:
            cout<<"Invalid choice\n";
            choice(app);
    }
}

int main()
{
    LoginManager app;
    printdash();
    cout<<"Password Manager by Arumukam Ganes Moorthe and B-Paul\n";
    printdash();
    cout<<"How can I help you?\nPress 1 for login.\nPress 2 for adding new member\n";
    choice(app);
printdash();
cout<<"\nThank you for using...\n";
printdash();

}
