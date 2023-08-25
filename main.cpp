#include <iostream>
#include <fstream>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <limits>
#include <vector>
#include <string>
using namespace std;
condition_variable cv;

using std::string; using std::vector;
using std::cout; using std::endl;
using std::cin; using std::numeric_limits;

string student(string name);
int q_num(int line_num);
float timer(float re);

int u, i, line_num;
string name[2], s;
float value, t, re[3];


string* student(){
    string stn1;
    string stn2;
    cout << "Enter the First Student Name : ";
    cin >> name[0];
    cout << "Enter the Second Student Name : ";
    cin >> name[1];
    return name ;
}
void read_value() {
    cin >> value;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"You have entered wrong input"<<endl;
    }
    cv.notify_one();
}
float* timer(){
    thread th(read_value);
    mutex mtx;
    unique_lock<mutex> lck(mtx);
    int i = 1;
    float t = 10;
    re[2] = 1;
    while ((cv.wait_for(lck, chrono::seconds(10)) == cv_status::timeout) && (i<=2)){

        if(t<20){
                cout << "\nYou have 10 second ";
                cout << "\nYour Answer : ";}
        i++;
        t=t+10;
        if(t==30){
            break;}
    }
    if (t==30){
        cout << "\nYour Time  is End \n\n";
        value = 0;}

    re[0] = value;
    re[1] = t;
    th.detach();
    return re;
}

//**************************************************************************************************
float answer ;
float num;

float option_01 (float answer);
float option_02 (float answer);
float option_03 (float answer);
float option_04 (float answer);
float option_05 (float answer);

float option_01 (){//int + or - int ( between 1 to 999)
    float num1 = (rand()%98) + 1 ;
    float num2 = (rand()%98) + 1 ;
    int operater = (rand()%2) + 1;
    if(num1>=num2){
        num = num1-num2;}
    else{
        num = num2-num1;}
    if (operater == 1){
        cout << num1 << " + " << num2 << " : " ;
        answer = num1+num2;}
    else if ((operater == 2) && (num > 0.1)){
        if(num1>=num2){
            cout << num1 << " - " << num2 << " : " ;
            answer = num1-num2;}
        else{
            cout << num2 << " - " << num1 << " : " ;
            answer = num2-num1;}
    }
    return answer ;
}

float option_02(){//int * int ( between 1 to 20)
    float num1 = (rand()%19) + 1 ;
    float num2 = (rand()%19) + 1 ;
    cout << num1 << " x " << num2 << " : " ;
    answer = num1*num2;
}

float option_03(){//float + or - float ( between 0.1 to 9.9)
    float n1 = (rand()%98) + 1 ;
    float n2 = (rand()%98) + 1 ;
    float num1 = n1/10;
    float num2 = n2/10;
    int operater = (rand()%2) + 1;

    if(num1>=num2){
        num = num1-num2;}
    else{
        num = num2-num1;}
    if (operater == 1){
        cout << num1 << " + " << num2 << " : " ;
        answer = num1+num2;}
    else if ((operater == 2) && (num > 0.1)){
        if(num1>=num2){
            cout << num1 << " - " << num2 << " : " ;
            answer = num1-num2;}
        else{
            cout << num2 << " - " << num1 << " : " ;
            answer = num2-num1;}
    }
    return answer;
}

float option_04(){//float * int ( between 0.1 to 9.9)
    float n1 = (rand()%98) + 1 ;
    float num2 = (rand()%8) + 1 ;
    float num1 = n1/10;
    cout << num1 << " x " << num2 << " : " ;
    answer = num1*num2;
    return answer;
}

float question(){//find question patten and question
    int num1;
    int num2;
    int option = (rand()%4) +1;
    switch (option){
    case 1 :
        option_01();
        break;
    case 2 :
        option_02();
        break;
    case 3 :
        option_03();
        break;
    case 4 :
        option_04();
        break;
    }
    return answer;
}

//**************************************************************************************************

//**************************************************************************************************

