#include "../include/artistList.hpp"
#include <istream>
#include <iostream>
#include <sstream>
#include <string>

static void parse_genres(std::istream & file, std::string genres[Artist::max_genres]) {
    std::string temp;

    std::getline(file, temp, '[');
    std::getline(file, temp, ']');

    auto genre_idx = 0u;
    for(auto start = 0u; start < temp.size() and genre_idx < Artist::max_genres; ){
        auto start_quote = temp.find_first_of('\'', start) + 1;
        auto end_quote = temp.find_first_of('\'', start_quote);
        
        genres[genre_idx] = temp.substr(start_quote, end_quote - start_quote);
        ++genre_idx;

        start = end_quote + 1;
    }
    
    while(genre_idx < Artist::max_genres){
        genres[genre_idx] = "";
        ++genre_idx;
    }
}

// parse_csv function to read and process each line in the CSV file
ArtistList parse_csv(std::istream& file) {

    ArtistList artist_list;  // The list to be returned

    std::string line;
    std::getline(file, line);  // Skip header line

    while (std::getline(file, line)) {
        std::stringstream line_stream(line);
        std::string artist_id, artist_name, total_followers_str, popularity_str;
        int total_followers, popularity;
        std::string genres[Artist::max_genres];

        // Parse each field by reading up to the next comma
        std::getline(line_stream, artist_id, ',');
        std::getline(line_stream, artist_name, ',');
        std::getline(line_stream, total_followers_str, ',');
        parse_genres(line_stream, genres);
        size_t last_comma = line.find_last_of(',');
        popularity_str = line.substr(last_comma + 1);

        total_followers = std::stoi(total_followers_str);
        popularity = std::stoi(popularity_str);
        
        Artist artist(artist_id, artist_name, total_followers, genres, popularity);
        artist_list.appendArtist(artist);
    }

    return artist_list;
}
