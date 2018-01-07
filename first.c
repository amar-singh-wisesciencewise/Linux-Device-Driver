
/*THIS IS A TEMPLET DRIVER OR BASIC DRIVER
*TEMPLET BECAUSE EVERYTHING THAT WILL GET ADDED WILL COME IN constructor() and
*destructor()
*/

/*There is no main() as main has already been loaded with kernel - other modules get inserted in the running kernel */


#include <linux/module.h>
#include <linux/kernel.h>


MODULE_DESCRIPTION("LINUX DEVICE DRIVER TEMPLET");
MODULE_AUTHOR("AMAR SINGH");
MODULE_LICENSE("GPL");  

/*constructor() is called when module/driver is loaded - during "insmod"*/
/*__init lets kernel know that the function needs execution once*/
static int __init constructor(void)
{
    pr_notice("TEMPLET DRIVER: CALLED FROM THE CONSTRUCTOR");
    return 0;
}

/*destructor() is called when module/driver is unloaded - during "rmmod"*/
static void __exit destructor(void)
{
    pr_notice("TEMPLET DRIVER: CALLED FROM THE DESTRUCTOR");
}

module_init(constructor);
module_exit(destructor);
