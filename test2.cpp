#include <iostream>
#include <windows.h>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <string>
#include <ctime>
#include <iomanip>
#include <thread>
#include <chrono>
#include <string>
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;

HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO butter_info;

#define orange "\033[38;5;214m"

const string colors[8]={"🟥","🟦","🟧","🟨","🟩","🟪","🟫","⬛"};
const int num_of_colors=8;
const int num_of_tetrominoes=7;
const int sleep_time_level_1=340;
const int sleep_time_level_2=270;
char name_level_1[]="resualt_of_level_1.txt";
char name_level_2[]="resualt_of_level_2.txt";

struct Table{
    int condition;
    int color;
};

struct hold{
    int tetrominoe=-1;
    int color;
};

struct leaderboard{
    string name;
    int score;
    int time;
};


void displayTable(vector <vector<Table>> table,int x,int y,int Location_x);
void emptyLines(vector <vector<Table>> &table,int y);
void removeLines(vector <int> filled_lines,vector <vector<Table>> &table);
void displayNextTetrominoes(int x,int y,int next_tetrominoes[3][2]);
void displayHold(hold hold_tetrominoe,int x,int y);
void displayScore(int score,int location_x);
void chekFullLines(vector <vector<Table>> &table,int location_x,int &score);
void DisplayTetrominoe(vector <vector<Table>> table,int x,int y,int kind,int tetrominoe,int color,int location_x);
void stoppingPlace(vector <vector<Table>> table,int x,int y,int kind,int tetrominoe,int location_x);
void moveFaster(int &sleep_time);
void fix(vector <vector<Table>> &table,int x,int y,int kind,int tetrominoe,int color);
void updateTetrominoes(int next_tetrominoes[3][2],int &color,int &tetrominoe);
void displayTime(int time,int location_x);
void displayBox(string name,int level,int location_x,int location_y,int length);
void getInformation(leaderboard &player,int location_x,int &length,int &width,int &level,char file_name[]);
int puase(int location_x);
void logo(int x,int y);
void Menu();
void HowToPlay(int x,int y);
void setColor(int color);
void playing();
void readOfFile(char file_name[]);
void sortAndDisplay(leaderboard participants[],int number_of_Participants);
void easterEgg(string name,int &score);

int tetrominoes[7][4][4][4] = {

    {
        
        {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        }
    },
    {
        {
            {0, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 1, 1, 1},
            {0, 0, 0, 1},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 1, 1, 0}
        }
    },
    {
        {
            {0, 0, 0, 0},
            {0, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 1, 1, 1},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0}
        }
    },
    {
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }
    },
    {
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 0, 1, 1},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 1, 0}
        }
    },
    {
        {
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 1, 1, 1},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 1, 0}
        }
    },
    {
        {
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 1, 1},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {0, 1, 0, 0}
        }
    }
};

void gotoxy(int x, int y) {
    COORD position={(short)x, (short)y};
    SetConsoleCursorPosition(hConsole, position);
}

