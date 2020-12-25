#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <numeric> 
#include <algorithm>

using namespace std;

int getLoopSize(int nr)
{
  unsigned long long y = 1;
  for (int i = 1; ; i++)
  {
    y *= 7;
    y %= 20201227;
    if (y == nr)
    {
      return  i;
    }
  }
}

int getEncryption(int card, int publicKey)
{
  long long encryption = 1;
  while (publicKey--)
  {
    encryption *= card;
    encryption %= 20201227;
  }
  return encryption;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int card1, card2;
  cin >> card1 >> card2;

  int publicKey1 = getLoopSize(card1);
  int publicKey2 = getLoopSize(card2);

  cout << card1 << " " << card2 << endl;
  cout << "encryption : " << getEncryption(card1, publicKey2) << endl;
  return 0;
}