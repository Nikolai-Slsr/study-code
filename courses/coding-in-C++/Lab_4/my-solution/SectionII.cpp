#include <iostream>
#include <iterator>

class geometricShape{
    public:
        geometricShape() = default;
        //destructor should be virtual to allow base classes to use the heap
        virtual double getArea() const{
            return 0.0;
        };


};

class Circle : public geometricShape{
    private:
        double radius;
        double const PI = 3.14;
    public:
        Circle(double input_radius) : geometricShape() , radius(input_radius){};
        virtual double getArea() const override{
            return PI * radius * radius;
        };
};

class Rectangle : public geometricShape{
    private:
        double a;
        double b;
    public:
        Rectangle(double ia, double ib) : geometricShape() , a(ia), b(ib){};

        double getArea() const override{
            return a * b;
        };

};

int main(){
    geometricShape* a = new Rectangle(2.0, 2.0);
    geometricShape* b = new Circle(3.0);


    geometricShape* Shapes[4];
    Shapes[0] = a;
    Shapes[1] = b;
    Shapes[2] = new Rectangle(1,2);
    Shapes[3] = new Circle(2);

    for (auto Shape : Shapes) {
        std::cout << "Area: " << Shape->getArea() << std::endl;
    }
    //this loop prints all areas nicely. I did not notice anything paticular
    
    return 0;
}