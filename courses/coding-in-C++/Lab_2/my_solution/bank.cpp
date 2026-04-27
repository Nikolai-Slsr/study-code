#include <string>
#include <iostream>
#include <cmath>

class bank
{
private:
    std::string owner;
    double balance;
public:
    void setOwner(std::string owner){
        this->owner = owner;
    }
    std::string getOwner(){
        return owner;
    }
    
};