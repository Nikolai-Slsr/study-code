#include <iostream>
#include <string>
#include <cstdint>
#include <iomanip>

void getGrade(std::int_fast16_t& output, std::string display_text){
    std::string input;
    while (true)
    {
        std::cout << display_text << std::endl;
        if(std::getline(std::cin, input)){
            try
            {
                std::int_fast16_t grade = std::stoi(input);
                if (grade >= 0 && grade <= 100)
                {
                    output = grade;
                }
                else
                {
                    std::cout << "Please enter a grade between 0 and 100. " << std::endl;
                    continue;
                }
                
            }
            catch (const std::exception&)
            {
                std::cout << "Please enter a valid grade. " << std::endl;
                continue;
            }
            break;
        }
    }
    output = std::stoi(input);
}
void readStudentData( std::string& name, std::int_fast16_t& homework, std::int_fast16_t& midterm, std::int_fast16_t& finalExam){
    std::cout << "Enter student name: " << std::endl;
    while (true)
    {
        if(!(std::getline(std::cin, name))){
            std::cout << "Please enter a valid name. " << std::endl;
            continue;
        }
        break;
    }
    getGrade(homework, "Enter homework grade: ");
    getGrade(midterm, "Enter midterm grade: ");
    getGrade(finalExam, "Enter final exam grade: ");
}

std::string getGradeAlphabetical(std::int_fast16_t& finalGrade){
    std::cout << (finalGrade / 10) << std::endl;
    switch ((finalGrade / 10))
    {
    case 10:
    case 9:
        return "A";
        break;
    case 8:
        return "B";
        break;
    case 7:
        return "C";
        break;
    case 6:
        return "D";
        break;
    case 5:
        return "E";
        break;
    default:
        return "F";
    }
}

void calculateGrade(std::int_fast16_t& homework, std::int_fast16_t& midterm, std::int_fast16_t& finalExam, std::int_fast16_t& finalGrade, std::string& letterGrade){
    // Check the Inputs:
    if (homework < 0 || homework > 100 || midterm < 0 || midterm > 100 || finalExam < 0 || finalExam > 100)
    {
        std::cout << "Please enter valid grades between 0 and 100. " << std::endl;
        return;
    }
    finalGrade = static_cast<std::int_fast16_t>(homework * 0.4 + midterm * 0.25 + finalExam * 0.35);
    letterGrade = getGradeAlphabetical(finalGrade);
}

const void printReport(std::string& finalGradeAlph, std::int_fast16_t& finalGrade){
    std::cout << std::setw(30) << std::setfill('-') << std::left << "|"<< std::right << "|" << std::endl;
    std::cout << std::setfill('.') << std::left << "Final grade" << std::setw(17) << std::right << finalGrade << "(" << finalGradeAlph << ")" << std::endl;
    std::cout << std::setw(30) << std::setfill('-') << std::left << "|"<< std::right << "|" << std::endl;
}

int main(){
    std::string name;
    std::int_fast16_t homework, midterm, finalExam;
    readStudentData(name, homework, midterm, finalExam);
    std::cout << "Student name: " << name << std::endl;
    std::cout << "Homework grade: " << homework << std::endl;
    std::cout << "Midterm grade: " << midterm << std::endl;
    std::cout << "Final exam grade: " << finalExam << std::endl;
    std::int_fast16_t finalGrade = 0;
    std::string finalGradeAlpabetical = "F";
    calculateGrade(homework, midterm, finalExam, finalGrade, finalGradeAlpabetical);
    
    printReport(finalGradeAlpabetical, finalGrade);
    return 0;
}