/**
 * Simple character device driver for educational purposes.
 * Provides (random) Magic 8-ball answers via a char device driver.
 *
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/random.h>
#include <asm/uaccess.h>

#include "8ball.h"

#define MAGIC8BALL_DRIVER_NAME    "magic8ball"
#define MAGIC8BALL_DRIVER_VERSION "0.1"


/* Chosen answer buffer */
#define MAX_BUF_SIZE 256
char answer[MAX_BUF_SIZE];

/* Char device operation handlers*/

/* Called on open syscall */
static int magic8ball_open(struct inode *inode, struct file *file)
{
	printk(KERN_DEBUG "8ball: Open\n");
	choose_answers(answer, MAX_BUF_SIZE);
	return 0;
}

/* Called on close syscall */
static int magic8ball_close(struct inode *inode, struct file *file)
{
	printk(KERN_DEBUG "8ball: Close\n");
	return 0;
}


/* Called on read syscall */
static ssize_t magic8ball_read(struct file *file, char __user *buf, size_t count, loff_t *ppos) 
{
	printk(KERN_DEBUG "8ball: Read\n");

	int ret;
	int answer_size = strlen(answer);


	/* Write answer to user space */

	if (*ppos >= answer_size)
		/* All of the buffer written, so nothing else to send */
		return 0;
	
	if (*ppos + count > answer_size)
		/* Userspace asked for more data than we have. */
		count = answer_size - *ppos;

	/* Copy from kernel buffer to userspace buffer */
	ret = copy_to_user(buf, &answer[*ppos], count);
	if (ret !=0 ) {
		printk(KERN_ERR "8ball: Error writing to userspace\n");
		return -EFAULT;
	}

	*ppos += count;

	/* Return how much we sent to user space */
	return count;
}


/* Called on write syscall */
static ssize_t magic8ball_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos) 
{
	printk(KERN_ERR "8ball: You think you are wiser than the Magic 8-ball?\n");
	return -EPERM;
}

/* File operations on char device */
static struct file_operations magic8ball_fops = {
	.owner 		= THIS_MODULE,
	.open  		= magic8ball_open,
	.read  		= magic8ball_read,
	.write 		= magic8ball_write,
	.release 	= magic8ball_close
};

/* Char device description */
static struct miscdevice magic8ball_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = MAGIC8BALL_DRIVER_NAME,
	.fops  = &magic8ball_fops
};

/* Function called on inmod run */
static int __init magic8ball_init(void)
{
	int ret;
	
	ret = misc_register(&magic8ball_device);
	if (ret < 0) {
		printk(KERN_ERR "8ball: Could not register device.\n");
		return ret;
	}
	
	printk(KERN_DEBUG "8ball: Module loaded.\n");
	return 0;
}


/* Function called on rmmod run */
static void __exit magic8ball_exit(void)
{
	misc_deregister(&magic8ball_device);
	printk(KERN_DEBUG "8ball: Module unloaded.\n");
}

/* Glue init and exit functions to kernel module framework */
module_init(magic8ball_init);
module_exit(magic8ball_exit);

MODULE_AUTHOR("Alex Juncu <alexj@linux.com>");
MODULE_DESCRIPTION("Simple char driver for generating answers to life");
MODULE_VERSION(MAGIC8BALL_DRIVER_VERSION);
MODULE_LICENSE("GPL");


