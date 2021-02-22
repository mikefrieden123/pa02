//Programmer: Mike Frieden
//Course: CS3800
//Section: 102
//Assignment: PA02 Scheduler Showdown

#include "schedulers.h"
#include<bits/stdc++.h> 

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

vector<int> ShortestProcessNext(const int& curTime, const vector<Process>& procList, int maxNumProcessors)
{

  static deque<int> ready;

  vector<int> idx = {};

  // first look through the process list and find any processes that are newly ready and add to back of ready que
  for(int i = 0, i_end = procList.size(); i < i_end; ++i)
  {
      if(procList[i].startTime == curTime)
      {
        ready.push_back(i);
      }
  }

  //organize the processes in the ready queue
  for(int i=0;i<ready.size()-1;i++)
  {
    for(int j=1;j<ready.size()-i-1;j++)
    {
      //order processes from least to greatest
      if(procList[ready[j]].totalTimeNeeded > procList[ready[j+1]].totalTimeNeeded)
        swap(ready[j], ready[j+1]);
    }
  }

  if(procList[ready[0]].isDone)
  {
      //remove process from front of ready que
      ready.pop_front();

  }

  if(ready.size() > 0)
  {
    int i = 0;
    int readySize = ready.size();

    while(i < maxNumProcessors && i < readySize)
    {
      idx.push_back(ready[i]);
      i++;
    }
  }

  else
  {
    idx = {-1};
  }

  std::sort (idx.begin(), idx.begin()+idx.size());

  return idx;
}

vector<int> ShortestRemainingTime(const int& curTime, const vector<Process>& procList, int maxNumProcessors)
{
  static deque<int> ready;

  vector<int> idx = {};

  for(int i = 0, i_end = procList.size(); i < i_end; ++i)
  {
      if(procList[i].startTime == curTime)
      {
        ready.push_back(i);
      }
  }

  //organize the processes from shortest remaining time to longest
  for(int i=0;i<ready.size()-1;i++)
  {
    for(int j=0;j<ready.size()-i-1;j++)
    { 
      //Remaining time for current process
      int a = procList[ready[j]].totalTimeNeeded - procList[ready[j]].timeScheduled;
      //Total time needed for next process
      int b = procList[ready[j+1]].totalTimeNeeded;
      //Sort processes by remaining time
      if(a>b)
        swap(ready[j], ready[j+1]);
    }
  }

  if(procList[ready[0]].isDone)
  {
    ready.pop_front();
  }

  if(ready.size() > 0)
  {
    int i = 0;
    int readySize = ready.size();

    while(i < maxNumProcessors && i < readySize)
    {
      idx.push_back(ready[i]);
      i++;
    }
  }

  // if the ready queue is empty
  else
  {
    idx = {-1};
  }

  std::sort (idx.begin(), idx.begin()+idx.size());

  return idx;

}

vector<int> HighestResponseRatioNext(const int& curTime, const vector<Process>& procList, int maxNumProcessors)
{
  static deque<int> ready;

  vector<int> idx = {};

  //Add processes to the ready que
  for(int i = 0, i_end = procList.size(); i < i_end; ++i)
  {
      if(procList[i].startTime == curTime)
      {
          ready.push_back(i);
      }
  }

  //organize the processes from highest ratio to lowest
  for(int i=0;i<ready.size()-1;i++)
  {
    for(int j=1;j<ready.size()-i-1;j++)
    {
      //Set ratio
      float a = ((curTime - procList[ready[j]].startTime)+procList[ready[j]].totalTimeNeeded)/procList[ready[j]].totalTimeNeeded;
      //Set ratio for next process
      float b = ((curTime - procList[ready[j+1]].startTime)+procList[ready[j+1]].totalTimeNeeded)/procList[ready[j+1]].totalTimeNeeded;
      //Sort from high to low
      if(a<b)
        swap(ready[j], ready[j+1]);
    }
  }

  if(procList[ready[0]].isDone)
  {
      //Remove front process from ready que
      ready.pop_front();
  }

  if(ready.size() > 0)
  {
    int i = 0;
    int readySize = ready.size();

    while(i < maxNumProcessors && i < readySize)
    {
      idx.push_back(ready[i]);
      i++;
    }
  }

  else
  {
    idx = {-1};
  }

  std::sort (idx.begin(), idx.begin()+idx.size());

  return idx;
}
