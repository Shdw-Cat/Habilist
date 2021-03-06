#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <istream>
// #include <chrono>
#include <time.h>
// #include <sqlite>


#define underline "\33[4m"
#define reset "\33[0m"
#define green "\033[1;32m"
#define blue "\033[1;34m"
#define red "\033[1;31m"
#define brown "\033[1;33m"
#define cyan "\033[1;36m"
#define grey "\033[1;37m"
#define boldyellow "\033[1m\033[33m"

using namespace std;

int points=0;
int task_count=0;
int task_completed=0;
int flag=0;
int tcnt=0;
int tcmp=0;
int pt=0;



class Habit{
protected:
    string task;
    int time_;
    
public:
    
    void get_habit(string a,int t){
        task=a;
        time_=t;
    }
    virtual void new_task();
    virtual void edit_task();
    virtual void display_task();
    virtual void delete_task();
    friend  void profile_(string);
    virtual void insert();
    virtual void menu(string);
    void remove_task();
    
};

class ToDo:public Habit{
    string task;
    int time_;
    
public:
    
    void get_ToDo(string a,int t){
        task=a;
        time_=t;
    }
    
    void new_task();
    void edit_task();
    void display_task();
    void delete_task();
    friend void profile_(string);
    void insert();
    void menu(string);
};



//////////////////////////////////////HABIT-NEW TASK /////////////////////////////////////////////////////

void Habit::new_task(){
    Habit h1;
    
    
    
    string task;
    
    
    int time_;
    
    cout<<"Enter the task: \n";
    cin>>task;
    cout<<"Enter the deadline in hours:\n";
    cin>>time_;
    // ofstream habits("habits.txt");
    h1.get_habit(task,time_);
    h1.insert();
    
}


////////////////////////////////////// HABIT-INSERT TASK /////////////////////////////////////////////////////

void Habit::insert(){
    int s_no;
    ifstream habits("habits.txt");;
    string line;
    int count=1;
    while(getline(habits,line)){
        count++; //to read no. of lines for s.no.
    }
    habits.close();
    
    ofstream habit;
    habit.open("habits.txt",ios::app); //to append in the habits file
    habit<<count <<' '<< task<<' '<<time_<<endl;
    
    task_count+=1;
    habit.close();
    
}


////////////////////////////////////// HABIT-EDIT TASK /////////////////////////////////////////////////////

void Habit::edit_task()
{
    Habit h;
    ToDo d;
    int s_no;
    int id;
    string task;
    string newtask;
    int time;
    int newtime;
    int flag=0;
    
    ifstream habits;
    habits.open("habits.txt",ios::in|ios::out);
    cout<<"Enter the task no. you wish to edit:\n";
    cin>>id;
    
    ofstream temp; //temporary file to write the data of habits.txt excluding the line to be edited
    temp.open("temp.txt",ios::out);
    
    while(habits >> s_no >> task >>time) //read from habits.txt line by line
    {
        
        if(id!=s_no){
            temp<< s_no<<' '<<task<<' '<<time<<endl; //write the data to temp file
            
        }
        
        else if(id==s_no){
            flag=1;
            cout<<s_no<<' '<<task<<' '<<time<<endl;
            cout<<"Is this the task you want to edit(y/n):\n";
            char ch;
            cin>>ch;
            if(ch=='y')
            {
                cout<<"Enter the new task:\n";
                cin>>newtask;
                cout<<"Enter the new deadline:\n";
                cin>>newtime;
                
                temp << s_no <<' '<< newtask <<' '<<newtime<<endl; //write the new task to temp file
            }
            
        }
        
        
    }
    
    if(flag==0) //id not found
    {
        cout<<"Task not found\n";
    }
    temp.close();
    habits.close();
    remove("habits.txt"); //remove habits.txt
    rename("temp.txt","habits.txt"); //rename temp.txt to habits.txt
}


////////////////////////////////////// HABIT-DISPLAY TASK /////////////////////////////////////////////////////

void Habit::display_task(){
    int s_no;
    string task;
    int time;
    fstream habits;
    cout<<red<<"        _____________________________ Your Current Habits __________________________________\n\n"<<reset;
    habits.open("habits.txt",ios::in); //read from file
    cout<<boldyellow<<setw(15)<<underline<<"S.no"<<reset<<boldyellow<<setw(35)<<underline<<"Tasks"<<reset<<boldyellow<<setw(35)<<underline<<"Deadline"<<reset<<endl<<endl;
    while(habits >>s_no >>task >>time){
        cout<<setw(15)<<s_no<<setw(37)<<task<<setw(32)<<time<<":00"<<endl;
        
    }
    cout<<endl;
}

