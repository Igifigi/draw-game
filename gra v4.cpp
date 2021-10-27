#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <conio.h>
#include <limits>
using namespace std;

int loadedSections = 0, stabs = 0;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
PCONSOLE_SCREEN_BUFFER_INFO lpScreenInfo = new CONSOLE_SCREEN_BUFFER_INFO();



void print(string text, bool wantNewLine) {
    GetConsoleScreenBufferInfo(hConsole, lpScreenInfo);
    COORD NewSBSize = lpScreenInfo -> dwSize;
    int newpos = ((NewSBSize.X - text.size()) / 2);

    if(NewSBSize.X > text.size()) {
        for(int i = 0; i < newpos; i++)
            cout << " ";
    }
    if(wantNewLine == true)
        cout << text << endl;
    else
       cout << text;
}



void counterDisplay(){
    COORD NewSBSize = lpScreenInfo -> dwSize;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {((NewSBSize.X-32)/2)+28, 7});
    cout << "(3)|";
    Sleep(1000);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {((NewSBSize.X-32)/2)+28, 7});
    cout << "(2)|";
    Sleep(1000);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {((NewSBSize.X-32)/2)+28, 7});
    cout << "(1)|";
    Sleep(1000);
}



void loading(int waitTime){
    GetConsoleScreenBufferInfo(hConsole, lpScreenInfo);
    COORD NewSBSize = lpScreenInfo -> dwSize;
    int newpos = ((NewSBSize.X - 32) / 2);
    system("CLS");


    if(loadedSections < 30){
        print("--------------------------------", true);
        print("|                              |", true);
        print("|   LADOWANIE, PROSZE CZEKAC!  |", true);
        print("|                              |", true);
        print("|                              |", true);
        print("|>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|", true);
        for(int i = 0; i < newpos; i++)
            cout << " ";
        cout << "|";
        for(int i = 0; i < loadedSections + 1; i++)
            cout << "=";
        for(int i = 1; i < 30 - loadedSections; i++)
            cout << " ";
        cout << "|" << endl;
        print("|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<|", true);
        print("|                              |", true);
        print("|                              |", true);
        print("--------------------------------", true);

        loadedSections++;
        Sleep(waitTime);
        loading(waitTime);
    }
}



void welcome(){
    system("CLS");
    print("--------------------------------", 1);
    print("|   Witaj w grze losujacej!    |", 1);
    print("|                              |", 1);
    print("|            ZASADY            |", 1);
    print("|1. Kod losuje liczbe od 1 do  |", 1);
    print("|   100, a Ty ja zgadujesz.    |", 1);
    print("|2. Probujesz zgadywac jak naj-|", 1);
    print("|   mniej razy.                |", 1);
    print("|3. Na koniec dostajesz ocene  |", 1);
    print("|   swojego zgadywania.        |", 1);
    print("|                              |", 1);
    print("| Press ENTER to continue...   |", 1);
    print("--------------------------------", 1);
    cin.get();
}



int draw(){
    int r;
    srand(time(NULL));
    r = rand() % 100 + 1;
//    cout << r;
    return r;
}



int guess(int drawNumber){
    GetConsoleScreenBufferInfo(hConsole, lpScreenInfo);
    COORD NewSBSize = lpScreenInfo -> dwSize;
    int newpos = ((NewSBSize.X - 32) / 2);
    int insertNumber;
    system("CLS");

    do{
    print("--------------------------------", 1);
    print("|            ZGADUJ            |", 1);
    print("|                              |", 1);
    for(int i = 0; i < ((NewSBSize.X - 32) / 2); i++){
        cout << " ";
    }
    cout << "|      Liczba strzalow: ";

    if(stabs < 10)
        cout << 0 << stabs << "     |" << endl;
    else
        cout << stabs << "     |" << endl;
    print("|                              |", 1);
    print("|                              |", 1);
    print("|         Twoja liczba:        |", 1);
    print("|                              |", 1);
    print("|                              |", 1);
    print("--------------------------------", 0);

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X/2)-1, 7});
    cin >> insertNumber;

    if(insertNumber == drawNumber){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {((NewSBSize.X-32)/2)+12, 8});
        cout << "Zgadles!";
        counterDisplay();
        return 0;
    }
    else{
        stabs++;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 5});
        for(int i = 0; i < (NewSBSize.X - 32) / 2; i++)
            cout << " ";
        if(insertNumber > drawNumber){
            cout <<  "|  Wpisana liczba jest za duza |";
        }
        else if(insertNumber < drawNumber){
            cout << "|  Wpisana liczba jest za mala |";
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {((NewSBSize.X-32)/2+1)+6, 8});
        cout << "Sprobuj jeszcze raz!" << endl;
        counterDisplay();
        system("CLS");
    }
    }while(insertNumber != drawNumber);
}



