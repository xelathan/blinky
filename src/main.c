#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#include "say_hello.h"

#define BLINK_DELAY 500
#define BLINK_LED_NODE DT_ALIAS(blink_led)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(BLINK_LED_NODE, gpios);

int main(void) {
    int ret;
    bool ledState = true;

    if (!gpio_is_ready_dt(&led)) {
        return 0;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

    if (ret != 0) {
        return 0;
    }

    for (;;) {
        ret = gpio_pin_toggle_dt(&led);
        if (ret != 0) {
            return 0;
        }

        ledState = !ledState;
        say_hello();
        k_msleep(BLINK_DELAY);
    }
}