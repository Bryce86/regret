#include <iostream>

class Point {
private:
    int x_; 
    int y_;

public:
    Point(int x, int y) : x_(x), y_(y) {}

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << '(' << p.x_ << ',' << p.y_ << ')';
    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x_ >> p.y_; 
    }
};


int main()
{
    Point p(1,2);
    std::cout << "[Output] ";
    std::cout << p << std::endl;

    std::cout << "[Input] ";
    std::cin >> p; 
    std::cout << p << std::endl;

    return 0;
}

