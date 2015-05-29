#include "VEGA.h"
//For shared memory
#include <sys/shm.h>
#include <sys/stat.h>
#include <cstdlib>

using namespace std;


//------------------------------------------------------------------------
//Class Virus methods definition
void Virus::runTest(string track_name) {
	cout << "testei" << endl;
}

void Virus::infection(Chromosome &host) {
	//cout << host.getChromosome()->getBits();
}

//-----------------------------------------------------------------------
//Class Host methods definition
void Host::mutate () {
	for (unsigned int i = 0; i < bits.length(); i++) {
		if (RANDOM_NUMBER < MUTATION_RATE) {
			if (bits.at(i) == '1')
				bits.at(i) = '0';
			else
				bits.at(i) = '1';
		}
	}
	return;
}

string	Host::getRandomBits (int length) {
	string bits;

	for (int i = 0; i < length; i++) {
		if (RANDOM_NUMBER > 0.5f)
			bits += "1";
		else
			bits += "0";
	}

	return bits;
}


void Host::runTest(string trackName, int testNumber) {
	string bin_path(boost::filesystem::current_path().native());
	unsigned pos = bin_path.find("bin");
	string str1 = bin_path.substr(0,pos);

	string track_path( bin_path.substr(0,pos) + "configs/" );

	track_path += trackName;

	string strID = SharedMemory();

	int myID = stoi(strID);
	string command1 = "torcs -r " + track_path + ".xml &";
	string command2 = "./FSMDriver " + bits + " " + strID + " port:300" + to_string(testNumber) + " maxSteps:10000";
	
	string fuser("fuser -k 300");
	fuser += to_string(testNumber) + "/udp";

	if(system(fuser.c_str()) == -1) cout << "ERROR" << endl;
	if(system(command1.c_str()) == -1)	cout << "ERROR" << endl;
	if(system(command2.c_str()) == -1)	cout << "ERROR" << endl;

	getResults(myID);
}

void Host::runTest(const std::vector<string>& trackNames) {
	string bin_path(boost::filesystem::current_path().native());
	unsigned pos = bin_path.find("bin");
	string str1 = bin_path.substr(0,pos);

	string track_path( bin_path.substr(0,pos) + "configs/" );

	vector<string> strID = SharedMemory(trackNames.size());

	string command1, command2;
	for (unsigned int i = 0; i < 4; ++i)
	{
		command1 += "torcs -r " + track_path + trackNames.at(i) + ".xml & ";
		command2 += "./FSMDriver " + bits + " " + strID.at(i) + " port:" + port(i+1) + " maxSteps:10000";

		if(i < 3)
		{
			command2 += " & ";
		}
	}
	for (int i = 0; i < 10; ++i)
	{
		string fuser("fuser -k ");
		fuser += port(i+1) + "/udp";
		if(system(fuser.c_str()) == -1) cout << "ERROR" << endl;
	}

	if(system(command1.c_str()) == -1)	cout << "ERROR" << endl;
	if(system(command2.c_str()) == -1)	cout << "ERROR" << endl;
	command1.clear();
	command2.clear();

	for (unsigned int i = 4; i < trackNames.size(); ++i)
	{
		command1 += "torcs -r " + track_path + trackNames.at(i) + ".xml & ";
		command2 += "./FSMDriver " + bits + " " + strID.at(i) + " port:" + port(i+1) + " maxSteps:10000";

		if(i < trackNames.size()-1)
		{
			command2 += " & ";
		}
	}
	for (int i = 0; i < 10; ++i)
	{
		string fuser("fuser -k ");
		fuser += port(i+1) + "/udp";
		if(system(fuser.c_str()) == -1) cout << "ERROR" << endl;
	}

	if(system(command1.c_str()) == -1)	cout << "ERROR" << endl;
	if(system(command2.c_str()) == -1)	cout << "ERROR" << endl;

	getResults(strID);
}

std::string Host::port(int p)
{
	p += 3000;
	return to_string(p);
}

void Host::getResults(int memoryID) {
	float* shared_memory;	//for communication between TORCS and GA
	// Reattach the shared memory segment, at a different address.
	shared_memory = (float*) shmat (memoryID, (void*) 0x5000000, 0);

	float fitness = shared_memory[0];

	cout << "fitness: " << fitness << endl;

	// Detach the shared memory segment.
	shmdt (shared_memory);

	// Deallocate the shared memory segment.
	shmctl (memoryID, IPC_RMID, 0);

	this->setFitness(fitness);
}

void Host::getResults(const vector<string>& memoriesIDs) {

	for(unsigned int i = 0; i < memoriesIDs.size(); ++i)
	{
		int memoryID = stoi(memoriesIDs.at(i));

		float* shared_memory;	// for communication between TORCS and GA
		/* Reattach the shared memory segment, at a different address. */
		shared_memory = (float*) shmat (memoryID, NULL, 0);

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

string Host::SharedMemory() {
	int segment_id;
	const int shared_segment_size = 3*sizeof(float);//0x6400;

	// Allocate a shared memory segment.
	segment_id = shmget (IPC_PRIVATE, shared_segment_size,IPC_CREAT|IPC_EXCL|S_IRUSR|S_IWUSR);


	return(to_string(segment_id));
}

std::vector<string> Host::SharedMemory(int numberOfMemories) {
	std::vector<string> memoriesIDs;
	for (int i = 0; i < numberOfMemories; ++i)
	{
		int segment_id;
		const int shared_segment_size = 3*sizeof(float);//0x6400;

		/* Allocate a shared memory segment. */
		segment_id = shmget (IPC_PRIVATE, shared_segment_size,IPC_CREAT|IPC_EXCL|S_IRUSR|S_IWUSR);

		memoriesIDs.push_back(to_string(segment_id));
	}

	return memoriesIDs;
}

string Host::hexToBin (string sHex)
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
