#include <string>
#include <iostream>

class User{
    protected:
        std::string name;
        int id;
    public:
        User(const std::string& name, int id) : name(name), id(id){};
        void printInfo(){
            std::cout << "Name: " << this->name << ", ID: " << this->id << std::endl;
        }
};

class Student : public User{
    protected:
        double average_grade;
    public:
        Student(const std::string& name, int id, double grade) : User(name, id), average_grade(grade){};
        void printRole(){
            std::cout << "Student: " << this->name << std::endl;
        }
};

class Teacher : public User{
    protected:
        int coolness;
    public:
        Teacher(const std::string& name, int id, double coolness) : User(name, id), coolness(coolness){};
        void printRole(){
            std::cout << "Lehrer: " << this->name << std::endl;
        }
};

int main(){
    Student student("Alice", 1, 3.5);
    Teacher teacher("Bob", 2, 10);

    student.printInfo();
    teacher.printInfo();

    student.printRole();
    teacher.printRole();

    return 0;
}