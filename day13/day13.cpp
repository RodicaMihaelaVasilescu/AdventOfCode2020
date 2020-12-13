#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include "MyLongLong.h"

using namespace std;

struct MyTuple
{
  MyLongLong X, Y, Z;
};

MyTuple euclid(MyLongLong  a, MyLongLong  b) {

  MyTuple t;
  if (a == 0)
  {
    return MyTuple{ b, 0, 1 };
  }
  else
  {
    t = euclid(b % a, a);
    swap(t.Y, t.Z);
    t.Y = t.Y - ((b / a)) * t.Z;

    return t;
  }

}

MyLongLong euclidModulo(MyLongLong a, MyLongLong b)
{
  MyTuple t = euclid(a, b);
  MyLongLong result = t.Y % b;
  if (result < 0)
  {
    result = max(t.Y, b) + result;
  }
  return result;
}


MyLongLong ChineseRemainderTheorem(vector<MyLongLong > busID, vector<MyLongLong > time)
{
  while (true) {

    MyLongLong a = euclidModulo(busID[1], busID[0]) * time[0] * busID[1] + euclidModulo(busID[0], busID[1]) * busID[0] * time[1];
    MyLongLong b = busID[0] * busID[1];

    time = vector<MyLongLong >(time.begin() + 2, time.end());

    time.insert(time.begin(), a % b);

    busID = vector<MyLongLong >(busID.begin() + 2, busID.end());
    busID.insert(busID.begin(), b);

    if (time.size() == 1)
    {
      break;
    }

  }
  return  time[0];
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  vector<MyLongLong > numbers = { 29, 41, 521, 23, 13, 17, 601, 37, 19 };
  vector<MyLongLong > time = { 29, 22, 492, -14, -29, -29, 541, -29, -60 };

  cout << "Part 2: " << ChineseRemainderTheorem(numbers, time);
  return 0;
}