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

      List<int> jolts = new List<int>();
      jolts.Add(0);

      int adapter, MaxAdapter = 0;
      while (!cin.EndOfStream)
      {
        adapter = int.Parse(cin.ReadLine());
        MaxAdapter = Math.Max(MaxAdapter, adapter);
        jolts.Add(adapter);
      }

      jolts.Add(MaxAdapter + 3);
      jolts.Sort();

      int oneJoltDiff = 0, threeJoltsDiff = 0;
      for (int i = 1; i < jolts.Count; i++)
      {
        if (jolts[i] - jolts[i - 1] == 1)
        {
          oneJoltDiff++;
        }
        else if (jolts[i] - jolts[i - 1] <= 3)
        {
          threeJoltsDiff++;
        }
      }

      Console.WriteLine("Part 1: " + oneJoltDiff * threeJoltsDiff);

      jolts.Add(jolts[jolts.Count - 1] + 3);

      //number of distinct ways you can arrange the adapters
      Dictionary<int, long> numberOfDistinctWays = new Dictionary<int, long>();
      numberOfDistinctWays[0] = 1;

      for (int i = 0; i < jolts.Count; i++)
      {
        for (int j = i + 1; j < jolts.Count && jolts[j] - jolts[i] <= 3; j++)
        {
          if (numberOfDistinctWays.ContainsKey(j))
          {
            numberOfDistinctWays[j] += numberOfDistinctWays[i];
          }
          else
          {
            numberOfDistinctWays.Add(j, numberOfDistinctWays.GetValueOrDefault(i, 0));
          }
        }
      }

      Console.WriteLine("Part 2: " + numberOfDistinctWays[jolts.Count - 1]);
    }
  }
}