void findMiddleOfLine(int &columns){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int random(int num){
    return(rand() %num);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawRectangle(int length,int width,int color,int x,int y){
    setColor(color);
    for(int i=0;i<width;i++)
        for(int j=0;j<length;j++){
            gotoxy(x+j,y+i);
            if(i==0){
                if(j==0)
                    cout<<"\u256D";
                if(j==length-1)
                    cout<<"\u256E";
                else if(j!=0)
                    cout<<"\u2500";
            }
            if(i==width-1){
                if(j==0)
                    cout<<"\u2570";
                if(j==length-1)
                    cout<<"\u256F";
                else if(j!=0)
                    cout<<"\u2500";
            }
            else if(i!=0)
                if(j==0 || j==length-1)
                    cout<<"\u2502";
        }
}

void vintagePrint(string str,int x,int y){
    gotoxy(x,y);
    setColor(4);
    for(int i=0 ; i < str.length() ; i++){
        Sleep(36);
        cout << str[i];
    }
}

void Menu() {
    int x;
    findMiddleOfLine(x);
    x=x/2;
    x=x-23;
    logo(x,0);
    gotoxy(x,6);
    cout<<"loading...";
    Sleep(4500);
    drawRectangle(17,3,15,x,6);
    gotoxy(x+1,7);
    setColor(2);
    cout << " 1. start game"<< endl;
    drawRectangle(18,3,15,x,9);
    setColor(2);
    gotoxy(x+1,10);
    cout << " 2. How to play"<< endl;
    drawRectangle(23,3,15,x,12);
    setColor(2);
    gotoxy(x+1,13);
    cout << " 3. Show leaderboard"<< endl;
    drawRectangle(11,3,15,x,15);
    setColor(2);
    gotoxy(x+1,16);
    cout << " 4. Exit"<< endl;

    switch (getch()) {
        case '1':
            playing();
            break;
        case '2':
            HowToPlay(x,0);
            break;
        case '3':
            int level;
            system("cls");
            drawRectangle(44,6,15,x,2);
            gotoxy(x+1,3);
            setColor(2);
            cout<<"which leaderboard would you like to see?";
            gotoxy(x+1,4);
            cout<<"1. level 1";
            gotoxy(x+1,5);
            cout<<"2. level 2";
            gotoxy(x+1,6);
            setColor(15);
            cin>>level;
            if(level==1)
                readOfFile(name_level_1);
            if(level==2)
                readOfFile(name_level_2);
            break;
        case '4':
        system("cls");  
        setColor(5);
        cout<<"\n\t─██████████████─██████████████─██████████████────████████──████████─██████████████─"<<endl;
        cout<<"\t─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██────██░░░░██──██░░░░██─██░░░░░░░░░░██─"<<endl;
        cout<<"\t─██░░██████████─██░░██████████─██░░██████████────████░░██──██░░████─██░░██████░░██─"<<endl;
        cout<<"\t─██░░██─────────██░░██─────────██░░██──────────────██░░░░██░░░░██───██░░██──██░░██─"<<endl;
        cout<<"\t─██░░██████████─██░░██████████─██░░██████████──────████░░░░░░████───██░░██████░░██─"<<endl;
        cout<<"\t─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██────────████░░████─────██░░░░░░░░░░██─"<<endl;
        cout<<"\t─██████████░░██─██░░██████████─██░░██████████──────────██░░██───────██░░██████░░██─"<<endl;
        cout<<"\t─────────██░░██─██░░██─────────██░░██──────────────────██░░██───────██░░██──██░░██─"<<endl;
        cout<<"\t─██████████░░██─██░░██████████─██░░██████████──────────██░░██───────██░░██──██░░██─"<<endl;
        cout<<"\t─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██──────────██░░██───────██░░██──██░░██─"<<endl;
        cout<<"\t─██████████████─██████████████─██████████████──────────██████───────██████──██████─"<<endl;
        setColor(15);
        exit(0);
    }
	system("cls");
}

void logo(int x,int y){
    system("cls");
    setColor(4);
    gotoxy(x,y);
    cout<<"████████╗";
    gotoxy(x,y+1);
    cout<<"╚══██╔══╝";
    gotoxy(x,y+2);
    cout<<"   ██║   ";
    gotoxy(x,y+3);
    cout<<"   ██║   ";
    gotoxy(x,y+4);
    cout<<"   ██║   ";
    gotoxy(x,y+5);
    cout<<"   ╚═╝   ";  
    gotoxy(x+9,y);
    cout<<orange<<"█"<<orange<<"█"<<orange<<"█"<<orange<<"█"<<orange<<"█"<<orange<<"█"<<orange<<"█"<<orange<<"╗";
    gotoxy(x+9,y+1);
    cout<<orange<<"█"<<orange<<"█"<<orange<<"╔"<<orange<<"═"<<orange<<""<<orange<<"═"<<orange<<"═"<<orange<<"═"<<orange<<"╝";
    gotoxy(x+9,y+2);
    cout<<orange<<"█"<<orange<<"█"<<orange<<"╔"<<orange<<"═"<<orange<<"═"<<orange<<"═"<<orange<<"═"<<orange<<"╝";
    gotoxy(x+9,y+3);
    cout<<orange<<"█"<<orange<<"█"<<orange<<"╔"<<orange<<"═"<<orange<<"═"<<orange<<"╝  ";
    gotoxy(x+9,y+4);
    cout<<orange<<"█"<<orange<<"█"<<orange<<"█"<<orange<<"█"<<orange<<"█"<<orange<<"█"<<orange<<"█"<<orange<<"╗";
    gotoxy(x+9,y+5);
    cout<<orange<<"╚"<<orange<<"═"<<orange<<"═"<<orange<<"═"<<orange<<"═"<<orange<<"═"<<orange<<"═"<<orange<<"╝";      
    setColor(6);
    gotoxy(x+17,y);
    cout<<"████████╗";
    gotoxy(x+17,y+1);
    cout<<"╚══██╔══╝";
    gotoxy(x+17,y+2);
    cout<<"   ██║   ";
    gotoxy(x+17,y+3);
    cout<<"   ██║   ";
    gotoxy(x+17,y+4);
    cout<<"   ██║   ";
    gotoxy(x+17,y+5);
    cout<<"   ╚═╝   "; 
    setColor(2);
    gotoxy(x+26,y);
    cout<<"██████╗ ";
    gotoxy(x+26,y+1);
    cout<<"██╔══██╗";
    gotoxy(x+26,y+2);
    cout<<"██████╔╝";
    gotoxy(x+26,y+3);
    cout<<"██╔══██╗";
    gotoxy(x+26,y+4);
    cout<<"██║  ██║";
    gotoxy(x+26,y+5);
    cout<<"╚═╝  ╚═╝"; 
    setColor(3);
    gotoxy(x+33,y);
    cout<<" ██╗";
    gotoxy(x+33,y+1);
    cout<<" ██";
    gotoxy(x+33,y+2);
    cout<<" ██║";
    gotoxy(x+33,y+3);
    cout<<" ██║";
    gotoxy(x+33,y+4);
    cout<<" ██║";
    gotoxy(x+33,y+5);
    cout<<" ╚═╝";
    setColor(5);
    gotoxy(x+37,y);
    cout<<" ██████╗";
    gotoxy(x+37,y+1);
    cout<<"██╔════╝";
    gotoxy(x+37,y+2);
    cout<<"╚█████╗";
    gotoxy(x+37,y+3);
    cout<<" ╚═══██╗";
    gotoxy(x+37,y+4);
    cout<<"██████╔╝";
    gotoxy(x+37,y+5);
    cout<<"╚═════╝"; 
    setColor(15);
    gotoxy(x,y+6);
}

void HowToPlay(int x,int y) {
    string str;
    system("cls");
    drawRectangle(55,15,15,x,y);
    str="Welcome to tetris";
    vintagePrint(str,x+20,y+1);
    x+=2;
    str="The game has two level of difficulty, ezay and hard" ;
    vintagePrint(str,x,y+2);
    str="you need to choose the level of the game";
    vintagePrint(str,x,y+3);
    str="according to your abilities." ;
    vintagePrint(str,x,y+4);
    str="Move the tetrominos. You can move them left and";
    vintagePrint(str,x,y+5);
    str="right,and you can rotate them inboth directions.";
    vintagePrint(str,x,y+6);
    str="(up is clockwise,and You can also speed up their";
    vintagePrint(str,x,y+7);
    str="fall ( known as \"Soft Drop\" used with the down";
    vintagePrint(str,x,y+8);
    str="button) or you can immediately set it down(known";
    vintagePrint(str,x,y+9);
    str="as \"Hard Drop\"used with the space bar).";     
    vintagePrint(str,x,y+10);
    str="Understand the different tetrominos.";
    vintagePrint(str,x,y+11);
    str="There are seven types of tetrominos.";
    vintagePrint(str,x,y+12);
    str="press to continu";
    vintagePrint(str,x+20,y+13);
    char a=getch();
    Menu();
}

int numOfParticipants(char file_name[]){
    ifstream file(file_name);
    int line_counter=0;
    string line;
    if(file.is_open()){
        while(getline(file,line))
            line_counter++;
        file.close();
    }
    return(line_counter-1);
}

bool findSimilarities(char file_name[],leaderboard player,int level){
    bool changes=false;
    leaderboard test;
    int number_of_participants=numOfParticipants(file_name);
    ifstream myfile(file_name);
    ofstream testfile("test.txt", ios::out);
    if(level==1)
        testfile<<"level_1";
    else
        testfile<<"level_2";
    if(myfile.is_open()){
        myfile>>test.name;
        for(int i=0;i<number_of_participants;i++){
            myfile>>test.name>>test.score>>test.time;
            if(test.name!=player.name)
                testfile<<endl<<test.name<<" "<<test.score<<" "<<test.time;
            else{
                changes=true;
                if(test.score<player.score || (test.score==player.score && player.time<test.time)){
                    testfile<<endl<<player.name<<" "<<player.score<<" "<<player.time;
                }
                else
                    testfile<<endl<<test.name<<" "<<test.score<<" "<<test.time;
            }
        }
    }
    myfile.close();
    testfile.close();
    remove(file_name);
    rename("test.txt",file_name);
    return(changes);
}

void wrightInFile(char file_name[],leaderboard player){
    ofstream myfile(file_name, ios::app);
    myfile<<endl<<player.name<<" "<<player.score<<" "<<player.time;
}

void sortAndDisplay(leaderboard participants[],int number_of_Participants){
    system("cls");
    bool changes=true;
    char input;
    int x;
    findMiddleOfLine(x);
    x=x/2-23;
    while(changes){
        changes=false;
        for(int i=0;i<number_of_Participants-1;i++)
            if(participants[i].score<participants[i+1].score
            || (participants[i].score==participants[i+1].score
             && participants[i].time>participants[i+1].time)){
                swap(participants[i].score,participants[i+1].score);
                swap(participants[i].name,participants[i+1].name);
                swap(participants[i].time,participants[i+1].time);
                changes=true;
            }
    }
    int i;
    for(i=0;i<number_of_Participants;i++)
        if(i<10){
            drawRectangle(46,3,15,x,i*3);
            gotoxy(x+1,i*3+1);
            cout<<i+1<<"- name: ";
            setColor(2);
            cout<<left<<setw(8)<<participants[i].name;
            setColor(15);
            cout<<" score: ";
            setColor(2);
            cout<<setw(6)<<participants[i].score;
            setColor(15);
            cout<<"time: ";
            setColor(2);
            cout<<left<<setw(2)<<participants[i].time/60<<":"<<participants[i].time%60;
        }
    setColor(15);
    gotoxy(x+1,i*3+1);
    cout<<"Press to return to the menu";
    input=getch();//We are waiting for the user to press a button to continue the game
    Menu();
}

void readOfFile(char file_name[]){
    ifstream file(file_name,ios::in);
    int number_of_players=numOfParticipants(file_name);
    if(number_of_players>0){
        leaderboard players[number_of_players];
        if (file.is_open()) {
            file>>players[0].name;
                for(int i=0;i<number_of_players;i++){
                    file>>players[i].name>>players[i].score>>players[i].time;
                }
            }
        sortAndDisplay(players,number_of_players);
    }
    else{
        system("cls");
        drawRectangle(30,5,15,2,1);
        gotoxy(3,2);
        setColor(2);
        cout<<"There is nothing to display";
        gotoxy(3,4);
        setColor(15);
        cout<<"press to return menu";
        char a=getch();
        Menu();
    }
    file.close();
    return;
}

void chekingFile(char file_name[],int level){
    ifstream fileCheck(file_name);
    if (!fileCheck.is_open()) {
        ofstream fileCreate(file_name);
        if(level==1)
            fileCreate<<"level_1";
        else
            fileCreate<<"level_2";
        fileCreate.close();
    }
}

bool collide(vector <vector<Table>> table,int x,int y,int kind,int tetrominoe){
    int n=table.size();
    int m=table[0].size();
    if(y>n-4 || x<0 || x>m-4)
        return(false);
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
            if(i>=y && i<y+4 && j>=x && j<x+4)
                if(tetrominoes[tetrominoe][kind][i-y][j-x]==1 && (table[i][j].condition==1 || table[i][j].condition==2))
                    return(false);
    return(true);
}

void DefineTheBorder(vector <vector<Table>> &table){
    int n=table.size();
    int m=table[0].size();
    cout<<m<<n<<endl;
    for(int i=0;i<=n-2;i++)
        for(int j=1;j<=m-2;j++){
            if(((i==0 || i==n-2) && (j>0 || j<m-1)) || ((j==m-2 || j==1) && i<n-1))
                table[i][j].condition=2;
            else
                table[i][j].condition=0;
        }
}

void cycleLeft(vector <vector<Table>> table,int x,int y,int &kind,int tetrominoe){
    if(collide(table,x,y,(kind+1)%4,tetrominoe))
        kind=(kind+1)%4;
}

void cycleRight(vector <vector<Table>> table,int x,int y,int &kind,int tetrominoe){
    if(collide(table,x,y,(kind+3)%4,tetrominoe))
        kind=(kind+3)%4;
}

void displayTable(vector <vector<Table>> table,int x,int y,int Location_x){
    int n=table.size();
    int m=table[0].size();
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(table[i][j].condition==1){
                gotoxy(Location_x+(2*j), i);
                cout<<colors[table[i][j].color];
            }
            if(i>y+3 || i<y || j<x || j>x+3)
                if(table[i][j].condition==0){
                    gotoxy(Location_x+(2*j), i);
                    cout<<" ";
                }
            if(table[i][j].condition==2){
                gotoxy(Location_x+(2*j), i);
                cout<<"\u2B1C";
            }
        }
    }
}

