#ifndef FSMDRIVER_STATE_OUTOFTRACK_H
#define FSMDRIVER_STATE_OUTOFTRACK_H

#include <cmath>
#include "FSM.h"


/******************************************************************************/
/** The car's skidding is measured by Yspeed, max_skidding is a constant to indicated how much the drive must brake  
*/
extern float MAX_SKIDDING; // = 3;
/** The negative_accel_percent is a proportinal factor to calculate accel
*/
extern float NEGATIVE_ACCEL_PERCENT; // = 0.1;
/** velocity_gear_4 is a constant that determine a speed which above it the gear must remain the same 
*/
extern int VELOCITY_GEAR_4; // = 90;
/** velocity_gear_3 is a constant that determine a speed which above it and bellow velocity_gear_3 the gear must be set 3
*/
extern int VELOCITY_GEAR_3; // = 70;
/** velocity_gear_2 is a constant that determine a speed which bellow it must be set 1
*/
extern int VELOCITY_GEAR_2; // = 40;
/** max_return_angle the a angle limit that turning steer to -1 or 1 depending the TrackPos sensor
*/
extern float MAX_RETURN_ANGLE; // = 0.7;
/** min_return_angle the a angle limit that turning steer to -1 or 1 depending the TrackPos sensor
*/
extern float MIN_RETURN_ANGLE; // = 0.5;
/******************************************************************************/

class FSMDriver;
/**
 * Handles the driving when the car is outside track limits. Since the outside the track the track's type change, like dirt road,
 * the driver losses performance that state manage to take the drive out of the track. 
 *
 */
class OutOfTrack : public DrivingState<FSMDriver> {
public:
    static OutOfTrack *instance();
    void enter(FSMDriver *driver);
    void exit(FSMDriver *driver);
    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs);

    ~OutOfTrack();

private:
    OutOfTrack();
    OutOfTrack(OutOfTrack const &);
    void operator=(OutOfTrack const&);

    /** getBrake obtain the brake based on the Xspeed,Yspeed and max_skidding
    * @param cs the driver's perception of the environment.
    * @return 0 when the car' Xspeed and Yspeed is not high enough, 0.1 when the car has Yspeed 
    * higher enough and 1 when the car has Xspeed < 0	 
    */
    float getBrake(CarState &cs);
    /** getAccel calculate the accel based on the Yspeed and negative_accel_percent
    * @param cs the driver's perception of the environment.
    * @return the accel value proportinal to Yspeed	 
    */
    float getAccel(CarState &cs);
    /** getGear calculate the accel based on the Xspeed and speed limits to each gear, that way
    * high speed need high gear. Please note that outoftrack does not use rpm to obtain gear.
    * @param cs the driver's perception of the environment.
    * @return the a gear value accordingthe car's Xspeed	 
    */
    int getGear(CarState &cs);
    /** getSteer calculate the steer based on the trackPos sensor, that allow to know which track 
    * border the car is, and angle that allow to know which side turn the steer.
    * @param cs the driver's perception of the environment.
    * @return 1 or -1 to Steer value 
    */
    float getSteer(CarState &cs);
};

#endif // FSMDRIVER_STATE_OUTOFTRACK_H
