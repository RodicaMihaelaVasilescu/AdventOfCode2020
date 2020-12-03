using System;
using System.Collections.Generic;
using System.IO;

namespace AdventProject
{

  class AdventOfCode
  {

    static int getNumberOfTrees(List<string> map, int right, int left)
    {
      int line = 0, column = 0, numberOfTrees = 0;
      int n = map.Count, m = map[0].Length;

      while (line < n)
      {
        if (map[line][column % m] == '#')
        {
          numberOfTrees++;
        }

        column += right;
        line += left;
      }
      return numberOfTrees;
    }

    static void Main(string[] args)
    {
      string inputFile = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.FullName + @"\in.txt";
      StreamReader cin = new StreamReader(inputFile);


      List<string> input = new List<string>();
      string inputLine;

      while (!cin.EndOfStream)
      {
        inputLine = cin.ReadLine();
        input.Add(inputLine);
      }

      Console.WriteLine("Part 1: " + getNumberOfTrees(input, 3, 1));
      Console.WriteLine("Part 2: " + 1l * getNumberOfTrees(input, 1, 1) *
                                          getNumberOfTrees(input, 3, 1) *
                                          getNumberOfTrees(input, 5, 1) *
                                          getNumberOfTrees(input, 7, 1) *
                                          getNumberOfTrees(input, 1, 2));

    }
  }
}
