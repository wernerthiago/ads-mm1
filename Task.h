/*
 * Task.h
 *
 *  Created on: Aug 19, 2017
 *      Author: werner
 */

#ifndef TASK_H_
#define TASK_H_

namespace mm1 {

class Task {
public:
	Task();
	Task(double sim_time);
	virtual ~Task();

	int getSimTime() const {
		return sim_time;
	}

	void setSimTime(int simTime) {
		sim_time = simTime;
	}

private:
	double sim_time;
};

} /* namespace mm1 */

#endif /* TASK_H_ */
