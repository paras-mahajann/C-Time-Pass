#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

class Account
{
private:
    int accNo;
    double balance;
    int pin;
    string name;

public:
    Account() {}
    Account(int a, string name, double b, int pin)
    {
        this->accNo = a;
        this->name = name;
        this->balance = b;
        this->pin = pin;
    }

    void deposit(double amt)
    {
        this->balance += amt;
    }

    bool withdraw(double amt)
    {
        if (this->balance < amt)
            return false;
        this->balance -= amt;
        return true;
    }

   
    bool verifyPin(int inputPin) const{
        return this->pin == inputPin;
    }
    void display() const
    {
        cout << "Account No : " << this->accNo << endl;
        cout << "Name : " << this->name << endl;
        cout << "Balance : " << this->balance << endl;
    }

    int getAccNo() const
    {
        return this->accNo;
    }

    void writeToFile(ofstream &fout) const
    {
        fout << this->accNo << " " << this->name << " " << this->balance << " " << this->pin << endl;
    }

    void readFromFile(ifstream &fin)
    {
        fin >> this->accNo >> this->name >> this->balance >> this->pin;
    }
};

vector<Account> loadAccounts(){
    vector<Account> accounts;
    ifstream fin("accounts.txt");

    if (!fin)
        return accounts;

    Account acc;

    while (1)
    {
        acc.readFromFile(fin);
        if (!fin)
            break;
        accounts.push_back(acc);
    }

    fin.close();
    return accounts;
}

void saveAccounts(const vector<Account> &accounts)
{
    ofstream fout("accounts.txt");

    for (const auto &acc : accounts)
    {
        acc.writeToFile(fout);
    }

    fout.close();
}

Account *findAccount(vector<Account> &accounts, int accNo)
{
    for (Account &acc : accounts)
    {
        if (acc.getAccNo() == accNo)
        {
            return &acc;
        }
    }
    return nullptr;
}

int main()
{
    vector<Account> accounts = loadAccounts();

    // for accurate randomness
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 eng(seed);
    uniform_int_distribution<> dist(100000, 999999);

    int choice;

    do
    {

        cout << "\n---BANK MENU---\n";
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. View Account" << endl;
        cout << "5. Send Money" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter Your Choice : ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Enter a number.\n";
            continue;
        }

        int no,pin;
        string name;
        double amt;
        switch (choice)
        {
        case 1:
            
            do{
                no = dist(eng);
            }while(findAccount(accounts,no)!=nullptr);
            cout << "Enter Your Name : ";
            cin.ignore();
            getline(cin,name);
            

            cout << "your generated account number is : " << no << endl;

            cout << "Enter Amount want to be Deposit : ";
            cin >> amt;
            while(amt<=0){
                cout<<"Amount must be Positive!!!\n";
                cout << "Enter Amount want to be Deposit : ";
                cin>>amt;
            }
            cout << "Set your personal pin for Transaction : ";
            cin >> pin;
            while(pin<1000 || pin>9999){
                cout<<"Pin must be 4 digits\n";
                cout << "Set your personal pin for Transaction : ";
                cin>>pin;
            }
            accounts.emplace_back(no, name, amt, pin);
            saveAccounts(accounts);
            break;

        case 2:
        {
            cout << "Enter Account Number for Deposit : ";
            cin >> no;

            cout << "Enter Amount to be Deposit : ";
            cin >> amt;
            
            while(amt<=0){
                cout<<"Amount must be Positive!!!\n";
                cout << "Enter Amount to be Deposit : ";
                cin>>amt;
            }

            Account *acc = findAccount(accounts, no);
            if (acc){
                acc->deposit(amt);
                saveAccounts(accounts);
            }
            else
            {
                cout << "Account is not Found!!! , plz check Account Number or Create new Account" << endl;
            }

            break;
        }

        case 3:
        {
            cout << "Enter your Account Number : ";
            cin >> no;
            cout << "Enter your Amount to be Withdraw : ";
            cin >> amt;
            while(amt<=0){
                cout<<"Amount must be Positive!!!\n";
                cout << "Enter your Amount to be Withdraw : ";
                cin>>amt;
            }
            cout << "Enter your Pin for transaction : ";
            cin >> pin;

            Account* user = findAccount(accounts,no);
            if(user==nullptr){
                cout<<"Account not Exist!!, plz check your account number\n";
                break;
            }
            if(!user->verifyPin(pin)){
                cout<<"You Entered wrong pin!!\n";
                break;
            }
            if(!user->withdraw(amt)){
                cout<<"Insufficient balance....\n";
                break;
            }
            cout<<"Withdrawal successfull..\n";
            saveAccounts(accounts);

            break;
        }

        case 4:
        {
            cout << "Enter your Account Number : ";
            cin >> no;
            cout << endl;

            Account* user = findAccount(accounts,no);
            if(user){
                user->display();
                break;
            }
            
            cout<<"Account not Exist!!, check account number\n";
            
            break;
        }
        case 5:
        {
            int receiverAccNo;
            cout << "Enter Your Account Number : ";
            cin >> no;
            cout << "Enter Receiver's Account Number : ";
            cin >> receiverAccNo;
            cout << "Enter Amount to be sent to receiver : ";
            cin >> amt;
            while(amt<=0){
                cout<<"Amount must be Positive !!!\n";
                cout << "Enter Amount to be sent to receiver : ";
                cin>>amt;
            }
            cout << "Enter Your Personal(sender) Pin : ";
            cin >> pin;
            

            if(no==receiverAccNo){
                cout<<"Cannot transfer to same account\n";
                break;
            }

            Account* sender = findAccount(accounts,no);
            Account* receiver = findAccount(accounts,receiverAccNo);
            
            if(!sender || !receiver){
                cout<<"Invalid sender or receiver\n";
                break;
            }

            
            if(!sender->verifyPin(pin)){
                cout<<"Wrong Pin\n";
                break;
            }

            if(!sender->withdraw(amt)){
                cout<<"Insufficient balance\n";
                break;
            }

            receiver->deposit(amt);
            cout<<"Transaction Successful\n";
            saveAccounts(accounts);

            break;
        }
        case 6:
            cout << "Exiting program.......\n";
            break;
        }
        

    } while (choice != 6);

    return 0;
}