int grade(int stabs){
    GetConsoleScreenBufferInfo(hConsole, lpScreenInfo);
    COORD NewSBSize = lpScreenInfo -> dwSize;
    system("CLS");

    int grade = 10 - stabs;
    if(grade < 1)
        grade = 1;

    print("--------------------------------", 1);
    print("|            OCENA             |", 1);
    print("|                              |", 1);
    print("|W skali od 1 do 10 Twoje zga- |", 1);
    print("|dywanie uzyskuje ocene:       |", 1);
    print("|                              |", 1);
    print("|                              |", 1);
    print("|                              |", 1);
    print("|     Smacznej kawusi! <3      |", 1);
    print("| Press ENTER to continue...   |", 1);
    print("--------------------------------", 1);

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X/2)-1, 6});
    if(grade < 10){
        cout << 0 << grade;
    }
    else{
        cout << grade;
    }
    getch();
}



void play(){
    int number = draw();
    guess(number);
    grade(stabs);
}



void goodbye(int sequenceCount){
    GetConsoleScreenBufferInfo(hConsole, lpScreenInfo);
    COORD NewSBSize = lpScreenInfo -> dwSize;
    system("CLS");

    print("--------------------------------", 1);
    print("|          WYLACZANIE          |", 1);
    print("|        Prosze czekac!        |", 1);
    print("|                              |", 1);
    print("|                              |", 1);
    print("|                              |", 1);
    print("|                              |", 1);
    print("|                              |", 1);
    print("|                              |", 1);
    print("--------------------------------", 1);

    for(int i = 0; i < sequenceCount; i++){
        switch(i % 19){
        case 0:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << ">****";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "*****";
            break;
        case 1:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << ">>***";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "*****";
            break;
        case 2:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << ">>>**";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "*****";
            break;
        case 3:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << ">>>>*";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "*****";
            break;
        case 4:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << ">>>>>";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "*****";
            break;
        case 5:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << ">>>>>";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "****<";
            break;
        case 6:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << ">>>>>";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "***<<";
            break;
        case 7:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << ">>>>>";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "**<<<";
            break;
        case 8:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << ">>>>>";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "*<<<<";
            break;
        case 9:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << ">>>>>";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "<<<<<";
            break;
        case 10:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << "*>>>>";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "<<<<<";
            break;
        case 11:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << "**>>>";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "<<<<<";
            break;
        case 12:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << "***>>";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "<<<<<";
            break;
        case 13:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << "****>";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "<<<<<";
            break;
        case 14:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << "*****";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "<<<<*";
            break;
        case 15:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << "*****";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "<<<**";
            break;

        case 16:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << "*****";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "<<***";
            break;
        case 17:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << "*****";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "<****";
            break;
        case 18:
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 5});
            cout << "*****";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 6});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 7});
            cout << "*   *";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(NewSBSize.X - 32)/2 + 13, 8});
            cout << "*****";
            break;
        }
        Sleep(100);
    }
}



int main(){
    loading(5); //normalnie <- 500, a szybko 5
    welcome();
    play();
    goodbye(100);
    system("CLS");
    return 0;
}

