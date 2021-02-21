#include<vector> // process vector
#include<iostream> // cout, cin
#include<chrono> // sleep duration
#include<thread> // sleep_for
#include<iomanip>  // setw
#include <math.h> // pow
#include <string> // string stoi
#include "schedulers.h" // scheduler functions and data objects

using namespace std;

int main(int argc, char* argv[])
{
  string fname;
  chrono::duration<int, std::milli> sleepTime = chrono::milliseconds(500); //change back to 500
  vector<Process> procList;
  int curTime = 0, input, schedChoice, numProc, timeQuantum;
  vector<int> procIdx;
  int maxNumProcessors = 0;
  bool done;
  string tempStr;

  //if user did not give us a filename or sleep time, then use a default
  if(argc == 1)
  {
      fname = "./procList.txt";
      maxNumProcessors = 1;
  }
  //gave a file name but not sleep time
  else if(argc == 2)
  {
      fname = argv[1];
      maxNumProcessors = 1;
  }
  else if(argc == 3)
  {
      fname = argv[1];
      string str(argv[2]);
      string::size_type sz;
      maxNumProcessors = stoi(str,&sz);
  }
  else
  {
      fname = argv[1];
      string str(argv[2]);
      string::size_type sz;
      maxNumProcessors = stoi(str,&sz);
      sleepTime = chrono::milliseconds(stoul(argv[3]));
  }

  //read in the process list and store the total number of processes
  readInProcList(fname, procList);
  numProc = procList.size();

  cout << "\nWelcome to the scheduler simulator IV mk17 1.32.87b, now with multi thread support!\n\n";

  //controlled prompt for which scheduler to run
  schedChoice = -1;
  do
  {
      cout << "What scheduler would you like to test?\n\n"
           << "1) Round Robin\n"
           << "2) Shortest Process Next\n"
          << "3) Shortest Remaining Time\n"
          << "4) Highest Response Ratio Next\n";
      cout << "\n--> ";
      cin >> input;

      if(input > 0 && input <= 4)
      {
          schedChoice = input;
      }
      else
      {
          cout << "INVALID ENTRY\n\n";
      }

  } while(schedChoice == -1);

  //if the scheduler selected needs a time quantum, ask for it
  if(schedChoice == 1)
  {
    cout << "Enter the time quantum you would like to use: ";
    cin >> timeQuantum;
  }
  //output the header for the run table
  cout << "\nStarting simulation\n"
       << "   O: Process scheduled\n"
       << "   X: Process completed\n"
       << "   !: Completed process scheduled more time than needed\n\n"
       << "Time ";
  tempStr = "-----";
  for(int i = 0; i < numProc; ++i)
  {
      cout << "| " << setw(4) << procList[i].id.substr(0,4) << " ";
      tempStr += "-------";
  }
  cout << "| IDLE |\n" << tempStr << "--------\n";

  //pre-run init
  done = false;
  curTime = 0;
  procIdx = {};

  //while not all processes have completed:
  while(!done)
  {
      //get the process to schedule next using the indicated scheduler
      switch(schedChoice)
      {
          //Round Robin
          case 1:
              procIdx = RoundRobin(curTime, procList, timeQuantum, maxNumProcessors);
              break;

          //Shortest Process Next
          case 2:


              // TODO set procIdx to the proper index for the next process to be scheduled using SPN


              break;

          //Shortest Remaining Time
          case 3:


              // TODO set procIdx to the proper index for the next process to be scheduled using SRT


              break;

          //Highest Response Ratio Next
          case 4:


              // TODO set procIdx to the proper index for the next process to be scheduled using HRRN

              break;
      }

      //if we were given a valid process index
      for(int i = 0, procIdxSize = procIdx.size(); i<procIdxSize; i++)
      {
        if(!(procIdx[0] == -1) && procIdx[i] < static_cast<int>(procList.size()))
        {
            //update the details for the scheduled process
            ++procList[procIdx[i]].timeScheduled;
            if(procList[procIdx[i]].totalTimeNeeded == procList[procIdx[i]].timeScheduled)
            {
                procList[procIdx[i]].isDone = true;
                procList[procIdx[i]].timeFinished = curTime;
            }
        }
      }

      // output the row for the time step, denoting which process was selected
      // also check and see if all processes have finished running yet
      cout << setw(4) << curTime;
      done = true;
      long unsigned int j = 0;

      for(int i = 0; i < numProc; ++i)
      {
          done = done && procList[i].isDone;

          if(i == procIdx[j])
          {

              j++;
              if(j == procIdx.size())
              {
                  j--;
              }
              //cout << procIdx[j];
              if(procList[i].isDone)
              {
                  if(procList[i].timeScheduled > procList[i].totalTimeNeeded)
                  {
                      cout << " |   ! ";
                  }
                  else
                  {
                      cout << " |   X ";
                  }
              }
              else
              {
                  cout << " |   O ";
              }

          }
          else
          {
              cout << " |     ";

          }
      }
      // output for the IDLE process
      if(procIdx[0] == -1 || static_cast<int>(procIdx.size()) > numProc)
      {
          cout << " |   O ";
      }
      else
      {
          cout << " |     ";
      }

      //cout << ":" << debug1 <<":" << debug2;
      cout << " |" << endl;

      //if we aren't done yet, sleep for a bit and move on to the next time step
      if(!done)
      {
          this_thread::sleep_for(sleepTime);
          curTime = curTime + 1;
      }
  }

  //its done! output the run statistics
  cout << "\n\nRun Statistics:\n";



  //TODO output the requested run stats

  return 0;
}
