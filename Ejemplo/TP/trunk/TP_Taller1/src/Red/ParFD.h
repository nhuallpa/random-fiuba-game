/*
 * ParFD.h
 *
 *  Created on: 11/11/2013
 *  Last Amended: 11/11/2013
 *      Author: natuchis
 */

#ifndef PARFD_H_
#define PARFD_H_

struct ParFD {
	int fdEnt;
	int fdSal;

	ParFD();
	ParFD(int fdEnt, int fdSal);
};

#endif /* PARFD_H_ */
