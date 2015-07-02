#ifndef FSMDRIVER_STATE_STUCK_H
#define FSMDRIVER_STATE_STUCK_H

#include <cmath>
#include "FSM.h"

/******************************************************************************/
/** stuck_speed is the value which bellow it a car may be stuck
*/
extern float STUCK_SPEED; // = 5;
/** min_raced_distance is distance raced that determine if the car is at begining of the race or not
*/
extern unsigned int MIN_RACED_DISTANCE; // = 100;
/** max_stuck_ticks determine the total time (by ticks) that stuck state can work without change to another state
*/
extern unsigned int MAX_STUCK_TICKS; // = 300;
/** maximum_slow_speed_ticks is the value of ticks that the pilot can be bellow 
*the stuck_speed to determine if is stuck or not
*/
extern unsigned int MAX_SLOW_SPEED_TICKS; // =50;
/******************************************************************************/

class FSMDriver;
/**
 * Handles the driving when the car is stuck. This usually means it is stopped
 * or has been driving at a very low speed for a while, mesuared by slow_speed_ticks.
 * Entering this state mean that the driver may be hitting a wall or a corner. The 
 * stuck has  a limit time to work without going to another state. it is highly desireble
 * at a actual race that the drive do not enter at this state, since the pilot can complete 
 * the race faster if it do not happend.
 *
 */
class Stuck : public DrivingState<FSMDriver> {
public:
    static Stuck *instance();
	static inline bool isStuck(CarState &cs) {
	    return (seemsStuck(cs) && !justStartedRace(cs));
	}

    void enter(FSMDriver *driver, CarState &cs);
    void exit(FSMDriver *driver);
    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs);
    ~Stuck();

private:
    unsigned int elapsedTicks;
    static unsigned int slowSpeedTicks;
    /** track_pos (sensor) value when the car enter the stuck state  
    */
    static float trackInitialPos;

    Stuck();
    Stuck(Stuck const &);
    void operator=(Stuck const&);
    
/**function to determine the steer
* @param cs the driver's perception of the environment.
* @return -1 or 1 at stuck in order to fast turn to right way
*/
	float getSteer(float trackInitialPos, CarState &cs);
/**Function to determine the track_pos at the begin of stuck state
* @param cs the driver's perception of the environment.
* @return the track_initial_pos
*/
	float getInitialPos(CarState &cs);
    
/** Function that check if the stuck state is appropriate to the event at the race 
* @param cs the driver's perception of the environment.
* @return true if the car has been at bellow the stuck_speed for long enough and false if not
*/
	static inline bool seemsStuck(CarState &cs) {
		cs.getSpeedX()<STUCK_SPEED?slowSpeedTicks++:slowSpeedTicks = 0;
		if(notStuckAnymore(cs.getTrackPos(), cs.getAngle())){
			slowSpeedTicks=0;
		}
		return (slowSpeedTicks>MAX_SLOW_SPEED_TICKS?1:0);
	    //return (abs(cs.getSpeedX()) <= STUCK_SPEED);
	}
/** Based on the distance raced it verify if the driver has just started the race
* @param cs the driver's perception of the environment.
* @return true if the pilot is at begining of the race or false if not
*/
	static inline bool justStartedRace(CarState &cs) {
	    return (cs.getDistRaced() <= MIN_RACED_DISTANCE); 
	}
/** Check if the car is driving according the race direction
* @param cs the driver's perception of the environment.
* @return true if the car is facing the right race direction or face on the other way
*/
	static inline bool onRightWay(float trackPos, float angle) {
	    return (((trackPos < 0) && (angle > -1.57) && (angle < 0)) ||
	            ((trackPos > 0) && (angle < 1.57 ) && (angle > 0)) ||
	            ((trackPos > 1) && (angle > 0))||
	            ((trackPos < -1) && (angle < 0)));
	}
/**  Based on the car's speed and stuck_speed this function determine if the car is stuck or not
* @param track_pos is the sensor value that measure the distance of the car to the tracks borders, angle 
* is the sensors value of the angle between the car direction and race direction.
* @return true if the car is not stuck anymore or false if it is
*/
	static inline bool notStuckAnymore(float trackPos, float angle) {
		return (onRightWay(trackPos, angle));
	}
/** Since the driver can not be stuck for a long time without goint back the track, a time limit is used,
*this check if the stuck state surpass that limit
* @param cs the driver's perception of the environment.
* @return true if the driver pass the time limit or false if not
*/
	inline bool hasBeenStuckLongEnough() {
		return (elapsedTicks >= MAX_STUCK_TICKS);
	}
};

#endif // FSMDRIVER_STATE_STUCK_H
