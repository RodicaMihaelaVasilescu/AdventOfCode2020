// Warning: this solution takes about 15-20 sec to run...

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;

int lin[] = { -1, -1, -1,  0, 0,  1, 1, 1 };
int col[] = { -1,  0,  1, -1, 1, -1, 0, 1 };

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int solutionPart1 = 0, solutionPart2 = 0;
  vector <string> input;
  string s;

  while (cin >> s)
  {
    s = "0" + s + "0";
    input.push_back(s);
  }
  string padding;
  for (char x : input[0])
  {
    padding += "0";
  }
  input.insert(input.begin(), padding);
  input.push_back(padding);

  auto seats = input;
  auto previousSeats = seats;
  bool hasChanged = true;

  // while seats' configuration hasn't changed
  while (hasChanged)
  {
    seats = previousSeats;
    solutionPart1 = 0;
    hasChanged = false;

    for (int i = 1; i < seats.size() - 1; i++)
    {
      for (int j = 1; j < seats[1].size() - 1; j++)
      {
        char previousValue = seats[i][j];
        map<char, int> neighborsFrequecy;
        for (int dir = 0; dir < 8; dir++)
        {
          int line = i + lin[dir];
          int column = j + col[dir];
          char seat = seats[line][column];
          neighborsFrequecy[seat]++;
        }

        // If a seat is empty (L) and there are no occupied seats adjacent to it, the seat becomes occupied.
        if (seats[i][j] == 'L' && neighborsFrequecy['#'] == 0)
        {
          previousSeats[i][j] = '#';
        }
        //If a seat is occupied (#) and four or more seats adjacent to it are also occupied, the seat becomes empty.
        else if (previousSeats[i][j] == '#' && neighborsFrequecy['#'] >= 4)
        {
          previousSeats[i][j] = 'L';
        }
        // count occupied seats
        if (seats[i][j] == '#')
        {
          solutionPart1++;
        }
        // check if seats configuration has changed
        if (previousValue != previousSeats[i][j])
        {
          hasChanged = true;
        }
      }
    }
  }
  cout << "Part 1: " << solutionPart1 << endl;

  seats = input;
  previousSeats.clear();
  hasChanged = true;

  // while seats' configuration hasn't changed
  while (hasChanged)
  {
    hasChanged = false;
    previousSeats = seats;
    solutionPart2 = 0;

    for (int i = 1; i < seats.size() - 1; i++) {
      for (int j = 1; j < seats[1].size() - 1; j++)
      {
        map<char, int> neighborsFrequecy;
        for (int dir = 0; dir < 8; dir++)
        {
          int line = i + lin[dir];
          int column = j + col[dir];
          while (previousSeats[line][column] != '0')
          {
            if (previousSeats[line][column] != '.')
            {
              break;
            }
            line += lin[dir];
            column += col[dir];
          }
          neighborsFrequecy[previousSeats[line][column]]++;
        }
        //If a seat is empty (L) and there are no occupied seats adjacent to it, the seat becomes occupied.
        if (previousSeats[i][j] == 'L' && neighborsFrequecy['#'] == 0)
        {
          seats[i][j] = '#';
        }
        //If a seat is occupied (#) and four or more seats adjacent to it are also occupied, the seat becomes empty.
        else if (previousSeats[i][j] == '#' && neighborsFrequecy['#'] >= 5)
        {
          seats[i][j] = 'L';
        }
        // count occupied seats
        if (seats[i][j] == '#')
        {
          solutionPart2++;
        }
        // check if seats configuration has changed
        if (seats[i][j] != previousSeats[i][j])
        {
          hasChanged = true;
        }

      }
    }
  }

  cout << "Part 2: " << solutionPart2 << endl;
}