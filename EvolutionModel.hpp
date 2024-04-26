#ifndef EVOLUTIONMODEL_HPP
#define EVOLUTIONMODEL_HPP

#include "DNASequence.hpp"
#include <random>

class EvolutionModel {
public:
    EvolutionModel(const std::string& initialSequence, double subRate, double insRate, double delRate);
    void simulateEvolution();
    std::string getSequence() const;


private:
    DNASequence dna;
    double substitutionRate;
    double insertionRate;
    double deletionRate;
    std::mt19937 generator;

    void performSubstitution();
    void performInsertion();
    void performDeletion();
    double generateExponentialTime(double rate);
    char randomNucleotide();
};

#endif // EVOLUTIONMODEL_HPP
