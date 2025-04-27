#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool backtrackHelp (
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& count,
    size_t day,
    size_t spot
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();

    sched.resize(numDays, vector<Worker_T>());

    vector<int> count(numWorkers, 0);

    return backtrackHelp(avail, dailyNeed, maxShifts, sched, count, 0, 0);
}

bool backtrackHelp (
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& count,
    size_t day,
    size_t spot
) {
    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();
    //base case if all are full
    if (day == numDays){
      return true;
    }

    //move to next day if slots are full
    if (spot == dailyNeed){
      return backtrackHelp (avail, dailyNeed, maxShifts, sched, count, day + 1, 0);
    }

    for (Worker_T worker = 0; worker < numWorkers; ++worker){
      if (avail[day][worker] && count[worker] < maxShifts){
        if (find(sched[day]. begin() , sched [day].end(), worker) != sched[day].end()){
          continue;
        }
        sched[day].push_back(worker);
        count[worker] = count[worker] + 1;

        if (backtrackHelp (avail, dailyNeed, maxShifts, sched, count, day, spot + 1)){
          return true;
        }

        sched[day].pop_back();
        count[worker] = count[worker] - 1;
      } 
    } 
  return false;
}