void emptyLines(vector <vector<Table>> &table,int y){
    int m=table[0].size();
    for(int i=0;i<m;i++)
        if(table[y][i].condition==1)
            table[y][i].condition=0;        //clearing the line
}

void removeLines(vector <int> filled_lines,vector <vector<Table>> &table){
    int m=table[0].size();
        for(int i=0;i<filled_lines.size();i++){
            for(int j=filled_lines[i];j>1;j--)
                for(int k=2;k<m-2;k++){
                    table[j][k].condition=table[j-1][k].condition;     //replacing the line with the top one
                    table[j][k].color=table[j-1][k].color;              
                }
        }
}

void displayNextTetrominoes(int x,int y,int next_tetrominoes[3][2]){
    drawRectangle(10,10,15,x,y);
    int tetrominoe;
    for(int i=0;i<3;i++){               //each i is for one of the three blocks
        tetrominoe=next_tetrominoes[i][0];
        for(int j=1;j<3;j++)
            for(int k=0;k<4;k++){
                gotoxy(x+1+2*k,y+1+(i*3)+j-1);
                if(tetrominoes[tetrominoe][0][j][k]==1)
                    cout<<colors[next_tetrominoes[i][1]];
                else
                    cout<<"  ";
            }
    }
}

void displayHold(hold hold_tetrominoe,int x,int y){
    drawRectangle(10,4,15,x,y);
    if(hold_tetrominoe.tetrominoe!=-1){
        for(int i=1;i<3;i++)
            for(int j=0;j<4;j++){
                if(tetrominoes[hold_tetrominoe.tetrominoe][0][i][j]==1){
                    gotoxy((x+1)+(2*j),(y+1)+(i-1));
                    cout<<colors[hold_tetrominoe.color];
                }
                else{
                    gotoxy((x+1)+(2*j),(y+1)+(i-1));
                    cout<<" ";
                }
            }
    }
}

