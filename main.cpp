#include "EvolutionModel.hpp"
#include <iostream>

int main() {
    EvolutionModel model("AGCTGATCG", 0.01, 0.01, 0.01);  // Rates for substitution, insertion, deletion
    for (int i=0; i<1000; i++) {
        model.simulateEvolution();
        std::cout << "Evolved sequence: " << model.getSequence() << std::endl;
    }

    return 0;
}

