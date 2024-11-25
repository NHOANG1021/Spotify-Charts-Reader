#include "artistList.hpp"
#include <iostream>

// Constructor
Artist::Artist(const std::string& artist_id, const std::string& artist_name, int total_followers, std::string genres[Artist::max_genres], int popularity)
    : artist_id(artist_id), artist_name(artist_name), total_followers(total_followers), popularity(popularity) {
    for (std::size_t i = 0; i < max_genres; ++i) {
        this->genres[i] = genres[i];
    }
}

// Print an artist record
void Artist::printArtist() const {
    std::cout << "Artist ID: " << artist_id << "\n";
    std::cout << "Artist Name: " << artist_name << "\n";
    std::cout << "Total Followers: " << total_followers << "\n";
    std::cout << "Genres: ";
    for (std::size_t i = 0; i < max_genres; ++i) {
        if (!genres[i].empty()) {
            std::cout << genres[i];
            if (i < max_genres - 1 && !genres[i + 1].empty()) {
                std::cout << ", ";
            }
        }
    }
    std::cout << "\n";
    std::cout << "Popularity: " << popularity << "\n";
}

// Get artist name
const std::string& Artist::name() const {
    return artist_name;
}

// Get artist ID
const std::string& Artist::id() const {
    return artist_id;
}
