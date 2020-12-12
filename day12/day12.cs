using System;
using System.Collections.Generic;
using System.IO;

namespace AdventProject
{
  class Point
  {
    public Point(int x, int y)
    {
      this.x = x;
      this.y = y;
    }

    public int x;
    public int y;
  };
  class AdventOfCode
  {
    static void Main(string[] args)
    {
      string inputFile = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.FullName + @"\in.txt";
      StreamReader cin = new StreamReader(inputFile);

      //            0  1  2  3
      //            E  S  W  N  
      int[] lin = { 0, 1, 0, -1 };
      int[] col = { 1, 0, -1, 0 };
      /*
        		   (-)
          			N
          			^
          			|
		   (-) W <---+---> E (+)
          			|
          			v
          			S
         		   (+)
		*/

      Dictionary<char, int> CharToInt = new Dictionary<char, int> { { 'E', 0 }, { 'S', 1 }, { 'W', 2 }, { 'N', 3 } };

      //The ship starts by facing east
      int direction = CharToInt['E'];
      Point point1 = new Point(0, 0);
      Point point2 = new Point(0, 0);

      // the waypoint starts 1 unit north (-) and 10 units east (+)
      Point waypoint = new Point(-1, 10);

      char s;
      int n;
      while (!cin.EndOfStream)
      {
        string line = cin.ReadLine();
        s = line[0];
        n = int.Parse(line.Substring(1, line.Length - 1));
        if (s == 'F')
        {
          //---------------- 1st part -------------------
          point1.x += n * lin[direction];
          point1.y += n * col[direction];
          //---------------- 2nd part -------------------
          point2.x += n * waypoint.x;
          point2.y += n * waypoint.y;
        }
        else if (s == 'E' || s == 'S' || s == 'W' || s == 'N')
        {
          //---------------- 1st part -------------------
          point1.x += n * lin[CharToInt[s]];
          point1.y += n * col[CharToInt[s]];
          //---------------- 2nd part -------------------
          waypoint.x += n * lin[CharToInt[s]];
          waypoint.y += n * col[CharToInt[s]];
        }
        // right rotation
        else if (s == 'R' && n == 90 || s == 'L' && n == 270)
        {
          //---------------- 1st part -------------------
          ++direction;
          direction %= 4;
          //---------------- 2nd part -------------------
          waypoint.x *= -1;
          waypoint = new Point(waypoint.y, waypoint.x);
        }
        // left rotation
        else if (s == 'L' && n == 90 || s == 'R' && n == 270)
        {
          //---------------- 1st part -------------------
          if (--direction < 0)
          {
            direction = 3;
          }
          //---------------- 2nd part -------------------
          waypoint.y *= -1;
          waypoint = new Point(waypoint.y, waypoint.x);
        }
        // 180 rotation
        else if (s == 'R' && n == 180 || s == 'L' && n == 180)
        {
          //---------------- 1st part -------------------
          direction += 2;
          direction %= 4;
          //---------------- 2nd part -------------------
          waypoint.x *= -1;
          waypoint.y *= -1;
        }
      }
      Console.WriteLine("Part 1: " + (Math.Abs(point1.x) + Math.Abs(point1.y)));
      Console.WriteLine("Part 2: " + (Math.Abs(point2.x) + Math.Abs(point2.y)));
    }
  }
}
