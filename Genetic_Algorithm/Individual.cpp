#include "Individual.h"

//-----------------------------------------------------------------------
//Class Individual methods definition
std::string	Individual::getRandomBits (int length) {
	std::string bits;

	for (int i = 0; i < length; i++) {
		if (RANDOM_NUMBER > 0.5f)
			bits += "1";
		else
			bits += "0";
	}

	return bits;
}

void Individual::runTest(const std::vector<std::string>& additionalParameters) {
	callTest(additionalParameters,this);
}
