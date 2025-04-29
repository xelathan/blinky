#include <zephyr/sys/printk.h>

#include "say_hello.h"

void say_hello(void) {
    printk("Hello World\r\n");
}