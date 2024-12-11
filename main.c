#include <linux/module.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <linux/cred.h>

MODULE_DESCRIPTION("Kernel module that runs an asymmetric encryption script.");
MODULE_AUTHOR("Joaquin Villagomez and Garrett Houck");
MODULE_LICENSE("GPL");

static int __init simple_driver_init(void)
{
    printk(KERN_NOTICE "Simple-driver: Initialization started\n");

    const char *script_path = "/home/joaquin/Documents/Project/script.sh";
    
    // arguments for the script
    char *args[] = {"/bin/bash", (char *)script_path, NULL};
    
    // environment variables for kernel space
    char *envp[] = {
        "HOME=/home/joaquin",
        "PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin",
        NULL
    };
    
    // call the user-space script
    int ret = call_usermodehelper(args[0], args, envp, UMH_WAIT_EXEC);

    if (ret == 0) {
        printk(KERN_NOTICE "Script executed successfully.\n");
    } else {
        printk(KERN_WARNING "Failed to execute script.");
    }

    return 0;
}

static void __exit simple_driver_exit(void)
{
    printk(KERN_NOTICE "Simple-driver: Exit\n");
}

module_init(simple_driver_init);
module_exit(simple_driver_exit);
