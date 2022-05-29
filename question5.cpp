//Question 5 - Class Inheritance, const correctness and operator overloading

// Task 1 : Add a Circle class that has a center point and radius fields, 
//create a base Shape class that both Circle and Rectangle inherit from, try to move as many common field/functions to the base class

// Task 2: Create an operator overload that will allow us to chain a point instance to a ostream (std::cout), for example:
////Point point1(5,7);
////std::cout << point1;
//The previous line should output "5/7" to the console

// Task 3: Review the const correctness of the Shape/Circle/Rectangle member functions and modify them where it's required

// Do not change the main function body - it should compile and run without any modifications after completion of all tasks  

#include <string>
#include <iostream>
#include <vector>
#include <iostream>

using namespace std;

struct Point {

	Point() :
		x(0),
		y(0)
	{}

	Point(int x_, int y_) :
		x(x_),
		y(y_)
	{}

	int x;
	int y;

};

struct Size {

	Size() :
		width(0),
		height(0){}

	Size(int width_, int height_) :
		width(width_),
		height(height_){}

	int width;
	int height;
};

class Shape 
{
    public:

        Shape (string& name, const Point& center, int area) :
            s_name(name),
            s_center(center),
            s_area(area)
        {}

        string getName() {
            return s_name;
        }
        const Point& center() {
		return s_center;
	    }

    protected :
        string s_name;
        Point s_center;
        int s_area;
};

class Rectangle : public Shape {

public:

	Rectangle(const Point& center, const Size& size) :
		m_center(center),
		m_size(size)
	

	const Size& size() {
		return m_size;
	}

	 size_t area() {
		return m_size.width *(size_t)m_size.height;
	}

protected:

	Point m_center;
	Size  m_size;
};

class Circle : public Shape {

public:

	Circle(const Point& center, int radius) :
		c_radius(radius)
	

	 int getArea() {
		return 3.14*c_radius*c_radius;
	}

protected:

	int c_radius;
};




int main(int argc, char** argv)
{
	//Do not change anything in this function body
	Circle circle1(Point(5, 5), 10);
	Rectangle rect1(Point(5, 5), Size(10, 10));
	Circle circle2(Point(8, 8), 4);

	std::vector<Shape*> shapes{&circle1, & rect1, & circle2};
	for (const Shape* shape : shapes) {
		std::cout << "Shape: " << shape->name() << " center: " << shape->center() << " area: " << shape->area() << std::endl;
	}

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}