void scoreCalculation(int &score,int num){
    int price=100;          //initialization for calculating the score
    for(int i=1;i<=num;i++){
        score+=i*price;
    }
}

void displayScore(int score,int location_x){
    drawRectangle(9,4,15,location_x,0);
    gotoxy(location_x+2,1);
    cout<<"score:";
    gotoxy(location_x+2,2);
    setColor(2);
    cout<<score;
}

void chekFullLines(vector <vector<Table>> &table,int location_x,int &score){
    int n=table.size();
    int m=table[0].size();
    vector <int> filled_lines; //a vector to store full lines
    bool line;
    for(int i=1;i<n-2;i++){
        line=true;
        for(int j=1;j<m-1;j++)
            if(table[i][j].condition==0)
                line=false;
        if(line){
            filled_lines.push_back(i);
            emptyLines(table,i);
        }
    }
    if(filled_lines.size()>0){
        displayTable(table,m+10,n+10,location_x);   //the reason of +10s is to make the cursor out of the table
        scoreCalculation(score,filled_lines.size());
        displayScore(score,location_x-9);
        Sleep(600);
        removeLines(filled_lines,table);
    }
}

void DisplayTetrominoe(vector <vector<Table>> table,int x,int y,int kind,int tetrominoe,int color,int location_x){
    for(int i=y;i<y+4;i++)
        for(int j=x;j<x+4;j++)
            if(tetrominoes[tetrominoe][kind][i-y][j-x]==1){
                gotoxy(location_x+(2*j), i);
                cout<<colors[color];
            }
            else if(table[i][j].condition==0){
                gotoxy(location_x+(2*j), i);
                cout<<" ";
            }
}

