#include<iostream>
#include<conio.h>

using namespace std;
bool gameOver;
const int height = 20;
const int width = 20;
int x,y,fruitX,fruitY,score;
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
            else
                cout<<" ";
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

    if(x>width || x<0 || y<0 || y>height)
        gameOver = true;


    if(x==fruitX && y==fruitY){
        fruitX = rand()%width;
        fruitY = rand()%height;
        score++;
    }
}
int main(){
    setup();
    while(!gameOver){
        draw();
        input();
        logic();
    }

}