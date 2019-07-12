/*
 * Server.h
 *
 *  Created on: Apr 24, 2019
 *      Author: klemen
 */

#ifndef MAIN_SERVER_H_
#define MAIN_SERVER_H_

SemaphoreHandle_t xSemaphore = NULL;

#define enablePwm 0
#define enableTaskManager 1
#define enableWifiClient 0

bool enableLcd = true;
bool enableMover = false;
bool enableLed = true;

IPAddress serverIP;
static const char* hostName = "esp32_door";


#endif /* MAIN_SERVER_H_ */
