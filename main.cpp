#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void setXY(short X, short Y){
    COORD coord = { X, Y };
    SetConsoleCursorPosition(stdOut, coord);
}
int tX,tY;
int mapsize = 25,lenght = 3,maxscore = 0;
int card[25][25];
short direction = 0;

char body = 219,apple = 178;
bool appleFlag = 0;

enum ConsoleColor
{
        Black         = 0,
        Blue          = 1,
        Green         = 2,
        Cyan          = 3,
        Red           = 4,
        Magenta       = 5,
        Brown         = 6,
        LightGray     = 7,
        DarkGray      = 8,
        LightBlue     = 9,
        LightGreen    = 10,
        LightCyan     = 11,
        LightRed      = 12,
        LightMagenta  = 13,
        Yellow        = 14,
        White         = 15
};

void setColor(ConsoleColor text,ConsoleColor background){
    SetConsoleTextAttribute(stdOut, (background << 4) | text);
}

bool update(){
    char key;
    if(_kbhit()){//проверка на нажатие
            key = _getch();//записываем что получили
            //setXY(0,0);
            system("cls");//чистим
            //cout << "Pressed: " << key << endl;
            //if(key == 'r'){
                //srand(time(NULL)*rand()*time(NULL));
              //  cout<<rand() % mapsize<<endl;
            //}
            if(key == 'H' && direction != 2){
                //cout<<"up";
                direction = 0;
            }
            if(key == 'M' && direction != 3){
                //cout<<"right";
                direction = 1;
            }
            if(key == 'P' && direction != 0){
                //cout<<"down";
                direction = 2;
            }
            if(key == 'K' && direction != 1){
                //cout<<"left";
                direction = 3;
            }
        }

        if (key == 27) { // 27 - ASCII-код клавиши "Esc"
                bool pause=1;
                key = 0;
                setColor(Blue,White);
                setXY(17,mapsize/2-1);
                cout<<" ______  ______   __  __   ______   ______    "<<endl;
                setXY(17,mapsize/2);
                cout<<"/\\  == \\/\\  __ \\ /\\ \\/\\ \\ /\\  ___\\ /\\  ___\\   "<<endl;
                setXY(17,mapsize/2+1);
                cout<<"\\ \\  _-/\\ \\  __ \\\\ \\ \\_\\ \\\\ \\___  \\\\ \\  __\\   "<<endl;
                setXY(17,mapsize/2+2);
                cout<<" \\ \\_\\   \\ \\_\\ \\_\\\\ \\_____\\\\/\\_____\\\\ \\_____\\ "<<endl;
                setXY(17,mapsize/2+3);
                cout<<"  \\/_/    \\/_/\\/_/ \\/_____/ \\/_____/ \\/_____/ "<<endl;
                setXY(15,mapsize/2+4);
                setColor(Black,White);
                cout<<"Press \"e\" or \"q\" to exit, press \"esc\" to continue,";
                setXY(25,mapsize/2+5);
                cout<<"Press \"r\" to restart";
                while(pause){
                    if(_kbhit()){//проверка на нажатие
                        key = _getch();//записываем что получили
                        if(key == 27){
                            pause = 0;
                        }else if(key == 'e' || key == 'q'){
                            exit(0);
                        }else if(key == 'к' || key == 'r'){
                            lenght = -1;
                            return 0;
                        }
                    }
                }
                system("cls");
                return 1;
                //return 0; // Выход из цикла при нажатии клавиши "Esc"
        }else{
            return 1;
        }
}

