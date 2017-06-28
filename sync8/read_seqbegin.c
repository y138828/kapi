/********************************************************************************
* File Name:	read_seqbegin.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/seqlock.h> 
#include <linux/init.h> 
#include <linux/module.h> 

MODULE_LICENSE("GPL"); 
static int __init read_seqbegin_init(void); 
static void __exit read_seqbegin_exit(void);

seqlock_t seqlock ;

int __init read_seqbegin_init(void) 
{	 
	int ret;

	seqlock_init( &seqlock );      		//初始化顺序锁

	write_seqlock( &seqlock );     		//写者申请顺序锁
	printk("<0>after write_seqlock, sequence: %d\n\n", seqlock.seqcount.sequence);

	write_sequnlock( &seqlock );   		//写者释放顺序锁
	printk("<0>after write_seqlock, sequence: %d\n\n", seqlock.seqcount.sequence);

	ret = read_seqbegin( &seqlock );	//读者访问共享资源前需要调用该函数
	printk("<0>ret = %d\n", ret );
	printk("<0>after write_seqlock, sequence: %d\n\n", seqlock.seqcount.sequence);

	return 0;
}

void __exit read_seqbegin_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(read_seqbegin_init); 
module_exit(read_seqbegin_exit);
