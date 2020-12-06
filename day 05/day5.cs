using System;
using System.IO;

namespace AdventProject
{
  class AdventOfCode
  {
    static void Main(string[] args)
    {
      string inputFile = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.FullName + @"\in.txt";
      StreamReader cin = new StreamReader(inputFile);

      String inputLine;
      int Max = 0, Min = 1000;
      int[] SeatIDsFrequency = new int[1000];
      while (!cin.EndOfStream)
      {
        inputLine = cin.ReadLine();
        int front = 0, back = 127;
        int left = 0, right = 7;
        char lastFrontBack = ' ', lastLeftRight = ' ';

        foreach (char direction in inputLine)
        {
          if (direction == 'F')
          {
            back = (front + back) / 2;
            lastFrontBack = direction;
          }
          else if (direction == 'B')
          {
            front = ((front + back) / 2 + 1);
            lastFrontBack = direction;
          }
          if (direction == 'L')
          {
            right = (left + right) / 2;
            lastLeftRight = direction;
          }
          else if (direction == 'R')
          {
            left = ((left + right) / 2 + 1);
            lastLeftRight = direction;
          }
        }

        int seatID = 8; // the 8 columns
        seatID *= lastFrontBack == 'F' ? front : back; // row
        seatID += lastLeftRight == 'L' ? left : right; // column

        SeatIDsFrequency[seatID]++;

        Min = Math.Min(seatID, Min);
        Max = Math.Max(seatID, Max);
      }
      Console.WriteLine("Part 1: " + Max);
      for (int i = Min; i <= Max; i++)
      {
        if (SeatIDsFrequency[i] == 0)
        {
          Console.WriteLine("Part 2: " + i);
        }
      }

    }
  }
}