////////////////////////////////////// HABIT-DELETE TASK /////////////////////////////////////////////////////

void Habit::delete_task()
{
    Habit h;
    ToDo d;
    int s_no;
    int id;
    int time_;
    string task;
    int flag=0;
    
    time_t now=time(0);
    struct tm *now_tm;
    int hour;
    int min;
    
    
    now_tm = localtime(&now);
    hour = now_tm->tm_hour+5; //to change time from gmt to ist , gmt+5.30=ist
    min = now_tm->tm_min;
    
    
    
    
    if(min>30){
        hour=hour+1;
        min=min%30;
    }
    
    ifstream habits;
    habits.open("habits.txt",ios::in|ios::out);
    cout<<"Enter the task no. you wish to delete:\n";
    cin>>id;
    
    
    while(habits >> s_no >> task >>time_) //read from habits.txt line by line
    {
        
        
        
        if(id==s_no){
            flag=1;
            cout<<s_no<<' '<<task<<' '<<time_<<endl;
            cout<<"Is this the task you want to delete(y/n):\n";
            char ch;
            cin>>ch;
            if(ch=='y')
            {
                if(time_>hour){
                    cout<<"\nBravo! You finished the task on time\n\n";
                    points+=100;
                    task_completed+=1;
                    
                }
                else{
                    cout<<"\nOops! Looks like you coudn't finish the task on time\n\n";
                    points-=40;
                }
                
            }
            
        }
        
        
    }
    
    if(flag==0) //id not found
    {
        cout<<"Task not found\n";
    }
    
    habits.close();
    
    
}

////////////////////////////////////// HABIT-REMOVE TASK /////////////////////////////////////////////////////

void Habit::remove_task()
{
    Habit h;
    ToDo d;
    int s_no;
    int id;
    int time_;
    string task;
    int flag=0;
    
    
    ifstream habits;
    habits.open("habits.txt",ios::in|ios::out);
    cout<<"Enter the task no. you wish to delete:\n";
    cin>>id;
    
    ofstream temp; //temporary file to write the data of habits.txt excluding the line to be edited
    temp.open("temp.txt",ios::out);
    
    while(habits >> s_no >> task >>time_) //read from habits.txt line by line
    {
        
        if(id!=s_no){
            if(flag==0)
                temp<< s_no<<' '<<task<<' '<<time_<<endl; //write the data to temp file
            else
                temp<< s_no-1<<' '<<task<<' '<<time_<<endl; //decrement the s.no by one, of the tasks
            //after the deleted task
        }
        else{
            flag=1;
            cout<<"Task has been successfully removed from the list\n";
        }
        
        
    }
    
    if(flag==0) //id not found
    {
        cout<<"Task not found\n";
    }
    temp.close();
    habits.close();
    remove("habits.txt"); //remove habits.txt
    rename("temp.txt","habits.txt"); //rename temp.txt to habits.txt
    
}
////////////////////////////////////// PROFILE /////////////////////////////////////////////////////

void profile_(string name){
    
    int t_count=0;
    int t_comp=0;
    int pts=0;
    int x=0;
    
    
    fstream profile("profile.txt",ios::in|ios::out);
    if(profile){
        
        
        fstream prof("profile.txt",ios::in);
        
        if(flag==0)
        {
            prof>>name>>t_count>>t_comp>>pts;
            tcnt=t_count;
            tcmp=t_comp;
            pt=pts;
            flag=1;
        }
        cout<<green<<"\n\n             ------------------------------------------ PROFILE ---------------------------------------------------\n\n"<<reset;
        cout<<cyan<<setw(35)<<"Name:"<<reset<<cyan<<setw(45)<<"Total Tasks:"<<reset<<endl;
        cout<<setw(35)<<name<<setw(45)<<tcnt+task_count<<endl<<endl<<endl;
        
        cout<<cyan<<setw(35)<<"Tasks Completed:"<<reset<<cyan<<setw(45)<<"Points:"<<reset<<endl;
        cout<<setw(35)<<tcmp+task_completed<<setw(45)<<pt+points<<endl<<endl;
        
        if(pt+points<=1000)
            cout<<cyan<<setw(59)<<"Rank:"<<reset<<"Newbie"<<endl;
        else if(pt+points>=1000 && pt+points<1500)
            cout<<cyan<<setw(59)<<"Rank:"<<reset<<"Rookie"<<endl;
        else if(pt+points>=1500 && pt+points<2000)
            cout<<cyan<<setw(59)<<"Rank:"<<reset<<"Amateur"<<endl;
        else
            cout<<cyan<<setw(59)<<"Rank:"<<reset<<"Pro"<<endl;
        cout<<green<<"\n\n             -----------------------------------------------------------------------------------------------------\n\n"<<reset;
        
        prof.close();
        
        ofstream temp("temp.txt",ios::out);
        
        
        temp<<name<<" "<<tcnt+task_count<<" "<<tcmp+task_completed<<" "<<pt+points;
        profile.close();
        temp.close();
        
        remove("profile.txt");
        rename("temp.txt","profile.txt");
        
        
    }
    else{
        ofstream profile("profile.txt",ios::out);
        cout<<"Profile doesn't exist.\n Enter a new task to create a profile\n";
        profile<<name<<" "<<t_count<<" "<<t_comp<<" "<<pts;
        profile.close();
        
    }
    
    
}

