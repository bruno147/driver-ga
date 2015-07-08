/* * * * * * * * * * * * * * * * * * DriverGeneticAlgorithm.h * * * * * * * * * * * * * * * * * */
/* 																								*/
/* Auxiliary Library of a Genetic Algorithm to evolve the racing parameters of FSMDriver [TORCS]*/
/* GitHub Repository: (https://github.com/bruno147/fsmdriver)									*/
/* 																								*/
/* Code derived from, and inspired by, AI junkie (www.ai-junkie.com)							*/
/* 																								*/
/* * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	*/

#ifndef DRIVERGENETICALGORITHM_H
#define DRIVERGENETICALGORITHM_H

#include "Individual.h"

class DriverGeneticAlgorithm {
private:
	/** Keep track of generation number
	*/
	int generationCount;
	/**Stores the best individual so far
        */
	Individual bestIndividual;
	/**The set of tracks being tested
        */
	std::vector<std::string> setOfTracks;
public:
	/**Constructor
	*/
	DriverGeneticAlgorithm(std::vector<std::string> setOfTracks) : generationCount(0), setOfTracks(setOfTracks) {};
	/**GA main method
	*/
	void run();
	/**Method for testing each individual in the population
	* @param Population, the individuals set at each generation 
        */
	void evaluatePopulation(std::vector<Individual> &Population);
	/**Method for applying crossover and mutation to the population	
	* @param data is a set of indivuals
	*/
	std::vector<Individual> updatePopulation(std::vector<Individual> &data);
	/**Uniform Crossover method
	* @param offspring1 is one individual to take part of cross-over
	* @param offspring2 is the individual to take part of cross-over
	* @return a new population created by mutation of the offsprings and cross-over 
	*/ 
	void uniformCrossover(Individual &offspring1, Individual &offspring2);
	/**One-point crossover method
	* @param offspring1 is one individual to take part of cross-over
	* @param offspring2 is the individual to take part of cross-over
	*/
	void onePointCrossover(Individual &offspring1, Individual &offspring2);
	/**Method for writting a file with the generation log
	* @param generation, a counter of generation
	* @param Population, the individuals set at each generation
	* @param bestChromosome is the induvidual who has the higher fitness or rank at the population 
	*/
	void generateLog(int generation, std::vector<Individual> Population, Individual bestChromosome);
	/**Method used for ordenating the individuals
 	* @param data is a set of indivuals
	* @return a ordenation set of indivuduals
	*/
	std::vector<Individual> merge_sort(const std::vector<Individual> &data);
	/**Convert binary to hexadecimal
	* @param rowresult is the string of bits of one population individual
	* @return the hexadixal value of the string of bits received 
	*/
	std::string binToHex(std::string rowresult);
	/**Convert blocks of binary to a single hexadecimal character
	* @param str is string of binary values that describe a individual
	* @return the hexadeximal representation of a individual 
	*/
	char getHexCharacter(std::string str);
	/**Remove a randon individual from the population
	* @param Population, the individuals set at each generation
	* @return the individual removed
	*/
	Individual pool(const std::vector<Individual> &population);
	/**Convert hexadecimal to binary
        * @param sHex is string of hexadeximal values that describe a individual
	* @return the binary representation of a individual 
	*/
	std::string hexToBin (std::string sHex);
	/**Print the current status in evolution.
	* @param generation, a counter of generation
	* @param individualNumber is the individual conter
	*/
	void status(int generation, int indivualNumber);

};

#endif // DRIVERGENETICALGORITHM_H
