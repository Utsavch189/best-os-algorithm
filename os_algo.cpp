#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

double AVG_WT_RR;
double AVG_WT_SJF;
double AVG_WT_FCFS;
double AVG_WT_PRIORITY;


struct Process {
  string name;
  int AT, BT, ST, P, TQ=3, WT,REM;
};

bool sort_sjf(Process a,Process b){
	return a.BT<b.BT;
}

bool sort_priority(Process a,Process b){
	return a.P>b.P;
}

int count_process() {
  int number;
  cout << "Enter the number of process(es): ";
  cin >> number;
  return number;
}

void take_user_input(vector<Process> &processes) {
  cout << "\nGive the input for all process in the following manner (name AT BT P):\n";
  for (int i = 0; i < processes.size(); ++i)
    cin >> processes[i].name >> processes[i].AT >> processes[i].BT >> processes[i].P;
}


double avg_wt_rr(vector<Process> processes) {
  int g=0;
  double avg;
  
  int sum_wt = 1;
  while (sum_wt) {
    sum_wt = 0;
    for (auto &process: processes) {
      if (process.BT < process.TQ && process.BT) {

        process.REM = process.BT;
        process.WT += (g - process.AT);
        g += process.REM;
        process.BT = 0;

      } else if (process.BT > 0) {

        process.REM = process.BT - process.TQ;
        process.BT = process.REM;
        process.WT += (g - process.AT);
        g += process.TQ;
        process.AT = g;

      }
      sum_wt += process.BT;
    }
  }
  for (auto &process : processes){
  	avg+=process.WT;
  }
    
  return avg/processes.size();
}

double avg_wt_sjf(vector<Process> processes) {
  sort(processes.begin(),processes.end(),sort_sjf);
  int g=0;
  double avg;
  for(auto &i:processes){
	i.ST=g;
  	g=g+i.BT;
  	i.WT=i.ST-i.AT;
  	avg=avg+i.WT;
 
  }
  
  return avg/processes.size();
}

double avg_wt_fcfs(vector<Process> processes) {
  int g=0;
  double avg;
  for(auto &i:processes){
  	i.ST=g;
  	g=g+i.BT;
  	i.WT=i.ST-i.AT;
  	avg=avg+i.WT;
  }
  return avg/processes.size();
}

double avg_wt_priority(vector<Process> processes) {	
  sort(processes.begin(),processes.end(),sort_priority);
  int g=0;
  double avg;
  for(auto &i:processes){
	i.ST=g;
  	g=g+i.BT;
  	i.WT=i.ST-i.AT;
  	avg=avg+i.WT;
 
  }
  
  return avg/processes.size();
}

void show_output(vector<Process> &processes) {
  AVG_WT_RR = avg_wt_rr(processes);
  AVG_WT_SJF = avg_wt_sjf(processes);
  AVG_WT_FCFS = avg_wt_fcfs(processes);
  AVG_WT_PRIORITY = avg_wt_priority(processes);

  vector<pair<double, string>> output;

  output.push_back({AVG_WT_SJF, "Shortest Job First (SJF)"});
  output.push_back({AVG_WT_RR, "Round Robin Scheduling (RR)"});
  output.push_back({AVG_WT_FCFS, "First Come First Serve (FCFS)"});
  output.push_back({AVG_WT_PRIORITY, "Priority Based Scheduling"});

  cout << "\nAlgorithm" << "\t\t\t" << "Avg. WT" << '\n';
  cout << "------------------------------------------\n";
  for (auto &ele : output)
    cout << ele.second << "\t" << ele.first << '\n';
  
  sort(output.begin(), output.end());
  cout << "\n* The best algorithm is " << output[0].second << " having " << output[0].first << "s average waiting time.";
}

int main() {
  vector<Process> processes(count_process());
  take_user_input(processes);
  show_output(processes);
  return 0;
}

/*
P0 0 5 3
P1 1 3 2
P2 2 8 1
P3 3 6 2
*/
