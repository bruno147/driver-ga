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

#include "VEGA.h"

class DriverGeneticAlgorithm {
private:
	int generation_count;
	Host bestIndividual;
	std::vector<std::string> track;
public:
	DriverGeneticAlgorithm(std::vector<std::string> tracks) : generation_count(0), track(tracks) {};
	void run();
	void    crossover(Host &offspring1, Host &offspring2);
	void log(int generation, Host population[], Host bestChromosome);
	std::vector<Host> merge_sort(const std::vector<Host> &data);
	std::string binToHex(std::string rowresult);
	char getHexCharacter(std::string str);
	Host pool(const std::vector<Host> &population);
	std::vector<float> getDataTrack(Host specimen);
	std::string hexToBin (std::string sHex);
	void status(int generation, int indivualNumber, int raceNumber);

};

#endif // DRIVERGENETICALGORITHM_H
