#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Point
{
	float x, y;
	Point(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	Point() = default;
};

struct PointsSet
{
	vector<Point> points;
	PointsSet(vector<Point> points)
	{
		this->points = points;
	}
	PointsSet(Point* points, int size, char c)
	{
		for (int i = 0; i < size; i++)
			this->points.push_back(points[i]);
	}
};

class Triangle
{
public:
	Point* points;
	float square;
	float Square(Point point1, Point point2, Point point3)
	{
		float AB = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
		float BC = sqrt(pow(point2.x - point3.x, 2) + pow(point2.y - point3.y, 2));
		float AC = sqrt(pow(point1.x - point3.x, 2) + pow(point1.y - point3.y, 2));
		float P = (AB + BC + AC) / 2;
		float S = sqrt((P - AB) * (P - AC) * (P - BC) * P);
		return S;
	}
	Triangle(Point* points)
	{
		this->points = points;
		square = Square(points[0], points[1], points[2]);
	}
	Triangle() = default;
};

struct Plane
{
	int width, height;
	vector<PointsSet> pointsSets;
	Plane(int width, int height)
	{
		this->width = width;
		this->height = height;
	}
};

vector <Point> GeneratePoints(int width, int height)
{
	int n = 0;
	while (n < 3 || n > 10)
	{
		cout << "Points count (min = 3, max = 10): ";
		cin >> n;
	}
	vector <Point> points;
	int x, y;
	for (int i = 0; i < n; i++)
	{
		printf("[%d]\n", i);
		printf("X(0:%d): ", width);
		cin >> x;
		printf("Y(0:%d): ", height);
		cin >> y;
		Point point(x, y);
		points.push_back(point);
		cout << endl;
	}
	return points;
}

float sign(Point p1, Point p2, Point p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(Point* points, Point targetPoint)
{
	float d1, d2, d3;
	bool has_neg, has_pos;

	d1 = sign(targetPoint, points[0], points[1]);
	d2 = sign(targetPoint, points[1], points[2]);
	d3 = sign(targetPoint, points[2], points[0]);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}


int main()
{
	int width = 10;
	int height = 10;
	Plane* plane = new Plane(width, height);
	cout << "Set 1:\n";
	PointsSet pointsSet1(GeneratePoints(width, height));
	cout << "Set 2:\n";
	PointsSet pointsSet2(GeneratePoints(width, height));
	plane->pointsSets.push_back(pointsSet1);
	plane->pointsSets.push_back(pointsSet2);
	//plane->DrawPlane();
	vector <Triangle> triangles;
	for (int i1 = 0; i1 < pointsSet1.points.size() - 2; i1++)
		for (int i2 = i1 + 1; i2 < pointsSet1.points.size() - 1; i2++)
			for (int i3 = i2 + 1; i3 < pointsSet1.points.size(); i3++)
			{
				Point* points = new Point[]{ pointsSet1.points[i1], pointsSet1.points[i2], pointsSet1.points[i3] };
				Triangle triangle(points);
				bool flag = true;
				for (int i = 0; i < pointsSet2.points.size(); i++)
					if (!PointInTriangle(triangle.points, pointsSet2.points[i]))
						flag = false;
				if (flag)
					triangles.push_back(triangle);
			}
	Triangle* targetTriangle = NULL;
	float minSquare = 10000;
	for (Triangle triangle : triangles)
	{
		if (triangle.square < minSquare)
		{
			minSquare = triangle.square;
			targetTriangle = &triangle;
		}
	}
	if (targetTriangle == NULL)
		return 0;
	cout << "Triangles points: " << endl;
	for (int i = 0; i < 3; i++)
		printf("(%d, %d)\n", (int)round(targetTriangle->points[i].x), (int)round(targetTriangle->points[i].y));
	cout << "Min square: " << minSquare << endl;
}