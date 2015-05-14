#include "TestTrack.h"

TestTrack::TestTrack() : targetSpeed(200), thresholdValue(60), lastDistFromStart(0) {}

TestTrack::TestTrack(TestTrack const &) {}

TestTrack *TestTrack::instance() {
    static TestTrack instance;
    return &instance;
}

void TestTrack::enter(FSMDriver *driver) {
    // cout << "Enter TestTrack" << endl;
}

void TestTrack::exit(FSMDriver *driver) {
    // cout << "Exit TestTrack" << endl;
}

CarControl TestTrack::drive(FSMDriver *fsmdriver, CarState &cs) {
    float accel = 0, brake = 0, gear = 1, steer = 0, clutch = 0;
    float speed = cs.getSpeedX();
    static bool targetSpeedCheck = false;
    float difference;

    if(speed >= targetSpeed) {
        lastDistFromStart = cs.getDistFromStart();
        brake = 1.0;
        targetSpeedCheck = true;
    }
    else if(speed < targetSpeed && !targetSpeedCheck) {
        accel = 1.0;
    }
    else if(speed < targetSpeed && targetSpeedCheck) {
        brake = 1.0;
    }
    else if(speed < 5 && targetSpeedCheck) {
        difference = cs.getDistFromStart() - lastDistFromStart;
        if(difference > thresholdValue)
        {
            typeTrack = TYPETRACK::DIRT;
        }
        else    typeTrack = TYPETRACK::ROAD;
    }

    steer = InsideTrack::getSteer(cs);
    gear = InsideTrack::getGear(cs);
    return CarControl(accel, brake, gear, steer, clutch);
}

TestTrack::~TestTrack() {}
