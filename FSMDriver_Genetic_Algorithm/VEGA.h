#ifndef VEGA_H
#define VEGA_H

#include "Chromosome.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>


#define LIFE_REDUCTION_RATE 0.9
#define MAX_INFECTION_RATE 0.1
#define INITIAL_INFECTION_RATE 0.05

#define CROSSOVER_RATE 0.95	// Rate defined by Núnez-Letamendia
#define MUTATION_RATE 0.01 	// Rate defined by Núnez-Letamendia
#define POPULATION_SIZE 30	// Must be an EVEN number
#define GENE_LENGTH 32
#define MAX_ALLOWABLE_GENERATIONS 616
#define NUMBER_OF_PARAMETERS 17	// Adjust to problem needs
#define CHROMOSOME_LENGTH GENE_LENGTH * NUMBER_OF_PARAMETERS
#define CHROMOSOME_TO_PRESERVE 4			//Must be an EVEN number
#define PARENTS_TO_BE_CHOSEN 10


//-------------------------------------------------------------------------
//Class Virus declaration
class Virus : public Chromosome {
private:
	float life;
	int locus;
public:	
	Virus(std::string new_bits,float new_fitness=0){
		life = 1;
		bits = new_bits;
		fitness = new_fitness;
	}
	virtual void runTest(std::string);
	inline void updateLife() {
		this->life = this->life * LIFE_REDUCTION_RATE + this->fitness;
	}
	inline bool shouldDie() {
		return life > 0? false:true;
	}
	void infection(Chromosome &host);
};

//--------------------------------------------------------------------------------
//Class Host declaration
class Host: public Chromosome {
	private:
		std::vector<float> track1;
	public:

		Host() {
			bits = getRandomBits(CHROMOSOME_LENGTH);
		}
		Host(std::string in_bits, float in_fitness) {
			bits = in_bits;
			fitness = in_fitness;
		}
		std::string SharedMemory();
		std::vector<float> getResults(int memoryID);
		virtual void runTest(std::string trackName,int testNumber);
		void mutate();
		std::string hexToBin(std::string sHex);
		std::string  getRandomBits(int length);	
		inline void setTrack1(std::vector<float> results){
			this->track1 = results;
		}
		inline std::vector<float> getTrack1() const {
			return this->track1;
		}
		inline bool operator<(const Host& rhs) {
			// overloaded operator that is used in merge sort
			if(this->getFitness() > rhs.getFitness())
				return true;
			else
				return false;
		}
	};


#endif // VEGA_H
