//
// Created by Harry on 4/19/24.
//

#include "DNASequence.hpp"

// Constructor that initializes the sequence from a given string
DNASequence::DNASequence(const std::string& initialSequence)
        : sequence(initialSequence.begin(), initialSequence.end()) {}

// Insert a base at the specified position
void DNASequence::insertBase(int position, char base) {
    if (position < 0 || position > sequence.size()) {
        return; // Optionally add error handling or exception throwing here
    }
    sequence.insert(sequence.begin() + position, base);
}

// Delete a base at the specified position
void DNASequence::deleteBase(int position) {
    if (position < 0 || position >= sequence.size()) {
        return; // Optionally add error handling or exception throwing here
    }
    sequence.erase(sequence.begin() + position);
}

// Substitute a base at the specified position with a new base
void DNASequence::substituteBase(int position, char newBase) {
    if (position < 0 || position >= sequence.size()) {
        return; // Optionally add error handling or exception throwing here
    }
    sequence[position] = newBase;
}

// Retrieve the current sequence as a standard string
std::string DNASequence::getSequence() const {
    return std::string(sequence.begin(), sequence.end());
}
