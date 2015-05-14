#include "Chromosome.h"

using namespace std;


Chromosome::Chromosome(): bits(""), fitness(0.0f) {}
Chromosome::Chromosome(std::string in_bits, float in_fitness = 0): bits(in_bits), fitness(in_fitness) {}

//--------------------------------------------------------------------
//Class Chromossome methods definition
float Chromosome::binToFloat (string bits) {
	bitset<32> a (bits);
	float *value = reinterpret_cast<float*>(&a);

	return *value;
}


string Chromosome::floatToBin (float value) {
	int bit = 0;
	string bits;
	int *b = reinterpret_cast<int*>(&value);

	for (int k = 31; k >=0; k--) {
		bit = ((*b >> k)&1);
		bits += to_string (bit);
	}

	return bits;
}
