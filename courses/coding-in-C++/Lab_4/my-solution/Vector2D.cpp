#include <iostream>
#include <cmath>

class Vector2D {
    protected:
        double x;
        double y;
    public:
        Vector2D() : x(0), y(0) {}  // Default constructor
        Vector2D(double ix, double iy) : x(ix), y(iy) {}  // Parameterized constructor

        double getX() const { return x; }  // Getter for x
        double getY() const { return y; }  // Getter for y

        void print() const {  // Print function
            std::cout << "Vector: (" << x << ", " << y << ")" << std::endl;
        }

        // Length of the vector 
        double length() const {  // Exact length
            return std::sqrt(x * x + y * y);
        }

        // Overloaded length method 
        double length(int precision) const {  // Length rounded to specified decimal places
            double len = std::sqrt(x * x + y * y);
            double factor = std::pow(10.0, precision); //because round alsways rouds komplely I shift the whole thing
            return std::round(len * factor) / factor;
        }

        // Operator overloading
        Vector2D operator+(const Vector2D& other) const {
            return Vector2D(this->x + other.x, this->y + other.y);
        }

        Vector2D& operator+=(const Vector2D& other) {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }

        Vector2D operator*(double scalar) const {
            return Vector2D(this->x * scalar, this->y * scalar);
        }

        Vector2D operator*(double scalar, const Vector2D& vec) {
            return Vector2D(vec.getX() * scalar, vec.getY() * scalar);
        }

};

int main() {
    Vector2D v1(3.0, 4.0);
    Vector2D v2(1.0, 2.0);

    v1.print(); // Output: Vector: (3, 4)
    v2.print(); // Output: Vector: (1, 2)

    Vector2D v3 = v1 + v2;
    v3.print(); // Output: Vector: (4, 6)

    Vector2D v4;
    v4 += v2;
    v4.print(); // Output: Vector: (1, 2)

    std::cout << "Length of v1: " << v1.length() << std::endl; // Exact length
    std::cout << "Length of v1 rounded to 1 decimal: " << v1.length(1) << std::endl; // Rounded length

    return 0;
}