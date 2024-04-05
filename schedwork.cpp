#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes any helper functions here
bool backtrack_worker(const AvailabilityMatrix &avail,
                      const size_t dailyNeed,
                      const size_t maxShifts,
                      DailySchedule &sched,
                      int* workerDaysSoFar,
                      size_t day,
                      Worker_T worker);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix &avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule &sched)
{
    if (avail.size() == 0U)
    {
        return false;
    }
    sched.clear();
    sched.push_back(vector<Worker_T>());
    // Add your code below
    int* workerDaysSoFar = new int[avail[0].size()];
    memset(workerDaysSoFar, 0, avail[0].size() * sizeof(int));
    bool result = backtrack_worker(avail, dailyNeed, maxShifts, sched, workerDaysSoFar, 0, 0);
    delete[] workerDaysSoFar;
    return result;
}

//iterate across workers, then move to next day
bool backtrack_worker(const AvailabilityMatrix &avail,
                      const size_t dailyNeed,
                      const size_t maxShifts,
                      DailySchedule &sched,
                      int* workerDaysSoFar,
                      size_t day,
                      Worker_T worker)
{
    if(day == avail.size())
    {
        return true;
    }
    if(day >= sched.size())
    {
        sched.push_back(vector<Worker_T>());
    }
    if(worker == avail[day].size())
    {
        return false;
    }
    if(workerDaysSoFar[worker] >= maxShifts)
    {
        return backtrack_worker(avail, dailyNeed, maxShifts, sched, workerDaysSoFar, day, worker + 1);
    }
    if(avail[day][worker])
    {
        sched[day].push_back(worker);
        workerDaysSoFar[worker]++;
        if(sched[day].size() == dailyNeed)
        {
            if(backtrack_worker(avail, dailyNeed, maxShifts, sched, workerDaysSoFar, day + 1, 0))
            {
                return true;
            }
        }
        else
        {
            if(backtrack_worker(avail, dailyNeed, maxShifts, sched, workerDaysSoFar, day, worker))
            {
                return true;
            }
        }
        workerDaysSoFar[worker]--;
        sched[day].pop_back();
        return false;
    } else {
        return backtrack_worker(avail, dailyNeed, maxShifts, sched, workerDaysSoFar, day, worker + 1);
    }
}