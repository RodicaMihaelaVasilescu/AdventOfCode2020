using System;
using System.Collections.Generic;
using System.IO;

namespace AdventProject
{
  class AdventOfCode
  {
    static void Main(string[] args)
    {
      HashSet<int> numbers = new HashSet<int>();

      string inputFile = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.FullName + @"\in.txt";
      StreamReader reader = new StreamReader(inputFile);

      while (!reader.EndOfStream)
      {
        int n;
        if (int.TryParse(reader.ReadLine(), out n) && n != 0)
        {
          if (numbers.Contains(2020 - n))
          {
            Console.WriteLine("Part 1: " + n * (2020 - n));
          }
          numbers.Add(n);
        }
      }

      foreach (var i in numbers)
      {
        foreach (var j in numbers)
        {
          if (numbers.Contains(2020 - i - j))
          {
            Console.WriteLine("Part 2: " + i * j * (2020 - i - j));
            return;
          }
        }
      }
    }
  }
}
