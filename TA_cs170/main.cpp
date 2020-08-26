/******************************************************************************/
/*!
\file main.cpp
\author Benjamin Tan
\par email: t.junrongbenjamin\@digipen.edu
\par DigiPen login: t.junrongbenjamin
\par Course: CS170C
\par Lab 09
\date 29/03/2019
\brief
This is a file containing different classes with various inheritance.
*/
/******************************************************************************/

#include <iostream>
using namespace std;

// CS170 Lab 9
// You have to implement following classes to match the output
class Point
{
  public:
  Point(int x=0, int y=0): x(x), y(y){}
  ~Point(){}
  
  private:
  int x;
  int y;
  
  // Overload for operator << for Point
  friend ostream &operator<<(ostream&out, const Point &pointin)
  {
    out << "(" << pointin.x << ", " << pointin.y << ")";
    return out;
  }
};

class Shape 
{
  public:
  Shape(Point a = Point()): first(a) //Constructor for 1 point
  {}
  ~Shape(){}
  
  protected:
  Point first;
};

class Polygon : public Shape 
{
  public:
  // Constructor for 2 points
  Polygon(Point a = Point(), Point b = Point()): Shape(a), second(b){};
  ~Polygon(){};
  
  protected:
  Point second;
};

class Line : public Polygon 
{
  public:
  // Constructor for 2 points
  Line(Point a = Point(), Point b = Point()): Polygon(a, b)
  {
    cout << "Line construction" << endl;
  }
  ~Line()
  {
    cout << "Line destruction" << endl;
  }
  void Draw() // Draw function
  {
    cout << "Line drawing" << endl;
  }
  
  // Overload for operator << for Line
  friend ostream &operator<<(ostream&out, const Line &pointin)
  {
    out << "Line " << pointin.first << " " << pointin.second << endl;
    return out;
  }
  
};

class Triangle : public Polygon 
{
  public:
  // Constructor for 3 points 
  Triangle(Point a = Point(), Point b = Point(), Point c = Point()):
  Polygon(a, b), third(c)
  {
    cout << "Triangle construction" << endl;
  };
  ~Triangle()
  {
    cout << "Triangle destruction" << endl;
  }
  
  // Overload for operator << for Triangle
  friend ostream &operator<<(ostream&out, const Triangle &pointin)
  {
    out << "Triangle " << pointin.first << " " << pointin.second << " " <<
    pointin.third << endl;
    return out;
  }
  
  protected:
  Point third;
};

class Circle : public Shape 
{
  public:
  // Constructor for Circle (1 point and radius)
  Circle(Point a = Point (), int r=0): Shape(a), radius(r)
  {
    cout << "Circle construction" << endl;
  };
  ~Circle()
  {
    cout <<  "Circle destruction" << endl;
  };
  
  // Overload for operator << for Circle
  friend ostream &operator<<(ostream&out, const Circle &pointin)
  {
    out << "Circle " << pointin.first << " " << pointin.radius << endl;
    return out;
  }
  
  protected:
  int radius;
};

int main() 
{
  Line l1;  //Output: Line construction
  std::cout << l1;  //Output: Line (0,0) (0,0)
  l1.Draw();  //Output: Line drawing

  Line l2(Point(), 
  Point(100,100));  //Output: Line construction
  std::cout << l2;  //Output: Line (0,0) (100,100)
  l1 = l2;
  std::cout << l1;  //Output: Line (0,0) (100,100)

  Triangle t1;  //Output: Triangle construction
  std::cout << t1;  //Output: Triangle (0,0) (0,0) (0,0)

  Triangle t2(Point(-100,100), 
  Point(100,100),
  Point(100,-100));//Output: Triangle construction
  t1 = t2;
  std::cout << t1;  //Output: Triangle (-100,100) (100,100) (100,-100)

  Circle c1;  //Output: Circle construction
  Circle c2(Point(), 10); //Output: Circle construction
  c1 = c2;
  std::cout << c1; //Output: Circle (0,0) 10

  return 0;
} //Output (in any order): 
  // Circle destruction
  // Circle destruction
  // Triangle destruction
  // Triangle destruction
  // Line destruction
  // Line destruction
