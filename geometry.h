#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <cmath>
#include <vector>
#define EPSILON 0.0001
/**
 * Contains two coordinates on different axises, often referred to as x and y.
 */
class Point{
    public:
        
        double x,//! \var The coordinate of the Point on the "x" axis
               y;//! \var The coordinate of the Point on the "y" axis
        Point():x(0.0),y(0.0)
    {}
        Point(double x,double y):
            x(x),y(y){}
        /**
         * Obtains the cross product of this point and another.
         */
        double crossProduct(const Point &a)const{
            return x*a.y-a.x*y;
        }
        /**
         * Computes the dot product of this point and another.
         */
        double dot(const Point &a)const{
            return a.x*x+a.y*y;
        }
        /**
         * alters the position specified by this point, adding dx to x and dy
         * to y.
         */
        void add(double dx,double dy){
            x+=dx;
            y+=dy;
        }
        Point getDifference(Point a)const{
            return Point(a.x-x,a.y-y);
        }

        Point getMidPoint(const Point& a)const{
            double dx=a.x-x;
            double dy=a.y-y;
            return Point(dx/2,dy/2);
        }
};
/**
 * Compute the distance between two points
 * */
double Distance(const Point&a,const Point&b);
/**
 * Compare two doubles with an error value which, should the difference be
 * smaller than error, will return 0, if value is larger than expected, it
 * returns 1, if the value is smaller than expected it returns -1.
 */
int compareWithError(double,double,double);
//class for generic shape access, you know, for shape things.
class Shape{
    public:
        Shape();
        ~Shape();
        /**
         * Get the points which make up the boundary of the shape
         * */
        virtual std::vector<Point> getPoints()const=0;
        /**
         * Determines whether another shape intersects this one.
         */
        virtual bool intersects(const Shape&)const;
        /**
         * Find the various points where there is negligable distance between
         * complementary pairs of points.
         */
        virtual void intersectionPoint(const Shape&,int&,std::vector<Point>&)const;
};
/**
 * Represents a line segment.
 */
class Line:public Shape{
    public:
        Point first,second;
        Line(){}
        Line(const Point& a,const Point &b):first(a),second(b){
            
        }
        ~Line(){}
        /**
         * First step for determining whether two lines intersect.
         */
        bool doBoundingBoxesIntersect(const Line& b)const;
        /**
         * Second step for determining whether two lines intersect.
         */
        bool isPointOnLine(Point a)const;
        /**
         * Third step for determining whether two Lines intersect.
         */
        bool isPointRightOfLine(Point b)const;
        /**
         * final step of determining whether two Lines intersect.
         */
        bool touchesOrCrossesLine(const Line &b)const;
        /**
         * Depreciated handle for the interface that existed prior to the
         * existence of Shape.intersects.
         */
        bool doLinesIntersect(const Line& b)const;
        /**
         * Alias for doLinesIntersect conforming to the Shape.intersects
         * specification.
         */
        bool intersects(const Line& b)const;
        /**
         * Calculates the distance between the start point and the end point,
         * and returns it.
         * 
         */
        double length()const;
        /**
         * Returns the points along the line.
         */
        std::vector<Point> getPoints()const;
};
class Circle:public Shape{
public:
    /**
     * The center of the circle.
     */
    Point thing;
    /**
     * The radius of the circle (A.K.A the distance between the center and any
     * given point on the boundary.
     */
    double radius;
    Circle():radius(0),thing(){}
    /**
     * Initializes a circle to have a specified center and radius.
     */
    Circle(Point center,double radius):thing(center),radius(radius)
    {}
    ~Circle(){}
    /**
     * returns true if this circle is intersecting another circle. Much faster
     * than Shape.intersects.
     * Guaranteed to not modify any objects or parameters.
     */
    bool intersects(const Circle &b)const;
    /**
     * Returns true if this circle is intersecting a line. Still very fast.
     */
    bool intersects(const Line &b)const;
    /**
     * Finds the intersection between this circle and this circle.
     */
    void intersectionPoint(const Circle& b,int &n,std::vector<Point> &output)const;
    /**
     * Finds the intersection between the a line and the boundary of the
     * circle, faster than the naive Shape.intersectionPoint
     */:w

    void intersectionPoint(const Line &b,int &n, std::vector<Point> &output)const;
    /**
     * Returns true if the point is very nearly on the boundary of the circle
     * (EPSILON in this case is 0.005).
     * Guaranteed to not modify any parameters or objects.
     */
    bool isOnCircle(const Point &i)const;
    /**
     * Returns true if the point is very nearly on the boundary of the circle,
     * within an error specified by the caller.
     *
     * Guaranteed to not modify parameters or objects.
     */
    bool isOnCircle(const Point &i,double error)const;
    /**
     * Returns an outline of points roughly in the shape of the circumferance
     * of the circle
     */
    std::vector<Point> getPoints()const;
};


class Polygon:public Shape{
    /**
     * The points which make up the endpoints of the line segments of the
     * polygon.
     */
    std::vector<Point> points;
    public:
    Polygon();
    ~Polygon();
    /**
     * Obtains a point cloud roughly in the shape of the polygon.
     */
    std::vector<Point> getPoints()const;
    /**
     * Add a point to end of the polygon(connected to the first point and the
     * last point previously specified).
     */
    void addPoint(const Point &i);
};
    
#endif
