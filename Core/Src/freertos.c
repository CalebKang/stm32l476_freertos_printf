/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512 * 4
};
/* Definitions for Debug */
osThreadId_t DebugHandle;
const osThreadAttr_t Debug_attributes = {
  .name = "Debug",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 512 * 4
};
/* Definitions for myTask03 */
osThreadId_t myTask03Handle;
const osThreadAttr_t myTask03_attributes = {
  .name = "myTask03",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
static int task_monitor(void);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void DebugTask(void *argument);
void StartTask03(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Debug */
  DebugHandle = osThreadNew(DebugTask, NULL, &Debug_attributes);

  /* creation of myTask03 */
  myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  float i = 0.0;
  float j = 31200.54256735;
  for(;;)
  {
    osDelay(1000);
    i += 0.001 * 1.0F;
    j += i * j;
    printf("StartDefaultTask : %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f, %3.5f\r\n",
        i, i, i, i, i, i, i, i, i, i, i,
        j, j, j, j, j, j, j, j, j, j, j);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_DebugTask */
/**
* @brief Function implementing the Debug thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DebugTask */
void DebugTask(void *argument)
{
  /* USER CODE BEGIN DebugTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(5000);
    task_monitor();
  }
  /* USER CODE END DebugTask */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
static int task_monitor(void)
{
  char buffer[505];
  vTaskList(buffer);
  {
    printf("\r\n");
    printf("Name          State  Priority  Stack   Num\r\n");
    printf("******************************************\r\n");
    printf((char *)buffer);
    printf("******************************************\r\n");
    printf("Free Heap: %d\r\n", xPortGetMinimumEverFreeHeapSize());
  }
  return 0;
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
