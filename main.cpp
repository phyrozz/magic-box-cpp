#include <iostream>
#include <bits/stdc++.h>
#include <cmath>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <conio.h>

using namespace std;

void setColor(int color)
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resizeConsoleWindow(int s)
{
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;

    GetWindowRect(console, &ConsoleRect);
    
    if (s > 0 && s < 9)
    {
    	MoveWindow(console, 0, 0, 600, 600, TRUE);
	}
	else
	{
		MoveWindow(console, 0, 0, s * 46, s * 50, TRUE);
	}
}

void oddBox(int size)
{	
    resizeConsoleWindow(size);

    int n = 1, magicConst = 0;
    int square[size][size];
    memset(square, 0, sizeof(square));

    int posX = size/2;
    int posY = 0;

    while (n <= size * size)
    {
        if (posX == size && posY == -1)
        {
            posX = size - 1;
            posY = 1;
        }
        else
        {
            if (posX == size)
            {
                posX = 0;
            }
            else if (posY == -1)
            {
                posY = size - 1;
            }
        }
        if (square[posX][posY])
        {
            posX -= 1;
            posY += 2;
            continue;
        }
        else {
            square[posX][posY] = n++;
        }
        posX++;
        posY--;
    }
    
    system("cls");
    setColor(7);

    cout << "\nMagic Box with size = " << size << "x" << size << "\nMagic constant = ";
    for (int n = 0; n < size; n++)
    {
        magicConst += square[n][0];
    }
    cout << magicConst << "\n\n";

    for (posY = 0; posY < size; posY++)
    {
        for (posX = 0; posX < size; posX++)
        {
            cout << setw(5) << "----";
        }
        cout << endl;
        for (posX = 0; posX < size; posX++)
        {
            cout << "|" << setw(4) << square[posX][posY];
        }
        cout << "|" << endl;
    }
    for (posX = 0; posX < size; posX++)
    {
        cout << setw(5) << "----";
    }
}

void doublyEven(int size)
{
	resizeConsoleWindow(size);
    int square[size][size], i, j, magicConst;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            square[i][j] = (size*i) + j + 1;
        }
    }
    for (i = 0; i < size/4; i++)
    {
        for ( j = 0; j < size/4; j++)
        {
            square[i][j] = (size*size + 1) - square[i][j];
        } 
    }
    for (i = 0; i < size/4; i++)
    {
        for ( j = 3 * (size/4); j < size; j++)
        {
            square[i][j] = (size*size + 1) - square[i][j];
        }
    }
    for (i = 3 * size/4; i < size; i++)
    {
        for (j = 0; j < size/4; j++)
        {
            square[i][j] = (size*size+1) - square[i][j];
        }
    }
    for (i = 3 * size/4; i < size; i++)
    {
        for (j = 3 * size/4; j < size; j++)
        {
            square[i][j] = (size*size + 1) - square[i][j];
        }
    }
    for (i = size/4; i < 3 * size/4; i++)
    {
        for (j = size/4; j < 3 * size/4; j++)
        {
            square[i][j] = (size*size + 1) - square[i][j];
        }
    }

    system("cls");
    setColor(7);

    cout << "\nMagic Box with size = " << size << "x" << size << "\nMagic constant = ";
    for (int n = 0; n < size; n++)
    {
        magicConst += square[n][0];
    }
    cout << magicConst << "\n\n";

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            cout << setw(5) << "----";
        }
        cout << endl;
        for (j = 0; j < size; j++)
        {
            cout << "|" << setw(4) << square[i][j];
        }
        cout << "|" << endl;
    }
    for (j = 0; j < size; j++)
    {
        cout << setw(5) << "----";
    }
}

void singlyEven(int size)
{

}

