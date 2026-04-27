#include "query.hpp"

std::string query::getTextInput() const {
    return textInput;
}

std::uint8_t query::getMaxResults() const {
    return maxResults;
}

std::double_t query::getMinRating() const {
    return minRating;
}

bool query::isValid() const {
    return !textInput.empty() && maxResults > 0 && minRating >= 0.0;
}


query query::setTextInput(const std::string& text) {
    textInput = text;
    return *this; // Return the current object for chaining
}

query query::setMaxResults(std::uint8_t max) {
    maxResults = max;
    return *this; // Return the current object for chaining
}

query query::setMinRating(std::double_t min) {
    minRating = min;
    return *this; // Return the current object for chaining
}
