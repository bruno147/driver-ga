#include "GADriver.h"

void GADriver::setFitness(CarState cs) {
//    static int laslapTime = 0;
//    if(laslapTime != cs.getLastLapTime())	fitness += cs.getLastLapTime();
	fitness = cs.getDistRaced();
}

void GADriver::storeFitness(int segment_id) {
	float* shared_memory;

    /* Attach the shared memory segment. */
    shared_memory = (float*) shmat (segment_id, 0, 0);

    // Assigned shared memory
    shared_memory[0] = fitness;

    /* Detach the shared memory segment. */
    shmdt (shared_memory);
}