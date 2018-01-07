#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

/*THIS IS A SIMPLE USB DRIVER WHICH REGISTERS A VENDOR AND PRODUCT ID TO the "usbcore" driver. _probe will be run upon hot pluging and _disconnet will be run upon pen drive pull. The dmesg logs can be inspected to see the action.

NOTE: ADD YOUR VENDOR AND PRODUCT ID
ALSO: remove usb_storage and depending modules.  

*/
 
MODULE_DESCRIPTION("USB Pen-Drive Registration Driver");
MODULE_AUTHOR("AMAR SINGH");
MODULE_LICENSE("GPL");

/*executes upon hot plugin*/
static int _probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	pr_notice("PD_driver: Pen-Drive plugged in with V:P id (%04X:%04X) \n", id->idVendor, id->idProduct);
	return 0;
}

/*upon pen drive pull*/
static void _disconnect(struct usb_interface *interface)
{
	pr_notice("PD_driver: Pen-Drive disconnected \n");
}


static struct usb_device_id _id_table[] =
{
	{ USB_DEVICE(0x8564, 0x1000) }, /*insert your device's vendor and product id - use "lsusb -v" command or "usb-devices" script to know your device details*/
	{}
};

/*helps in auto loading of driver */
MODULE_DEVICE_TABLE (usb, _id_table);
 
static struct usb_driver PD_driver =
{
	.name = "PD_driver",
	.id_table = _id_table,
	.probe = _probe,
	.disconnect = _disconnect,
};

 
static int __init constructor(void)
{
	pr_notice("PD_driver: FROM CONSTRUCTOR");
	return usb_register(&PD_driver);
}
 
static void __exit destructor(void)
{
	pr_notice("PD_driver: FROM DESTRUCTOR");
	usb_deregister(&PD_driver);
}
 
module_init(constructor);
module_exit(destructor);

