#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>


using namespace std;

int main(){

    // ofstream fout;
    // fout.open("zoom.txt");//file ko open karega nhito create kar dega

    // fout<<"My name is Paras Mahajan";
    // fout.close();


    
    // ifstream fin;
    // fin.open("zoom.txt");

    // char c = fin.get();

    // while(!fin.eof()){
    //     cout<<c;
    //     c = fin.get();
    // }


    // ifstream fin;
    // fin.open("zoom.txt");

    // string line;
    // // getline(fin,line);
    // // cout<<line<<endl;

    // while(getline(fin,line)){
    //     cout<<line<<endl;
    // }

    // fin.close();


    //task : make file and put some number and print sorted version of that number on same file

    ofstream fout;
    fout.open("task.txt");
    vector<int>v = {3,20,101,1,280};
   
    for(auto it:v){
        fout<<it<<" ";
    }
    
    fout.close();

    ifstream fin;

    fin.open("task.txt");
    vector<int>v2;
    int n;
    
    while(fin>>n){
        cout<<n<<" ";
        v2.push_back(n);
    }
  
    fin.close();

    ofstream fout2;
    fout2.open("task.txt",ios::app);
    sort(v2.begin(),v2.end());

    fout2<<"\n";
    

    for(auto it:v2){
        fout2<<it<<" ";
    }

    cout<<"done"<<endl;
    fout2.close();

    
    
    
    




    return 0;
}