#include "EvolutionModel.hpp"
#include <iostream>
EvolutionModel::EvolutionModel(const std::string& initialSequence, double subRate, double insRate, double delRate)
        : dna(initialSequence), substitutionRate(subRate), insertionRate(insRate), deletionRate(delRate), generator(std::random_device{}()) {
            std::cout << "Constructed with initial sequence: " << initialSequence << std::endl;
            std::cout << "Substitution rate: " << substitutionRate << std::endl;
            std::cout << "Insertion rate: " << insertionRate << std::endl;
            std::cout << "Deletion rate: " << deletionRate << std::endl;
            }

void EvolutionModel::simulateEvolution() {
    double timeSubstitution = generateExponentialTime(substitutionRate);
    double timeInsertion = generateExponentialTime(insertionRate);
    double timeDeletion = generateExponentialTime(deletionRate);

    if (timeSubstitution < timeInsertion && timeSubstitution < timeDeletion) {
        performSubstitution();
    } else if (timeInsertion < timeDeletion) {
        performInsertion();
    } else {
        performDeletion();
    }
}

char EvolutionModel::randomNucleotide() {
    std::array<char, 4> nucleotides = {'A', 'G', 'C', 'T'};
    std::uniform_int_distribution<> dist(0, 3);
    return nucleotides[dist(generator)];
}

void EvolutionModel::performDeletion() {
    if (dna.getSequence().size() == 0) return;
    std::uniform_int_distribution<> dis(0, (int)dna.getSequence().size() - 1);
    int position = dis(generator);
    dna.deleteBase(position);
}

double EvolutionModel::generateExponentialTime(double rate) {
    std::exponential_distribution<> expDist(rate);
    return expDist(generator);
}
std::string EvolutionModel::getSequence() const {
    return dna.getSequence();  // Assuming dna is a DNASequence object and getSequence is a public method
}
void EvolutionModel::performSubstitution() {
    if (dna.getSequence().empty()) return;
    std::uniform_int_distribution<> dis(0, (int)dna.getSequence().size() - 1);
    int position = dis(generator);
    char newBase = randomNucleotide();  // Assuming randomNucleotide() is a member method
    dna.substituteBase(position, newBase);
}

void EvolutionModel::performInsertion() {
    std::uniform_int_distribution<> dis(0, (int)dna.getSequence().size());
    int position = dis(generator);
    char newBase = randomNucleotide();  // Assuming randomNucleotide() is a member method
    dna.insertBase(position, newBase);
}
