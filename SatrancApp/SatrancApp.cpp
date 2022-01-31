// Deneme.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class BaseChess
{
public:
     string ReadFromFile();
     vector<vector<string>> chessString;
     vector<vector<string>> fixTheReadedFile(string readval);
     virtual vector<vector<string>> checkKnightThread() = 0;
     virtual vector<vector<string>> checkPawnThread() = 0;
     virtual vector<vector<string>> checkQueenThread() = 0;
     virtual float getSum() = 0;
     virtual float calculateFinalResult() = 0;
     virtual void setSum(float inputVal) = 0;
     vector<string> pieces;
private:
    float sum = 0;
};

class whitePieces:public BaseChess
{
public:
    
    vector<vector<string>> checkKnightThread();
    vector<vector<string>> checkPawnThread();
    vector<vector<string>> checkQueenThread();
    float calculateFinalResult();
    float getSum() { return sum; };
    void setSum(float inputVal) { sum = inputVal; };
    vector<string> pieces = {"pb","ab","fb","kb","vb","sb"};
private:
    float sum = 0;
};
class blackPieces :public BaseChess
{
public:

    vector<vector<string>> checkKnightThread();
    vector<vector<string>> checkPawnThread();
    vector<vector<string>> checkQueenThread();
    float calculateFinalResult();
    float getSum() { return sum; };
    void setSum(float inputVal) { sum = inputVal; };
    vector<string> pieces = { "ps","as","fs","ks","vs","ss" };
private:
    float sum = 0;
};

//Reading function from .txt file
string BaseChess::ReadFromFile()
{
    ifstream myReadFile;
    myReadFile.open("board.txt");
    char output[100];
    string val;
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {


            myReadFile >> output;
            val += output;
        }
        myReadFile.close();
        return val;
    }
    else
    {
        cout << "File could not be found";
        delete output;
        return 0;
    }

}

