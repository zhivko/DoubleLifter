#include "Taskmanager.h"
#include <esp_task_wdt.h>


void taskmanageTask(void * pvParameters){
	TaskStatus_t *pxTaskStatusArray = nullptr;
	volatile UBaseType_t uxArraySize;
	uint32_t ulTotalRunTime;
	char outputBuffer[256];

	while(true){
		uxArraySize = uxTaskGetNumberOfTasks();

		if(pxTaskStatusArray != nullptr) //Free memory
			delete pxTaskStatusArray;

		pxTaskStatusArray = (TaskStatus_t*) pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));
		uxArraySize = uxTaskGetSystemState(pxTaskStatusArray, uxArraySize, &ulTotalRunTime);
		sprintf(outputBuffer, "%15s%15s%15s%15s%15s%15s%15s%15s%15s\r\n", "NAME", "ID", "STATE", "PRIO", "BASE", "TIME", "CPU", "STACK", "CORE");
		Serial.print(outputBuffer);

		for(int i = 0; i < uxArraySize; i++){

/*
			vTaskGetInfo(
							  pxTaskStatusArray[i].xHandle,
			                  &xTaskDetails,
			                  pdTRUE,
			                  eInvalid );
			uint32_t taskWatermark = xTaskDetails.usStackHighWaterMark;
			((tskTCB*)pxTaskStatusArray[i].xHandle)-

			pxTaskStatusArray[i].
*/

			sprintf(outputBuffer, "%15s", pxTaskStatusArray[i].pcTaskName);
			Serial.print(outputBuffer);
			sprintf(outputBuffer, "%15u", pxTaskStatusArray[i].xTaskNumber);
			Serial.print(outputBuffer);



			switch (pxTaskStatusArray[i].eCurrentState){
			case eRunning:
				sprintf(outputBuffer, "%15s", "running");
				Serial.print(outputBuffer);
				break;
			case eReady:
				sprintf(outputBuffer, "%15s", "ready");
				Serial.print(outputBuffer);
				break;
			case eBlocked:
				sprintf(outputBuffer, "%15s", "blocked");
				Serial.print(outputBuffer);
				break;
			case eSuspended:
				sprintf(outputBuffer, "%15s", "suspended");
				Serial.print(outputBuffer);
				break;
			case eDeleted:
				sprintf(outputBuffer, "%15s", "deleted");
				Serial.print(outputBuffer);
				break;
			default:
				sprintf(outputBuffer, "%15s", "unkown");
				Serial.print(outputBuffer);
				break;
			}

			sprintf(outputBuffer, "%15u", pxTaskStatusArray[i].uxCurrentPriority);
			Serial.print(outputBuffer);
			sprintf(outputBuffer, "%15u", pxTaskStatusArray[i].uxBasePriority);
			Serial.print(outputBuffer);
			sprintf(outputBuffer, "%15u", pxTaskStatusArray[i].ulRunTimeCounter);
			Serial.print(outputBuffer);
			sprintf(outputBuffer, "%15f", (float) pxTaskStatusArray[i].ulRunTimeCounter / (float) ulTotalRunTime);
			Serial.print(outputBuffer);
			sprintf(outputBuffer, "%15d", pxTaskStatusArray[i].usStackHighWaterMark);
			Serial.print(outputBuffer);
			sprintf(outputBuffer, "%15d", pxTaskStatusArray[i].xCoreID);
			Serial.print(outputBuffer);
			sprintf(outputBuffer, "\r\n");
			Serial.print(outputBuffer);
		}
	    esp_err_t err = esp_task_wdt_reset();
	    if(err != ESP_OK){
	        log_e("Failed to feed WDT! Error: %d", err);
	    }
		delay(4000);
	}
}
