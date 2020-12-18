#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

long long computeSumPart1(vector<char> expression)
{

  long long currentExpressionValue = 0;
  bool isFirstOperator = true;
  char lastChar = 0;

  for (int i = 0; i != expression.size(); i++)
  {
    if (isdigit(expression[i]))
    {
      if (isFirstOperator)
      {
        currentExpressionValue = expression[i] - '0';
        isFirstOperator = false;
      }
      else if (lastChar == '+')
      {
        currentExpressionValue += expression[i] - '0';
      }
      else  if (lastChar == '*')
      {
        currentExpressionValue *= expression[i] - '0';
      }

    }
    else  if (expression[i] == '+' || expression[i] == '*')
    {
      lastChar = expression[i];
    }
    else if (expression[i] == '(')
    {
      int openBrackets = 1;
      int indexClosedBracket = i;
      while (openBrackets != 0)
      {
        indexClosedBracket++;
        if (expression[indexClosedBracket] == '(')
        {
          openBrackets++;
        }
        else if (expression[indexClosedBracket] == ')')
        {
          openBrackets--;
        }
      }
      vector<char> brackets = vector<char>(expression.begin() + i + 1, expression.begin() + indexClosedBracket);
      if (isFirstOperator)
      {
        currentExpressionValue = computeSumPart1(brackets);
        isFirstOperator = false;
      }
      if (lastChar == '+')
      {
        currentExpressionValue += computeSumPart1(brackets);
      }
      else  if (lastChar == '*')
      {
        currentExpressionValue *= computeSumPart1(brackets);
      }
      i = indexClosedBracket;
    }
    else if (expression[i] == ')')
    {
      return currentExpressionValue;
    }
  }
  return currentExpressionValue;
}


long long computeSumPart2(vector<char> v)
{

  long long currentExpressionValue = 0;
  bool isFirstOperator = true;
  char lastChar = 0;
  stack<int> myStack;
  for (int i = 0; i != v.size(); i++)
  {
    if (isdigit(v[i]))
    {
      if (isFirstOperator)
      {
        myStack.push(v[i] - '0');
        isFirstOperator = false;
      }
      else if (lastChar == '+')
      {

        currentExpressionValue = myStack.top() + (v[i] - '0');
        myStack.pop();
        myStack.push(currentExpressionValue);
      }
      else  if (lastChar == '*')
      {
        myStack.push(v[i] - '0');
      }

    }
    else  if (v[i] == '+' || v[i] == '*')
    {
      lastChar = v[i];
    }
    else if (v[i] == '(')
    {
      int openBrackets = 1;
      int indexClosedBracket = i;
      while (openBrackets != 0)
      {
        indexClosedBracket++;
        if (v[indexClosedBracket] == '(')
        {
          openBrackets++;
        }
        else if (v[indexClosedBracket] == ')')
        {
          openBrackets--;
        }
      }
      vector<char> brackets = vector<char>(v.begin() + i + 1, v.begin() + indexClosedBracket);

      if (isFirstOperator)
      {
        myStack.push(computeSumPart2(brackets));
        isFirstOperator = false;
      }
      if (lastChar == '+')
      {
        currentExpressionValue = myStack.top() + computeSumPart2(brackets);
        myStack.pop();
        myStack.push(currentExpressionValue);
      }
      else  if (lastChar == '*')
      {
        myStack.push(computeSumPart2(brackets));
      }
      i = indexClosedBracket;
    }
    else if (v[i] == ')')
    {
      long long multiplication = 1;
      while (!myStack.empty())
      {
        multiplication *= myStack.top();
        myStack.pop();

      }
      return multiplication;
    }
  }

  long long multiplication = 1;
  while (!myStack.empty())
  {
    multiplication *= myStack.top();
    myStack.pop();

  }
  return multiplication;

}

int main()
{

  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string inputLine;
  long long sum1 = 0, sum2 = 0;
  while (getline(cin, inputLine))
  {
    vector<char> expression;
    for (auto ch : inputLine)
    {
      if (ch != ' ')
      {
        expression.push_back(ch);
      }
    }
    sum1 += computeSumPart1(expression);
    sum2 += computeSumPart2(expression);
  }
  cout << "Part 1: " << sum1 << endl;
  cout << "Part 2: " << sum2 << endl;
  return 0;
}

