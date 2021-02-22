/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MYPID_H__
#define __MYPID_H__

#include "main.h"


typedef struct {

	/* Controller gains */
	float Kp;
	float Ki;
	float Kd;

//	/* Derivative low-pass filter time constant */
//	float tau;

	/* Output limits */
	float limMin;
	float limMax;
	
	/* Integrator limits */
	float limMinInt;
	float limMaxInt;

	/* Sample time (in seconds) */
	float T;

	/* Controller "memory" */
	float integrator;
	float prevError;			/* Required for integrator */
//	float differentiator;
//	float prevMeasurement;		/* Required for differentiator */

	/* Controller output */
	float out;

} PIDController;

void  PIDController_Init(PIDController *pid);
float PIDController_Update(PIDController *pid, float setpoint, float measurement);






#endif /* __MYPID_H__ */

/**************END OF FILE*****************/
