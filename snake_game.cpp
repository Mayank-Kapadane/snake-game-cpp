#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;

int tailX[100], tailY[100];
int ntail; // Length of the tail

int x, y, fruitX, fruitY, score; // x,y are head position of snake

enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;

void Setup();
void Draw();
void Input();
void Logic();

void Setup()
{
    gameOver = false;
    dir = STOP;

    // set the spawn position for in the middle of the map
    x = width / 2;
    y = height / 2;

    fruitX = rand() % width; // crate random number between 0 to n-1
    fruitY = rand() % height;

    score = 0;
}

void Draw()
{
    system("cls");

    for (int i = 0; i < width + 2; i++)
        cout << '#';
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";

            if (i == y && j == x) // Add a logic to this point // i = height, j = width
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";

            else
            {
                bool print = false;
                for (int k = 0; k < ntail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i) // j = x-cordiante, i = y-cordinate
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++)
        cout << '#';
    cout << endl;

    cout << "Score = " << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
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
            gameOver = true;
            break;

        default:
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < ntail; i++) // if ntail = 3 then loop run 2 times (i.e. i=1 and i=2)
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

    // termination of program
    if (x > width || x < 0 || y > height || y < 0) // If snake head hit the wall then the program will terminate
        gameOver = true;

    // For left<->right
    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        ntail++;
    }
}

int main()
{
    Setup();
    while (!gameOver) // Run untill not game over or we can say untill gameover != false
    {
        Draw();
        Input();
        Logic();
        Sleep(30);
    }

    return 0;
}