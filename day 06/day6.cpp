#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <set>
#include <string>
#include <map>

using namespace std;


int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string s;
  set<char> allQuestions; 
  map<char, int> questionsFrequencyPerGroup; 
  int numberOfAllQuestions = 0;
  int numberOfAllQuestionsPerGroup = 0;
  int numberOfAllAnsweredQuestions = 0;
  
  while (getline(cin, s))
  {
    if (s != "")
    {
      for (char c : s)
      {
        allQuestions.insert(c);
        questionsFrequencyPerGroup[c]++;
      }
      numberOfAllQuestionsPerGroup++;
    }
    else
    {
      // questions to which anyone answered "yes";
      numberOfAllQuestions += allQuestions.size();

      for (auto questionFrequency : questionsFrequencyPerGroup)
      {
        if (questionFrequency.second == numberOfAllQuestionsPerGroup)
        {
          // questions to which everyone answered "yes"!
          numberOfAllAnsweredQuestions++;
        }
      }

      numberOfAllQuestionsPerGroup = 0;
      questionsFrequencyPerGroup.clear();
      allQuestions.clear();
    }
  }

  // questions to which anyone answered "yes";
  numberOfAllQuestions += allQuestions.size();

  for (auto questionFrequency : questionsFrequencyPerGroup)
  {
    if (questionFrequency.second == numberOfAllQuestionsPerGroup)
    {
      // questions to which everyone answered "yes"!
      numberOfAllAnsweredQuestions++;
    }
  }

  cout << "Part 1: " << numberOfAllQuestions << endl;
  cout << "Part 2: " << numberOfAllAnsweredQuestions << endl;

  return 0;
}