void stoppingPlace(vector <vector<Table>> table,int x,int y,int kind,int tetrominoe,int location_x){
    while(true){
        if(collide(table,x,y+1,kind,tetrominoe)==false)
            break;
        y++;
    }
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(tetrominoes[tetrominoe][kind][i][j]==1){
                gotoxy(location_x+2*(j+x),y+i);
                setColor(15);
                cout<<"𝌳";               //place prediction for blocks 
            }
}

void moveFaster(int &sleep_time){
    sleep_time=(sleep_time*3)/10;          //for the level 2 of the game
}

void fix(vector <vector<Table>> &table,int x,int y,int kind,int tetrominoe,int color){
    int n=table.size();
    int m=table[0].size();
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(i>=y && i<y+4 && j>=x && j<x+4)
                if(tetrominoes[tetrominoe][kind][i-y][j-x]==1){
                    table[i][j].condition=1;
                    table[i][j].color=color;
                }
}
void game_over(int x){
    system("cls");
    setColor(4);
    gotoxy(x,2);
    cout<<"░██████╗░░█████╗░███╗░░░███╗███████╗  ░█████╗░██╗░░░██╗███████╗██████╗░";
    gotoxy(x,3);
    cout<<"██╔════╝░██╔══██╗████╗░████║██╔════╝  ██╔══██╗██║░░░██║██╔════╝██╔══██╗";
    gotoxy(x,4);
    cout<<"██║░░██╗░███████║██╔████╔██║█████╗░░  ██║░░██║╚██╗░██╔╝█████╗░░██████╔╝";
    gotoxy(x,5);
    cout<<"██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░  ██║░░██║░╚████╔╝░██╔══╝░░██╔══██╗";
    gotoxy(x,6);
    cout<<"╚██████╔╝██║░░██║██║░╚═╝░██║███████╗  ╚█████╔╝░░╚██╔╝░░███████╗██║░░██║";
    gotoxy(x,7);
    cout<<"░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝  ░╚════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝";
    Sleep(4500);
}
void updateTetrominoes(int next_tetrominoes[3][2],int &color,int &tetrominoe){
        tetrominoe=next_tetrominoes[0][0];
        color=next_tetrominoes[0][1];
        for(int i=0;i<2;i++){
        next_tetrominoes[i][0]=next_tetrominoes[i+1][0];
        next_tetrominoes[i][1]=next_tetrominoes[i+1][1];
        }
        next_tetrominoes[2][0]=rand() % num_of_tetrominoes;      //new random tetris
        next_tetrominoes[2][1]=rand() % num_of_colors;           //color of new random tetris
}

