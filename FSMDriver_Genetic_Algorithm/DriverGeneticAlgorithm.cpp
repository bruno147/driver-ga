/* * * * * * * * * * * * * * * * * * DriverGeneticAlgorithm.cpp * * * * * * * * * * * * * * * * */
/* 																								*/
/* Implementation of a Genetic Algorithm to evolve the racing parameters of FSMDriver [TORCS]	*/
/* GitHub Repository: (https://github.com/bruno147/fsmdriver)									*/
/* 																								*/
/* Code derived from, and inspired by, AI junkie (www.ai-junkie.com)							*/
/* 																								*/
/* * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	*/


#include "DriverGeneticAlgorithm.h"

using	namespace std;

// Chromosome generation process (Main Method)
int main (int argc, char* argv[]) {
	if(POPULATION_SIZE%2) {
		cout << "ERROR\nPOPULATION_SIZE must be an even number\n";
		return 0;
	}
	vector<string> setOfTracks = {"spring","wheel2","etrack3","forza"};
	DriverGeneticAlgorithm ga(setOfTracks);
	ga.run();
	return 0;
}


//------------------------------------------------------------------------
// GA Methods (Implementations)
void DriverGeneticAlgorithm::run() {
	// Random number generator's seeder
	srand ((int)time(NULL));

	//flag
	bool	evolved			= false;

	//Initialize a random population
	vector<Individual> Population;
	for (int i = 0; i < POPULATION_SIZE; i++) Population.push_back(Individual());

	// Genetic Algorithm actual loop
	while (!evolved) {

		evaluatePopulation(Population);

		//sort the population and store best individual
		Population = merge_sort(Population);
		bestIndividual = Population[0];

		//Records the current population into logfile
		generateLog(generationCount, Population, bestIndividual);
		
		//Aplly crossover and mutation
		Population = updatePopulation(Population);

		cout << endl << endl;
		cout << "Generation " << generationCount+1 << " complete." << "  || " <<"Generation " << generationCount+1 << " complete." << "  || " <<"Generation " << generationCount+1 << " complete." << endl;

		++generationCount;

		// If the maximum number of generations is reached, ends program
		if (generationCount >= MAX_ALLOWABLE_GENERATIONS) {
			cout << "Maximum allowable generations reached! Chromosome evolved." << endl;
			evolved = true;
		}
	}

}

void DriverGeneticAlgorithm::evaluatePopulation(vector<Individual> &Population) {
	for (unsigned int i = 0; i < POPULATION_SIZE; ++i){
		if (Population[i].getFitness() == 0) {
			status(generationCount, i);
			Population[i].runTest(setOfTracks);
		}
	}
}

vector<Individual> DriverGeneticAlgorithm::updatePopulation(vector<Individual> &data) {
	// Creates new population members through crossover and/or mutation (by chance)
	vector<Individual>	newPopulation(data);
	int populationCounter = CHROMOSOME_TO_PRESERVE;
	while (populationCounter < POPULATION_SIZE) {
		// Selects 2 new members to apply crossover and mutation

		Individual offspring1 = pool(data);
		Individual offspring2 = pool(data);

		onePointCrossover(offspring1, offspring2);

		offspring1.mutate();
		offspring1.resetFitness();
		offspring2.mutate();
		offspring2.resetFitness();
		// Replaces the old members for the new ones
		newPopulation[populationCounter++] = offspring1;
		newPopulation[populationCounter++] = offspring2;	
	}
	return newPopulation;
}

void DriverGeneticAlgorithm::onePointCrossover (Individual &offspring1, Individual &offspring2) {
	if (RANDOM_NUMBER < CROSSOVER_RATE) {
	    // Randomic choice of the crossover point
	    int crossover 	= (int) (RANDOM_NUMBER * CHROMOSOME_LENGTH);

	    string new1		= (offspring1.getBits()).substr (0, crossover) + (offspring2.getBits()).substr (crossover, CHROMOSOME_LENGTH);
	    string new2		= (offspring2.getBits()).substr (0, crossover) + (offspring1.getBits()).substr (crossover, CHROMOSOME_LENGTH);

	    offspring1.setBits(new1);
	    offspring2.setBits(new2);
	}			  
}


void DriverGeneticAlgorithm::uniformCrossover (Individual &offspring1, Individual &offspring2) {
	if (RANDOM_NUMBER < CROSSOVER_RATE) {
		Individual mask1, mask2;
	  	string new1, new2;

	  	for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
	  		if (mask1.getBits().at(i) == '0')
	  			new1.push_back(offspring1.getBits().at(i));
	  		else
	  			new1.push_back(offspring2.getBits().at(i));
	  	}

	  	for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
	  		if (mask2.getBits().at(i) == '0')
	  			new2.push_back(offspring1.getBits().at(i));
	  		else
	  			new2.push_back(offspring2.getBits().at(i));
	  	}

	    offspring1.setBits(new1);
	    offspring2.setBits(new2);
	}			  
}

