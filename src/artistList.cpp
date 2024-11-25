#include "artistList.hpp"
#include <iostream>

// ArtistEntry Constructor
ArtistList::ArtistEntry::ArtistEntry(ArtistList* list, const Artist& a)
    : list(list), next(nullptr), prev(nullptr), artist(a) {}

// ArtistList Constructor
ArtistList::ArtistList() : length(0), first(nullptr), last(nullptr) {}

// Copy Constructor
ArtistList::ArtistList(const ArtistList& list) : length(0), first(nullptr), last(nullptr) {
    ArtistEntry* current = list.first;
    while (current) {
        appendArtist(current->artist);
        current = current->next;
    }
}

// Destructor
ArtistList::~ArtistList() noexcept {
    while (!is_empty()) {
        removeFirstArtist();
    }
}

// Size of list
std::size_t ArtistList::size() const {
    return length;
}

// Check if list is empty
bool ArtistList::is_empty() const {
    return length == 0;
}

// Prepend artist to the list
void ArtistList::prependArtist(const Artist& a) {
    ArtistEntry* newEntry = new ArtistEntry(this, a);
    newEntry->next = first;

    if (first) {
        first->prev = newEntry;
    }
    first = newEntry;

    if (!last) {
        last = newEntry;
    }
    ++length;
}

// Append artist to the list
void ArtistList::appendArtist(const Artist& a) {
    ArtistEntry* newEntry = new ArtistEntry(this, a);
    newEntry->prev = last;

    if (last) {
        last->next = newEntry;
    }
    last = newEntry;

    if (!first) {
        first = newEntry;
    }
    ++length;
}

// Remove first artist
void ArtistList::removeFirstArtist() {
    if (!first) return;

    ArtistEntry* temp = first;
    first = first->next;
    if (first) {
        first->prev = nullptr;
    } else {
        last = nullptr;
    }
    delete temp;
    --length;
}

// Remove last artist
void ArtistList::removeLastArtist() {
    if (!last) return;

    ArtistEntry* temp = last;
    last = last->prev;
    if (last) {
        last->next = nullptr;
    } else {
        first = nullptr;
    }
    delete temp;
    --length;
}

// Print the artist list
void ArtistList::printArtistList() const {
    ArtistEntry* current = first;
    while (current) {
        current->artist.printArtist();
        current = current->next;
    }
}

// Find artist by name
Artist* ArtistList::findArtistName(const std::string& name) const {
    ArtistEntry* current = first;
    while (current) {
        if (current->artist.name() == name) {
            return &(current->artist);
        }
        current = current->next;
    }
    return nullptr;
}

// Remove artist by name
void ArtistList::removeArtistbyName(const std::string& name) {
    ArtistEntry* current = first;
    while (current) {
        if (current->artist.name() == name) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                first = current->next;
            }

            if (current->next) {
                current->next->prev = current->prev;
            } else {
                last = current->prev;
            }

            delete current;
            --length;
            return;
        }
        current = current->next;
    }
}

// Insert artist at a specific index
void ArtistList::insertArtistAt(std::size_t index, const Artist& artist) {
    if (index > length) return;

    if (index == 0) {
        prependArtist(artist);
        return;
    } else if (index == length) {
        appendArtist(artist);
        return;
    }

    ArtistEntry* current = first;
    for (std::size_t i = 0; i < index; ++i) {
        current = current->next;
    }

    ArtistEntry* newEntry = new ArtistEntry(this, artist);
    newEntry->next = current;
    newEntry->prev = current->prev;

    if (current->prev) {
        current->prev->next = newEntry;
    }
    current->prev = newEntry;

    ++length;
}

// Access artist at index
Artist* ArtistList::at(size_t index) {
    if (index >= length) return nullptr;

    ArtistEntry* current = first;
    for (std::size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return &current->artist;
}

const Artist* ArtistList::at(size_t index) const {
    if (index >= length) return nullptr;

    ArtistEntry* current = first;
    for (std::size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return &current->artist;
}

// Access first artist
Artist* ArtistList::firstArtist() {
    return first ? &first->artist : nullptr;
}

const Artist* ArtistList::firstArtist() const {
    return first ? &first->artist : nullptr;
}

// Access last artist
Artist* ArtistList::lastArtist() {
    return last ? &last->artist : nullptr;
}

const Artist* ArtistList::lastArtist() const {
    return last ? &last->artist : nullptr;
}
