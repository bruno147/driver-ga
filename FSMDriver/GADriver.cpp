#include "GADriver.h"

void GADriver::setFitness(CarState cs) {
	fitness = cs.getDistRaced();
}
void GADriver::saveFitness(int segment_id) {
	float* shared_memory;

    /* Attach the shared memory segment. */
    shared_memory = (float*) shmat (segment_id, 0, 0);

    // Assigned shared memory
    shared_memory = &fitness;

    /* Detach the shared memory segment. */
    shmdt (shared_memory);
}