void draw(bool &life){
    setColor(LightMagenta, White);
    setXY(12,2);
    int nj,ni;
    setColor(Black,White);
    cout<<char(218);
    for(int i = 0; i < mapsize;i++){
        setColor(Black,White);
        cout<<char(196)<<char(196);
    }
    cout<<char(191)<<"\t Your score: "<<lenght - 3;
    setXY(73,3);
    cout<<"Best score: "<<maxscore;

    for(int i = 0; i < mapsize;i++){
        setXY(12,i+3);
        setColor(Black,White);
        cout<<char(179);
        for(int j = 0; j < mapsize;j++){
            if(card[j][i] == lenght){
                setColor(LightMagenta, White);
                setXY(13+j*2,i+3);
                cout<<body<<body;
                if(direction == 0){
                    //card[j][i-1]=lenght;
                    nj = j;
                    ni = i-1;
                }else if(direction == 2){
                    //card[j][i+1]=lenght;
                    nj = j;
                    ni = i+1;
                }else if(direction == 1){
                    //card[j+1][i]=lenght;
                    nj = j+1;
                    ni = i;
                }else{
                    //card[j-1][i]=lenght;
                    nj = j-1;
                    ni = i;
                }
                if(nj>=mapsize){
                    nj = 0;
                }else if(nj<0){
                    nj = mapsize-1;
                }
                if(ni>=mapsize){
                    ni = 0;
                }else if(ni<0){
                    ni = mapsize-1;
                }
                if(card[nj][ni] == -1){
                    //appleFlag =1;
                    lenght++;
                    srand(time(NULL)*rand()*time(NULL));
                    int aj = rand() %mapsize,ai =rand() %25;
                    while(card[aj][ai] != 0){
                        srand(time(NULL)*rand()*time(NULL));
                        aj = rand() %mapsize;
                        ai = rand() %mapsize;
                        //srand(time(NULL)*rand()*time(NULL));
                    }
                    for(int x = 0; x < mapsize;x++){
                        for(int y = 0; y < mapsize;y++){
                            if (card[x][y]>0){
                                card[x][y]++;
                            }
                        }
                    }
                    //card[tX][tY]=1;
                    tX=0;
                    tY = 0;
                    card[aj][ai] = -1;
                    card[nj][ni] = lenght;
                    //return;
                }else{
                    if(card[nj][ni] > 0 && appleFlag == 0){
                    life = 0;
                    //return;
                }
                    appleFlag = 0;
                }

                if(appleFlag == 0) card[j][i]--;
            }else if(card[j][i] > 0){
                setColor(LightGreen, White);
                setXY(13+j*2,i+3);
                cout<<body<<body;
                if(appleFlag == 0) card[j][i]--;
                if(card[j][i]==0){
                    tX=j;
                    tY=i;
                }
            }else if(card[j][i] == -1){
                setColor(Red, White);
                setXY(13+j*2,i+3);
                cout<<apple<<apple;
            }
        }

        setColor(Black,White);
        setXY(13+25*2,i+3);
        cout<<char(179);
    }
    setXY(12,3+mapsize);
    cout<<char(192);
    for(int i = 0; i < mapsize;i++){
        setColor(Black,White);
        cout<<char(196)<<char(196);
    }
    cout<<char(217);
    card[nj][ni] = lenght;
    setXY(13 + tX*2,tY+3);
    cout<<' '<<' ';
    if(card[tX+1][tY]==0 && tX+1 < mapsize){
        setXY(14 + tX*2,tY+3);
        cout<<' '<<' ';
    }
    if(card[tX-1][tY]==0 && tX-1 > mapsize){
        setXY(12 + tX*2,tY+3);
        cout<<' '<<' ';
    }
    if(card[tX][tY+1]==0 && tY+1 < mapsize){
        setXY(13 + tX*2,tY+4);
        cout<<' '<<' ';
    }
    if(card[tX][tY-1]==0 && tY-1 > mapsize){
        setXY(13 + tX*2,tY+2);
        cout<<' '<<' ';
    }
    setXY(0,0);
}

