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
  char passwordPolicy;
  string password;

  char delimiter;

  while (cin >> lowest >> delimiter >> highest >> passwordPolicy >> delimiter >> password)
  {
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
