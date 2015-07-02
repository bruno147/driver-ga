#include "Individual.h"
//For shared memory
#include <sys/shm.h>
#include <sys/stat.h>
#include <cstdlib>

using namespace std;

//--------------------------------------------------------------------------
//Auxiliary methods
string getPortNumber(int p) {
	p += 3000;
	return to_string(p);
}

//Return the path in where .xml of the tracks are located
string getTrackPath() {
	string binPath(boost::filesystem::current_path().native());
	unsigned pos = binPath.find("bin");
	string trackPath( binPath.substr(0,pos) + "configs/" );
	return trackPath;
}
//Clear any remaining attatchments in the ports
void clearPorts() {
	for (int i = 0; i < 10; ++i) {
		string fuser("fuser -k ");
		fuser += getPortNumber(i+1) + "/udp";
		if(system(fuser.c_str()) == -1) cout << "ERROR" << endl;
	}
}

//-----------------------------------------------------------------------
//Class Individual methods definition
string	Individual::getRandomBits (int length) {
	string bits;

	for (int i = 0; i < length; i++) {
		if (RANDOM_NUMBER > 0.5f)
			bits += "1";
		else
			bits += "0";
	}

	return bits;
}

void Individual::runTest(const std::vector<string>& setOfTracks) {
	unsigned int numberOfTracks = setOfTracks.size();
	string trackPath = getTrackPath();
	//Vector of memory IDs
	vector<string> strID = getMemoryID(setOfTracks.size());
	// Commands that are going to be joined by a system call
	string command1, command2;

	//This loop allows tests to be hold simultaneously in different tracks reducing computational time needed.
	for (unsigned int k = 0; k < numberOfTracks/MAX_SIMULTANEOUS_TESTS + 1; k++) {
		if (k == numberOfTracks/MAX_SIMULTANEOUS_TESTS) {
			for (unsigned int i = 0; i < numberOfTracks%MAX_SIMULTANEOUS_TESTS ; i++) {
				command1 += "torcs -r " + trackPath + setOfTracks.at(i) + ".xml & ";
				command2 += "./FSMDriver " + bits + " " + strID.at(i) + " port:" + getPortNumber(i+1) + " maxSteps:10000";

				if(i < numberOfTracks%MAX_SIMULTANEOUS_TESTS - 1)
					command2 += " & ";
			}
		}
		else {
			for (unsigned int i = 0; i < MAX_SIMULTANEOUS_TESTS ; i++) {
				command1 += "torcs -r " + trackPath + setOfTracks.at(i) + ".xml & ";
				command2 += "./FSMDriver " + bits + " " + strID.at(i) + " port:" + getPortNumber(i+1) + " maxSteps:10000";

				if(i < MAX_SIMULTANEOUS_TESTS - 1)
					command2 += " & ";
			}
		}
	}

	clearPorts();

	//Run the commands in the terminal via system call
	if(system(command1.c_str()) == -1)	cout << "ERROR" << endl;
	if(system(command2.c_str()) == -1)	cout << "ERROR" << endl;

	command1.clear();
	command2.clear();
	//Get the results generated and set them as the individual fitness
	retrieveResults(strID);
}

void Individual::retrieveResults(const vector<string>& memoriesIDs) {

	for(unsigned int i = 0; i < memoriesIDs.size(); ++i)
	{
		int memoryID = stoi(memoriesIDs.at(i));

		float* shared_memory;	// for communication between TORCS and GA
		/* Reattach the shared memory segment, at a different address. */
		shared_memory = (float*) shmat (memoryID, NULL, 0);

		//Shared memory stores a float pointer, it can cointain more than one number
		//In this case we have only a single number
		float fitness = shared_memory[0];

		cout << "Race: " << i << endl;
		cout << "fitness: " << fitness << endl;

		/* Detach the shared memory segment. */
		shmdt (shared_memory);

		/* Deallocate the shared memory segment. */
		shmctl (memoryID, IPC_RMID, 0);

		this->setFitness(fitness);
	}
}

std::vector<string> Individual::getMemoryID(int numberOfMemories) {
	std::vector<string> memoriesIDs;
	for (int i = 0; i < numberOfMemories; ++i)
	{
		int segment_id;
		//Defining space for storing a float number
		const int shared_segment_size = sizeof(float);

		/* Allocate a shared memory segment. */
		segment_id = shmget (IPC_PRIVATE, shared_segment_size,IPC_CREAT|IPC_EXCL|S_IRUSR|S_IWUSR);

		memoriesIDs.push_back(to_string(segment_id));
	}

	return memoriesIDs;
}

