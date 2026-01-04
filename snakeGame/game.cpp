#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

bool gameOver;
const int height = 20;
const int width = 20;
int x,y,fruitX,fruitY,score;
int tailX[100],tailY[100];
int nTail=0;
enum eDirection {STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;

void setup(){
    gameOver = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
void draw(){
    system("cls");//to clear a window
    for(int i=0;i<width;i++)
        cout<<"#";

    cout<<endl;

    for(int i=0;i<height;i++){

        for(int j=0;j<width;j++){
            if(j==0 || j==width-1)
                cout<<"#";
            else if(i==y && j==x)
                cout<<"O";
            else if(i==fruitY && j==fruitX)
                cout<<"F";
            else{
                bool print = false;
                for(int k=0;k<nTail;k++){
                    
                    if(tailX[k]==j && tailY[k]==i){
                        cout<<"o";
                        print = true;
                        break;
                    }
                    if(!print)
                        cout<<" ";
                }
                
            }
                
        }
        cout<<endl;
    }

    for(int i=0;i<width;i++)
        cout<<"#";

    cout<<endl;
    cout<<"your current score is: "<<score<<endl;
}
void input(){
    if(_kbhit()){
        switch (_getch())
        {
        case 'a':
            dir = LEFT;            
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'w':
            dir = UP;
            break;        
        case 'x':
            gameOver = true;
            break;
        default:
            break;
        }
    }
}
void logic(){
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i=1;i<nTail;i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
    }
    switch (dir)
    {
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
    
    case STOP:
        break;
    
    default:
        break;
    }

    // if(x>width || x<0 || y<0 || y>height)
    //     gameOver = true;
    if(x>=width) x = 0;else if(x<0) x=width-1;
    if(y>=height) y = 0; else if(y<0) y=height -1;

    for(int i=0;i<nTail;i++){
        if(tailX[i]==x && tailY[i]==y)
            gameOver = true;
    }


    if(x==fruitX && y==fruitY){
        fruitX = rand()%width;
        fruitY = rand()%height;
        score+=10;
        nTail++;
    }
}
int main(){
    setup();
    while(!gameOver){
        draw();
        input();
        logic();
        Sleep(100);
    }

    return 0;

}