#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>

class Processor {
 public:
    float Utilization();  // TODO: See src/processor.cpp
    void previous(std::vector<float>);

  // TODO: Declare any necessary private members
 private:
    float prev_user, prev_nice, prev_system, prev_idle, prev_iowait, prev_irq, prev_softirq, prev_steal, prev_guest, prev_guest_nice;
    float prev_idlealltime, prev_virtalltime, prev_systemalltime, prev_totaltime;
};

#endif