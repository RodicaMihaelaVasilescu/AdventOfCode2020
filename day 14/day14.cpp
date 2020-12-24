#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "MyLongLong.h"

using namespace std;

string decimalToReversedBinary(long long decimalValue)
{
  if (decimalValue == 0)
  {
    return "0";
  }
  string reversedBinaryValue;
  while (decimalValue > 0) {
    char lastDigit = (decimalValue % 2) + '0';
    reversedBinaryValue = reversedBinaryValue + lastDigit;
    decimalValue /= 2;
  }
  return reversedBinaryValue;
}

MyLongLong binaryToDecimal(MyLongLong binaryValue)
{
  MyLongLong decimalValue = 0;
  MyLongLong base = 1; // powers of 2, starting with 2^0

  while (binaryValue != 0) {
    MyLongLong lastDigit = binaryValue % 10;
    binaryValue = binaryValue / 10;
    decimalValue += lastDigit * base;
    base = base * 2;
  }
  return decimalValue;
}

string reversedString(string str)
{
  string rev;
  for (int j = str.size() - 1; j >= 0; j--)
  {
    char x = str[j];
    rev = rev + x;
  }
  return rev;
}
int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string  memoryAddress, delimiter;
  string value;
  string mask;
  map<int, string> addresses;
  while (cin >> memoryAddress >> delimiter >> value)
  {
    if (memoryAddress == "mask")
    {
      mask = value;
    }
    else
    {
      long long addressValue = stoll(memoryAddress.substr(4, memoryAddress.size() - 4 - 1));

      string reversedBinary = decimalToReversedBinary(stoll(value));
      string reversedMask = reversedString(mask);
      long index = 0;
      string result;

      while (index < reversedMask.size())
      {
        char bit = reversedMask[index];

        if (bit == '0')
        {
          result = result + "0";
        }
        else if (bit == '1')
        {
          result = result + "1";
        }
        else
        {
          if (index >= reversedBinary.size())
          {
            result = result + "0";
          }
          else
          {
            result = result + reversedBinary[index];
          }
        }
        index++;
      }
      addresses[addressValue] = reversedString(result);
    }
  }

  MyLongLong sum = 0;
  for (auto address : addresses)
  {
    sum += binaryToDecimal(address.second);
  }

  cout << sum << endl;

  return 0;
}