#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

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


//--------------------------------------------------------------------------------
//Class Individual declaration
class Individual: public Chromosome {
	public:
		//Build an individual with random chromossome
		Individual() {
			bits = getRandomBits(CHROMOSOME_LENGTH);
		}
		//Build an individual with specific chromossome and fitness
		Individual(std::string in_bits, float in_fitness) {
			bits = in_bits;
			fitness = in_fitness;
		}

		//Method for allocating memory segments for the driver to save its results.
		//it returns the IDs of the spaces allocated.
		std::vector<std::string> getMemoryID(int);

		//Method that access previous allocated memory IDs and retrieve its information
		//it has a internal call of setFitness(float)
		void retrieveResults(const std::vector<std::string>& memoriesID);

		
		//Method that acctually tests each individual in TORCS environment for a set of tracks
		virtual void runTest(const std::vector<std::string>& setOfTracks);

		std::string  getRandomBits(int length);	
		
		inline bool operator<(const Individual& rhs) {
			// overloaded operator that is used in merge sort
			if(this->getFitness() > rhs.getFitness())
				return true;
			else
				return false;
		}
	};


#endif // INDIVIDUAL_H
