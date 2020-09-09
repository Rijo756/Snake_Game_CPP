#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
using namespace std;

struct snake  //Dynamic Structure to take the length of the Snake
{
    int x;
    int y;
    snake* next;
};

void ShowConsoleCursor(bool showFlag) // Function to set the visibility of cursor in the console
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void gotoxy(int x, int y)  // A Function to go to particular position in the screen.
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

int border()  // A Function to Display the borders of the game 4 < X < 74 and 1 < Y < 26
{
    gotoxy(4, 0);
    for (int j = 4; j < 74; j++)
    {
        cout << "_";
    }
    for (int j = 1; j < 26; j++)
    {
        gotoxy(3, j);
        cout << "|";
        gotoxy(74, j);
        cout << "|";
    }
    gotoxy(4, 26);
    for (int j = 4; j < 74; j++)
    {
        cout << "`";
    }
    return 0;
}

int Display_snake(snake front) // A Function to Display the current position of the snake
{
    while (1)
    {
        gotoxy(front.x, front.y);
        cout << "*";
        if (front.next == NULL)
            break;
        else
            front = *front.next;
    }
    return 0;
}

int Move(snake* front, int dir = 1) // Function used to move the snake in the direction of its heading
{
    int x = front->x;
    int y = front->y;
    switch(dir)
    { 
        case 1:
            x = x + 1;
            break;
        case 2:
            y = y + 1;
            break;
        case 3:
            x = x - 1;
            break;
        case 4:
            y = y - 1;
            break;
    }
    int temp = 0;
    snake *run = front;
    int x1, y1;
    int x_temp, y_temp;
    while (1)
    {
        if (temp == 0)
        {
            x_temp = run->x;
            y_temp = run->y;
            run->x = x;
            run->y = y;
            temp = 1;
        }
        else
        {
            x1 = run->x;
            y1 = run->y;
            run->x = x_temp;
            run->y = y_temp;
            x_temp = x1;
            y_temp = y1;
        }
        if (run->next == NULL)
        { 
            gotoxy(x_temp, y_temp);
            cout << " ";
            break;
        }
        else
            run = run->next;
    }
    return 0;
}

int Check_condition(snake* Front) // Function to check whether the Snake crossed the boundaries.
{
    if (Front->x == 3 || Front->x == 73 || Front->y == 0 || Front->y == 26)
        return 2;
    else
    {
        int x = Front->x;
        int y = Front->y;
        Front = Front->next;
        while (Front)
        {
            if (x == Front->x && y == Front->y)
                return 2;
            Front = Front->next;
        }
    }
    return 0;
        
}

snake* Insert(snake* front, int dir = 1) // Function to grow the snake after eating the food.
{
    snake* add; 
    add = new snake;
    int x = front->x;
    int y = front->y;
    switch (dir)
    {
    case 1:
        x = x + 1;
        break;
    case 2:
        y = y + 1;
        break;
    case 3:
        x = x - 1;
        break;
    case 4:
        y = y - 1;
        break;
    }
    add->x = x;
    add->y = y;
    add->next = front;
    front = add;
    return front;
}

void Destroy(snake* front) // FUnction to destroy the snake after the GAME OVER
{
    while(front)
    { 
    snake *temp = front;
    front = front->next;
    delete(temp);
    }
}


int Input(int dir)  // Function to get the user input to set the direction of snake
{
    if (_kbhit())
        switch (_getch()) 
           {
            case 72: //Up
                if (dir != 2)
                    dir = 4;
                break;
            case 80: // Down
                if (dir != 4)
                    dir = 2;
                break;
            case 77: //Right
                if (dir != 3)
                    dir = 1;
                break;
            case 75: // Left
                if (dir != 1)
                    dir = 3;
                break;
            }
    return dir;
}

void Food(int x, int y) //Function to display the Food at a particular location for snake
{
    gotoxy(x, y);
    cout << "$";
}

void points(int x) // Function to display the points
{
    gotoxy(85, 12);
    cout << "POINTS: " << x;
}

int start() // Main Function for the game to set initial conditions and to start the game
{
    if (border() == 0)
        TRUE;
    snake* rear;
    snake* front;
    rear = NULL;
    int speed = 50; // Control the speed of the snake (Smaller the faster)
    front = new snake;
    front->x = 10;
    front->y = 15;
    front->next = rear;
    front = Insert(front, 1);
    front = Insert(front, 1);
    front = Insert(front, 1);
    front = Insert(front, 1);
    int dir = 1;
    int pnts = 0;
    points(pnts);
    int random_x = 6 + rand() % 66;
    int random_y = 2 + rand() % 22;
    Food(random_x, random_y);
    while(1)
    {
        if (Display_snake(*front) == 0)
            TRUE;
        dir = Input(dir);
        Sleep(speed); 
        dir = Input(dir);
        if (Move(front, dir) == 0)
            TRUE;
        if (Check_condition(front) == 2)
            break;
        if (front->x == random_x && front->y == random_y)
        {
            front = Insert(front, dir);
            random_x = 6 + rand() % 66;
            random_y = 2 + rand() % 22;
            Food(random_x, random_y);
            pnts = pnts + 10;
            points(pnts);
        }

        
    }
    Destroy(front);
    for (int k = 10; k < 14; k++)
    {
        gotoxy(30, k);
        cout << "GAME OVER";
    }
    gotoxy(0, 26);
    return 0;
}


int main()
{
    ShowConsoleCursor(false);
    int a = start();
}