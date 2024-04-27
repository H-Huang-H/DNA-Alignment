#ifndef Nucleotide_hpp
#define Nucleotide_hpp

#include <set>


class Nucleotide {

    public:
                                Nucleotide(void);
        Nucleotide*             getLft(void) { return lft; }
        Nucleotide*             getRht(void) { return rht; }
        Nucleotide*             getAnc(void) { return anc; }
        std::set<Nucleotide*>&  getDes(void) { return des; }
        int                     getNucleotide(void) { return nucleotide; }
        void                    setLft(Nucleotide* p) { lft = p; }
        void                    setRht(Nucleotide* p) { rht = p; }
        void                    setAnc(Nucleotide* p) { anc = p; }
        void                    setNucleotide(int x) { nucleotide = x; }
        void                    addDescendant(Nucleotide* p) { des.insert(p); }
        void                    removeDescendant(Nucleotide* p) { des.erase(p); }
        void                    removeAllDescendants(void) { des.clear(); }
    
    private:
        Nucleotide*             lft;
        Nucleotide*             rht;
        Nucleotide*             anc;
        std::set<Nucleotide*>   des;
        int                     nucleotide;
};

#endif
