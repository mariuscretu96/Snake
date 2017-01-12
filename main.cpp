#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gOver;
const int width = 40;
const int height = 40;
int x,y,fruitX,fruitY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void Setup(){
    gOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width; fruitY = rand() % height;
    score = 0;
}

void Draw(){
    system("cls");
    for(int i=0; i <width + 2; i++)
        cout<< "#";
    cout<<endl;

    for(int i = 0;i<height;i++){
        for(int j=0; j<width;j++){
            if(j == 0)
                cout<< "#";
            if(i == y && j == x)
                cout<< "0";
            else if(i == fruitY && j == fruitX)
                cout<< "F";
            else
                cout<< " ";
            if(j == width - 1)
                cout<< "#";
        }
        cout<<endl;
    }

    for(int i=0; i <width + 2; i++)
        cout<< "#";
    cout<<endl;

    cout<<"Score: "<<score<<endl;
}

void Imput(){
    if(_kbhit()){
        switch(_getch()){
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gOver = true;
            break;
        }
    }
}

void Logic(){
    switch(dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if(x > width || x < 0 || y > height || y < 0)
        gOver = true;

    if(x == fruitX && y == fruitY){
        score += 10;
        fruitX = rand() % width; fruitY = rand() % height;
    }
}
int main()
{
    Setup();
    while(!gOver){
        Draw();
        Imput();
        Logic();
        Sleep(30); //sleep(10);
    }
    return 0;
}
