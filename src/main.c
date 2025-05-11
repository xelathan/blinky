#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#ifdef CONFIG_SAY_HELLO
#include "say_hello.h"
#endif

#define BLINK_DELAY 1000
#define BLINK_LED_NODE DT_ALIAS(blink_led)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(BLINK_LED_NODE, gpios);

void work_handler(struct k_work* work);
void timer_handler(struct k_timer* timer);

K_WORK_DEFINE(my_work, work_handler);
K_TIMER_DEFINE(my_timer, timer_handler, NULL);

void work_handler(struct k_work* work) {
    int ret;

    ret = gpio_pin_toggle_dt(&led);
    if (ret < 0) {
        printk("Failed to toggle LED\r\n");
    }

    printk("Work flags: %d\r\n", work->flags);
#ifdef CONFIG_SAY_HELLO
    say_hello();
#endif
}

void timer_handler(struct k_timer* timer) {
    printk("Timer status: %d\r\n", timer->status);
    k_work_submit(&my_work);
}

int main(void) {
    int ret;

    if (!gpio_is_ready_dt(&led)) {
        printk("GPIO not ready\r\n");
        return 0;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

    if (ret < 0) {
        printk("Failed configure GPIO\r\n");
        return 0;
    }

    k_timer_start(&my_timer, K_MSEC(10000), K_MSEC(BLINK_DELAY));
}