#ifndef TEST_TRACK_H
#define TEST_TRACK_H

#include "FSM.h"
#include "InsideTrack.h"

class FSMDriver;
class InsideTrack;

class TestTrack : public DrivingState<FSMDriver> {
public:
    static TestTrack *instance();
    void enter(FSMDriver *driver);
    void exit(FSMDriver *driver);
    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs);
    ~TestTrack();

private:
    int targetSpeed, thresholdValue, lastDistFromStart, typeTrack;

    TestTrack();
    TestTrack(TestTrack const &);
    void operator=(TestTrack const&);
};

#endif // TEST_TRACK_H