void displayTime(int time,int location_x){
    time=time/1000;            //turning to seconds
    drawRectangle(9,4,15,location_x,4);
    gotoxy(location_x+1,5);
    cout<<"time:";
    gotoxy(location_x+1,6);
    setColor(2);
    cout<<time/60;             //showing minutes
    gotoxy(location_x+3,6);
    setColor(15);
    cout<<":";
    setColor(2);
    cout<<time%60;             //showing seconds
}

void displayBox(string name,int level,int location_x,int location_y,int length){
    drawRectangle(length,3,15,location_x,location_y);
    gotoxy(location_x+1,location_y+1);
    cout<<"   name:";
    setColor(2);
    cout<<name;
    gotoxy(location_x+length-11,location_y+1);
    setColor(15);
    cout<<"level:";
    setColor(2);
    cout<<level;
}

void getInformation(leaderboard &player,int location_x,int &length,int &width,int &level,char file_name[]){
    system("cls");
    drawRectangle(43,4,15,location_x,3);
    gotoxy(location_x+2,4);
    setColor(2);
    cout<<"Enter your name"<<endl;
    gotoxy(location_x+2,5);
    setColor(15);
    cin>>player.name;
    system("cls");
    drawRectangle(43,4,15,location_x,3);
    gotoxy(location_x+2,4);
    setColor(2);
    cout<<"Enter the length and width of the table"<<endl;
    setColor(15);
    gotoxy(location_x+2,5);
    cin>>length>>width;
    if (length < 5 || width < 5) {
    system("cls");
    drawRectangle(10,3,15,44,3);
    setColor(4);
    gotoxy(45,4);
    cout << "invalid";
    Sleep(3000);
    playing();
    }
    system("cls");
    drawRectangle(43,4,15,location_x,3);
    gotoxy(location_x+2,4);
    setColor(2);
    cout<<"Choose your level (1.easy   2.hard)"<<endl;
    setColor(15);
    gotoxy(location_x+2,5);
    cin>>level;
    if(level==1)
        strcpy(file_name, name_level_1);
    if(level==2)
        strcpy(file_name, name_level_2);
    
}

