using System;
using System.IO;

namespace AdventProject
{
  class AdventOfCode
  {
    static void Main(string[] args)
    {
      int solutionPart1 = 0, solutionPart2 = 0;
      int lowest, highest;
      char passwordPolicy;
      String password, numbers;
      string inputFile = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.FullName + @"\in.txt";
      StreamReader cin = new StreamReader(inputFile);

      string inputLine;
      while (!cin.EndOfStream)
      {
        inputLine = cin.ReadLine();

        int index = inputLine.IndexOf('-');
        int index2 = inputLine.IndexOf(' ');

        lowest = int.Parse(inputLine.Substring(0, index));
        highest = int.Parse(inputLine.Substring(index + 1, index2 - index - 1));

        passwordPolicy = inputLine[index2 + 1];
        password = inputLine.Substring(index2 + 4, inputLine.Length - index2 - 4);

        int count = 0;
        foreach (char p in password)
        {
          if (p == passwordPolicy)
          {
            count++;
          }
        }

        if (count >= lowest && count <= highest)
        {
          solutionPart1++;
        }

        if (password[lowest - 1] == passwordPolicy && password[highest - 1] != passwordPolicy
            || password[lowest - 1] != passwordPolicy
                && password[highest - 1] == passwordPolicy)
        {
          solutionPart2++;
        }
      }

      Console.WriteLine("Part 1: " + solutionPart1);
      Console.WriteLine("Part 2: " + solutionPart2);

    }
  }
}
