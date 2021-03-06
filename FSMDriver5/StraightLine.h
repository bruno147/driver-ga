#ifndef FSMDriver5_STATE_STRAIGHTLINE_H
#define FSMDriver5_STATE_STRAIGHTLINE_H

#include "FSM.h"

class FSMDriver5;

 /**
  * @brief StraightLine state.
  * @details Class to treat the state where there is a minimal curvature possible, this state is important considering that it can perform maximum speed.
  * @param start_gear initial gear set at the begining of the race
  * @param low_gear_limit threshlod to bound low gears.
  * @param low_rpm threshlod of rpm to delimit the change of low gears.
  * @param average_rpm threshlod to decrease high gears.
  * @param high_rpm threshlod to delimit the change of high gears.
  */
class StraightLine : public DrivingState<FSMDriver5> {
public:
    /** start gear is the gear value set to the begining of the race*/
    static int START_GEAR;
    
    StraightLine(int _sg = 1, int _lgl = 4, int _lrpm = 1500,
                 int _arpm = 4000, int _hrpm = 9500);
    StraightLine(StraightLine const &);
    void operator=(StraightLine const&);
    
    virtual CarControl drive(FSMDriver5 *FSMDriver5, CarState &cs);
    static int getGear(CarState &cs);

    ~StraightLine();

private:
    /** Statics because they are parameters of getGear. */
    /** low_gear_limit separetes high and low gears. */
    static int LOW_GEAR_LIMIT;
    /** low_rpm threshlod value to change low gears. */
    static int LOW_RPM;
    /** average_rpm threshold to decrease the high gears. */
    static int AVERAGE_RPM;
    /** high_gear threshold to increase the high gears. */
    static int HIGH_RPM;

    /** get Brake verify if the car is running back, if true it brakes
    * @param cs the driver's perception of the environment.
    * @return the brake value, '1' if it is running back and '0' if not
    */
    float getBrake(CarState &cs);
    /** Check the current_gear and rpm, if the gear and rpm is above a certain value the function authorize decrease gear at one gear
    * @param current_gear the gear of the car at the moment of execution
    * @param rpm the value of rpm read by the sensor
    * @return true if the driver must decrease gear and false if it must not 
    */
    static bool shouldDecreaseGear(int currentGear, int rpm);
    /** Check if rpm is bellow a certain value(low_rpm)
    * @param rpm the value of rpm read by the sensor
    * @return true if rpm is bellow low_rpm and false if it is not
    */
    static inline bool runningOnLow(int rpm);
    /** Check if rpm is bellow a certain value(average_rpm)
    * @param rpm the value of rpm read by the sensor
    * @return true if rpm is bellow average_rpm and false if it is not
    */
    static inline bool runningUnderAverage(int rpm);
    /** Check if rpm is above a certain value(high_rpm)
    * @param rpm the value of rpm read by the sensor
    * @return true if rpm is above high_rpm and false if it is not
    */
    static inline bool runningOnHigh(int rpm);
    /** Check if gear is between two value(start_gear and low_gear_limit)
    * @param rpm the value of rpm read by the sensor
    * @return true if gear is between start_gear and low_gear_limit, false if it is not
    */
    static inline bool isLowGear(int gear);
    /** Check if gear is above a certain value(low_gear_limit)
    * @param rpm the value of rpm read by the sensor
    * @return true if gear is above low_gear_limit, false if it is not
    */
    static inline bool isHighGear(int gear);
    /** Check the current_gear and rpm, if the gear and rpm is bellow a certain value the function authorize increase gear at one gear
    * @param current_gear the gear of the car at the moment of execution
    * @param rpm the value of rpm read by the sensor
    * @return true if the driver must increase gear and false if it must not 
    */
    static inline bool shouldIncreaseGear(int currentGear, int rpm);
};

#endif // FSMDriver5_STATE_STRAIGHTLINE_H
