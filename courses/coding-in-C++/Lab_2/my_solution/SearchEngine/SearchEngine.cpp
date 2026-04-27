#include "SearchEngine.hpp"
#include "WebContent.hpp"
#include "query.hpp"
#include <set>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Initialisierung der statischen Klassen-Variable
int SearchEngine::total_number_of_requests = 0;


//Helper funciton:
std::vector<std::string>& splitKeywords(const std::string& query) {
    std::vector<std::string> keywords;
    std::istringstream iss(query);
    std::string word;
    
    while (iss >> word) {
        keywords.push_back(word);
    }
    return keywords;
}

std::string& to_lower(std::string& input){
    std::string out = "";
    for(auto c : input){
        out += (std::tolower(static_cast<unsigned char>(c)));
    }
    return out;
}

bool SearchEngine::isValidAddress(const std::string& address) const{
    if(address.empty()){
        return false;
    }
    for (const WebContent& web_content : this->content)
    {
        if (web_content.getAddress() == address)
        {
            return false;
        }
        
    }
    return true;
}

std::multiset<WebContent> SearchEngine::strict_search(const query& query) {
    if (!query.isValid())
    {
        return {};
    }
    
    std::multiset<WebContent> results;

    for (const auto& entry: content)
    {
        if (std::string::npos != entry.getAddress().find(query.getTextInput()) || std::string::npos != entry.getContent().find(query.getTextInput()))
        {
            results.insert(entry);
        }
    } 
    SearchEngine::local_number_of_requests ++;
    SearchEngine::total_number_of_requests ++;
    return results;
}

std::multiset<WebContent> SearchEngine::fuzzy_search(const query& query) {

    std::string lower_query = to_lower(query.getTextInput());
    if (!query.isValid())
    {
        return {};
    }

    
    
    std::multiset<WebContent> results;

    //generate keywords form query

    std::vector<std::string> keywords = splitKeywords(query.getTextInput());

    //search for the keywords in the webpages.
    for (const auto& entry: content)
    {   
        for (const auto& keyword: keywords)
        {
            if (std::string::npos != entry.getAddress().find(keyword) || std::string::npos != entry.getContent().find(keyword))
            {
                results.insert(entry);
                break;
            }
        }
    } 
    SearchEngine::local_number_of_requests ++;
    SearchEngine::total_number_of_requests ++;
    return results;
}


bool SearchEngine::addContent(const WebContent& newContent)
{
    if (!this->isValidAddress(newContent.getAddress()) || newContent.getRating() < 0 || content.empty())
    {
        return false;
    }
    this->content.insert(newContent);
    return true;
}

bool SearchEngine::addContent(const std::string& address, const std::string& content, double rating)
{
    WebContent newContent(address, content, rating);
    return this->addContent(newContent); //unsing the already defined addCOntet that uses the object.
}

bool SearchEngine::removeContent(const std::string& adress){
    for(auto it_content = content.begin(); it_content != content.end(); it_content ++ ){
        if (it_content->getAddress() == adress)
        {
            content.erase(it_content);
            return true;
        }
    }
    return false;
}

bool SearchEngine::saveContetentToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        return false;
    }

    // Iteriere über das Set und speichere jede WebContent-Einheit ab
    // Format pro WebContent: Addresse (Zeile 1), Rating (Zeile 2), Content (Zeile 3)
    for (const auto& webObj : content) {
        outFile << webObj.getAddress() << "\n";
        outFile << webObj.getRating() << "\n";
        outFile << webObj.getContent() << "\n"; 
    }

    outFile.close();
    return true;
}

std::int16_t SearchEngine::loadContentFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return -1;
    }

    std::string address;
    std::string ratingStr;
    std::string webContentText;

    std::int16_t count_loaded_sites= 0;

    // Wir lesen immer im 3er-Pack die Zeilen aus
    while (std::getline(inFile, address) && 
           std::getline(inFile, ratingStr) && 
           std::getline(inFile, webContentText)) {
        
        try {
            // String in Double konvertieren
            double rating = std::stod(ratingStr);
            
            // Neues Objekt erstellen und in unser Set einfügen 
            WebContent newContent(address, webContentText, rating);
            count_loaded_sites ++;
            content.insert(newContent);
        } catch (const std::exception& e) {
            // Ignoriere fehlerhafte Konvertierungen und mache weiter
            std::cerr << "Fehler beim Parsen des Ratings für " << address << std::endl;
        }
    }

    inFile.close();
    return count_loaded_sites;
}


