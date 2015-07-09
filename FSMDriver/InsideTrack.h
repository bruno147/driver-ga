#ifndef FSMDRIVER_STATE_TRACK_H
#define FSMDRIVER_STATE_TRACK_H

#include <cmath>
#include "FSM.h"
#include "Knowledge.h"

//-----------------------------------------------------------------
/**start_gear is the gear used at the begining of the race
*/
extern int START_GEAR;
/**low_gear_limit is the gear value that determine if the driver must decreace or increace gear based on gear
*/
extern int LOW_GEAR_LIMIT;
/**low_rpm is the rpm value that determine if the driver must decreace or increace gear based on the gear
*/
extern int LOW_RPM;
/**average_rpm is the rpm value that determine if the driver must decreace or increace gear based on the rpm
*/
extern int AVERAGE_RPM;
/**high_rpm is the rpm value that determine if the driver must decreace or increace gear based on the rpm
*/
extern int HIGH_RPM;
/**current_speed is the driver's speed at the present code execution
*/
extern int currentGear;
/**base_speed is a parameter to determine if the driver's speed
*/
extern float BASE_SPEED;
/**speed_factor is a proportional parameter to determine driver's speed
*/
extern float SPEED_FACTOR;
//-----------------------------------------------------------------

class FSMDriver;

/**
 * Handles the driving when the car is within track limits, which mean that the the 
 * sensors track wil return values > 0 inside the track. This state is responsible 
 * for any event that occur inside the track including curves and straightline tracks. 
 */

class InsideTrack : public DrivingState<FSMDriver> {
public:
    static InsideTrack *instance();
    void enter(FSMDriver *driver);
    void exit(FSMDriver *driver);
    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs);
    /** Auxiliar function to obtain the gear analysing the car's rpm.
    */
    static int getGear(CarState &cs);
    /** Auxiliar function to obtain the gear analysing Carstate data.
    */
    static float getSteer(CarState &cs);
    ~InsideTrack();

private:
    InsideTrack();
    InsideTrack(InsideTrack const &);
    void operator=(InsideTrack const&);
    int currentGear;
    float safeDist;
    /** distance is the highest value of the 19 track sensors
    */
    static float distance;
    /** target_speed is the speed the car must reach, it is calculated based on distance, base_speed and speed_factor
    */
    static float targetSpeed;
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
    /** It receive gear from cs, base on gear and rpm it change gear
    *@param cs a data structure cointaining information from the car's sensors.
    *@return the accel based on cs values
    */
    float getAccel(CarState &cs);
    /** Change the target_speed based on base_speed, speed_factor and distance
    *@param cs a data structure cointaining information from the car's sensors.
    */
    void setTargetSpeed(CarState &cs);
    /** isFacingWrongWay verify if the car is driving the right path, once it is possible
    * that the car collide and turn to the opposite way.
    * @param cs a data structure cointaining information from the car's sensors.
    */
    static bool isFacingWrongWay(CarState &cs);
    /** Compare the XSpeed with target speed to obtain the brake
    *@param cs a data structure cointaining information from the car's sensors.
    *@return 0 if the current speedX is lower the target speed and 0.3 if it higher the target speed
    */
    float getBrake(CarState cs);
    /** Find the highest value of the 19 track sensors.
    *@param cs a data structure cointaining information from the car's sensors.
    *@return the index of the track sensor with highest value
    */
    static float findFarthestDirection(CarState &cs);
    /** It receive angle at radians (0.785398 to -0.785398) and normalize it turning -1 to 1
    *@param angle a data from the car's sensor angle.
    *@return a normalized value
    */
    static float normalizeSteer(float angle);
};

#endif // FSMDRIVER_STATE_INSIDETRACK_H
