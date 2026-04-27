#ifndef QUERY_HPP
#define QUERY_HPP

#include <string>
#include <cstdint>

class query{
    private:
        std::string textInput;
        std::uint8_t maxResults;
        std::double_t minRating;
    public:
        //constructor
        query(const std::string& textInput, std::uint8_t maxResults, std::double_t minRating)
            : textInput(textInput), maxResults(maxResults), minRating(minRating)
        {

        }
        //copy constructor
        query(const query& other)
            : textInput(other.textInput), maxResults(other.maxResults), minRating(other.minRating)
        {

        }

        bool isValid() const;

        //getters
        std::string getTextInput() const;
        std::uint8_t getMaxResults() const;
        std::double_t getMinRating() const;

        //setters
        query setTextInput(const std::string& text); //for function chaining
        query setMaxResults(std::uint8_t max);
        query setMinRating(std::double_t min);
};

#endif // QUERY_HPP