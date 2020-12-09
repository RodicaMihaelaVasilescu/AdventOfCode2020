using System;
using System.Collections.Generic;
using System.IO;

namespace AdventProject
{
  class AdventOfCode
  {
    static void Main(string[] args)
    {
      string inputFile = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.FullName + @"\in.txt";
      StreamReader cin = new StreamReader(inputFile);

      int preamble = 25;
      List<long> numbers = new List<long>();
      long n, solution = 0;
      int offset = 0;

      for (int i = 0; i < preamble; i++)
      {
        n = long.Parse(cin.ReadLine());
        numbers.Add(n);
      }

      offset = 0;
      while (!cin.EndOfStream)
      {
        string x = (cin.ReadLine());

        n = long.Parse(x);

        bool valid = false;
        for (int i = offset; i < numbers.Count; i++)
        {
          for (int j = i + 1; j < numbers.Count; j++)
          {
            if (numbers[i] + numbers[j] == n)
            {
              valid = true;
            }
          }
        }

        offset++;
        numbers.Add(n);

        if (!valid)
        {
          Console.WriteLine("Part 1: " + n);
          solution = n;
        }
      }

      for (int i = 0; i < numbers.Count; i++)
      {
        long sum = 0, Min = 9999999, Max = 0;
        for (int j = i; j < numbers.Count && sum < solution; j++)
        {
          Min = Math.Min(numbers[j], Min);
          Max = Math.Max(numbers[j], Max);
          sum += numbers[j];
          if (sum == solution && numbers[j] != solution)
          {
            Console.WriteLine("Part 2: " + (Min + Max));
          }
        }
      }
    }
  }
}
