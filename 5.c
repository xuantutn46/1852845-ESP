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


int t2=200;
int t3=300;
int h2=10;
int h3=5;
xTimerHandle T2=NULL;
xTimerHandle T3=NULL;

void ATimerCallback (xTimerHandle pxTimer){
    int tID = (int) pvTimerGetTimerID(pxTimer);

    if (tID==0){
        static int count = 1;
        if(count <=h2){
            printf("Times %d: Ahihi at %d ms\n",count,(int)clock());
            if(count==h2){
                printf("End of Ahihi\n");
            }
            else xTimerReset(T2,0);
            count++;
        }
    }
    if (tID==1){
        static int count = 1;
        if(count<=h3){
            printf("Times %d: Ihaha at %d ms\n",count,(int)clock());
            if(count==h3){
                printf("End of Ihaha\n");
            }
            else xTimerReset(T3,0);
            count++;
        }
    }
   
}

void app_main(void)
{
    T2 = xTimerCreate("ahihi",t2,pdFALSE,(void*)0,ATimerCallback);
    T3 = xTimerCreate("ihaha",t3,pdFALSE,(void*)1,ATimerCallback);
    xTimerStart(T2,0);
    xTimerStart(T3,0);

}
