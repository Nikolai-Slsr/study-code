#ifndef TUI_HPP
#define TUI_HPP

#include "SearchEngine.hpp"

class TUI {
private:
    SearchEngine engine;
    
    void displayMenu() const;
    void handleSearch();
    void handleAddContent();
    void handleLoadFromFile();
    void handleSaveToFile();

public:
    TUI() = default;
    
    // Starts the interactive Text User Interface
    void run();
};

#endif // TUI_HPP
