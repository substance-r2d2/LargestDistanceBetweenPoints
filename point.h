#pragma once

#include <iostream>

using namespace std;

class point
{
private:
  int x, y;
public:
  point(int x1, int y1)
  {
	x = x1;
	y = y1;
  }

  float distance(point p1)
  {
	return  ((p1.x - x)*(p1.x - x)) + ((p1.y - y)*(p1.y - y));
  }
  void print()
  {
	cout << x << "," << y << endl;
  }
  point operator=(point& p)
  {
	x = p.x;
	y = p.y;
	return *this;
  }
  int getX()
  {
	return x;
  }
  int getY()
  {
	return y;
  }
};
