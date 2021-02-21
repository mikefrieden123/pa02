#include "schedulers.h"

vector<int> RoundRobin(const int& curTime, const vector<Process>& procList, const int& timeQuantum, int maxNumProcessors)
{
    static int timeToNextSched = timeQuantum;
    static deque<int> ready;

    vector<int> idx = {};

    //runs through the procList and add any to the ready deque
    for(int i = 0, i_end = procList.size(); i < i_end; ++i)
    {
        if(procList[i].startTime == curTime)
        {
            ready.push_back(i);
        }
    }

    //% This bit of code if making a list of processes that can be removed from the list because they are done.
    vector<int> removeList = {};
    for(int i = 0, i_end = ready.size(); i < i_end; ++i)
    {
      if(procList[ready[i]].isDone)//% if a process is done then add it to the remove List processes added to this list will be removed in the next bit of code.
      {
        removeList.push_back(ready[i]);
      }

    }

    //%Time to move on to the next process
    if(timeToNextSched == 0 || removeList.size() > 0)
    {
        for(int i = 0; i < maxNumProcessors; i++)
        {
          if(!procList[ready[0]].isDone)
          {
              ready.push_back(ready[0]);
          }

          ready.pop_front();//% this removes the front which is a copy of what was moved to the back.
        }
        timeToNextSched = timeQuantum;
    }

    //% if the ready size is >0 then we should tell the processors to process these.
    if(ready.size() > 0)
    {
        int i = 0;
        int readySize = ready.size();

        while(i < maxNumProcessors && i < readySize)
        {
          idx.push_back(ready[i]);
          i++;
        }
        --timeToNextSched;
    }
    else
    {

        idx = {-1};
        timeToNextSched = 0;
    }
    std::sort (idx.begin(), idx.begin()+idx.size());//THIS IS VERY IMPORTANT ALWAYS PUT THIS BEFORE YOU RETURN IDX

    return idx;
}
