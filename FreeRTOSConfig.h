#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configCPU_CLOCK_HZ                  (8000000UL)
#define configTICK_RATE_HZ                  (1000UL)

#define configMAX_PRIORITIES                5
#define configMINIMAL_STACK_SIZE            128
#define configMAX_TASK_NAME_LEN             16

#define configTOTAL_HEAP_SIZE              (10 * 1024)

#define configUSE_PREEMPTION                1
#define configUSE_IDLE_HOOK                 0
#define configUSE_TICK_HOOK                 0

#define configUSE_MUTEXES                   1
#define configUSE_COUNTING_SEMAPHORES       1

#define configUSE_TIMERS                    0

#define configUSE_16_BIT_TICKS              0
#define configSUPPORT_DYNAMIC_ALLOCATION    1

#define INCLUDE_vTaskDelay                  1
#define INCLUDE_vTaskDelete                 1
#define INCLUDE_vTaskSuspend                1

#define configPRIO_BITS                     4

#define configKERNEL_INTERRUPT_PRIORITY     (255 << (8 - configPRIO_BITS))
#define configMAX_SYSCALL_INTERRUPT_PRIORITY (5 << (8 - configPRIO_BITS))

#endif