void inputBoxSize(int &s)
{
	try
	{
        string line;
        cout << "\nPlease enter the size of the box to be generated (type \"help\" for more info):\n";
        while (getline(cin, line))
        {
        	if (line == "help")
            {
                cout << "WHAT IS A MAGIC BOX?\n" << 
                "A Magic Box, or a Magic Square, is a square array of numbers, consisting of" <<
                " distinct positive integers; and are arranged such that the sum of" <<
                " the numbers in any horizontal, vertical, or diagonal line is always the" <<
                " same number, which is called the Magic Constant.\n\n" <<
                "EXAMPLE:\nMagic Box with size = 3x3\n" <<
                " ---- ---- ---- \n" <<
                "|   8|   1|   6|\n" <<
                " ---- ---- ---- \n" <<
                "|   3|   5|   7|\n" <<
                " ---- ---- ---- \n" <<
                "|   4|   9|   2|\n" <<
                " ---- ---- ---- \n" <<
                "These arrangements of numbers aren't just random. They're placed so that when" <<
                " you add the numbers horizontally, vertically, or diagonally, the sum is ALWAYS" <<
                " the same. Try it!\n\n" <<
                "HOW DO I GENERATE A MAGIC BOX?\n" <<
                "It's simple. Just type a number once the program asks you to enter the size" <<
                " of the box to be generated.\nTake note that zero or negative numbers, as well" <<
                " as decimal numbers, are not allowed and will give you an error message instead.\n";
				cout << "\nPlease enter the size of the box to be generated:\n";
			}
            stringstream ss(line);
            if (ss >> s)
            {
                if (ss.eof())
                {
                    break;
                }
            }
        }
		if ((s % 2 == 0 && s % 4 != 0) || s < 1 || s > 47)
		{
			throw (s);
		}
	}
	catch (int n)
	{
		if (s > 47)
		{
            setColor(12);
			cout << "\nThat size looks too big for a magic square. ";
		}
		else
		{
            setColor(12);
			cout << "\nThe size of the box must be a positive odd integer. ";
		}
		cout << "Please try again.";
        setColor(7);
        cout << "\n\nNot sure what to input? Try entering \"";
		n = 2 * rand() % 30 + 8;
		cout << n+1 << "\"\n\n\n";
		inputBoxSize(s);
	}

	// try
	// {
	// 	cout << "\nPlease enter the size of the box to be generated:\n";
	// 	cin >> s;
	// 	cin.clear();
	// 	cin.ignore(10000, '\n');
	// 	if (s % 2 == 0 || s < 1 || s > 99)
	// 	{
	// 		throw (s);
	// 	}
	// }
	// catch (int n)
	// {
	// 	if (s > 99)
	// 	{
	// 		cout << "\nThat size looks too big for a magic square. ";
	// 	}
	// 	else
	// 	{
	// 		cout << "\nThe size of the box must be a positive odd integer. ";
	// 	}
	// 	cout << "Please try again.\n\nNot sure what to input? Try entering the number ";
	// 	n = 2 * rand() % 30 + 8;
	// 	cout << n+1 << "\n\n\n";
	// 	inputBoxSize(s);
	// }
}

void inputRegenerate(int size)
{
	string prompt;
    setColor(7);
	cout << "\n\nWould you like to generate another box? (Y/N)\n";
    cin >> prompt;
    
	if (prompt == "Y" || prompt == "y")
	{
		system("cls");
		inputBoxSize(size);
    	if (size % 2 == 1)
        {
            oddBox(size);
        }
        else
        {
            doublyEven(size);
        }
    	inputRegenerate(size);
	}
	else if (prompt == "N" || prompt == "n")
	{
		cout << "\nThank you for using this program!";
	}
	else
	{
        setColor(12);
		cout << "Invalid input. Please try again.\n\n";
		inputRegenerate(size);
	}
}

int main()
{
    int size;
    
    cout << "=========================== Magic Box Generator ===========================\n\n";
    cout << "Welcome! This program can generate a magic box. Even the even ones!\n";
    cout << "To learn more about the program and magic boxes, type \"help\".\n\n";
    inputBoxSize(size);
    if (size % 2 == 1)
    {
        oddBox(size);
    }
    else
    {
        doublyEven(size);
    }
    inputRegenerate(size);
    
    return 0;
}
