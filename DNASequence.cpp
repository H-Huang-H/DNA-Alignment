//
// Created by Harry on 4/19/24.
//
#include <iostream>
#include "DNASequence.hpp"
#include "Msg.hpp"
#include "Nucleotide.hpp"
#include "Probability.hpp"
#include "RandomVariable.hpp"



DNASequence::DNASequence(const DNASequence& s) {

    this->length = s.length;
    
    Nucleotide* sp = s.lftMostNucleotide;
    Nucleotide* p = nullptr;
    while (sp != nullptr)
        {
        Nucleotide* newNuc = new Nucleotide;
        if (p == nullptr)
            {
            this->lftMostNucleotide = newNuc;
            }
        else
            {
            p->setRht(newNuc);
            newNuc->setLft(p);
            }
            
        sp = sp->getRht();
        p = newNuc;
        }
}

DNASequence::DNASequence(double lambda, double mu) {

    if (lambda > mu)
        Msg::error("The insertion rate must be less than the deletion rate");
        
    RandomVariable& rng = RandomVariable::randomVariableInstance();
    length = Probability::Geometric::rv(&rng, lambda/mu);
    
    Nucleotide* p = nullptr;
    for (int i=0; i<length; i++)
        {
        Nucleotide* newNuc = new Nucleotide;
        if (p == nullptr)
            {
            lftMostNucleotide = newNuc;
            }
        else
            {
            p->setRht(newNuc);
            newNuc->setLft(p);
            }
        p = newNuc;
        }
}

DNASequence::~DNASequence(void) {

    Nucleotide* p = lftMostNucleotide;
    while (p != nullptr)
        {
        Nucleotide* prevP = p;
        p = p->getRht();
        delete prevP;
        }
}

Nucleotide* DNASequence::operator[](int idx) {

    if (idx < 0 || idx >= length)
        Msg::error("Index is out of the sequences range");
        
    int i = 0;
    Nucleotide* p = lftMostNucleotide;
    while (p != nullptr)
        {
        if (i == idx)
            break;
        p = p->getRht();
        i++;
        }
    return p;
}

DNASequence* DNASequence::evolve(double lambda, double mu, double t) {

    RandomVariable& rng = RandomVariable::randomVariableInstance();
    DNASequence* newSeq = new DNASequence(*this);
    
    double pos = 0.0;
    int iter = 0;
    while (pos < t)
        {
        std::cout <<"Step " << iter++ << std::endl;
        double rate = newSeq->getLength() * mu + (newSeq->getLength() + 1) * lambda;
        pos += Probability::Exponential::rv(&rng, rate);
        if (pos < t)
            {
            double u = rng.uniformRv();
            if (u < ((newSeq->getLength() + 1) * lambda) / rate)
                {
                // insertion event
                Nucleotide* newNuc = new Nucleotide;
                int insertionPoint = (int)(rng.uniformRv() * (newSeq->getLength()+1));
                if (insertionPoint < newSeq->getLength())
                    {
                    // insert to the left
                    Nucleotide* insertionNuc = (*newSeq)[insertionPoint];
                    std::cout << "insertionPoint = " << insertionPoint << " length = " << length << std::endl;
                    std::cout << "insertionNuc = " << insertionNuc << std::endl;
                    newNuc->setLft( insertionNuc->getLft() );
                    insertionNuc->setLft(newNuc);
                    newNuc->setRht(insertionNuc);
                    }
                else
                    {
                    // add to the end of the sequence
                    Nucleotide* lastNuc = newSeq->getLastNucleotide();
                    lastNuc->setRht(newNuc);
                    newNuc->setLft(lastNuc);
                    }
                newSeq->length++;
                }
            else
                {
                // deletion event
                int deletedNucIdx = (int)(rng.uniformRv()*newSeq->getLength());
                Nucleotide* deletedNuc = (*newSeq)[deletedNucIdx];
                if (deletedNuc->getLft() != nullptr)
                    deletedNuc->getLft()->setRht(deletedNuc->getRht());
                if (deletedNuc->getRht() != nullptr)
                    deletedNuc->getRht()->setLft(deletedNuc->getLft());
                delete deletedNuc;
                newSeq->length--;
                }
            }
        newSeq->print();
        }
    
    return newSeq;
}

Nucleotide* DNASequence::getLastNucleotide(void) {

    Nucleotide* p = lftMostNucleotide;
    while (p != nullptr)
        {
        if (p->getRht() == nullptr)
            return p;
        p = p->getRht();
        }
    return nullptr;
}

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

void DNASequence::print(void) {

    Nucleotide* p = lftMostNucleotide;
    while (p != nullptr)
        {
        std::cout << "*";
        p = p->getRht();
        }
    std::cout << " [" << length << "]" << std::endl;
}
