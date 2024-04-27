#ifndef DNASEQUENCE_HPP  // Make sure this matches
#define DNASEQUENCE_HPP  // This should define the same macro as the #ifndef checks for

#include <string>
#include <vector>
class Nucleotide;


class DNASequence {

    public:
                            DNASequence(void) = delete;
                            DNASequence(const DNASequence& s);
                            DNASequence(double lambda, double mu);
                            DNASequence(const std::string& initialSequence);
                           ~DNASequence(void);
        Nucleotide*         operator[](int idx);

        DNASequence*        evolve(double lambda, double mu, double t);
        int                 getLength(void) { return length; }
        Nucleotide*         getLastNucleotide(void);
        void                print(void);
        
        void                insertBase(int position, char base);
        void                deleteBase(int position);
        void                substituteBase(int position, char newBase);
        std::string         getSequence() const;

    private:
        std::vector<char>   sequence;
        
        Nucleotide*         lftMostNucleotide;
        int                 length;
};

#endif
