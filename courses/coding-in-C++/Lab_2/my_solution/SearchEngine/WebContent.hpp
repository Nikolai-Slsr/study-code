#ifndef WEB_CONTENT_HPP
#define WEB_CONTENT_HPP

#include <string>

class WebContent{
    private:
        static constexpr double POPULARITY_THRESHOLD = 4.0;
        std::double_t rating;
        const std::string address;
        std::string content;
    public:
        /**
         * @brief Default constructor for WebContent.
         *
         * Initializes an empty WebContent object. The content is empty and the rating is 0.0.
         */
        WebContent() = default;
        
        /**
         * @brief Constructor with initialization parameters.
         *
         * Creates a new WebContent object with the specified address, text content, and rating.
         *
         * @param[in] address   The unique address representation for this web content
         * @param[in] content  The text content associated with the web resource
         * @param[in] rating   The initial relevance or rating value
         */
        WebContent(const std::string& address, const std::string& content, const std::double_t rating)
            : rating(rating),address(address), content(content)
        {

        }

        /**
         * @brief Copy constructor.
         *
         * Creates a copy of an existing WebContent object.
         *
         * @param[in] other  The WebContent reference to copy from
         */

        WebContent(const WebContent& other)
            : rating(other.rating), 
            address(other.address), 
            content(other.content)
        {

        }

        /**
         * @brief Checks if the web content is considered popular.
         *
         * Based on the derived rank/popularity threshold, this determines if
         * the current web content's rating exceeds the required static threshold.
         *
         * @return  true if rating > POPULARITY_THRESHOLD, false otherwise
         */
        bool isPopular() const;
        /**
         * @brief Comparison operator for WebContent.
         * Compares this WebContent object with another based on their ratings.
         * @return true if this object's rating is less than the other object's rating, false otherwise.
         */
        
        bool operator<(const WebContent& other) const;

        /**
         * @brief Retrieves the current rating.
         *
         * @return  The stored double rating value
         */
        std::double_t getRating() const;

        /**
         * @brief Retrieves the web address.
         *
         * @return  A constant reference to the stored address string
         */
        const std::string& getAddress() const;

        /**
         * @brief Retrieves the text content.
         *
         * @return  A constant reference to the stored content string
         */
        const std::string& getContent() const;

        /**
         * @brief Updates the cached rating of the web content.
         *
         * @param[in] newRating  The new double rating score to set
         * @return               true on success, false on failure (optional)
         */
        bool setRating(std::double_t& newRating);

        /**
         * @brief Updates the stored text content value.
         *
         * @param[in] newContent  The new string content 
         * @return                true on success, false on failure (optional)
         */
        bool setContent(const std::string& newContent);
};

#endif //WEB_CONTENT_HPP