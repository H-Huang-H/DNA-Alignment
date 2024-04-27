#include "EvolutionModel.hpp"
#include <iostream>
#include "DNASequence.hpp"



int main() {

    
    DNASequence seq(10.0, 10.2);
    seq.print();
    
    DNASequence* seq2 = seq.evolve(10.0, 10.0, 1.0);
    seq2->print();

//    EvolutionModel model("AGCTGATCG", 0.01, 0.02, 0.01);  // Rates for substitution, insertion, deletion
//    for (int i=0; i<1000; i++) {
//        model.simulateEvolution();
//        std::cout << "Evolved sequence: " << model.getSequence() << std::endl;
//    }

    return 0;
}

