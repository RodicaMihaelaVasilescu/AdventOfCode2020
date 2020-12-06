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

      string inputLine;
      HashSet<int> allQuestions = new HashSet<int>();
      Dictionary<char, int> questionsFrequencyPerGroup = new Dictionary<char, int>();
      int numberOfAllQuestions = 0;
      int numberOfAllQuestionsPerGroup = 0;
      int numberOfAllAnsweredQuestions = 0;

      while (!cin.EndOfStream)
      {
        inputLine = cin.ReadLine();
        if (inputLine != "")
        {
          foreach (char ch in inputLine)
          {
            allQuestions.Add(ch);
            if (!questionsFrequencyPerGroup.ContainsKey(ch))
            {
              questionsFrequencyPerGroup.Add(ch, 0);
            }
            questionsFrequencyPerGroup[ch]++;
          }
          numberOfAllQuestionsPerGroup++;
        }
        else
        {
          // questions to which anyone answered "yes";
          numberOfAllQuestions += allQuestions.Count;

          foreach (var questionFrequency in questionsFrequencyPerGroup)
          {
            if (questionFrequency.Value == numberOfAllQuestionsPerGroup)
            {
              // questions to which everyone answered "yes"!
              numberOfAllAnsweredQuestions++;
            }
          }

          numberOfAllQuestionsPerGroup = 0;
          questionsFrequencyPerGroup.Clear();
          allQuestions.Clear();
        }
      }

      // questions to which anyone answered "yes";
      numberOfAllQuestions += allQuestions.Count;

      foreach (var questionFrequency in questionsFrequencyPerGroup)
      {
        if (questionFrequency.Value == numberOfAllQuestionsPerGroup)
        {
          // questions to which everyone answered "yes"!
          numberOfAllAnsweredQuestions++;
        }
      }

      Console.WriteLine("Part 1: " + numberOfAllQuestions);
      Console.WriteLine("Part 2: " + numberOfAllAnsweredQuestions);

    }
  }
}
