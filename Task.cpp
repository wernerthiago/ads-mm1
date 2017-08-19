/*
 * Task.cpp
 *
 *  Created on: Aug 19, 2017
 *      Author: werner
 */

#include "Task.h"

namespace mm1 {

Task::Task() {
	// TODO Auto-generated constructor stub
	sim_time = 0;
}

Task::Task(double sim_time){
	this->sim_time = sim_time;
}

Task::~Task() {
	// TODO Auto-generated destructor stub
}

} /* namespace mm1 */
