#include <iostream>
#include <string>

class Note {
private:
    std::string* text;

public:
    // Constructor
    Note(std::string t) {
        std::string *newString = new std::string;
        *newString = t;
        this->text = newString;
    }

    // // Copy Constructor (For Task Part 2)
    // Note(const Note& other) {
    //     std::string *newString = new std::string;
    //     this->text = newString;
    // }

    // Destructor
    ~Note() {
        delete this->text;
        this->text = NULL;
        std::cout << "Memory released!" << std::endl;
    }

    // Display method
    void display() {
        std::cout << "Current text: " << *this->text << std::endl;
    }
};

int main() {
    // --- Task Part 1 ---
    
    Note *note = new Note("Hallo Welt");
    //keine ahnung warum das geht?
    Note *note2 = new Note(*note);
    
    /* 
       TODO: Observe and explain in these comments:
       1. Why can you initialize the second object with the first one?
       Antwort: ...

       2. When the destructor is automatically called?
       Antwort: ...

       3. What exception occurs or might occur in the destructor?
       Antwort: ...
    */

    // --- Task Part 2 ---

    // TODO: Verify if the copy constructor resolves the observed issue from Part 1.

    return 0;
}
