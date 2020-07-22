#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {

    long hours=(seconds/3600)%60;
    long minutes=(seconds/60)%60;
    long seconds_= seconds%60;

    if (seconds_ < 10)
        return (std::to_string(hours)+":"+std::to_string(minutes)+":"+"0"+std::to_string(seconds_));
    return (std::to_string(hours)+":"+std::to_string(minutes)+":"+std::to_string(seconds_)); 
}