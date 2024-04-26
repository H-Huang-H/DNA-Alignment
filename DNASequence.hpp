#ifndef DNASEQUENCE_HPP  // Make sure this matches
#define DNASEQUENCE_HPP  // This should define the same macro as the #ifndef checks for

#include <string>
#include <vector>

class DNASequence {
public:
    DNASequence(const std::string& initialSequence);
    void insertBase(int position, char base);
    void deleteBase(int position);
    void substituteBase(int position, char newBase);
    std::string getSequence() const;

private:
    std::vector<char> sequence;
};

#endif
