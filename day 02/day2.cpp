#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int solutionPart1 = 0, solutionPart2 = 0;

  int lowest, highest;

  string passwordPolicyWithDelimiter; // password policy ending with the ':' delimiter
  string password;

  char delimiter; // '-' delimiter between the lowest and highest number

  while (cin >> lowest >> delimiter >> highest >> passwordPolicyWithDelimiter >> password)
  {
    int passwordPolicy = passwordPolicyWithDelimiter[0]; // password policy without the ':' delimiter

    int count = std::count(password.begin(), password.end(), passwordPolicy);

    if (count >= lowest && count <= highest)
    {
      solutionPart1++;
    }

    if (password[lowest - 1] == passwordPolicy && password[highest - 1] != passwordPolicy || password[lowest - 1] != passwordPolicy && password[highest - 1] == passwordPolicy)
    {
      solutionPart2++;
    }
  }

  cout << "Part 1: " << solutionPart1 << endl;
  cout << "Part 2: " << solutionPart2 << endl;

  return 0;
}
