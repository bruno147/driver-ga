#ifndef FSMDriver5_STATE_CURVE_H
#define FSMDriver5_STATE_CURVE_H

#include <cmath>
#include "FSM.h"
#include "StraightLine.h"


class FSMDriver5;
/**
 * @brief Curve state
 * @details Class to treat curve state where the track has a minimal curvature. Note that this state is important at the race considering 
 *          oponents with equal speed the way the driver complete the curve can achieve the lead at the race.
 */
class Curve : public DrivingState<FSMDriver5> {
public:
    Curve();
    Curve(Curve const &);
    void operator=(Curve const&);
    virtual CarControl drive(FSMDriver5 *FSMDriver5, CarState &cs);

    ~Curve();

private:
    int currentGear;


    float getAccel(CarState &cs);
    /** isFacingWrongWay verify if the car is driving the right path, once it is possible
    * that the car collide and turn to the opposite way.
    * @param cs a data structure cointaining information from the car's sensors.
    */
    bool isFacingWrongWay(CarState &cs);
    /** Check if XSpeed negative, which indicates that the car is running back
    *@param cs a data structure cointaining information from the car's sensors.
    *@return '0' if the current speedX higher than 0 and '1' if it bellow 0
    */
    float getBrake(CarState cs);
    /** Find the highest value of the 19 track sensors.
    *@param cs a data structure cointaining information from the car's sensors.
    *@return the index of the track sensor with highest value
    */
    float findFarthestDirection(CarState &cs);
    /** It receive angle at radians (0.785398 to -0.785398) and normalize it turning -1 to 1, 
    * since the TORCS receive a value between -1 and 1 to the steer it used this function to normalize
    *@param angle a data from the car's sensor angle.
    *@return a normalized value
    */
    float normalizeSteer(float angle);
    /** getSteer obtain steer value checking first if the driven is at the right direction, if not the steer is 
    *calculated using angle value, case not using the distance(highest track sensor value)
    *@param angle a data from the car's sensor angle.
    *@return a normalized steer value
    */
    float getSteer(CarState &cs);
};

#endif // FSMDriver5_STATE_CURVE_H
