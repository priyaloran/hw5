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
bool helper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts,
  DailySchedule& sched, vector<int>& shifts, size_t day, size_t position);

bool helper2(const vector<Worker_T>& today, Worker_T worker);

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
    
    size_t days = avail.size();
    size_t workers = avail[0].size();

    sched.resize(days, vector<Worker_T>());

    vector<int> shifts(workers, 0);

    return helper(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);

}

bool helper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts,
  DailySchedule& sched, vector<int>& shifts, size_t day, size_t position)
{

  if (sched.size() == day)  {
    return true;
  }

  if (position == dailyNeed) {
    return helper(avail, dailyNeed, maxShifts, sched, shifts, day + 1, 0);
  }

  size_t workers = avail[0].size();
  for (size_t workerNow = 0; workerNow < workers; workerNow++)  {
    if (avail[day][workerNow] && shifts[workerNow] < maxShifts) {
      if (!helper2(sched[day], workerNow))  {
        sched[day].push_back(workerNow);
        shifts[workerNow]++;

        if (helper(avail, dailyNeed, maxShifts, sched, shifts, day, position + 1)) {
          return true;
        }

        sched[day].pop_back();
        shifts[workerNow]--;
      }
    }
  }

  return false;

}

bool helper2(const vector<Worker_T>& today, Worker_T worker)
{

  for (size_t i = 0; i < today.size(); i++) {
    if (today[i] == worker) {
      return true;
    }
  }

  return false;

}

