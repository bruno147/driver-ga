#ifndef LOG_H
#define LOG_H

#include "FSM.h"

#include <iostream>
#include <fstream>

//For shared memory
#include <sys/shm.h>
#include <sys/stat.h>

class FSMDriver;

class Log {
public:
    ~Log(){}
    static Log *instance() {
        static Log instance;
        return &instance;
    }
    void updateLog(DrivingState<FSMDriver> *s, CarState cs) {
        assert(s);
        damage=cs.getDamage();
        distRaced = cs.getDistRaced();
        totalTime = cs.getLastLapTime();      
    }


    // send totalTime to shared memory
    void saveTotalTime(int segment_id){
        float* shared_memory;

        /* Attach the shared memory segment. */
        shared_memory = (float*) shmat (segment_id, 0, 0);
    
        // Assigned shared memory
        shared_memory[0] = totalTime;
        shared_memory[1] = damage;
        shared_memory[2] = distRaced;


        /* Detach the shared memory segment. */
        shmdt (shared_memory);

    }


private:
    Log() : lapCounter(0), flag(0), damage(0), distRaced(0), totalTime(0) {}
    int lapCounter;
    int flag;
    float damage;
    float distRaced;
    float totalTime;
};



#endif // LOG_H
