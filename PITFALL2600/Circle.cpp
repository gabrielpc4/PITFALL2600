#include "Circle.h"

Circle::Circle()
	: Circle(0,0, 1)
{

}
Circle::Circle(float centerX, float centerY , int radius)
{
	this->center = Point(centerX, centerY);
	this->radius = radius;
	buildCircle();
}


void Circle::buildCircle()
{
	bresenhamCircleScan();

	int size = (int)temp.size();
	int j = size - 1;

	// Inverts the order of the points of the current 1/8th of the circle
	for (int i = 0; i < size; i++)
	{
		points.push_back(temp[j]);
		j--;
	}

	// Do the symmetry for the next 1/8th
	for (int i = 0; i < size; i++)
	{
		points.push_back(Point(-temp[i].x(), temp[i].y()));		
	}

	// We don't need that anymore
	temp.clear();

	for (unsigned i = 0; i < points.size(); i++)
	{
		// Do the circle center shift
		points[i] += center;
	}
}
void Circle::draw()
{
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);			// Start defining the points to be lit
	for (unsigned i = 0; i < points.size(); i++)
	{		
		// Informs openGL the coordinates to be lit when the function glFlush is called	
		glVertex2i(points[i].x(), points[i].y());
	}

	// Finishes defining the points to be lit in this iteration
	glEnd();
}
void Circle::light(Point p)
{
	// Assigns the point coordinates to temporary variables 
	// to save some process of the method x() and y() call all the time;
	float x = p.x();
	float y = p.y();

	// Vector of points, it contains the current x,y values, as well all the other 
	// points of the 8-was symmetry of this iteration of the algorithm

	// For this program we only need this one for now
	temp.push_back(Point(-x, -y));

	
}
void Circle::bresenhamCircleScan()
{
	int Xp = 0;
	int Yp = radius;
	Point P(Xp, Yp);

	light(P);

	Point A = P + Point(1, 0);
	Point B = P + Point(1, -1);

	int F = 1 - radius;

	while (Xp < Yp)
	{
		if (F >= 0)
		{
			light(B);
			F += (2 * Xp - 2 * Yp + 5);
			Xp = B.x();
			Yp = B.y();

			A = B + Point(1, 0);
			B = B + Point(1, -1);
		}
		else
		{
			light(A);
			F += (2 * Xp + 3);
			Xp = A.x();
			Yp = A.y();

			B = A + Point(1, -1);
			A = A + Point(1, 0);
		}
	}
}
Circle::~Circle()
{
	points.clear();
}
