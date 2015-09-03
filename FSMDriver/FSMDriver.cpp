#include "FSMDriver.h"
#include "InsideTrack.h"
#include "OutOfTrack.h"
#include "Stuck.h"
#include "Log.h"
#include "Knowledge.h"

#include <vector>



/******************************************************************************/
const int NUM_SENSORS = 19;
/******************************************************************************/


//-------------------------------------------------------------------------------------------------------------------
//FSMDriver Class


FSMDriver::FSMDriver() : DrivingFSM<FSMDriver>(this), accel(0),brake(0),steer(0),gear(0) {
    if(stage==BaseDriver::WARMUP)    change_to(InsideTrack::instance());
    else    change_to(InsideTrack::instance());
}

FSMDriver::FSMDriver(int argc, char** argv) : DrivingFSM<FSMDriver>(this), accel(0),brake(0),steer(0),gear(0) {
    if(stage==BaseDriver::WARMUP)    change_to(InsideTrack::instance());
    else    change_to(InsideTrack::instance());

    //temporary normalization of LOW_GEAR_LIMIT between 1 and 6(integer)
    LOW_GEAR_LIMIT = 1+round(5*normalization(binToUsignedInt(getArgument(0, argv))));

    //temporary normalization of LOW_RPM, AVERAGE_RPM, HIGH_RPM between 0 and 15000
    LOW_RPM = round(15000*normalization(binToUsignedInt(getArgument(1, argv))));
    AVERAGE_RPM = round(15000*normalization(binToUsignedInt(getArgument(2, argv))));
    HIGH_RPM = round(15000*normalization(binToUsignedInt(getArgument(3, argv))));


    //0 to 50
    STUCK_SPEED = 50*normalization(binToUsignedInt(getArgument(4, argv)));

    MIN_RACED_DISTANCE = binToFloat(getArgument(5, argv));
    MAX_STUCK_TICKS = binToFloat(getArgument(6, argv));
    MAX_SLOW_SPEED_TICKS = binToFloat(getArgument(7, argv));


    //temporary normalization of MAX_STEERING between -1 and 1
    //MAX_STEERING = -1+2*normalization(binToUsignedInt(getArgument(8, argv)));

    //temporary normalization of TARGET_POS between -1 and 1
    //TARGET_POS = -1+2*normalization(binToUsignedInt(getArgument(9, argv)));


    SPEED_FACTOR = normalization(binToUsignedInt(getArgument(8, argv)));


    //temporary normalization of BASE_SPEED between 0 and 340 *just because*
    BASE_SPEED =  340*normalization(binToUsignedInt(getArgument(9, argv)));


    MAX_SKIDDING = 500*normalization(binToUsignedInt(getArgument(10, argv)));

    VELOCITY_GEAR_4 = 500*normalization(binToUsignedInt(getArgument(11, argv)));
    VELOCITY_GEAR_3 = 500*normalization(binToUsignedInt(getArgument(12, argv)));
    VELOCITY_GEAR_2 = 500*normalization(binToUsignedInt(getArgument(13, argv)));

    //percent
    NEGATIVE_ACCEL_PERCENT = normalization(binToUsignedInt(getArgument(14, argv)));

    //0 to PI
    MAX_RETURN_ANGLE = M_PI*normalization(binToUsignedInt(getArgument(15, argv)));
    MIN_RETURN_ANGLE = M_PI*normalization(binToUsignedInt(getArgument(16, argv)));


    //MAX_STRAIGHT_LINE_VAR =  binToFloat(getArgument(18, argv));
    //MIN_STRAIGHT_LINE_VAR =  binToFloat(getArgument(19, argv));
    //MAX_APPROACHING_CURVE_VAR =  binToFloat(getArgument(20, argv));
    //MIN_APPROACHING_CURVE_VAR =  binToFloat(getArgument(21, argv));

    segment_id = stoi(argv[2]);

    // Read the file, offline learning
    string trackFile = this->trackName;
    trackFile += ".bin";
    ifstream infile(trackFile.c_str(), ios::in | ios::binary);
    if(!infile.is_open()) return;

    const size_t count = infile.tellg() / sizeof(Knowledge);
    infile.seekg(0, ifstream::beg);
    memory.resize(count);
    infile.read(reinterpret_cast<char*>(&memory[0]), count*sizeof(Knowledge));
    infile.close();

}

CarControl FSMDriver::wDrive(CarState cs) {
    transition(cs);
    setFitness(cs);
    storeFitness(segment_id);
    return update(cs);
}

 void FSMDriver::onRestart() {
    cout << "Restarting the race!" << endl;
}

string FSMDriver::getArgument(int i, char** argv){
    return string(argv[1]).substr((i*32), ((i+1)*32));
}

float FSMDriver::normalization(unsigned int number){
    return (float)((double)number/binToUsignedInt("11111111111111111111111111111111"));
}


void FSMDriver::onShutdown() {
    cout << this->trackName << endl;
    // Write file, offline learning
    if(string(this->trackName) != string("unknown")) {
        Knowledge aux[memory.size()];

        for (unsigned int i = 0; i < memory.size(); ++i)
        {
            aux[i] = memory.at(i);
        }

        ofstream outfile;
        string str(this->trackName);
        str += ".bin";
        outfile.open(str.c_str(), ios::binary | ios::out);
        outfile.write(reinterpret_cast<const char*>(&aux[0]), memory.size()*sizeof(Knowledge));
        outfile.close();
        cout << "landmarks " << memory.size() << endl;
    }

    cout << "End of race!" << endl;
}

template<typename T>
T signum(T n)
{
    if (n < 0) return -1;
    return 1;
}

void FSMDriver::init(float *angles){
    //for (int i = 0; i < NUM_SENSORS; ++i)
    //    angles[i] = i*10-90; // @todo como assim?
    for (int i = 0; i < NUM_SENSORS; ++i)
        angles[i]=signum((i*1.0/3)-3)*exp(-(0.5)*powf((((i+9)%18)*1.0/3)-3, 2))*90;
}

void FSMDriver::transition(CarState &cs) {
    DrivingState<FSMDriver> *state = current_state;

    if(Stuck::isStuck(cs)) {
        state = Stuck::instance();
    } else {
        if (cs.getTrack(1) > 0) 
            state = InsideTrack::instance();
        else {
            if(cs.getSpeedX() > 85) {
                memory.push_back(Knowledge(abs(cs.getSpeedX())*0.9, cs.getDistFromStart()));
                sort(memory.begin(), memory.end(), Knowledge::aux_sort);
            }
            state = OutOfTrack::instance();
        }
    }

    if (current_state != state) change_to(state);
}

float FSMDriver::binToFloat (string bits) {
    bitset<32> a (bits);
    float *value = reinterpret_cast<float*>(&a);

    return *value;
}

unsigned int FSMDriver::binToUsignedInt (string bits) {
    bitset<32> a (bits);
    unsigned int *value = reinterpret_cast<unsigned int*>(&a);

    return *value;
}