////////////////////////////////////// HABIT-MENU /////////////////////////////////////////////////////

void Habit::menu(string name)
{
    Habit h1;
    cout<<"\n\n"<<setw(35)<<blue<<underline<<"Select your choice:"<<reset<<"\n\n ";
    cout<<setw(50)<<"1.Enter a new task\n"<<setw(46)<<"2.Edit a task\n"<<setw(67)<<"3.Delete a task(Mark as completed)\n";
    cout<<setw(62)<<" 4.Remove a task from the list\n"<<setw(52)<<" 5.Display all tasks\n"<<setw(39)<<" 6.Exit\n";
    int ch2;
    cin>>ch2;
    
    int t_count=0;
    int t_comp=0;
    int pts=0;
    int x=0;
    
    
    switch(ch2)
    {
        case 1: h1.new_task();break;
            
        case 2: h1.edit_task();break;
            
        case 3: h1.delete_task();break;
            
        case 4: h1.remove_task();break;
            
        case 5: h1.display_task();break;
            
        case 6: exit(0);
            
            
            
        default: cout<<"Invalid option\n";
    }
}

////////////////////////////////////// TO-DO NEW TASK /////////////////////////////////////////////////////

void ToDo::new_task(){
    ToDo t1;
    
    
    
    string task;
    
    
    int time_;
    
    cout<<"Enter the task: \n";
    cin>>task;
    cout<<"Enter the deadline in hours:\n";
    cin>>time_;
    t1.get_ToDo(task,time_);
    t1.insert();
    
}

////////////////////////////////////// TO-DO EDIT TASK /////////////////////////////////////////////////////

void ToDo::edit_task(){
    
    ToDo d;
    int s_no;
    int id;
    string task;
    string newtask;
    int time;
    int newtime;
    int flag=0;
    
    ifstream to_do;
    to_do.open("ToDo.txt",ios::in|ios::out);
    cout<<"Enter the task no. you wish to edit:\n";
    cin>>id;
    
    ofstream temp; //temporary file to write the data of habits.txt excluding the line to be edited
    temp.open("temp.txt",ios::out);
    
    while(to_do >> s_no >> task >>time) //read from ToDo.txt line by line
    {
        
        if(id!=s_no){
            temp<< s_no<<' '<<task<<' '<<time<<endl; //write the data to temp file
            
        }
        
        else if(id==s_no){
            flag=1;
            cout<<s_no<<' '<<task<<' '<<time<<endl;
            cout<<"Is this the task you want to edit(y/n):\n";
            char ch;
            cin>>ch;
            if(ch=='y')
            {
                cout<<"Enter the new task:\n";
                cin>>newtask;
                cout<<"Enter the new deadline:\n";
                cin>>newtime;
                
                temp << s_no <<' '<< newtask <<' '<<newtime<<endl; //write the new task to temp file
            }
            
        }
        
        
    }
    
    if(flag==0) //id not found
    {
        cout<<"Task not found\n";
    }
    temp.close();
    to_do.close();
    remove("ToDo.txt"); //remove habits.txt
    rename("temp.txt","ToDo.txt"); //rename temp.txt to habits.txt
    
    
    
}

////////////////////////////////////// TO-DO INSERT /////////////////////////////////////////////////////

void ToDo::insert(){
    int s_no;
    ifstream to_do("ToDo.txt");;
    string line;
    int count=1;
    while(getline(to_do,line)){
        count++; //to read no. of lines for s.no.
    }
    to_do.close();
    
    ofstream todo;
    todo.open("ToDo.txt",ios::app); //to append in the habits file
    todo<<count <<' '<< task<<' '<<time_<<endl;
    
    task_count+=1;
    todo.close();
    
    
}

////////////////////////////////////// TO-DO DELETE TASK /////////////////////////////////////////////////////

