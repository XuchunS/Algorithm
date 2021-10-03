#include <cmath>

struct Vector {
    double x, y;
    Vector(double x, double y) : x(x), y(y) {}
};

struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

// 点积
double dot(Point a, Point b)
{
    return a.x * b.x + a.y * b.y;
}

// 叉积
double cross(Point a, Point b)
{
    return a.x * b.y - b.x * a.y;
}

// 取模
double get_length(Point a)
{
    return sqrt(dot(a, a));
}

// 计算两个向量构成的平行四边形的面积
double area(Point a, Point b, Point c)
{
    return cross(b - a, c - a);
}

// 向量A顺时针旋转C的角度
Vector rotate(Vector a, double angle)
{
    return Vector(a.x * cos(angle) + a.y * sin(angle), -a.x * sin(angle) + a.y * cos(angle));
}

// 两直线相交
// cross(v, w) == 0则两直线平行或者重合
Point get_line_intersection(Point p, Vector v, Point q, vector w)
{
    Vector u = p - q;
    double t = cross(w, u) / cross(v, w);
    return p + v * t;
}

// 浮点数的比较
const double eps = 1e-8;
int sign(double x)  // 符号函数
{
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}
int cmp(double x, double y)  // 比较函数
{
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}

// 点到直线的距离
double distance_to_line(Point p, Point a, Point b)
{
    Vector v1 = b - a, v2 = p - a;
    return fabs(cross(v1, v2) / get_length(v1));
}
// 点到线段的距离
double distance_to_segment(Point p, Point a, Point b)
{
    if (a == b) return get_length(p - a);
    Vector v1 = b - a, v2 = p - a, v3 = p - b;
    if (sign(dot(v1, v2)) < 0) return get_length(v2);
    if (sign(dot(v1, v3)) > 0) return get_length(v3);
    return distance_to_line(p, a, b);
}

// 点在直线上的投影
double get_line_projection(Point p, Point a, Point b)
{
    Vector v = b - a;
    return a + v * (dot(v, p - a) / dot(v, v));
}
// 点是否在线段上
bool on_segment(Point p, Point a, Point b)
{
    return sign(cross(p - a, p - b)) == 0 && sign(dot(p - a, p - b)) <= 0;
}
// 判断两线段是否相交
bool segment_intersection(Point a1, Point a2, Point b1, Point b2)
{
    double c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1);
    double c3 = cross(b2 - b1, a2 - b1), c4 = cross(b2 - b1, a1 - b1);
    return sign(c1) * sign(c2) <= 0 && sign(c3) * sign(c4) <= 0;
}

