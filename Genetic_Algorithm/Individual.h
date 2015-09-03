#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "Chromosome.h"
#include "GaAdapter.h"

//--------------------------------------------------------------------------------
/**Class Individual declaration, it's data and operations like creating a chromossome can be found here
*/
class Individual: public Chromosome, public GaAdapter {
	public:
		/**Build an individual with random chromossome
		*/
		Individual() {
			bits = getRandomBits(CHROMOSOME_LENGTH);
		}
		/**Build an individual with specific chromossome and fitness
		*/
		Individual(std::string in_bits, float in_fitness) {
			bits = in_bits;
			fitness = in_fitness;
		}
		/**Function that actually tests the individual
		*/
		virtual void runTest(const std::vector<std::string>& additionalParameters = {});
		/**Returns a string with lenght size of random bits 
		*/
		std::string  getRandomBits(int length);	
		/**Overloaded operator that is used in merge sort
		*/
		inline bool operator<(const Individual& rhs) {
			if(this->getFitness() > rhs.getFitness())
				return true;
			else
				return false;
		}
	};


#endif // INDIVIDUAL_H
