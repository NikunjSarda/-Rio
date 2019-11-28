/*
 * building.h
 *
 *  Created on: Nov 20, 2019
 *      Author: rio
 */

#ifndef BUILDING_H_
#define BUILDING_H_

class Building {
public:
	int buildingId;
	int executeTime;
	int totalTime;
	Building (){
		buildingId = 0;
		executeTime = 0;
		totalTime = 0;
	}
};

#endif /* BUILDING_H_ */
