/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <time.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h."
#include "FreeRTOSConfig.h"
#include "freertos/timers.h"
#include "freertos/queue.h"

static const uint32_t queue_length = 4;
static QueueHandle_t aQueue;

typedef struct AMessage{
    int eDataID;
    char *IDataValue;
}xMessage;

void receptional_task(void *pvParameter){
    static int taskID = 1;
    while(1){
        xMessage inputMessage;
        inputMessage.eDataID = taskID;
        switch(taskID){
            case 1:
                inputMessage.IDataValue = "This message is for functional task 1";
                break;
            case 2:
                inputMessage.IDataValue = "This message is for functional task 2";
                break;
            case 3:
                inputMessage.IDataValue = "This message is for functional task 3";
                break;    
            case 4:
                inputMessage.IDataValue = "No task is execute";
                break;
            default:
                printf("ERROR task ID\n");
                break;
        }
        xQueueSend(aQueue, &inputMessage,10);
        if(taskID>=4) taskID = 1;
        else taskID++;
        vTaskDelay(1000/portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}

void functional_task_1(void *pvParameter){
    xMessage message;
    while(1){
        if(aQueue !=0){
            if(xQueuePeek(aQueue,(void*)&message,10)==pdTRUE){
                if(message.eDataID == 1){
                    if(xQueueReceive(aQueue,(void*)&message,10)==pdPASS){
                        printf("Task 1 receive message: %s with data id = %d.\n",message.IDataValue, message.eDataID);
                    }
                }
            }
        }
        vTaskDelay(1000/portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}
void functional_task_2(void *pvParameter){
    xMessage message;
    while(1){
        if(aQueue !=0){
            if(xQueuePeek(aQueue,(void*)&message,10)==pdTRUE){
                if(message.eDataID == 2){
                    if(xQueueReceive(aQueue,(void*)&message,10)==pdPASS){
                        printf("Task 2 receive message: %s with data id = %d.\n",message.IDataValue, message.eDataID);
                    }
                }
            }
        }
        vTaskDelay(1000/portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}
void functional_task_3(void *pvParameter){
    xMessage message;
    while(1){
        if(aQueue !=0){
            if(xQueuePeek(aQueue,(void*)&message,10)==pdTRUE){
                if(message.eDataID == 3){
                    if(xQueueReceive(aQueue,(void*)&message,10)==pdPASS){
                        printf("Task 3 receive message: %s with data id = %d.\n",message.IDataValue, message.eDataID);
                    }
                }
            }
        }
        vTaskDelay(1000/portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}
void error_task(void *pvParameter){
    xMessage message;
    while(1){
        if(aQueue !=0){
            if(xQueuePeek(aQueue,(void*)&message,10)==pdTRUE){
                if(message.eDataID == 4){
                    if(xQueueReceive(aQueue,(void*)&message,10)==pdPASS){
                        printf("Error: %s with data id = %d.\n",message.IDataValue, message.eDataID);
                    }
                }
            }
        }
        vTaskDelay(1000/portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    aQueue = xQueueCreate(queue_length, sizeof(xMessage));
    xTaskCreatePinnedToCore(&receptional_task,"receptional task",2048,NULL,2,NULL,1);
    xTaskCreatePinnedToCore(&functional_task_1,"functional_task_1",2048,NULL,1,NULL,1);
    xTaskCreatePinnedToCore(&functional_task_2,"functional_task_2",2048,NULL,1,NULL,1);
    xTaskCreatePinnedToCore(&functional_task_3,"functional_task_3",2048,NULL,1,NULL,1);
    xTaskCreatePinnedToCore(&error_task,"error task",2048,NULL,1,NULL,1);


}
