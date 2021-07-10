#include <iostream>
#include <bits/stdc++.h>
#include <cmath>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include <sstream>

using namespace std;

// setColor function for error texts
void setColor(int color)
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Adaptive window size depending on the size of the box
// The maximum size of the box before the box's values starts wrapping to the next line
// will depend on the user's screen resolution (tested on 1920x1080 monitor)
void resizeConsoleWindow(int s)
{
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;

    GetWindowRect(console, &ConsoleRect);
    
    MoveWindow(console, 0, 0, s * 46, s * 50, TRUE);
    
    if (s > 0 && s < 15)
    {
    	MoveWindow(console, 0, 0, 800, 600, TRUE);
	}
	else
	{
		MoveWindow(console, 0, 0, s * 46, s * 50, TRUE);
	}
}

// Algorithm function for odd-sized box
int** oddBox(int size)
{	
    resizeConsoleWindow(size);

    int n = 1, magicConst = 0;
    int** square = new int*[size];
    for (int i = 0; i < size; i++)
    {
        square[i] = new int[size];
        for (int j = 0; j < size; j++)
        {
            square[i][j] = 0;
        }
    }

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

    return square;
}

// Algorithm function for doubly even-sized box
int** doublyEven(int size)
{
	resizeConsoleWindow(size);

    int** square = new int*[size];
    int i, j, magicConst;

    for (int i = 0; i < size; i++)
    {
        square[i] = new int[size];
    }

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

    return square;
}

// Algorithm function for singly even-sized box
int** singlyEven(int size)
{
    resizeConsoleWindow(size);

    int** square = new int*[size];
    int i, j, magicConst, swapNumbers[1][1];

    int** quadrantSquare = oddBox(size/2);
    
    for (i = 0; i < size; i++)
    {
        square[i] = new int[size];
    }

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            square[i][j] = 0;
        }
    }
    
    for (i = 0; i < size; i++)
    {
        if (i < size/2)
        {
            for (j = 0; j < size; j++)
            {
                if (j < size/2)
                {
                    square[i][j] = quadrantSquare[i][j];
                }
                else
                {
                    square[i][j] = quadrantSquare[i][j-size/2];
                    square[i][j] = square[i][j] + size/2 * size/2 * 3;
                }
            }
        }
        else
        {
            for (j = 0; j < size; j++)
            {
                if (j < size/2)
                {
                    square[i][j] = quadrantSquare[i-size/2][j];
                    square[i][j] = square[i][j] + size/2 * size/2 * 2;
                }
                else
                {
                    square[i][j] = quadrantSquare[i-size/2][j-size/2];
                    square[i][j] = square[i][j] + size/2 * size/2;
                }
            }
        }
    }

    for (i = 0; i < (size/2)/2; i++)
    {
        for (j = 0; j < size/2; j++)
        {
            if (j == (size/2)/2)
            {
                swapNumbers[0][0] = square[i+1][j];
                square[i+1][j] = square[i+1][size/2+j];
                square[i+1][size/2+j] = swapNumbers[0][0];
            }
            else
            {
                swapNumbers[0][0] = square[i][j];
                square[i][j] = square[i][size/2+j];
                square[i][size/2+j] = swapNumbers[0][0];
            }
        }
    }

    for (i = size - 1; size-i-1 < (size/2)/2-1; i--)
    {
        for (j = 0; j < size/2; j++)
        {
            swapNumbers[0][0] = square[i][j];
            square[i][j] = square[i][size/2+j];
            square[i][size/2+j] = swapNumbers[0][0];
        }
    }

    return square;
}

void printSquare(int size)
{
    int** square = 0;
    if (size % 2 == 1)
    {
        square = oddBox(size);

    }
    else
    {
        if (size % 4 != 0)
        {
            square = singlyEven(size);
        }
        else
        {
            square = doublyEven(size);
        }
    }
    
    int magicConst = 0, x = 0, y = 0;
    
    system("cls");
    // Clears the console window before printing the square
    setColor(7);
    
	// Appropriate output formatting for the square
    cout << "\nMagic Box with size = " << size << "x" << size << "\nMagic constant = ";
    for (int n = 0; n < size; n++)
    {
        magicConst += square[n][0];
    }
    cout << magicConst << "\n\n";

    for (y = 0; y < size; y++)
    {
        for (x = 0; x < size; x++)
        {
            cout << setw(5) << "----";
        }
        cout << endl;
        for (x = 0; x < size; x++)
        {
            cout << "|" << setw(4) << square[x][y];
        }
            cout << "|" << endl;
        }
    for (x = 0; x < size; x++)
    {
        cout << setw(5) << "----";
    }

	// Clean the memory allocated for the square array
    for (int a = 0; a < size; a++)
    {
        delete [] square[a];
    }
    delete [] square;
    square = 0;
}

void inputBoxSize(int &s)
{
	// Error handling
	try
	{
        string line;
        cout << "\nPlease enter the size of the box to be generated (type \"help\" for more info):\n";
        while (getline(cin, line))
        {
        	if (line == "help")
            {
                cout << "\nWHAT IS A MAGIC BOX?\n" << 
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
                " of the box to be generated.\nTake note that zero, two, or negative numbers, as well" <<
                " as decimal numbers, are not allowed and will give you an error message instead.\n";
				cout << "\nPlease enter the size of the box to be generated:\n";
			}
			
			// Calling stringstream in order to provide error handling when the user inputs strings and
			// characters.
            stringstream ss(line);
            if (ss >> s)
            {
                if (ss.eof())
                {
                    break;
                }
            }
        }
        // The program can only generate squares up to 100x100. Feel free to change the number below
        // If you desire to let the user generate bigger squares (unless you don't have a 8k monitor or
        // something)
        if (s < 1 || s > 100 || s == 2)
        {
            throw(s);
        }
	}
	catch (int n)
	{
        setColor(12);
		if (s > 100)
		{
			cout << "\nThat size looks too big for a magic box. ";
		}
        else if (s == 2)
        {
            cout << "\nInvalid input. You can't make a 2x2 magic box. ";
        }
		else
		{
			cout << "\nThe size of the box must be a positive integer (except 2). ";
		}
		cout << "Please try again.";
        setColor(7);
        cout << "\n\nNot sure what to input? Try entering \"";
		n = 2 * rand() % 30 + 8;
		cout << n+1 << "\"\n\n\n";
		inputBoxSize(s);
	}
}

// Prompt the user if they would want to generate a new box
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
        printSquare(size);
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
    
    cout << "=========================== Magic Box Generator ===========================\n\n" <<
    "Welcome! This program can generate a magic box. Even the even ones!\n" <<
    "If you are generating larger boxes. I would recommend enabling \"Wrap Text on Resize\"\n" <<
    "on the Console Properties.\n\n" <<
    "To learn more about the program and magic boxes, type \"help\".\n\n";
    inputBoxSize(size);
    printSquare(size);
    inputRegenerate(size);
    
    return 0;
}