//After reading the .txt file, string data need to store in a 2d vector. This func store the data in proper way.
vector<vector<string>> BaseChess::fixTheReadedFile(string readval)
{
    int counter = 0;
    string tempsquares[16][16];
    char* char_arr;
    char_arr = &readval[0];
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {

            tempsquares[i][j] = char_arr[counter];
            counter++;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        chessString.push_back(std::vector<string>());
        for (int j = 0; j < 8; j++)
        {
            chessString[i].push_back(tempsquares[i][j * 2] + tempsquares[i][j * 2 + 1]);
        }
    }
    return chessString;
}
//Check all the threat from white pawns
vector<vector<string>> whitePieces::checkPawnThread()
{
    for (int row = 0; row < chessString.size(); row++)
    {
        for (int col = 0; col < chessString[row].size(); col++)
        {
            if (chessString[row][col] == pieces.at(0))
            {
                
                if (row >= 1 && col <= 6 && row <= 6 && chessString[row - 1][col + 1].at(1) == 's')
                {
                    chessString[row - 1][col + 1] += "1";
                }
                if (col >= 1 && row >= 1 &&  chessString[row - 1][col - 1].at(1) == 's')
                {
                    chessString[row - 1][col - 1] += "1";
                }
            }

        }
    }
    return chessString;
}
//Check all the threat from white knights
vector<vector<string>> whitePieces::checkKnightThread()
{
    for (int row = 0; row < chessString.size(); row++)
    {
        for (int col = 0; col < chessString[row].size(); col++)
        {
            if (chessString[row][col] == pieces.at(1))
            {
                if (row >= 2 && col >= 1 && chessString[row - 2][col - 1].at(1) == 's')
                {
                    chessString[row - 2][col - 1] += "1";
                }

                if (row >= 2 && chessString[row - 2][col + 1].at(1) == 's')
                {
                    chessString[row - 2][col + 1] += "1";
                }

                if (col >= 2 && row <= 6 &&chessString[row + 1][col - 2].at(1) == 's')
                {
                    chessString[row + 1][col - 2] += "1";
                }

                if (row >= 1 && col >= 2 && chessString[row - 1][col - 2].at(1) == 's')
                {
                    chessString[row - 1][col - 2] += "1";
                }

                if (row >= 1 && col <= 5 && chessString[row - 1][col + 2].at(1) == 's')
                {
                    chessString[row - 1][col + 2] += "1";
                }

                if (col >= 1 && row <=5 && chessString[row + 2][col - 1].at(1) == 's')
                {
                    chessString[row + 2][col - 1] += "1";
                }

                if (row <= 5 && col <= 6 && chessString[row + 2][col + 1].at(1) == 's' )
                {
                    chessString[row + 2][col + 1] += "1";
                }

                if (row <= 6 && col <= 5 &&chessString[row + 1][col + 2].at(1) == 's' )
                {
                    chessString[row + 1][col + 2] += "1";
                }
            }

        }
    }
    return chessString;
}
//Check all the threat from white queen
vector<vector<string>> whitePieces::checkQueenThread()
{
    int counter = 1;
    char a;
    for (int row = 0; row < chessString.size(); row++)
    {
        for (int col = 0; col < chessString[row].size(); col++)
        {
            if (chessString[row][col] == pieces.at(4))
            {
                //checking for cross thread from queen
                while ((row + counter <= 7) && col + counter <= 7)
                {
                    if (chessString[row + counter][col + counter].at(1) == 's')
                    {
                        chessString[row + counter][col + counter] += "1";
                        break;
                    }
                    else if (chessString[row + counter][col + counter].at(1) == 'b')
                    {
                        break;
                    }
                    counter++;
                }

                //checking for cross thread from queen
                while ((row-counter) >= 0 && (col - counter) >= 0)
                {
                    if (chessString[row - counter][col - counter].at(1) == 's')
                    {
                        chessString[row - counter][col - counter] += "1";
                        break;
                    }
                    else if (chessString[row - counter][col + counter].at(1) == 'b')
                    {
                        break;
                    }
                    counter++;
                }
                counter = 1;
                //checking for cross thread from queen
                while (col + counter <= 7 && (row - counter) >= 0)
                {
                    if (chessString[row - counter][col + counter].at(1) == 's')
                    {
                        chessString[row - counter][col + counter] += "1";
                        break;
                    }
                    else if (chessString[row - counter][col + counter].at(1) == 'b')
                    {
                        break;
                    }
                    counter++;
                }
                counter = 1;
                //checking for cross thread from queen
                while ((row + counter <= 7) && col - counter >= 7)
                {
                    counter = 1;
                    if (chessString[row + counter][col - counter].at(1) == 's')
                    {
                        chessString[row + counter][col - counter] += "1";
                        break;
                    }
                    else if (chessString[row + counter][col - counter].at(1) == 'b')
                    {
                        break;
                    }
                    counter++;
                }
                counter = 1;
                //checking for straight line tread for queen
                while ((row + counter <= 7))
                {
                    if (chessString[row + counter][col].at(1) == 's')
                    {
                        chessString[row + counter][col] += "1";
                        break;
                    }
                    else if (chessString[row + counter][col].at(1) == 'b')
                    {
                        break;
                    }
                    counter++;
                }
                counter = 1;
                //checking for straight line tread for queen
                while ((row - counter) >= 0)
                {
                    if (chessString[row - counter][col].at(1) == 's')
                    {
                        chessString[row - counter][col] += "1";
                        break;
                    }
                    else if (chessString[row - counter][col].at(1) == 'b')
                    {
                        break;
                    }
                    counter++;
                }
                counter = 1;
                //checking for left-straight line tread for queen
                while ((col - counter) >= 0)
                {
                    if (chessString[row][col - counter].at(1) == 's')
                    {
                        chessString[row][col - counter] += "1";
                        break;
                    }
                    else if (chessString[row][col- counter].at(1) == 'b')
                    {
                        break;
                    }
                    counter++;
                }
                counter = 1;
                //checking for right-straight line tread for queen
                while ((col + counter) <= 7)
                {
                    if (chessString[row][col + counter].at(1) == 's')
                    {
                        chessString[row][col + counter] += "1";
                        break;
                    }
                    else if (chessString[row][col + counter].at(1) == 'b')
                    {
                        break;
                    }
                    counter++;
                }
            }

        }
    }
    return chessString;
}
//Calcute the final score, after black pawns, knights and queen threats
float whitePieces::calculateFinalResult()
{
    for (int row = 0; row < chessString.size(); row++)
    {
        for (int col = 0; col < chessString[row].size(); col++)
        {
            if (chessString[row][col].at(1) == 'b')
            {
                if (chessString[row][col].size() == 2 && chessString[row][col].at(0) == 'p')
                {
                    sum += 1;
                }
                if (chessString[row][col].size() == 3 && chessString[row][col].at(0) == 'p')
                {
                    sum += 0.5;
                }
                if (chessString[row][col].size() == 4 && chessString[row][col].at(0) == 'p')
                {
                    sum += 0.5;
                }
                if (chessString[row][col].size() == 2 && chessString[row][col].at(0) == 'a')
                {
                    sum += 3;
                }
                if (chessString[row][col].size() == 3 && chessString[row][col].at(0) == 'a')
                {
                    sum += 1.5;
                }
                if (chessString[row][col].size() == 4 && chessString[row][col].at(0) == 'a')
                {
                    sum += 1.5;
                } 
                if (chessString[row][col].size() == 5 && chessString[row][col].at(0) == 'a')
                {
                    sum += 1.5;
                }
                if (chessString[row][col].size() == 2 && chessString[row][col].at(0) == 'f')
                {
                    sum += 3;
                }
                if (chessString[row][col].size() == 3 && chessString[row][col].at(0) == 'f')
                {
                    sum += 1.5;
                }
                if (chessString[row][col].size() == 4 && chessString[row][col].at(0) == 'f')
                {
                    sum += 1.5;
                }
                if (chessString[row][col].size() == 2 && chessString[row][col].at(0) == 'k')
                {
                    sum += 5;
                }
                if (chessString[row][col].size() == 3 && chessString[row][col].at(0) == 'k' )
                {
                    sum += 2.5;
                }
                if (chessString[row][col].size() == 4 && chessString[row][col].at(0) == 'k' )
                {
                    sum += 2.5;
                }
                if (chessString[row][col].size() == 2 && chessString[row][col].at(0) == 'v')
                {
                    sum += 9;
                }
                if (chessString[row][col].size() == 3 && chessString[row][col].at(0) == 'v')
                {
                    sum += 4.5;
                }
                if (chessString[row][col].size() == 4 && chessString[row][col].at(0) == 'v')
                {
                    sum += 4.5;
                }
                if (chessString[row][col].size() == 2 && chessString[row][col].at(0) == 's')
                {
                    sum += 100;
                }
                if (chessString[row][col].size() == 3 && chessString[row][col].at(0) == 's')
                {
                    sum += 50;
                }
                if (chessString[row][col].size() == 4 && chessString[row][col].at(0) == 's')
                {
                    sum += 50;
                }

            }

        }
    }
    return sum;
}
//Check all the threat from black pawns
vector<vector<string>> blackPieces::checkPawnThread()
{
    for (int row = 0; row < chessString.size(); row++)
    {
        for (int col = 0; col < chessString[row].size(); col++)
        {
            if (chessString[row][col].at(0) == 'p' && chessString[row][col].at(1) == 's')
            {

                if (row >= 1 && col <= 6 && row <= 6 && chessString[row + 1][col + 1].at(1) == 'b')
                {
                    chessString[row + 1][col + 1] += "1";
                }
                if (col >= 1 && row >= 1 && chessString[row + 1][col - 1].at(1) == 'b')
                {
                    chessString[row + 1][col - 1] += "1";
                }
            }

        }
    }
    return chessString;
}
//Check all the threat from black knights
vector<vector<string>> blackPieces::checkKnightThread()
{
    for (int row = 0; row < chessString.size(); row++)
    {
        for (int col = 0; col < chessString[row].size(); col++)
        {
            if (chessString[row][col ].at(0) == 'a' && chessString[row][col].at(1) == 's')
            {
                if (row >= 2 && col >= 1 && chessString[row - 2][col - 1].at(1) == 'b')
                {
                    chessString[row - 2][col - 1] += "1";
                }

                if (row >= 2 && chessString[row - 2][col + 1].at(1) == 'b')
                {
                    chessString[row - 2][col + 1] += "1";
                }

                if (col >= 2 && chessString[row + 1][col - 2].at(1) == 'b')
                {
                    chessString[row + 1][col - 2] += "1";
                }

                if (row >= 1 && col >= 2 && chessString[row - 1][col - 2].at(1) == 'b')
                {
                    chessString[row - 1][col - 2] += "1";
                }

                if (row >= 1 && col <= 5 && chessString[row - 1][col + 2].at(1) == 'b')
                {
                    chessString[row - 1][col + 2] += "1";
                }

                if (col >= 1 && row <= 5 && chessString[row + 2][col - 1].at(1) == 'b')
                {
                    chessString[row + 2][col - 1] += "1";
                }

                if (row <= 5 && col <= 6 && chessString[row + 2][col + 1].at(1) == 'b')
                {
                    chessString[row + 2][col + 1] += "1";
                }

                if (row <= 6 && col <= 5 && chessString[row + 1][col + 2].at(1) == 'b')
                {
                    chessString[row + 1][col + 2] += "1";
                }
            }

        }
    }
    return chessString;
}
//Check all the threat from black queen
vector<vector<string>> blackPieces::checkQueenThread()
{
    int counter = 1;
    char a;
    for (int row = 0; row < chessString.size(); row++)
    {
        for (int col = 0; col < chessString[row].size(); col++)
        {
            if (chessString[row][col].at(0) == 'v' && chessString[row][col].at(1) == 's')
            {
                //checking for cross thread from queen
                while ((row + counter <= 7) && col + counter <= 7)
                {
                    if (chessString[row + counter][col + counter].at(1) == 'b')
                    {
                        chessString[row + counter][col + counter] += "1";
                        break;
                    }
                    else if (chessString[row + counter][col + counter].at(1) == 's')
                    {
                        break;
                    }
                    counter++;
                }

                //checking for cross thread from queen
                while ((row - counter) >= 0 && (col - counter) >= 0)
                {
                    if (chessString[row - counter][col - counter].at(1) == 'b')
                    {
                        chessString[row - counter][col - counter] += "1";
                        break;
                    }
                    else if (chessString[row - counter][col + counter].at(1) == 's')
                    {
                        break;
                    }
                    counter++;
                }
                counter = 1;
                //checking for cross thread from queen
                while (col + counter <= 7 && (row - counter) >= 0)
                {
                    if (chessString[row - counter][col + counter].at(1) == 'b')
                    {
                        chessString[row - counter][col + counter] += "1";
                        break;
                    }
                    else if (chessString[row - counter][col + counter].at(1) == 's')
                    {
                        break;
                    }
                    counter++;
                }
                counter = 1;
                //checking for cross thread from queen
                while ((row + counter <= 7) && col - counter >= 7)
                {
                    counter = 1;
                    if (chessString[row + counter][col - counter].at(1) == 'b')
                    {
                        chessString[row + counter][col - counter] += "1";
                        break;
                    }
                    else if (chessString[row + counter][col - counter].at(1) == 's')
                    {
                        break;
                    }
                    counter++;
                }
                counter = 1;
                //checking for straight line tread for queen
                while ((row + counter <= 7))
                {
                    if (chessString[row + counter][col].at(1) == 'b')
                    {
                        chessString[row + counter][col] += "1";
                        break;
                    }
                    else if (chessString[row + counter][col].at(1) == 's')
                    {
                        break;
                    }
                    counter++;
                }
                counter = 1;
                //checking for straight line tread for queen
                while ((row - counter) >= 0)
                {
                    if (chessString[row - counter][col].at(1) == 'b')
                    {
                        chessString[row - counter][col] += "1";
                        break;
                    }
                    else if (chessString[row - counter][col].at(1) == 's')
                    {
                        break;
                    }
                    counter++;
                }
                counter = 1;
                //checking for left-straight line tread for queen
                while ((col - counter) >= 0)
                {
                    if (chessString[row][col - counter].at(1) == 'b')
                    {
                        chessString[row][col - counter] += "1";
                        break;
                    }
                    else if (chessString[row][col - counter].at(1) == 's')
                    {
                        break;
                    }
                    counter++;
                }
                counter = 1;
                //checking for right-straight line tread for queen
                while ((col + counter) <= 7)
                {
                    if (chessString[row][col + counter].at(1) == 'b')
                    {
                        chessString[row][col + counter] += "1";
                        break;
                    }
                    else if (chessString[row][col + counter].at(1) == 's')
                    {
                        break;
                    }
                    counter++;
                }
            }

        }
    }
    return chessString;
}
//Calcute the final score, after white pawns,knights and queen threats
float blackPieces::calculateFinalResult()
{
    for (int row = 0; row < chessString.size(); row++)
    {
        for (int col = 0; col < chessString[row].size(); col++)
        {
            if (chessString[row][col].at(1) == 's')
            {
                if (chessString[row][col].size() == 2 && chessString[row][col].at(0) == 'p')
                {
                    sum += 1;
                }
                if (chessString[row][col].size() == 3 && chessString[row][col].at(0) == 'p')
                {
                    sum += 0.5;
                }
                if (chessString[row][col].size() == 4 && chessString[row][col].at(0) == 'p')
                {
                    sum += 0.5;
                }
                if (chessString[row][col].size() == 2 && chessString[row][col].at(0) == 'a')
                {
                    sum += 3;
                }
                if (chessString[row][col].size() == 3 && chessString[row][col].at(0) == 'a')
                {
                    sum += 1.5;
                }
                if (chessString[row][col].size() == 4 && chessString[row][col].at(0) == 'a')
                {
                    sum += 1.5;
                }
                if (chessString[row][col].size() == 2 && chessString[row][col].at(0) == 'f')
                {
                    sum += 3;
                }
                if (chessString[row][col].size() == 3 && chessString[row][col].at(0) == 'f')
                {
                    sum += 1.5;
                }
                if (chessString[row][col].size() == 4 && chessString[row][col].at(0) == 'f')
                {
                    sum += 1.5;
                }
                if (chessString[row][col].size() == 2 && chessString[row][col].at(0) == 'k')
                {
                    sum += 5;
                }
                if (chessString[row][col].size() == 3 && chessString[row][col].at(0) == 'k')
                {
                    sum += 2.5;
                }
                if (chessString[row][col].size() == 4 && chessString[row][col].at(0) == 'k')
                {
                    sum += 2.5;
                }
                if (chessString[row][col].size() == 2 && chessString[row][col].at(0) == 'v')
                {
                    sum += 9;
                }
                if (chessString[row][col].size() == 3 && chessString[row][col].at(0) == 'v')
                {
                    sum += 4.5;
                }
                if (chessString[row][col].size() == 4 && chessString[row][col].at(0) == 'v')
                {
                    sum += 4.5;
                }
                if (chessString[row][col].size() == 2 && chessString[row][col].at(0) == 's')
                {
                    sum += 100;
                }
                if (chessString[row][col].size() == 3 && chessString[row][col].at(0) == 's')
                {
                    sum += 50;
                }
                if (chessString[row][col].size() == 4 && chessString[row][col].at(0) == 's')
                {
                    sum += 50;
                }

            }

        }
    }
    return sum;
}

int main()
{
    BaseChess* bcwhite = new whitePieces();
    BaseChess* bcblack = new blackPieces();
    string readval;
    readval = bcwhite->ReadFromFile();
    
    bcwhite->chessString = bcwhite->fixTheReadedFile(readval);
    bcwhite->chessString = bcwhite->checkKnightThread();
    bcwhite->chessString = bcwhite->checkPawnThread();
    bcwhite->chessString = bcwhite->checkQueenThread();

    bcblack->chessString = bcwhite->chessString;
    bcblack->chessString = bcblack->checkKnightThread();
    bcblack->chessString = bcblack->checkPawnThread();
    bcblack->chessString = bcblack->checkQueenThread();

    bcwhite->chessString = bcblack->chessString;
    bcblack->setSum(bcblack->calculateFinalResult());
    bcwhite->setSum(bcwhite->calculateFinalResult());
    float x = bcblack->getSum();
    cout << "Siyah:" << bcblack->getSum() << endl;
    cout << "Beyaz:" << bcwhite->getSum() << endl;
}
