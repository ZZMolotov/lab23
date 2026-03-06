#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &score, vector<char> &grade){
    ifstream fin (filename);
    string s;
    while(getline(fin,s)){
        const char* cs = s.c_str();
        char format[] = "%[^:]: %d %d %d";
        char name[100];
        int score1, score2, score3;
        sscanf(cs, format, name, &score1, &score2, &score3);
        int sum = score1 + score2 + score3;
        char gradecal = score2grade(sum);
        string namestring = name;
        names.push_back(namestring);
        score.push_back(sum);
        grade.push_back(gradecal);
    }
}

void getCommand(string &command, string &key){
    string temp;
    cout<<"Please input your command:"<<endl;
    getline(cin, temp);
    const char * Ctemp = temp.c_str();
    char Ccommand[100];
    char Cname[100];
    char format[] = "%s %[^\n]";
    sscanf(Ctemp, format, Ccommand, Cname);
    command = Ccommand;
    key = Cname;
}

void searchName(vector <string> &name, vector<int> &score, vector<char> &grade, string key){
    bool found = false;
    for (unsigned int i = 0; i < name.size(); i++){
        if(toUpperStr(name[i]) == key){
            cout<<"---------------------------------" << "\n";
            cout<<name[i]<< "'s score = "<<score[i]<<"\n";
            cout<<name[i]<< "'s grade = "<<grade[i]<<"\n";
            cout<<"---------------------------------" << "\n";
            found = true;
        }
        
        
    }
    if (!found){
            cout<<"---------------------------------" << "\n";
            cout<<"Cannot found."<<"\n";
            cout<<"---------------------------------" << "\n";
        }  
}

void searchGrade(vector<string> &name, vector<int> &score, vector<char> &grade, string key){
    bool found = false;
    char charkey = key[0];
    cout<<"---------------------------------" << "\n";
    for(unsigned int i = 0; i < name.size(); i++){
        if(grade[i] == charkey){
            cout<<name[i]<<" ("<<score[i]<<")"<<"\n";
            found = true;
        }
    }
    if (!found){
        cout<<"Cannot found."<<"\n";
    }
    cout<<"---------------------------------" << "\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
