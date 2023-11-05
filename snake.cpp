#include <iostream>
#include <conio.h>
#include <windows.h>

#pragma comment(lib, "Winmm.lib")

//#include<stdlib.h>
//#include<stdio.h>
//#include<dos.h>
#include<ctype.h>

using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    system("cls"); //system("clear"); for linux
    bool draw_jabri_name = false;

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            //Draw snake head
            if (i == y && j == x)
                cout << "\x99";
            //Draw Fruit
            else if (i == fruitY && j == fruitX)
                cout << "\xA2";
            else
            {
                bool print = false;

                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }

                }
                if (!print)
                {
                    cout << " ";
                }


            }
            if (j == width - 1)
            {
                cout << "#";
                
                    if (i == height / 2 && draw_jabri_name == false)
                    {
                        cout << "          Jabri Snake Game Test            ";
                        draw_jabri_name = true;
                    } 
            }
            /*
            if (i == height / 2 && draw_jabri_name == false)
            {
                cout << "Jabri Snake Game";
                draw_jabri_name = true;
            } */

        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;


}
void Input()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    // x and y coordinates dial snakehead
   // tailX[0] = x;
   // tailY[0] = y;
    

    // _kbhit hiya ki detecti button li brekti eliha
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'q':
            if (tailX[0] == tailX[1] + 1 && (tailY[0] == tailY[1]))
            {
                break;
            }
            else
            dir = LEFT;
            break;
        case 'd':
            if (tailX[0] == tailX[1] - 1 && (tailY[0] == tailY[1]))
            {
                break;
            }
            else
            dir = RIGHT;
            break;

        case 'z':
            if (tailY[0] == tailY[1] + 1 && (tailX[0] == tailX[1]))
            {
                break;
            }
            else
            dir = UP;
            break;

        case 's':
            if (tailY[0] == tailY[1] - 1 && (tailX[0] == tailX[1]))
            {
                break;

            }
            else
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }


}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    // x and y defines coordinates fpr snakehead
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
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
    default:
        break;

    }
  // this line for endgame if touching the wall |condition li mghtya dial ila to3ban 9ass l7it

 /*  if (x > width || x < 0 || y > height || y < 0)
    {
        gameOver = true;
    }
    */
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;


    //if the tail touched himself | ila to3ban 9ass zantit dialo
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {

            gameOver = true;
        }

    }

    // if the snake ate the fruit | ila kliti fruit
    if (x == fruitX && y == fruitY)
    {
        //sound(1500);

        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }



}


int main() {

    Setup();
    while (!gameOver)
    {
        //mciSendString(L"open \"*.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
        //PlaySound(L"applaud.wav", NULL, SND_SYNC);

        Draw();
        Input();
        Logic();
        //for refresh rate:
        Sleep(75);
        //end
    }


    return 0;
}
