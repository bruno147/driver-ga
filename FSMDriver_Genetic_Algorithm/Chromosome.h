#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <string>
#include <bitset>
#include <vector>
#include <cstdlib>

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
	virtual void runTest(std::string,int) = 0;
	//! mehtod set for genes
	inline void setBits(std::string bits) {
		this->bits = bits;
	}
	inline void resetFitness() {
		this->fitness = 0;
	}
	//! method get for genes
	inline std::string getBits() const {
		return this->bits;
	}
	//! method set for fitness
	inline void setFitness(float fitness) {
		this->fitness += fitness;
	}
	//! method get for fitness
	inline float getFitness() const {
		return this->fitness;
	}
	//!	Overload the relational operator <
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
};

#endif // CHROMOSOME_H
