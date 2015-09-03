#ifndef GAADAPTER_H
#define GAADAPTER_H


#define MAX_SIMULTANEOUS_TESTS 4	//Caution. 4 tests running simultaneously demmands a lot of computational resource

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

//-------------------------------------------------------------------------
/**Class GAAdapter declaration. It will handle the specific operations
between GA and TORCS
*/
class GaAdapter {
public:
	//Empty constructor
	GaAdapter(){}
	//Request and return memory IDs from the system
	std::vector<std::string> getMemoryID(int);
	//Actual test function
	void callTest(const std::vector<std::string>& setOfTracks,Chromosome*);
	//Acces the shared memory and return the results stored there
	void retrieveResults(const std::vector<std::string>& memoriesID,Chromosome*);
};

#endif // GAAAPTER_H