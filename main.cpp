#include <queue>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

#define HUGE_VAL 1000000000000000000000000000000000000000000000000000000.0
#define T_MAX 100.0

enum Server {
	IDLE, BUSY
};

class Statistics {
private:
	double processingTime = 0.0;
	double simulationTime = 0.0;
	double totalTime = processingTime + simulationTime;
public:
	Statistics() {

	}

	void update() {

	}

	double rand_poisson(double lambda) {
		double L = exp(-lambda);
		double k = 0.0;
		double p = 1;
		while (p <= L) {
			k = k + 1;
			double r = rand();
			p = p * r;
		}
		return k;
	}
};

class Task {
public:
	double sim_time = 0.0;

	Task() {

	}

	Task(double sim_time) {
		this->sim_time = sim_time;
	}
};

int main() {
	Server s = IDLE;
	Statistics stats;
	double sim_time = 0.0;
	double next_departure = HUGE_VAL;
//	srand(clock());
	double mean_arrival = 1.0;
	double mean_processing = 2.0;
	double next_arrival = stats.rand_poisson(mean_arrival);
//	double next_arrival = random.poisson(mean_arrival);
	queue<Task> queue;

	double last_event_time = 0.0;
	double waiting_time_queue_total = 0.0;

	while (sim_time < T_MAX) {
//		stats.update();
		cout << "1-sim_time: " << sim_time << endl;
		cout << "1-next_departure: " << next_departure << endl;
		cout << "1-next_arrival: " << next_arrival << endl;
		if (next_arrival < next_departure) {
			sim_time = next_arrival;
			cout << "	2-sim_time: " << sim_time << endl;
			if (s == IDLE) {
				s = BUSY;
//				next_departure = sim_time + exp(mean_processing);
				next_departure = sim_time + rand();
				cout << "		3-next_departure: " << next_departure << endl;
			} else {
				Task task;
				queue.push(task);
				cout << "Tamanho da fila: " << queue.size() << endl;
			}
//			next_arrival = sim_time + exp(mean_arrival);
			next_arrival = sim_time + rand();
			cout << "			4-next_arrival: " << next_arrival << endl;
		} else {
			sim_time = next_departure;
			cout << "TESTE" << endl;
			if (queue.empty()) {
				cout << "Empty?: " << queue.size() << endl;
				s = IDLE;
				next_departure = HUGE_VAL;
			} else {
				queue.pop();
				cout << "Saindo..." << endl;
//				next_departure = sim_time + exp(mean_processing);
				next_departure = sim_time + rand();
			}
		}
		last_event_time = sim_time;
	}
}
