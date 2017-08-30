#include <queue>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "MetodoCongruente.h"

using namespace std;

#define HUGE_VAL 1000000000000000000000000000000000000000000000000000000.0
#define T_MAX 200.0
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
	double arrivalA = 0.0;
	double arrivalB = 0.0;
	double arrivalTime = 0.0;
	double departureTime = 0.0;
	double requisitionInterval[100];
	double firstArrival = 0.0;
	double lastDeparture = 0.0;
	double totalBusyTime = 0.0;
	int aux = 0;
	MetodoCongruente crand = MetodoCongruente(1103515245,12345,2147483648,rand());

public:
	Statistics() {

	}

	void setfirstArrival(double value){
		this->firstArrival = value;
	}

	void setlastDeparture(double value){
		this->lastDeparture = value;
	}

	void setarrivalTime(double value){
		this->arrivalTime = value;
	}

	void setarrivalA(double value){
		this->arrivalA = value;
	}

	void setarrivalB(double value){
			this->arrivalB = value;
	}

	void setdepartureTime(double value){
		this->departureTime = value;
	}

	void update() {
		requisitionInterval[aux] = arrivalB - arrivalA;
		aux++;
		arrivalA = 0.0;
		arrivalB = 0.0;
		departureTime = 0.0;
	}
	//intervalo entre requisições
	double intervalMean(){
		int i = 0;
		double j = 0;
		while(i < aux){
			j = requisitionInterval[i] + j;
			i++;
		}
		return j/aux;
	}
	//tempo de medio de todas as task no sistema
	float taskMean(queue<Task> queue){
		double i = 0;
		float j = 0;
		int h = queue.size();
		cout << "Tasks: " << h << endl;

		while(i < h){
			Task task = queue.front();
			j = task.sim_time + j;
			//cout << "task.sim_time: " << task.sim_time << endl;
			//cout << "j: " << j << endl;
			//cout << "h: " << h << endl;
			queue.pop();
			i++;
		}
		cout << "j: " << j << endl;
		this->totalBusyTime = j;
		return j/h;
	}

	float serviceMeanTime(){
		return totalBusyTime/(lastDeparture-firstArrival);
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
	double mean_processing = 0.775;
	double next_arrival = stats.rand_exp(mean_arrival);
	stats.setfirstArrival(next_arrival);
	queue<Task> queue;
	std::queue<Task> queueStatistics;

	cout << "next_arrival: " << next_arrival << endl;
	while (sim_time < T_MAX) {
		if(!queue.empty()) stats.update();
		if (next_arrival < next_departure) {
			sim_time = next_arrival;
			stats.setarrivalA(next_arrival);
			//cout << "Arrival A: " << next_arrival << endl;
			if (s == IDLE) {
				s = BUSY;
				stats.setarrivalTime(next_arrival);
				next_departure = sim_time + stats.rand_exp(mean_processing);
				stats.setdepartureTime(next_departure);
				cout << "BUSY" << endl;
			} else {
				Task task;
				task.ID = ID++;
				task.sim_time = sim_time;
				queue.push(task);
				cout << "Entrando: " << queue.size() << endl;
			}
			next_arrival = sim_time + stats.rand_exp(mean_arrival);
			stats.setarrivalB(next_arrival);
			//cout << "Arrival B: " << next_arrival << endl;
		} else {
			sim_time = next_departure;
			if (queue.empty()) {
				s = IDLE;
				next_departure = HUGE_VAL;
			} else {
				Task task = queue.back();
				task.sim_time = sim_time - task.sim_time;
				queueStatistics.push(task);
				queue.pop();
				cout << "Saindo..." << endl;
				next_departure = sim_time + stats.rand_exp(mean_processing);
			}
		}
	}
	cout << "next_departure: " << next_departure << endl;
	stats.setlastDeparture(next_departure);
	cout << "1 - Intervalo medio de Tasks no sistema: " << stats.taskMean(queueStatistics) << endl;
	cout << "2 - Intervalo medio de requisicoes: " << stats.intervalMean() << endl;
	cout << "3 - Tempo médio de serviço: " << stats.serviceMeanTime() << endl;
}
