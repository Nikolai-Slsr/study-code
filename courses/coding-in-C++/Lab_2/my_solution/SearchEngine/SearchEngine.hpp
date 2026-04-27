#ifndef SEARCH_ENGINE_HPP
#define SEARCH_ENGINE_HPP

#include "WebContent.hpp"
#include "query.hpp"
#include <set>

class SearchEngine
{
private:
    static int total_number_of_requests;
    int local_number_of_requests;
    int number_of_search_hits;
    std::multiset<WebContent> content;
public:
    SearchEngine() = default;


    bool addContent(const WebContent& newContent);
    bool addContent(const std::string& address, const std::string& content, double rating); 
    bool removeContent(const std::string& address);
    bool saveContetentToFile(const std::string& filename) const;
    std::int16_t loadContentFromFile(const std::string& filename);
    //search funcitons
    std::multiset<WebContent> strict_search(const query& query);
    std::multiset<WebContent> fuzzy_search(const query& query);
    bool isValidAddress(const std::string& address) const;
    //debug functions
    void printStatistics() const;
};

#endif // SEARCH_ENGINE_HPP