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
static QueueHandle_t Q;

typedef struct {
    int ID;
    char *IDValue;
}SMess;

void input_task(void *pvParameter){
    static int taskID = 1;
    while(1){
        SMess cmt;
        cmt.ID = taskID;
        if (taskID==1){
            cmt.IDValue = "Task 1";
        }else if (taskID==2){
            cmt.IDValue = "Task 2";
        }else if (taskID==3){
            cmt.IDValue = "Task 3";
        }else if (taskID==4){
            cmt.IDValue = "No task is execute";
        }else {
            printf("ERROR task ID\n");
        }
        xQueueSend(Q, &cmt,10);
        if(taskID>=4) taskID = 1;
        else taskID++;
        vTaskDelay(1000/portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}

void task(void *pvParameter){
    SMess message;
    while(1){
        for (int i=1;i<=4;){
            if(xQueuePeek(Q,(void*)&message,10)==pdTRUE){
                if(message.ID != 4){
                    if(xQueueReceive(Q,(void*)&message,10)==pdPASS){
                        printf("Task %d receive message: %s with id = %d.\n" ,i,message.IDValue, message.ID);
                    }
                } else if(message.ID == 4){
                    if(xQueueReceive(Q,(void*)&message,10)==pdPASS){
                        printf("Error: %s with id = %d.\n",message.IDValue, message.ID);
                        i=1;
                    }
                }i++;
            }
        }
        vTaskDelay(1000/portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}


void app_main(void)
{
    Q = xQueueCreate(queue_length, sizeof(SMess));
    xTaskCreatePinnedToCore(&input_task,"input task",2048,NULL,2,NULL,1);
    xTaskCreatePinnedToCore(&task,"task1",2048,NULL,1,NULL,1);
    xTaskCreatePinnedToCore(&task,"task2",2048,NULL,1,NULL,1);
    xTaskCreatePinnedToCore(&task,"task3",2048,NULL,1,NULL,1);
    xTaskCreatePinnedToCore(&task,"error",2048,NULL,1,NULL,1);

}
