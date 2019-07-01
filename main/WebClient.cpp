#include "WebClient.h"
#include <esp_task_wdt.h>
#include "WiFiClient.h"

WiFiClient client;
//char server[] = "192.168.1.7";
int a = 1;
int position=15000;

void webClientTask(void * pvParameters) {

	char* webserverIp = (char *)pvParameters;
	IPAddress serverIp;
	serverIp.fromString(webserverIp);
	Serial.printf("IP of server from parameter %s\n", webserverIp);
	char buff[200];
	const char* host = "esp32_door";

	while (true) {
		if (client.connect(serverIp, 81)) {
			Serial.println("connected to server at: " + serverIp.toString());

			position = position + a*1000;
			Serial.println("send request to server...");
			sprintf(buff, "/target1?target1=%d HTTP/1.1", position);
		    client.print(String("GET ") + buff + " HTTP/1.1\r\n" +
		                 "Host: " + host + "\r\n" +
		                 "Connection: close\r\n\r\n");
		    Serial.println("send request to server...end.");

//		    unsigned long timeout = millis();
//		    while (client.available() == 0) {
//		        if (millis() - timeout > 5000) {
//		            Serial.println(">>> Client Timeout !");
//		            client.stop();
//		            break;
//		        }
//		    }

			a = -1*a;
		}
		esp_err_t err = esp_task_wdt_reset();
		if (err != ESP_OK) {
			log_e("WebClient failed to feed WDT! Error: %d", err);
		}
		delay(10000);
	}
	vTaskDelete( NULL );
}
