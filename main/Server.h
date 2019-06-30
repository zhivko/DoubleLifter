/*
 * Server.h
 *
 *  Created on: Apr 24, 2019
 *      Author: klemen
 */

#ifndef MAIN_SERVER_H_
#define MAIN_SERVER_H_

SemaphoreHandle_t xSemaphore = NULL;

#define enablePwm 1
#define enableTaskManager 1
#define enableWifiClient 0

bool enableLcd = false;
bool enableMover = false;
bool enableLed = true;

IPAddress serverIP;

#endif /* MAIN_SERVER_H_ */
