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
	//Keep track of generation number
	int generationCount;
	//Stores the best individual so far
	Individual bestIndividual;
	//The set of tracks being tested
	std::vector<std::string> setOfTracks;
public:
	//Constructor
	DriverGeneticAlgorithm(std::vector<std::string> setOfTracks) : generationCount(0), setOfTracks(setOfTracks) {};
	//GA main method
	void run();
	//Method for testing each individual in the population
	void evaluatePopulation(std::vector<Individual> &Population);
	//Method for applying crossover and mutation to the population
	std::vector<Individual> updatePopulation(std::vector<Individual> &data);
	//Uniform Crossover method 
	void uniformCrossover(Individual &offspring1, Individual &offspring2);
	//One-point crossover method
	void onePointCrossover(Individual &offspring1, Individual &offspring2);
	//Method for writting a file with the generation log
	void generateLog(int generation, std::vector<Individual> Population, Individual bestChromosome);
	//Method used for ordenating the individuals
	std::vector<Individual> merge_sort(const std::vector<Individual> &data);
	//Convert binary to hexadecimal
	std::string binToHex(std::string rowresult);
	//Convert blocks of binary to a single hexadecimal character
	char getHexCharacter(std::string str);
	//Remove a randon individual from the population
	Individual pool(const std::vector<Individual> &population);
	//Convert hexadecimal to binary
	std::string hexToBin (std::string sHex);
	//Print the current status in evolution.
	void status(int generation, int indivualNumber);

};

#endif // DRIVERGENETICALGORITHM_H
