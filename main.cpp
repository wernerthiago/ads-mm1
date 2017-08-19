#include <queue>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace mm1;
using namespace std;

#define HUGE_VAL 10000.0
#define T_MAX 100.0

enum Server {IDLE,BUSY};

int main() {
	Server s = IDLE;
	double sim_time = 0.0;
	double next_departure = HUGE_VAL;
	random(gettimeofday());
	double next_arrival = random();
	//double next_arrival = random.poisson(mean_arrival);
	queue <Task> queue;

	while (sim_time < T_MAX) {
		if (next_arrival < next_departure) {
			sim_time = next_arrival;
			if (s == IDLE) {
				s = BUSY;
				next_departure = sim_time + random();
			} else {
				Task task = new Task(sim_time);
				queue.push(task);
			}
			next_arrival = sim_time + random();
		} else {
			sim_time = next_departure;
			if ( queue.empty() ) {
				s = IDLE;
				next_departure = HUGE_VAL;
			} else {
				Task t = queue.pop();
				next_departure = sim_time + random();
			}
		}
	}
}
