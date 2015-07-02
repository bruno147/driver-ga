#ifndef FSMDRIVER_STATE_TRACK_H
#define FSMDRIVER_STATE_TRACK_H

#include <cmath>
#include "FSM.h"
#include "Knowledge.h"

//-----------------------------------------------------------------

extern int START_GEAR;
extern int LOW_GEAR_LIMIT;
extern int LOW_RPM;
extern int AVERAGE_RPM;
extern int HIGH_RPM;
extern int currentGear;
extern float BASE_SPEED;
extern float SPEED_FACTOR;
//-----------------------------------------------------------------

class FSMDriver;

class InsideTrack : public DrivingState<FSMDriver> {
public:
    static InsideTrack *instance();
    void enter(FSMDriver *driver);
    void exit(FSMDriver *driver);
    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs);
    static int getGear(CarState &cs);
    static float getSteer(CarState &cs);
    ~InsideTrack();

private:
    InsideTrack();
    InsideTrack(InsideTrack const &);
    void operator=(InsideTrack const&);
    int currentGear;
    float safeDist;
    static float distance, targetSpeed;

    static bool shouldDecreaseGear(int currentGear, int rpm);
    static inline bool runningOnLow(int rpm);
    static inline bool runningUnderAverage(int rpm);
    static inline bool runningOnHigh(int rpm);
    static inline bool isLowGear(int gear);
    static inline bool isHighGear(int gear);
    static inline bool shouldIncreaseGear(int currentGear, int rpm);
    float getAccel(CarState &cs);
    void setTargetSpeed(CarState &cs);
    static bool isFacingWrongWay(CarState &cs);
    float getBrake(CarState cs);
    static float findFarthestDirection(CarState &cs);
    static float normalizeSteer(float angle);
};

#endif // FSMDRIVER_STATE_INSIDETRACK_H
