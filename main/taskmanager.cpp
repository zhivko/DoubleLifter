#include "Taskmanager.h"
#include <esp_task_wdt.h>
#include <memory>

void taskmanageTask(void *params) {
	esp_task_wdt_add(NULL);
	while (true) {
		UBaseType_t taskCount = uxTaskGetNumberOfTasks();
		std::unique_ptr<TaskStatus_t[]> taskList(new TaskStatus_t[taskCount]);
		uint32_t ulTotalRunTime;
		UBaseType_t retrievedTaskCount = uxTaskGetSystemState(taskList.get(),
				taskCount, &ulTotalRunTime);
		printf("time[us]: %" PRIu64 " core: %d, freeHeap: %u, largest: %u\n",
				esp_timer_get_time(), xPortGetCoreID(),
				heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
				heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));

		printf("%15s%10s%10s%10s%10s%10s%10s%10s%10s\n", "NAME", "ID", "STATE",
				"PRIO", "BASE", "TIME", "CPU", "STACK", "CORE");

		for (int task = 0; task < retrievedTaskCount; task++) {
			printf("%15s%10d%10s%10d%10d%10ull%10.2f%10d%10d\n",
					taskList[task].pcTaskName, taskList[task].xTaskNumber,
					taskList[task].eCurrentState == eRunning ? "Running" :
					taskList[task].eCurrentState == eReady ? "Ready" :
					taskList[task].eCurrentState == eBlocked ? "Blocked" :
					taskList[task].eCurrentState == eSuspended ? "Suspended" :
					taskList[task].eCurrentState == eDeleted ?
							"Deleted" : "Unknown",
					taskList[task].uxCurrentPriority,
					taskList[task].uxBasePriority,
					taskList[task].ulRunTimeCounter,
					(float) taskList[task].ulRunTimeCounter
							/ (float) ulTotalRunTime,
					taskList[task].usStackHighWaterMark,
					taskList[task].xCoreID);
		}
		esp_err_t err = esp_task_wdt_reset();
		if (err != ESP_OK) {
			log_e("TaskManager - Failed to feed WDT! Error: %d", err);
		}
		vTaskDelay(pdMS_TO_TICKS(20000));
	}
}
