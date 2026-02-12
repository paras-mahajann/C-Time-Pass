#include<iostream>
#include<unordered_map>
#include<vector>
#include<fstream>
#include<algorithm>


using namespace std;

class Student{
private:
    int rollNo;
    string name;
    float marks;
    string department;

public:
    Student(){};
    Student(int roll,string name,float marks,string dept){
        this->rollNo = roll;
        this->department = dept;
        this->name = name;
        this->marks = marks;
    }
    int getRoll(){
        return this->rollNo;
    }
    void display()const{
        cout<<"Name : "<<this->name<<endl;
        cout<<"Roll No : "<<this->rollNo<<endl;
        cout<<"Department : "<<this->department<<endl;
        cout<<"Marks : "<<this->marks<<endl;
    }
    int getRoll() const{
        return rollNo;
    }
    float getMarks() const{
        return marks;
    }
    string getName() const{
        return name;
    }
    void writeToFile(ofstream &fout)const{
        fout<<this->rollNo << " "<<this->name<<" "<<this->marks<<" "<<this->department<<endl;
    }

    void readFromFile(ifstream &fin){
        fin>>this->rollNo>>this->name>>this->marks>>this->department;
    }   
};

unordered_map<int,Student> loadStudents(){
    unordered_map<int,Student> students;

    ifstream fin("students.txt");

    if(!fin) return students;
    Student s;
    while(fin){
        s.readFromFile(fin);
        if(!fin) break;
        students[s.getRoll()] = s;
    }

    fin.close();
    return students;
}

void saveStudents(const unordered_map<int,Student>&students){
    ofstream fout("students.txt");

    for(const auto &it:students){
        it.second.writeToFile(fout);
    }

    fout.close();

}


int main(){
    unordered_map<int,Student> students = loadStudents();
    int choice;

    do{
        cout << "\n---STUDENT MENU---\n";
        cout << "1. Add Student" << endl;
        cout << "2. View All Students" << endl;
        cout << "3. Search Student by Roll" << endl;
        cout << "4. Sort Student By Marks" << endl;
        cout << "5. Sort Student By Name" << endl;
        cout << "6. Delete Student" << endl;
        cout << "7. Save & Exit" << endl;
        cout << "Enter Your Choice : ";
        cin >> choice;

        switch(choice){
            case 1:
            {   
                string name,dept;
                int rollNo;
                float marks;

                cout<<"Enter Roll No : ";
                cin>>rollNo;

                if(students.count(rollNo)){
                    cout<<"Student already Exist!\n";
                    break;
                }

                cout<<"Enter Name : ";
                cin.ignore();
                getline(cin,name);
                
                cout<<"Enter Marks : ";
                cin>>marks;
                while(marks<0 && marks>100){
                    cout<<"Marks must be between 0 to 100: ";
                    cin>>marks;                    
                }
                
                cout<<"Enter Department : ";
                cin>>dept;
               
                
                students[rollNo] =  Student(rollNo,name,marks,dept);
                cout<<"Student Added Successfully!\n";
                break;
            }
            case 2:{
                cout<<"------------------"<<endl;
                for(auto &st:students){
                    st.second.display();
                }

                break;
            }
            case 3:{
                int roll;
                cout<<"Enter roll No to search: ";
                cin>>roll;
                auto it = students.find(roll);
                if(it!=students.end()){
                    it->second.display();
                }
                else{
                    cout<<"Student not found!"<<endl;
                }
                break;
            }
            case 4:{
                //sort by marks
                vector<pair<int,Student>>temp;
                for(auto &pair:students){
                    temp.push_back(pair);
                }

                sort(temp.begin(),temp.end(),[](auto &a,auto &b){
                    return a.second.getMarks()>b.second.getMarks();
                });
                
                

                break;
            }
            case 5:{

                break;
            }
            case 6:{

                break;
            }
            case 7:{
                cout<<"Exiting Menu......\n";
                break;
            }
        }

        saveStudents(students);

    }while(choice!=7);


    

    return 0;
}