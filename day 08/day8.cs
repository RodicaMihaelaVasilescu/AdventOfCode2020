using System;
using System.Collections.Generic;
using System.IO;

namespace AdventProject
{
  class AdventOfCode
  {

    static long run(List<KeyValuePair<string, int>> instructions)
    {
      List<bool> visited = new List<bool>();
      for (int i = 0; i < instructions.Count; i++)
      {
        visited.Add(false);
      }
      long acc = 0;
      for (int i = 0; i != instructions.Count; i++)
      {
        if (visited[i])
        {
          return acc;
        }
        visited[i] = true;

        string instr = instructions[i].Key;
        int val = instructions[i].Value;

        if (instr == "nop")
        {
          continue;
        }
        else if (instr == "acc")
        {
          acc += val;
        }
        else if (instr == "jmp")
        {
          i += val - 1;
        }
      }
      Console.WriteLine("Part 2: " + acc);
      return acc;
    }
	
    static void Main(string[] args)
    {
      string inputFile = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.FullName + @"\in.txt";
      StreamReader cin = new StreamReader(inputFile);

      string instr;
      int value;
      List<KeyValuePair<string, int>> instructions = new List<KeyValuePair<string, int>>();

      while (!cin.EndOfStream)
      {
        instr = cin.ReadLine();
        var index = instr.IndexOf(" ");
        value = int.Parse(instr.Substring(index, instr.Length - index));
        instr = instr.Substring(0, index);
        KeyValuePair<string, int> pair = new KeyValuePair<string, int>();
        instructions.Add(new KeyValuePair<string, int>(instr, value));
      }
	  
      Console.WriteLine("Part 1: " + run(instructions));

      var instrCopy = instructions;
      for (int i = 0; i < instructions.Count; i++)
      {
        if (instructions[i].Key == "jmp")
        {
          instrCopy[i] = new KeyValuePair<string, int>("nop", instructions[i].Value);
        }
        else if (instrCopy[i].Key == "nop")
        {
          instrCopy[i] = new KeyValuePair<string, int>("jmp", instructions[i].Value);
        }

        run(instrCopy);

        if (instructions[i].Key == "jmp")
        {
          instrCopy[i] = new KeyValuePair<string, int>("nop", instructions[i].Value);
        }
        else if (instrCopy[i].Key == "nop")
        {
          instrCopy[i] = new KeyValuePair<string, int>("jmp", instructions[i].Value);
        }
      }

    }
  }
}
