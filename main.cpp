#include <queue>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "MetodoCongruente.h"

using namespace std;

#define HUGE_VAL 1000000000000000000000000000000000000000000000000000000.0
#define T_MAX 100.0
static int ID = 0;

enum Server {
	IDLE, BUSY
};

class Task {
public:
	double sim_time = 0.0;
	int ID;

	Task() {

	}

	Task(double sim_time) {
		this->sim_time = sim_time;
	}
};

class Statistics {
private:
	double arrivalTime = 0.0;
	double departureTime = 0.0;
	double requisitionInterval[100];
	int aux = 0;
	MetodoCongruente crand = MetodoCongruente(1103515245,12345,2147483648,rand());

public:
	Statistics() {

	}

	void setarrivalTime(double value){
		this->arrivalTime = value;
	}

	void setdepartureTime(double value){
		this->departureTime = value;
	}

	void update() {
		requisitionInterval[aux] = departureTime - arrivalTime;
		aux++;
		arrivalTime = 0.0;
		departureTime = 0.0;
	}

	double intervalMean(){
		int i = 0;
		double j = 0;
		while(i < aux){
			j = requisitionInterval[i] + j;
			i++;
		}
		return j/aux;
	}

	double taskMean(queue<Task> queue){
		double i = 0;
		int j = 0;
		int h = queue.size();

		while(i < h){
			Task task = queue.back();
			j = task.sim_time + j;
			queue.pop();
			i++;
		}
		return j/h;
	}

	double rand_exp(double lambda){
		double y = - 1 + ((double) this->crand.GeraNumeroAleatorio() / (RAND_MAX)) + 1;
		double x;

		return x = -lambda*log(y);
	}
};

int main() {
	Server s = IDLE;
	Statistics stats;
	double sim_time = 0.0;
	double next_departure = HUGE_VAL;
	double mean_arrival = 2.0;
	double mean_processing = 1.0;
	double next_arrival = stats.rand_exp(mean_arrival);
	queue<Task> queue;
	std::queue<Task> queueStatistics;


	while (sim_time < T_MAX) {
		stats.update();
		if (next_arrival < next_departure) {
			sim_time = next_arrival;
			if (s == IDLE) {
				s = BUSY;
				next_departure = sim_time + stats.rand_exp(mean_processing);
			} else {
				Task task;
				task.ID = ID++;
				task.sim_time = sim_time;
				queue.push(task);
				cout << "Entrando: " << queue.size() << endl;
			}
			next_arrival = sim_time + stats.rand_exp(mean_arrival);
			stats.setarrivalTime(next_arrival);
		} else {
			sim_time = next_departure;
			if (queue.empty()) {
				s = IDLE;
				next_departure = HUGE_VAL;
			} else {
				Task task = queue.back();
				task.sim_time -= sim_time;
				queueStatistics.push(task);
				queue.pop();
				cout << "Saindo..." << endl;
				next_departure = sim_time + stats.rand_exp(mean_processing);
				stats.setarrivalTime(next_departure);
			}
		}
	}
	cout << "Intervalo medio de Tasks no sistema: " << stats.taskMean(queueStatistics) << endl;
	cout << "Intervalo medio de requisicoes: " << stats.intervalMean() << endl;
}
