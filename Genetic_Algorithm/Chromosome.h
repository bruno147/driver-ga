#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <string>
#include <bitset>
#include <vector>
#include <cstdlib>

//GA parameters
#define CROSSOVER_RATE 0.95	// Rate defined by Núnez-Letamendia
#define MUTATION_RATE 0.01 	// Rate defined by Núnez-Letamendia
#define POPULATION_SIZE 30	// Must be an EVEN number
#define GENE_LENGTH 32
#define MAX_ALLOWABLE_GENERATIONS 616 //Calculated using A LANDER , J. 1992. On optimal population size of genetic algorithms.
#define NUMBER_OF_PARAMETERS 17	// Number of parameters to be evolved
#define CHROMOSOME_LENGTH GENE_LENGTH * NUMBER_OF_PARAMETERS
#define CHROMOSOME_TO_PRESERVE 4			// Must be an EVEN number
#define PARENTS_TO_BE_CHOSEN 10

//! @def Calculates a randon number between 0.0 and 1.0
#define RANDOM_NUMBER ((float)rand()/(RAND_MAX))

/**
 * @class Chromossome
 * @brief Definition of the Chromosome's class: In this case, a binary std::string
 * @details Class that defines a chromossome object, simbolizes a especimen of an population, used in GA
 *
 * @param bits genes of chromossome
 * @param fitness is a measure of how good that chromosome is at solving the problem
 */
class Chromosome {
protected:
	std::string	bits; /**< binary std::string for the Data Structure*/
	float	fitness;  /**< float number for the Fitness Score (metric analysis)*/

public:
	//! Constructor
	/**
	 * @brief Create a object default
	 * @details Constructor, initialize a chromossome with parameters default
	 */
	Chromosome();
	/**
	 * @brief Crete a object with predetermined params
	 * @details Constructor, initialize a chromossome with predetermined bits and fitness
	 * 
	 * @param in_bits bits of chromossome, genes
	 * @param in_fitness [description]
	 */
	Chromosome(std::string in_bits, float in_fitness); /**< Constructor*/

	//!	Test the chromossome
	/**
	 * @brief Test the chromossome in the simulator
	 * @details Calls the simulator and the Driver with chromossome, run 
	 * 
	 * @param  chromossome
	 */
	virtual void runTest(const std::vector<std::string>& addtionalParameters) = 0;
	/** method set for genes
	*@param bits is a string of the chrmossome representation 
	*/
	inline void setBits(std::string bits) {
		this->bits = bits;
	}
	/** method for redefining an individual fitness
	*/
	inline void resetFitness() {
		this->fitness = 0;
	}
	/** method get for genes
	*/
	inline std::string getBits() const {
		return this->bits;
	}
	/** method set for fitness
	*/
	inline void setFitness(float fitness) {
		this->fitness += fitness;
	}
	/** method get for fitness
	*/
	inline float getFitness() const {
		return this->fitness;
	}
	/** Overload the relational operator <
	*/
	inline bool operator<(const Chromosome& _c) {
		return this->fitness < _c.getFitness()? true:false;
	}
	/**
	 * @brief Convert base-2 to base-10
	 * @details Convert bits base-2 to base-10 floating point
	 * 
	 * @param bits chromossome base-2
	 * @return chromossome base-10
	 */
	float	binToFloat(std::string bits);
	/**
	 * @brief Convert base-10 to base-2
	 * @details Convert bits base-10, floating point, to base-2
	 * 
	 * @param bits chromossome base-10
	 * @return chromossome base-2
	 */
	std::string	floatToBin(float value);

	/**Mutate a chromossome, that means that if a specific bit is '1' it wil turn '0', if it is '0' it will turn '1'
	*/
	void mutate();
};

#endif // CHROMOSOME_H