int pause(int location_x){
    int input;
    system("cls");
    drawRectangle(14,6,15,location_x,2);
    setColor(2);
    gotoxy(location_x+1,3);
    cout<<"1. Exit";
    gotoxy(location_x+1,4);
    cout<<"2. Continue";
    gotoxy(location_x+1,5);
    cout<<"3. Restart";
    gotoxy(location_x+3,6);
    setColor(15);
    cin>>input;
    system("cls");
    return(input);
}
void easterEgg(string name,int &score){
    if(name=="amirhossein")
        score=1000;
}
void playing(){
    int score=0,time=0,time_puase=0,kind,x,y,m,n,tetrominoe,sleep_time,color,level;
    int time_level=1;
    char file_name[23];
    leaderboard player;
    bool hold_condition=false;
    hold hold_tetrominoe;
    char a;
    int location_x;
    findMiddleOfLine(location_x);
    location_x=location_x/2;
    int next_tetrominoes[3][2];
    getInformation(player,location_x-21,m,n,level,file_name);
    easterEgg(player.name,score);
    chekingFile(file_name,level);
    system("cls");
    vector <vector <Table>> table(m+3, vector<Table>(n+4));
    location_x-=(n+4)/2+3;
    DefineTheBorder(table);
    for(int i=0;i<3;i++){
        next_tetrominoes[i][0]=rand() % num_of_tetrominoes;
        next_tetrominoes[i][1]=rand() % num_of_colors;
    }
    chrono::high_resolution_clock::time_point start_time = chrono::high_resolution_clock::now();
    while(true){
        y=-1;
        x=(n+4)/2-2;
        kind=0;
        if(hold_condition==false){
            updateTetrominoes(next_tetrominoes,color,tetrominoe);
        }
        else{
            if(hold_tetrominoe.tetrominoe==-1){
                hold_tetrominoe.tetrominoe=tetrominoe;
                hold_tetrominoe.color=color;
                updateTetrominoes(next_tetrominoes,color,tetrominoe);
            }
            else{
                color+=hold_tetrominoe.color;
                hold_tetrominoe.color=color-hold_tetrominoe.color;
                color=color-hold_tetrominoe.color;
                tetrominoe+=hold_tetrominoe.tetrominoe;
                hold_tetrominoe.tetrominoe=tetrominoe-hold_tetrominoe.tetrominoe;
                tetrominoe=tetrominoe-hold_tetrominoe.tetrominoe;                
            }
        }
        hold_condition=false;
        if(level==1)
            sleep_time=sleep_time_level_1;
        if(level==2)
            sleep_time=sleep_time_level_2-((time_level-1)*20);
        if(collide(table,x,y+1,kind,tetrominoe)==false){
           system("cls");
            cout<<"you lost";
            break;
        }
        while(true){
            y++;
            if(collide(table,x,y,kind,tetrominoe)==false){
                fix(table,x,y-1,kind,tetrominoe,color);
                break;
            }
            for(int i=0;i<3;i++){
                if(kbhit()){
                    a=getch();
                    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                    switch (a)
                    {
                    case 'z':
                        if(collide(table,x-1,y,kind,tetrominoe))
                            --x;
                        break;
                    case 'x':
                        if(collide(table,x+1,y,kind,tetrominoe))
                            ++x;
                        break;
                    case 's':
                        cycleLeft(table,x,y,kind,tetrominoe);
                        break;
                    case 'a':
                        cycleRight(table,x,y,kind,tetrominoe);
                        break;
                    case 'c':
                        moveFaster(sleep_time);
                        break;                        
                    case 'e':
                        chrono::high_resolution_clock::time_point middle_time_1 = chrono::high_resolution_clock::now();
                        int input=pause(location_x+5);
                        if(input==1){
                            chrono::high_resolution_clock::time_point time_1 = chrono::high_resolution_clock::now();
                            chrono::seconds ending = chrono::duration_cast<chrono::seconds>(time_1 - start_time);
                            player.time=ending.count()-time_puase;
                            player.score=score;
                            if(findSimilarities(file_name,player,level)==false)
                                wrightInFile(file_name,player);
                            Menu();
                            return;    
                        }
                        if(input==3){
                            playing();
                            return;
                        }
                        chrono::high_resolution_clock::time_point middle_time_2 = chrono::high_resolution_clock::now();
                        chrono::milliseconds puase_time = chrono::duration_cast<chrono::milliseconds>(middle_time_2 - middle_time_1);
                        time_puase+=puase_time.count();
                        break;
                    }
                    if(level==1){
                        if(a=='d'){
                            hold_condition=true;
                            break;
                        }
                    }
                }
            displayTable(table,x,y,location_x);
            stoppingPlace(table,x,y,kind,tetrominoe,location_x);
            DisplayTetrominoe(table,x,y,kind,tetrominoe,color,location_x);
            displayNextTetrominoes(location_x+2*(n+4)+1,0,next_tetrominoes);
            if(level==1)
                displayHold(hold_tetrominoe,location_x+2*(n+4)+1,10);
            displayScore(score,location_x-9);
            displayBox(player.name,level,location_x-9,m+3,20+2*(n+4));
            gotoxy(m+5,n+5);
            chrono::high_resolution_clock::time_point middle_time = chrono::high_resolution_clock::now();
            chrono::milliseconds game_time = chrono::duration_cast<chrono::milliseconds>(middle_time - start_time);
            gotoxy(0,1);
            displayTime(game_time.count()-time_puase,location_x-9);
            if(game_time.count()-time_puase>20000*time_level)
                time_level++;
            gotoxy(0,0);
            cout<<"       ";
            Sleep(sleep_time);
            }
        if(hold_condition)
            break;
        }
        chekFullLines(table,location_x,score);
    }
    chrono::high_resolution_clock::time_point end_time = chrono::high_resolution_clock::now();
    chrono::seconds duration = chrono::duration_cast<chrono::seconds>(end_time - start_time);
    player.time=duration.count()-(time_puase/1000);
    player.score=score;
    if(findSimilarities(file_name,player,level)==false)
        wrightInFile(file_name,player);
    game_over(location_x+12);
    Menu();
}

int main(){
    srand(static_cast<unsigned int>(time(nullptr)));
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    // Set the cursor size to 1 (invisible)
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    Menu();
    return 0;
}