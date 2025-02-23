#include <linux/delay.h>
#include <linux/gpio.h>

static int __init usb_fix_for_tmcs(void)
{
	if (loongson_sysconf.workarounds & WORKAROUND_USB_TMCS) {
		gpio_request(13, "gpio13");
		gpio_request(12, "gpio12");
		gpio_request(11, "gpio11");
		gpio_request(9, "gpio9");
		gpio_request(8, "gpio8");

		gpio_direction_output(11, 1);
		msleep(1000);
		gpio_direction_output(13, 0);
		gpio_direction_output(12, 0);
		gpio_direction_output(9, 0);
		gpio_direction_output(8, 0);

		gpio_set_value(8, 1);
		gpio_set_value(13, 1);
		msleep(1000);
		gpio_set_value(9, 1);
		gpio_set_value(12, 1);
	}

	return 0;
}

late_initcall(usb_fix_for_tmcs);
