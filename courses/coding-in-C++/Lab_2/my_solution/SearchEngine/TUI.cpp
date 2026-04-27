#include "TUI.hpp"
#include "query.hpp"
#include <iostream>
#include <string>
#include <cstdint>

// ANSI Escape Codes für Farben
const std::string RESET   = "\033[0m";
const std::string BOLD    = "\033[1m";
const std::string RED     = "\033[31m";
const std::string GREEN   = "\033[32m";
const std::string YELLOW  = "\033[33m";
const std::string BLUE    = "\033[34m";
const std::string CYAN    = "\033[36m";

void clearScreen() {
    // Löscht den Terminal-Bildschirm (funktioniert auf fast allen UNIX/MacOS/Windows-Terminals)
    std::cout << "\033[2J\033[1;1H";
}

void waitForKey() {
    std::cout << "\n" << YELLOW << "Drücke Enter, um zum Menü zurückzukehren..." << RESET;
    std::string dummy;
    std::getline(std::cin, dummy);
}

void TUI::displayMenu() const {
    clearScreen();
    std::cout << BOLD << CYAN << "==============================\n";
    std::cout << "===   SearchEngine TUI     ===\n";
    std::cout << "==============================\n" << RESET << "\n";
    std::cout << BOLD << BLUE << "[1]" << RESET << " Daten aus Datei laden\n";
    std::cout << BOLD << BLUE << "[2]" << RESET << " Webseite suchen\n";
    std::cout << BOLD << BLUE << "[3]" << RESET << " Neue Webseite hinzufügen\n";
    std::cout << BOLD << BLUE << "[4]" << RESET << " Daten in Datei speichern\n";
    std::cout << BOLD << BLUE << "[5]" << RESET << " Beenden\n\n";
    std::cout << BOLD << GREEN << "Bitte wähle eine Option (1-5): " << RESET;
}

void TUI::handleLoadFromFile() {
    std::string filename;
    std::cout << "\nDateiname eingeben (z.B. test_data.txt oder ../large_test_data.txt): ";
    std::getline(std::cin, filename);
    
    // Nutze deinen Rückgabewert (int16_t)
    std::int16_t sites_loaded = engine.loadContentFromFile(filename);
    
    if (sites_loaded > 0) {
        std::cout << GREEN << "[ERFOLG] " << sites_loaded << " Webseiten wurden erfolgreich geladen!\n" << RESET;
    } else if (sites_loaded == 1 || sites_loaded == 0 || sites_loaded == true) { // Fallback, falls loadContentFromFile im Hintergrund nur false/true liefert
        std::cout << GREEN << "[ERFOLG] Daten wurden erfolgreich geladen!\n" << RESET;
    } else {
        std::cout << RED << "[FEHLER] Datei konnte nicht geladen werden.\n" << RESET;
    }
    
    waitForKey();
}

void TUI::handleSearch() {
    std::string keyword;
    std::cout << "\nSuchbegriff eingeben: ";
    std::getline(std::cin, keyword);

    std::string searchMode;
    std::cout << "Suchmodus wählen - [1] Strict Search, [2] Fuzzy Search: ";
    std::getline(std::cin, searchMode);

    query q(keyword, 10, 0.0);
    std::multiset<WebContent> results;

    if (searchMode == "2") {
        results = engine.fuzzy_search(q);
        std::cout << "\n" << CYAN << "--- Fuzzy-Suchergebnisse für '" << keyword << "' ---" << RESET << "\n";
    } else {
        results = engine.strict_search(q);
        std::cout << "\n" << CYAN << "--- Strict-Suchergebnisse für '" << keyword << "' ---" << RESET << "\n";
    }

    if (results.empty()) {
        std::cout << YELLOW << "Keine passenden Ergebnisse gefunden.\n" << RESET;
    } else {
        for (const auto& res : results) {
            std::cout << BOLD << "Adresse: " << RESET << res.getAddress() 
                      << CYAN << " | Rating: " << res.getRating() << RESET << "\n"
                      << "Inhalt: " << res.getContent() << "\n";
            std::cout << YELLOW << "--------------------------------------\n" << RESET;
        }
    }
    
    waitForKey();
}

void TUI::handleAddContent() {
    std::string address, content, ratingStr;
    double rating;

    std::cout << "\nAdresse (URL) eingeben: ";
    std::getline(std::cin, address);
    
    std::cout << "Rating eingeben (z.B. 4.5): ";
    std::getline(std::cin, ratingStr);
    
    try {
        rating = std::stod(ratingStr);
    } catch (...) {
        std::cout << RED << "[FEHLER] Ungültiges Rating. Abbruch.\n" << RESET;
        waitForKey();
        return;
    }

    std::cout << "Inhalt eingeben: ";
    std::getline(std::cin, content);

    if (engine.addContent(address, content, rating)) {
        std::cout << GREEN << "[ERFOLG] Webseite wurde hinzugefügt!\n" << RESET;
    } else {
        std::cout << RED << "[FEHLER] Konnte nicht hinzugefügt werden (URL existiert bereits oder Rating < 0).\n" << RESET;
    }
    
    waitForKey();
}

void TUI::handleSaveToFile() {
    std::string filename;
    std::cout << "\nDateiname zum Speichern eingeben: ";
    std::getline(std::cin, filename);

    auto sites_saved = engine.saveContetentToFile(filename);

    if (sites_saved >= 0) {
        std::cout << GREEN << "[ERFOLG] " << sites_saved << " Webseiten wurden erfolgreich gespeichert!\n" << RESET;
    } else {
        std::cout << RED << "[FEHLER] Daten konnten nicht gespeichert werden.\n" << RESET;
    }
    
    waitForKey();
}

void TUI::run() {
    std::string input;
    bool running = true;

    while (running) {
        displayMenu();
        std::getline(std::cin, input);

        if (input == "1") {
            handleLoadFromFile();
        } else if (input == "2") {
            handleSearch();
        } else if (input == "3") {
            handleAddContent();
        } else if (input == "4") {
            handleSaveToFile();
        } else if (input == "5" || input == "q" || input == "quit") {
            clearScreen();
            std::cout << CYAN << "Auf Wiedersehen!\n" << RESET;
            running = false;
        } else {
            std::cout << RED << "\n[FEHLER] Ungültige Eingabe.\n" << RESET;
            waitForKey();
        }
    }
}
