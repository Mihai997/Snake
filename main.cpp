#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define DIML 24
#define DIMC 50

using namespace std;

struct punct {
    int L;
    int C;
};

int L, C; // dimensiunile tablei de joc
int a[DIML][DIMC]; // matricea ce codifica tabla de joc
punct s[DIML*DIMC];
int LH, CH, N, D, speed,p,M;
char c,d;
// 0 = liber
// 1 = corp sarpe
// 2 = cap sarpe
// 3 = mancare


void puneHrana() {
    int ok;
    do {
        LH = rand() % L + 1;
        CH = rand() % C + 1;

        ok = 0;
        for (int i=1;i<=N;i++)
            if (LH == s[i].L && CH == s[i].C) {
                ok = 1;
                break;
            }

    } while (ok);
}


void init() {
    speed = 250;
    L = 10;
    C = 20;
    srand(time(0));
    N = 4;
    s[1].L = 2; s[1].C = 5;
    s[2].L = 2; s[2].C = 4;
    s[3].L = 2; s[3].C = 3;
    s[4].L = 2; s[4].C = 2;
    puneHrana();
    D = 2; // D: 1 = sus   2 = dreapta   3 = jos   4 = stanga
}

void save() {
    ofstream fout("salvare.out");
    fout<<speed<<" "<<p<<" "<<L<<" "<<C<<" "<<N<<" ";
    for (int i=1;i<=N;i++)
        fout<<s[i].L<<" "<<s[i].C<<" ";
    fout<<D;
    fout.close();
}

void load() {
    ifstream fout("salvare.out");
    fout>>speed>>p>>L>>C>>N;
    for (int i=1;i<=N;i++)
        fout>>s[i].L>>s[i].C;
    fout>>D;
    fout.close();
}
void savescore() {
    ofstream fout("savescore.out");
    M=p;
    fout<<M;
}
void loadscore(){
    ifstream fout("savescore.out");
    fout>>M;
}

void afisare() {
    int i,j;
    // construiesc pe a
    for (i=1;i<=L;i++)
        for (j=1;j<=C;j++)
            a[i][j] = 0;

    for (i=2;i<=N;i++)
        a[ s[i].L ][ s[i].C ] = 1;
    a[ s[1].L ][ s[1].C ] = 2;
    a[ LH ][ CH ] = 3;

    system("cls");


    cout<<(char)201;
    for (i=1;i<=C;i++)
        cout<<(char)205;
    cout<<(char)187<<"\n";


    for (i=1;i<=L;i++) {
        cout<<(char)186;
        for (j=1;j<=C; j++) {
            if (a[i][j] == 0)
                cout<<" ";
            if (a[i][j] == 1)
                cout<<"o";
            if (a[i][j] == 2)
                cout<<"*";
            if (a[i][j] == 3)
                cout<<"H";

        }
        cout<<(char)186<<"\n";
    }
    cout<<(char)200;
    for (i=1;i<=C;i++)
        cout<<(char)205;
    cout<<(char)188<<"\n";
    cout<<'\n';

    cout<<"Score: "<<" "<<p;
    cout<<'\n';
    if (p > 50 && p<100)
        cout<<"You are : Good!";

    if(p>=100 &&p<200)
        cout<<"You are : Very Good!";
    if(p>= 200&&p<300)
        cout<<"You are : Excellent!";
    if (p >=300)
        cout<< "You are : Snake!";



}

void muta() {
    int i;
    for (i=N;i>=2;i--)
        s[i] = s[i-1];
    if (D == 1)
        s[1].L --;
    if (D == 3)
        s[1].L ++;
    if (D == 2)
        s[1].C ++;
    if (D == 4)
        s[1].C --;
}

void asteapta(int milisecunde) {
    int ti = clock();
    while ( clock()-ti < milisecunde ) ;
}

int lose() {
    if (s[1].L == 0 || s[1].L == L+1 || s[1].C == 0 || s[1].C == C+1)
        return 1;


    for (int i=2;i<=N;i++)
        if (s[1].L == s[i].L && s[1].C == s[i].C)
            return 1;
    savescore();
    return 0;

}

int main() {
    cout<<" *Apasa nr. corespunzator pt. a alege o optiune*\n";
    cout<<" Instructiuni:W-sus; S-jos; A-stanga; D-dreapta; X-save\n";
    cout<<"1. Joc nou\n";
    cout<<"2. Incarca joc\n";
    cout<<"3. Easy mode\n";
    cout<<"4. Extreme mode\n";
    loadscore();
    cout<<"5. Highscore : "<<M<<'\n';




    c = getch();
    init();



    if (c == '2')

        load();
    if(c == '3')

        speed=500;
    if(c== '4')


        speed=10;

    do {
        afisare();
        asteapta(speed);

        if ( kbhit() ) {
            c = getch();
            if (c == 'a')
                D = 4;
            if (c == 'w')
                D = 1;
            if (c == 'd')
                D = 2;
            if (c == 's')
                D = 3;
            if (c == 'x') {
                save();
            }
        }
        muta();

        // testez daca ajung pe hrana
        if (s[1].L == LH && s[1].C == CH) {
            N++;
            p+=10;
            savescore();
            if (N%3 == 0)
                speed -= 5;





            puneHrana();

        }




        if (lose())

            break;

    } while (1);

    afisare();
    if(p>M)
            cout<<"!!! New high score !!! ";

    return 0;
}
