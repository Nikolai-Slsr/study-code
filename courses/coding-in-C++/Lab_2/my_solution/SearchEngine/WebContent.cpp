#include "WebContent.hpp"

bool WebContent::isPopular() const {
    return rating > POPULARITY_THRESHOLD;
}

bool WebContent::operator<(const WebContent& other) const {
    // Umdrehen der Logik: Höheres Rating bedeutet, es kommt "weiter nach vorne" 
    // in der Sortierung des Multisets
    return rating > other.rating;
}

double WebContent::getRating() const {
    return rating;
}

const std::string& WebContent::getAddress() const {
    return address;
}

const std::string& WebContent::getContent() const {
    return content;
}

bool WebContent::setRating(std::double_t& newRating) {
    if (newRating < 0.0) {
        return false; // Invalid rating
    }
    rating = newRating;
    return true;
}

bool WebContent::setContent(const std::string& newContent) {
    content = newContent;
    return true;
}