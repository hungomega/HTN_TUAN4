#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"

/* RCC */
#define RCC_APB2ENR     (*(volatile uint32_t *)0x40021018UL)

/* GPIOA */
#define GPIOA_CRL       (*(volatile uint32_t *)0x40010800UL)
#define GPIOA_ODR       (*(volatile uint32_t *)0x4001080CUL)

/* Enable GPIOA clock */
#define RCC_IOPAEN      (1UL << 2)

/* LED pins */
#define LED1_PIN        0   // PA0
#define LED2_PIN        1   // PA1
#define LED3_PIN        2   // PA2


/* ================= GPIO ================= */

static void LED_Init(void)
{
    /* Enable clock for GPIOA */
    RCC_APB2ENR |= RCC_IOPAEN;

    /*
     * PA0, PA1, PA2:
     * Output push-pull, 2 MHz
     *
     * Each pin uses 4 bits in GPIOA_CRL.
     * 0x2 = Output push-pull, 2 MHz
     */

    GPIOA_CRL &= ~(0xFFFUL);
    GPIOA_CRL |=  (0x222UL);

    /* Initially turn all LEDs OFF */
    GPIOA_ODR &= ~((1UL << LED1_PIN) |
                   (1UL << LED2_PIN) |
                   (1UL << LED3_PIN));
}


/* Toggle one LED */
static void LED_Toggle(uint32_t pin)
{
    GPIOA_ODR ^= (1UL << pin);
}


/* ================= LED BLINK ================= */

/*
 * frequency:
 *
 * 0.1 Hz -> toggle every 5000 ms
 * 1 Hz   -> toggle every 500 ms
 * 10 Hz  -> toggle every 50 ms
 */
static void LED_Blink(uint32_t pin, uint32_t delay_ms)
{
    LED_Toggle(pin);

    vTaskDelay(pdMS_TO_TICKS(delay_ms));
}


/* ================= TASKS ================= */

static void LED1_Task(void *argument)
{
    (void)argument;

    while (1)
    {
        LED_Blink(LED1_PIN, 5000);
    }
}


static void LED2_Task(void *argument)
{
    (void)argument;

    while (1)
    {
        LED_Blink(LED2_PIN, 500);
    }
}


static void LED3_Task(void *argument)
{
    (void)argument;

    while (1)
    {
        LED_Blink(LED3_PIN, 50);
    }
}


/* ================= MAIN ================= */

int main(void)
{
    LED_Init();

    xTaskCreate(
        LED1_Task,
        "LED1",
        128,
        NULL,
        1,
        NULL
    );

    xTaskCreate(
        LED2_Task,
        "LED2",
        128,
        NULL,
        1,
        NULL
    );

    xTaskCreate(
        LED3_Task,
        "LED3",
        128,
        NULL,
        1,
        NULL
    );

    vTaskStartScheduler();

    while (1)
    {
    }
}