int main(){
    cout<<"***************************************************************************\n";
    cout<<"**                           CALCULATION MASTER                          **\n";
    cout<<"***************************************************************************\n\n";

    string number[5] = {"Frist", "Second", "Third", "Fourth", "Fifth"};

    char agian = 'Y';

    while ((agian == 'y') || (agian == 'Y')){
        student();
        cout << "\n_________------question round start------_________\n\n\n";

        int qn ;
        int student_marks[2] = {0,0};
        for(qn=0;qn<=4;qn++){
            int st ;
            for (st = 0;st<=1;st++){
                cout << name[st]<< ", the "<<number[qn]<<" question you get\n" ;
                cout <<"Question : ";
                question();
                cout << "\nYou Have 20 second for give Answer" ;
                cout << "\nYour Answer : ";
                timer();
                cout << "Answer is " << answer<< endl;
                if(re[0] == answer){
                    cout << name[st]<< " your answer is Correct\n" ;
                    cout << name[st]<< " You get 20 Points\n" ;
                    student_marks[st] += 20;}
                else if (re[1]==30){
                    cout << "\nYou not have a answer \n";
                    student_marks[st] = student_marks[st];
                    cout << name[st]<< " Your marks is not changeing\n" ;}
                else if(re[0] != answer || re[2] == 2){
                    cout << name[st]<< " your answer is InCorrect\n" ;
                    cout << name[st]<< " You lost 10 Points\n" ;
                    student_marks[st] -= 10;}
                cout << "\n";
            }
            cout << "\n---------------------------------------------------------------------\n\n";
        }
        cout << name[0]<< ", Youer marks is "<<student_marks[0] <<endl;
        cout << name[1]<< ", Youer marks is "<<student_marks[1] <<endl;

        cout << "\n_________------questoin Round End------________\n\n";

        if ((student_marks[0] <= 0) && (student_marks[1] > 0)){
            cout <<name[0]<< " You are a Loser\n";
            cout << "\nCongratulations " <<name[1] ;
            cout << "CALCULATION MASTER IS ------------> " <<name[1] ;}
        else if (student_marks[1] <= 0 && (student_marks[0] > 0)){
            cout <<name[1]<< " You are a Loser\n";
            cout << "\nCongratulations " <<name[0] ;
            cout << "CALCULATION MASTER IS ------------> " << name[0] ;}
        else if ((student_marks[0] <= 0) && (student_marks[1] <= 0)){
            cout <<name[0]<< " You are a Loser\n";
            cout <<name[1]<< " You are a Loser\n";}
        else if ((student_marks[0] > 0) && (student_marks[1] > 0)){
             if (student_marks[0] > student_marks[1]){
                 cout << "\nCongratulations " <<name[0] ;
                 cout << "CALCULATION MASTER IS ------------> " <<name[0] ;
             }else if (student_marks[1] >student_marks[0]){
                  cout << "CALCULATION MASTER IS ------------> " <<name[1] ;
                  cout << "\nCongratulations " <<name[1] ;
             }else if(student_marks[0] == student_marks[1]){
                cout << "Congratulations\n" ;
                cout <<name[0]<< " and " << name[1] << ", your marks is Equal\n" ;
                cout << "\n_________------extra question Round start------_________\n\n";

                string number[5] = {"Frist", "Second", "Third", "Fourth", "Fifth"};
                int eqn, e_line_num;
                int student_marks[2] = {0,0};
                for(eqn=0;eqn<=2;eqn++){
                    int st = 0;
                    string cho;

                    cout << name[0] <<" and "<< name[1]<< " you get " << number[eqn]<<" extra questoin \n" ;
                    cout <<"Questoin : ";
                    question();
                    cout << "\nchoices (Student 01 ----> 1 and Student 02 ----> 2) : ";
                    cin >> cho;
                    string c = "1";
                    string d = "2";
                    int check1 , check2;
                    check1 = cho.compare(c);
                    check2 = cho.compare(d);
                    if (check1 == 0 ){
                        cout << "\nYour Answer : ";
                        timer();
                        cout << "Answer is " << answer << endl;
                        if(re[0] == answer){
                            cout << name[0]<< " your answer is Correct\n" ;
                            cout << name[0]<< " You get 20 Points\n" ;
                            student_marks[0] += 20;}
                        else{
                            cout << name[0]<< " your answer is Incorrect\n" ;
                            cout << name[0]<< " You lost 10 Points\n" ;
                            student_marks[0] -= 10;}
                    }else if (check2 == 0 ){
                        cout << "\nYour Answer : ";
                        timer();
                        cout << "Answer is " << answer << endl;
                        if(re[0] == answer){
                            cout << name[1]<< " your answer is Correct\n" ;
                            cout << name[1]<< " You get 20 Points\n" ;
                            student_marks[1] += 20;}
                        else{
                            cout << name[1]<< " your answer is Incorrect\n" ;
                            cout << name[1]<< " You lost 10 Points\n" ;
                            student_marks[1] -= 10;}
                    }
                    cout << "\n\n------------------------------------------------------------------------------\n\n";
                }
                cout<<"\n---------------Extra Question Round End-----------------\n";//extra round over

                cout <<  name[0] <<" your extra round marks : "<<student_marks[0] << endl;
                cout <<  name[1] <<" your extra round marks : "<<student_marks[1] << endl;
                cout << "\n\n";
                if ((student_marks[0] < 0) &&  (student_marks[1] < 0)){
                    cout <<name[0]<< " You are a Loser\n";
                    cout <<name[1]<< " You are a Loser\n";}
                else if (student_marks[0] == student_marks[1]){
                    cout << "Congratulations\n" ;
                    cout <<name[0]<< " and " << name[1] << ", yours marks is Equal\n" ;
                    cout << "CALCULATION MASTER IS ------------> " << name[0] << " and " << name[1] ;}
                else if (student_marks[0] > student_marks[1]){
                    cout << "\nCongratulations " <<name[0] ;
                    cout << "CALCULATION MASTER IS ------------> " << name[0] ;
                }
                else if (student_marks[1] > student_marks[0]){
                    cout << "\nCongratulations " <<name[1] <<"\n";
                    cout << "CALCULATION MASTER IS ------------> " <<name[1] ;
                }
             }
        }
        cout <<"\n\n----------------------------------------------------------------------\n\n";
        cout << "\nDo You Want to Continue Doing this  (Y OR N) : ";
        cin >> agian;
        cout <<"----------------------------------------------------------------------\n\n";

    }
    cout<<"       ***********************************************      \n\n";
    cout<< "Have a Nice Day\n";
    cout<< "Thank You\n\n\n";
}