int main()
{
    ifstream in("data.txt");
    in>>maxscore;
    in.close();
    while(true){
        lenght = 3;
        for(int i = 0; i < mapsize;i++){
            for(int j = 0; j < mapsize;j++){
                card[j][i] = 0;
            }
        }
        card[12][12] = lenght;
        int aj = rand() %mapsize,ai =rand() %mapsize;
            while(card[aj][ai] != 0){
                aj = rand() %mapsize;
                ai = rand() %mapsize;
                srand(time(NULL)*rand()*time(NULL));
            }
            card[aj][ai] = -1;
        setColor(LightMagenta, White);
        setXY(0,0);
        system("cls");
        direction = 0;
        bool alive = 1;
        while(alive){
            short pdirection = direction;
            for(short i = 0;(i<5) && (alive) && (direction == pdirection);i++){
                alive = update();
                Sleep(1);
            }

            draw(alive);
            //for(int i = 0;i<500;i++){
                //alive = up    date();
            //alive = update();
            }
        if(lenght - 3 > maxscore){
            setColor(Red,White);
            maxscore = lenght-3;
            ofstream out("data.txt");
            out<<maxscore;
            out.close();
            setXY(0,mapsize/2-1);
            cout<<" __   __   ______   __     __       ______   ______   ______   ______   ______   _____    "<<endl;
            cout<<"/\\ \"-.\\ \\ /\\  ___\\ /\\ \\  _ \\ \\     /\\  == \\ /\\  ___\\ /\\  ___\\ /\\  __ \\ /\\  == \\ /\\  __-.  "<<endl;
            cout<<"\\ \\ \\-.  \\\\ \\  __\\ \\ \\ \\/ \".\\ \\    \\ \\  __< \\ \\  __\\ \\ \\ \\____\\ \\ \\/\\ \\\\ \\  __< \\ \\ \\/\\ \\ "<<endl;
            cout<<" \\ \\_\\\\\"\\_\\\\ \\_____\\\\ \\__/\".~\\_\\    \\ \\_\\ \\_\\\\ \\_____\\\\ \\_____\\\\ \\_____\\\\ \\_\\ \\_\\\\ \\____- "<<endl;
            cout<<"  \\/_/ \\/_/ \\/_____/ \\/_/   \\/_/     \\/_/ /_/ \\/_____/ \\/_____/ \\/_____/ \\/_/ /_/ \\/____/ "<<endl;
            //cout<<""<<endl;
            setColor(Black,White);
            system("pause");
        }else if(lenght == -1){
            setColor(Cyan,White);
            setXY(8,mapsize/2-1);
            cout<<" ______   ______   ______   ______  ______   ______  ______  "<<endl;
            setXY(8,mapsize/2);
            cout<<"/\\  == \\ /\\  ___\\ /\\  ___\\ /\\__  _\\/\\  __ \\ /\\  == \\/\\__  _\\ "<<endl;
            setXY(8,mapsize/2+1);
            cout<<"\\ \\  __< \\ \\  __\\ \\ \\___  \\\\/_/\\ \\/\\ \\  __ \\\\ \\  __<\\/_/\\ \\/ "<<endl;
            setXY(8,mapsize/2+2);
            cout<<" \\ \\_\\ \\_\\\\ \\_____\\\\/\\_____\\  \\ \\_\\ \\ \\_\\ \\_\\\\ \\_\\ \\_\\ \\ \\_\\ "<<endl;
            setXY(8,mapsize/2+3);
            cout<<"  \\/_/ /_/ \\/_____/ \\/_____/   \\/_/  \\/_/\\/_/ \\/_/ /_/  \\/_/ "<<endl;
            //cout<<"  \\/_____/ \\/_/\\/_/ \\/_/  \\/_/ \\/_____/     \\/_____/ \\/_/    \\/_____/ \\/_/ /_/ "<<endl;
            setXY(14,mapsize/2+4);
            setColor(Black,White);
            system("pause");
        }else{
            cout<<endl;
            setColor(Blue,White);
            setXY(0,mapsize/2-1);
            cout<<" ______   ______   __    __   ______       ______   __   __ ______   ______    "<<endl;
            cout<<"/\\  ___\\ /\\  __ \\ /\\ \"-./  \\ /\\  ___\\     /\\  __ \\ /\\ \\ / //\\  ___\\ /\\  == \\   "<<endl;
            cout<<"\\ \\ \\__. \\ \\  __ \\\\ \\ \\-./\\ \\\\ \\  __\\     \\ \\ \\/\\ \\\\ \\ \\'/ \\ \\  __\\ \\ \\  __<   "<<endl;
            cout<<" \\ \\_____\\\\ \\_\\ \\_\\\\ \\_\\ \\ \\_\\\\ \\_____\\    \\ \\_____\\\\ \\__|  \\ \\_____\\\\ \\_\\ \\_\\ "<<endl;
            cout<<"  \\/_____/ \\/_/\\/_/ \\/_/  \\/_/ \\/_____/     \\/_____/ \\/_/    \\/_____/ \\/_/ /_/ "<<endl;
            setColor(Black,White);
            system("pause");
            }
        }
}
