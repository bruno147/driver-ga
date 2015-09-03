#ifndef GADRIVER_H
#define GADRIVER_H

#include "WrapperBaseDriver.h"

//For shared memory
#include <sys/shm.h>
#include <sys/stat.h>

class GADriver : public WrapperBaseDriver {
private:
	float fitness;
public:
	virtual CarControl wDrive(CarState cs) = 0;
	GADriver(): fitness(0) {}
	virtual ~GADriver(){}
	void setFitness(CarState cs);
	void storeFitness(int segment_id);
	inline float getFitness() {
		return this->fitness;
	}
};

#endif // GADRIVER_H