void ToDo::delete_task(){
    
    ToDo d;
    int s_no;
    int id;
    int time_;
    string task;
    int flag=0;
    
    time_t now=time(0);
    struct tm *now_tm;
    int hour;
    int min;
    
    
    now_tm = localtime(&now);
    hour = now_tm->tm_hour+5; //to change time from gmt to ist , gmt+5.30=ist
    min = now_tm->tm_min;
    
    
    
    
    if(min>30){
        hour=hour+1;
        min=min%30;
    }
    
    ifstream to_do;
    to_do.open("ToDo.txt",ios::in|ios::out);
    cout<<"Enter the task no. you wish to delete:\n";
    cin>>id;
    
    ofstream temp; //temporary file to write the data of ToDo.txt excluding the line to be edited
    temp.open("temp.txt",ios::out);
    
    while(to_do >> s_no >> task >>time_) //read from ToDo.txt line by line
    {
        
        if(id!=s_no){
            if(flag==0)
                temp<< s_no<<' '<<task<<' '<<time_<<endl; //write the data to temp file
            else
                temp<< s_no-1<<' '<<task<<' '<<time_<<endl; //decrement the s.no by one, of the tasks
            //after the deleted task
        }
        
        else if(id==s_no){
            flag=1;
            cout<<s_no<<' '<<task<<' '<<time_<<endl;
            cout<<"Is this the task you want to delete(y/n):\n";
            char ch;
            cin>>ch;
            if(ch=='y')
            {
                if(time_>hour){
                    cout<<"\nBravo! You finished the task on time\n\n";
                    points+=100;
                    task_completed+=1;
                    
                }
                else{
                    cout<<"\nOops! Looks like you coudn't finish the task on time\n\n";
                    points-=40;
                }
                
            }
            
        }
        
        
    }
    
    if(flag==0) //id not found
    {
        cout<<"Task not found\n";
    }
    temp.close();
    to_do.close();
    remove("ToDo.txt"); //remove ToDo.txt
    rename("temp.txt","ToDo.txt"); //rename temp.txt to ToDo.txt
    
    
}

////////////////////////////////////// TO-DO DISPLAY TASK /////////////////////////////////////////////////////

void ToDo::display_task(){
    int s_no;
    string task;
    int time;
    fstream to_do;
    cout<<red<<"        _____________________________ Your Current To-Dos __________________________________\n\n"<<reset;
    to_do.open("ToDo.txt",ios::in); //read from file
    cout<<boldyellow<<setw(15)<<underline<<"S.no"<<reset<<boldyellow<<setw(35)<<underline<<"Tasks"<<reset<<boldyellow<<setw(35)<<underline<<"Deadline"<<reset<<endl<<endl;

    while(to_do >>s_no >>task >>time){
        cout<<setw(15)<<s_no<<setw(37)<<task<<setw(32)<<time<<":00"<<endl;
        
    }
    cout<<endl;
    
}

////////////////////////////////////// TO-DO MENU /////////////////////////////////////////////////////

void ToDo::menu(string name){
    ToDo t1;
    cout<<"\n\n"<<setw(35)<<blue<<underline<<"Select your choice:"<<reset<<"\n\n ";
    cout<<setw(50)<<"1.Enter a new task\n"<<setw(46)<<"2.Edit a task\n"<<setw(67)<<"3.Delete a task(Mark as completed)\n";
    cout<<setw(52)<<" 4.Display all tasks\n"<<setw(39)<<"5.Exit\n";
    int ch2;
    cin>>ch2;
    
    
    switch(ch2)
    {
        case 1: t1.new_task();break;
            
        case 2: t1.edit_task();break;
            
        case 3: t1.delete_task();break;
            
        case 4: t1.display_task();break;
            
        case 5: exit(0);
            
        default: cout<<"Invalid Choice\n";
    }
    
}

////////////////////////////////////// MAIN /////////////////////////////////////////////////////

int main()
{
    Habit hab;
    ToDo td;
    string name;
    cout<<brown<<"********************************************* Welcome to the Habilist *********************************************     \n\n"<<reset;
    cout<<"Enter your name:\n";
    cin>>name;
    
    while(1){
        
        
        cout<<"\n\n"<<setw(35)<<blue<<underline<<"Select your choice:"<<reset<<"\n\n ";
        cout<<setw(40)<<"1.Habit\n"<<setw(41)<<"2.To-Do\n"<<setw(53)<<"3.View Your Profile\n"<<setw(40)<<"4.Exit\n";
        int ch;
        cin>>ch;
        switch(ch)
        {
            case 1: hab.menu(name);break;//Call habit menu
                
            case 2: td.menu(name);break;//call to-do menu
                
            case 3: profile_(name);break;//call profile
                
            case 4: exit(0);
                
            default:cout<<"Not a valid option\n";
        }
        
    }
    return 0;
    
}
