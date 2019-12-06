/*
 * Server.h
 *
 *  Created on: Apr 24, 2019
 *      Author: klemen
 */

#ifndef MAIN_SERVER_H_
#define MAIN_SERVER_H_

//extern "C" {
//	#include "alexa.h"
//}


SemaphoreHandle_t xSemaphore = NULL;

#define enablePwm 1
#define enableTaskManager 1
#define enableWifiClient 0

#if enablePwm == 1
	#define enableEncSaver 1
	#if enableEncSaver  == 1
		#include "encoderSaver.h"
		static int encoderSaverCore = 0;
	#endif
#else
#define enableEncSaver 0
#endif


bool enableLcd = false;
bool enableMover = false;
bool enableLed = true;

const char *get_local_ip(void);


IPAddress serverIP;
static const char* hostName = "esp32_door";




#endif /* MAIN_SERVER_H_ */
