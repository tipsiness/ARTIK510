#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <artik_module.h>
#include <artik_loop.h>
#include <artik_platform.h>
#include <artik_gpio.h>

struct led_gpio {
	artik_gpio_handle handle;
	artik_gpio_config config;
};

int main() {
	int i;
	artik_gpio_module *gpio = (artik_gpio_module *)artik_request_api_module("gpio");
	artik_error ret = S_OK;
	struct led_gpio led_port[] = {
		{NULL, {ARTIK_A710_GPIO8, "LED", GPIO_OUT, GPIO_DIGITAL, GPIO_EDGE_NONE, 0, NULL }},
	};
	ret = gpio->request(&led_port[0].handle, &led_port[0].config);
	for (i = 0; i < 10; i++) {
		gpio->write(led_port[0].handle, 1);
		usleep(500000);
		gpio->write(led_port[0].handle, 0);
		usleep(500000);
	}g
	pio->release(led_port[0].handle);
	ret = artik_release_api_module(gpio);
	return 0;
}

