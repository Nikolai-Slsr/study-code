#include <cstdint>
#include <iostream>

namespace validation
{
    bool is_adult(std::int_fast16_t age){
        if (age >= 18)
        {
            return true;
        }
        return false;
    }
    bool is_senior(std::int_fast16_t age);
    
}

bool validation::is_senior(std::int_fast16_t age){
        if (age >= 65)
        {
            return true;
        }
        return false;
    }
int main()
{
    std::int_fast16_t age;
    std::cout << "Please enter your age: " << std::endl;
    std::cin >> std::ws;
    if(!(std::cin >> age)){
        std::cout << "Please enter a valid age. " << std::endl;
        return -1;
    }
    

    std::cout << "Your age is: " << age << std::endl;
    if (validation::is_senior(age))
    {
        std::cout << "That means that you are a senior citizen." << std::endl;
        return 0;
    }
    if (validation::is_adult(age))
    {
        std::cout << "That means that you are an adult." << std::endl;
        return 0;
    }

    std::cout << "That means that you are still a kid or teenager." << std::endl;
        return 0;
}

