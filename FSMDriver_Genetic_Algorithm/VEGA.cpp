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

	this->track1 = getResults(myID);

}

std::vector<float> Host::getResults(int memoryID){
	char* shared_memory;	//for communication between TORCS and GA
	/* Reattach the shared memory segment, at a different address. */
	shared_memory = (char*) shmat (memoryID, (void*) 0x5000000, 0);
	//result = atof(shared_memory);
	string temp(shared_memory);

	float total_time = 0;
	float raced_dist = 0;
	float damage = 0;
	if(temp.length() > 0)
	{
		unsigned pos2 = temp.find(' ');
		unsigned pos3 = temp.substr(pos2+1).find(' ');
		total_time = stof(temp.substr(0, pos2));
		damage = stof(temp.substr(pos2+1,pos3));
		raced_dist = stof(temp.substr(pos2+pos3+1));
	}
	cout << "total_time: " << total_time << endl;
	cout << "damage: " << damage << endl;
	cout << "raced_dist: " << raced_dist << endl;
	vector<float> results = { total_time, raced_dist, damage };
	/* Detach the shared memory segment. */
	shmdt (shared_memory);

	/* Deallocate the shared memory segment. */
	shmctl (memoryID, IPC_RMID, 0);

	this->setFitness(raced_dist);
	return results;
}


string Host::SharedMemory(){
	int segment_id;
	const int shared_segment_size = 0xC;//0x6400;

	/* Allocate a shared memory segment. */
	segment_id = shmget (IPC_PRIVATE, shared_segment_size,IPC_CREAT|IPC_EXCL|S_IRUSR|S_IWUSR);


	return(to_string(segment_id));
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
