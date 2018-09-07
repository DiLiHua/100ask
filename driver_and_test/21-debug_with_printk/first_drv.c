#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>

#include <linux/proc_fs.h>
#include <linux/poll.h>
#include <linux/device.h>

static int major;
static struct class *firstdrv_class;
static struct class_device *firstdrv_class_dev;

volatile unsigned long *gpfcon = NULL;
volatile unsigned long *gpfdat = NULL;

#define debug_printk printk
//#define debug_printk(x...) 

static int first_drv_open (struct inode *inode, struct file *file)
{
	/*����gpioΪ���״̬*/
	printk("--- %s --- \r\n",__func__);
//	debug_printk("-- %s:%d --\r\n",__func__,__LINE__);
	*gpfcon &= ~((0x3<<(4*2))|(0x3<<(5*2))|(0x3<<(6*2))); 
//	debug_printk("-- %s:%d --\r\n",__func__,__LINE__);
	*gpfcon |= ((0x1<<(4*2))|(0x1<<(5*2))|(0x1<<(6*2)));
//	debug_printk("-- %s:%d --\r\n",__func__,__LINE__);

	return 0;
}


static ssize_t first_drv_write (struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
	int val;
	
	printk("--- %s --- \r\n",__func__);
	if (copy_from_user(&val,buf,size))
		return -EFAULT;

	printk("kernel:val = %d\r\n",val);

	if (val == 1){
		//���
//		printk("--- %s:%d ---\r\n",__func__,__LINE__);
		printk(KERN_DEBUG"--- %s:%d ---\r\n",__func__,__LINE__);
		*gpfdat &= ~((1<<4)|(1<<5)|(1<<6));
	}else{
		//���
//		printk("--- %s:%d ---\r\n",__func__,__LINE__);
		printk(KERN_DEBUG"--- %s:%d ---\r\n",__func__,__LINE__);
		*gpfdat |= ((1<<4)|(1<<5)|(1<<6));
	}

	return 0;
}


static struct file_operations first_drv_fops = {
	.owner = THIS_MODULE,
	.open  = first_drv_open,
	.write = first_drv_write, 
};


static int __init first_drv_init(void)
{
	printk("--- %s --- \r\n",__func__);
	//0�Զ������豸��
//	debug_printk("-- %s:%d --\r\n",__func__,__LINE__);
	printk(KERN_DEBUG"--- %s:%d ---\r\n",__func__,__LINE__);
	major = register_chrdev(0,"first_drv",&first_drv_fops);
//	debug_printk("-- %s:%d --\r\n",__func__,__LINE__);
	printk(KERN_DEBUG"--- %s:%d ---\r\n",__func__,__LINE__);

	firstdrv_class = class_create(THIS_MODULE,"firstdrv");
//	debug_printk("-- %s:%d --\r\n",__func__,__LINE__);
	printk(KERN_DEBUG"--- %s:%d ---\r\n",__func__,__LINE__);

	firstdrv_class_dev = class_device_create(firstdrv_class,NULL,MKDEV(major,0),NULL,"xxx");
//	debug_printk("-- %s:%d --\r\n",__func__,__LINE__);
	printk(KERN_DEBUG"--- %s:%d ---\r\n",__func__,__LINE__);

	//gpfcon =(volatile unsigned long *) ioremap(0x56000050,16);
	gpfcon =(volatile unsigned long *)0x56000050;
	gpfdat = gpfcon + 1;

	return 0;
}

static void __exit first_drv_exit(void)
{
	printk("--- %s --- \r\n",__func__);
	unregister_chrdev(111,"first_drv");
	class_device_unregister(firstdrv_class_dev);
	class_destroy(firstdrv_class);
	iounmap(gpfcon);

}

module_init(first_drv_init);
module_exit(first_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhuangzebin@hello.com");
MODULE_DESCRIPTION("My first driver test");
