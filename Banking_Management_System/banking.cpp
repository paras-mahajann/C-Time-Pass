#include<iostream>
#include<fstream>
#include<random>
#include<chrono>

using namespace std;

class Account{
    private:
        int accNo;
        double balance;
        int pin;
        string name; 
        

    public:
        Account(){}
        Account(int a,string name,double b,int pin){
            this->accNo = a;
            this->name = name;
            this->balance = b;
            this->pin = pin;
        }

        void deposite(double amt){
            this->balance += amt;
        }

        bool withdraw(double amt){
            if(this->balance<amt) return false;
            this->balance -= amt;
            return true;
        }

        int getPin(){
            return this->pin;
        }
        void display()const{
            cout<<"Account No : "<<this->accNo<<endl;
            cout<<"Name : "<<this->name<<endl;
            cout<<"Balance : "<<this->balance<<endl;
        }

        int getAccNo()const{
            return this->accNo;
        }

        void writeToFile(ofstream &fout){
            fout<<this->accNo<<" "<<this->name<<" "<<this->balance<<" "<<this->pin<<endl;
        }

        void readFromFile(ifstream &fin){
            fin>>this->accNo>>this->name>>this->balance>>this->pin;
        }

        
};

vector<Account> loadAccounts(){
    vector<Account> accounts;
    ifstream fin("accounts.txt");

    if(!fin) return accounts;

    Account acc;

    while(1){
        acc.readFromFile(fin);
        if(!fin) break;
        accounts.push_back(acc);
    }


    fin.close();
    return accounts;

}

void saveAccounts(const vector<Account>&accounts){
    ofstream fout("accounts.txt");

    for(auto acc:accounts){
        acc.writeToFile(fout);
    }

    fout.close();
}

bool accExist(vector<Account>&accounts,int accNo,double amt){
    bool ans = false;

    for(Account &acc:accounts){
        if(acc.getAccNo()==accNo){
            ans = true;
            acc.deposite(amt);
        }
    }
    return ans;
}

int main(){
    vector<Account> accounts = loadAccounts();

    //for accurate randomness
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 eng(seed);                
    uniform_int_distribution<> dist(100000,999999);


    int choice;

    do{

        cout<<"\n---BANK MENU---\n";
        cout<<"1. Create Account"<<endl;
        cout<<"2. Deposite"<<endl;
        cout<<"3. Withdraw"<<endl;
        cout<<"4. View Account"<<endl;
        cout<<"5. Send Money"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<"Enter Your Choice : ";
        cin>>choice;

        if(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"Invalid input! Enter a number.\n";
            continue;
        }


        int no,pin;string name;double amt;
        switch(choice){
            case 1:                
                no = dist(eng);
                cout<<"Enter Your Name : ";
                cin>>name;
                
                cout<<"your generated account number is : "<<no<<endl;

                cout<<"Enter Amount want to be Deposite : ";
                cin>>amt;
                cout<<"Set your personal pin for Transaction : ";
                cin>>pin;
                

                accounts.emplace_back(no,name,amt,pin);
                break;
            
            case 2:

                cout<<"Enter Account Number for Deposite : ";
                cin>>no;
                

                cout<<"Enter Amount to be Deposite : ";
                cin>>amt;cout<<endl;

               
                if(!accExist(accounts,no,amt)){
                    cout<<"Account Number is not Exist!!! , plz check Account Number or Create new Account"<<endl;
                }

                break;
            
            case 3:
                cout<<"Enter your Account Number : ";
                cin>>no;             
                cout<<"Enter your Amount to be Withdraw : ";
                cin>>amt;
                cout<<"Enter your Pin for transaction : ";
                cin>>pin;


                for(Account &acc:accounts){
                    if(acc.getAccNo()==no){
                        if(acc.getPin()==pin){
                            if(!acc.withdraw(amt)){
                                cout<<"Your Account Balance is not enough to Withdraw this amount!"<<endl;
                                break;
                            }
                            cout<<"Withdraw successfull."<<endl;
                            break;
                        }
                        cout<<"Plz enter correct Pin.."<<endl; 
                        break;               

                    }

                }

                break;

            case 4:
                cout<<"Enter your Account Number : ";
                cin>>no;cout<<endl;

                for(Account &acc:accounts){
                    if(acc.getAccNo()==no)
                    {
                        acc.display();
                        break;
                    }
                }
                break;
            case 5:
                int pin;
                int receiverAccNo;
                cout<<"Enter Your Account Number : ";
                cin>>no;
                cout<<"Enter Receiver's Account Number : ";
                cin>>receiverAccNo;
                cout<<"Enter Amount to be sent to receiver : ";
                cin>>amt;
                cout<<"Enter Your Personal(sender) Pin : ";
                cin>>pin;
               
                for(Account &acc: accounts){
                    if(acc.getAccNo()==no){
                        if(acc.getPin()==pin){
                            if(!acc.withdraw(amt)){
                                cout<<"You don't have enough money to sent!!!"<<endl;
                                break;
                            }
                            cout<<"Money Successfully deducted from sender's account."<<endl;
                            if(!accExist(accounts,receiverAccNo,amt)){
                                cout<<"This Receiver doesn't exist!!!!,plz check account number carefully"<<endl;
                                break;
                            }
                            cout<<"Transaction Successfull!!!"<<endl;
                            break;
                        }
                        
                        cout<<"Your Personal Pin is Wrong , try again.."<<endl;
                        break;
                    }
                }

                
                break;

            case 6:
                cout<<"Exiting program.......\n";
                break;
        }
        saveAccounts(accounts);

    }while(choice!=6);

    
    
    return 0;

}