void DriverGeneticAlgorithm::generateLog(int generation, vector<Individual> Population, Individual bestIndividual){
	ofstream logFile;
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    logFile.open("log.txt", std::ios_base::app);


    //only for generation 0
   
    if(generation==0){
    	logFile << "Genetic Algorithm at " << asctime(timeinfo) << endl;
	    logFile << "TRACKS: ";
        for(unsigned int i = 0; i < setOfTracks.size(); ++i)
        {
            logFile << setOfTracks.at(i) << ", ";
        }
        logFile << endl;
    	logFile << "Parameters:" << endl;
    	logFile << "CROSSOVER_RATE: " << CROSSOVER_RATE << endl;
    	logFile << "MUTATION_RATE: " << MUTATION_RATE << endl;
    	logFile << "POPULATION_SIZE: " << POPULATION_SIZE << endl;
    	logFile << "MAX_ALLOWABLE_GENERATIONS: " << MAX_ALLOWABLE_GENERATIONS << endl;

    	logFile << "CHROMOSOME_TO_PRESERVE: " << CHROMOSOME_TO_PRESERVE << endl;
    	logFile << "PARENTS_TO_BE_CHOSEN: " << PARENTS_TO_BE_CHOSEN << endl;

    	logFile << endl << endl;
    }

    logFile << endl << endl;
    logFile << endl << "Generation " << generation << endl;
    logFile << asctime(timeinfo);
    logFile << endl << "Best Chromosome so far: " << setw(164) << endl;
    logFile << binToHex(bestIndividual.getBits()) << "\t" << bestIndividual.getFitness() << endl;
    logFile << endl << "Population: " << endl;

	for(unsigned int i=0; i < Population.size(); i++){
		logFile << binToHex(Population[i].getBits()) << "\t" << Population[i].getFitness() <<  endl;
	}

	logFile.close();
}


char DriverGeneticAlgorithm::getHexCharacter(std::string str)
{
	if(str.compare("1111") == 0) return 'F';
	else if(str.compare("1110") == 0) return 'E';
	else if(str.compare("1101")== 0) return 'D';
	else if(str.compare("1100")== 0) return 'C';
	else if(str.compare("1011")== 0) return 'B';
	else if(str.compare("1010")== 0) return 'A';
	else if(str.compare("1001")== 0) return '9';
	else if(str.compare("1000")== 0) return '8';
	else if(str.compare("0111")== 0) return '7';
	else if(str.compare("0110")== 0) return '6';
	else if(str.compare("0101")== 0) return '5';
	else if(str.compare("0100")== 0) return '4';
	else if(str.compare("0011")== 0) return '3';
	else if(str.compare("0010")== 0) return '2';
	else if(str.compare("0001")== 0) return '1';
	else if(str.compare("0000")== 0) return '0';
	else if(str.compare("111")== 0) return '7';
	else if(str.compare("110")== 0) return '6';
	else if(str.compare("101")== 0) return '5';
	else if(str.compare("100")== 0) return '4';
	else if(str.compare("011")== 0) return '3';
	else if(str.compare("010")== 0) return '2';
	else if(str.compare("001")== 0) return '1';
	else if(str.compare("000")== 0) return '0';
	else if(str.compare("11")== 0) return '3';
	else if(str.compare("10")== 0) return '2';
	else if(str.compare("01")== 0) return '1';
	else if(str.compare("00")== 0) return '0';
	else if(str.compare("1")== 0) return '1';
	else if(str.compare("0")== 0) return '0';
	return '0';
}


string DriverGeneticAlgorithm::hexToBin (string sHex)
{
	string sReturn = "";
	for (unsigned int i = 0; i < sHex.length (); ++i)
	{
		switch (sHex [i])
		{
			case '0': sReturn.append ("0000"); break;
			case '1': sReturn.append ("0001"); break;
			case '2': sReturn.append ("0010"); break;
			case '3': sReturn.append ("0011"); break;
			case '4': sReturn.append ("0100"); break;
			case '5': sReturn.append ("0101"); break;
			case '6': sReturn.append ("0110"); break;
			case '7': sReturn.append ("0111"); break;
			case '8': sReturn.append ("1000"); break;
			case '9': sReturn.append ("1001"); break;
			case 'A': sReturn.append ("1010"); break;
			case 'B': sReturn.append ("1011"); break;
			case 'C': sReturn.append ("1100"); break;
			case 'D': sReturn.append ("1101"); break;
			case 'E': sReturn.append ("1110"); break;
			case 'F': sReturn.append ("1111"); break;
		}
	}
	return sReturn;
}


std::string DriverGeneticAlgorithm::binToHex(string rowresult)
{
	std::string endresult = "";
	for(unsigned int i = 0; i < rowresult.length(); i = i+4)
	{
		endresult += getHexCharacter(rowresult.substr(i,4));
	}
	return endresult;
}

std::vector<Individual> DriverGeneticAlgorithm::merge_sort(const std::vector<Individual> &data)
{
	if (data.size() <= 1) {
		return data;
	}
 
	int middle = data.size() / 2;
	std::vector<Individual> left(data.begin(), data.begin()+middle);
	std::vector<Individual> right(data.begin()+middle, data.end());
 
	left = merge_sort(left);
	right = merge_sort(right);
 
	std::vector<Individual> result(data.size());
	std::merge(left.begin(), left.end(), 
	           right.begin(), right.end(),
	           result.begin());
 
	return result;
}

Individual DriverGeneticAlgorithm::pool(const std::vector<Individual> &population)
{
	return population.at( rand()%PARENTS_TO_BE_CHOSEN );
}

void DriverGeneticAlgorithm::status(int generation, int indivualNumber){
	cout << endl 
	<< "Generation: " << generation+1 << " of " << MAX_ALLOWABLE_GENERATIONS << endl
	<< "Individual: " << indivualNumber+1 << " of " << POPULATION_SIZE << endl;
	// << "Race: " << raceNumber+1 << " of " << this->track.size() << endl;
}