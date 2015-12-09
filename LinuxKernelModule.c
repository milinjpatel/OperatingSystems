#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

struct birthday {
	char* name;
	int day;
	int month;
	int year;	
	struct list_head list;
};

static LIST_HEAD(birthday_list);

/* This function is called when the module is loaded. */
int simple_init(void)
{
        printk(KERN_INFO "Linked List Birthday Test\n");

struct birthday *john;
	john = kmalloc(sizeof(*john), GFP_KERNEL);
	john->name = "John";
	john->day = 26;
	john->month = 6;
	john->year = 1991;
	INIT_LIST_HEAD(&john->list);
struct birthday *bob;
	bob = kmalloc(sizeof(*bob), GFP_KERNEL);
	bob->name = "Bob";
	bob->day = 15;
	bob->month = 3;
	bob->year = 1985;
	list_add_tail(&bob->list, &birthday_list);
struct birthday *mary;
	mary = kmalloc(sizeof(*mary), GFP_KERNEL);
	mary->name = "Mary";
	mary->day = 8;
	mary->month = 4;
	mary->year = 1994;
	list_add_tail(&mary->list, &birthday_list);
struct birthday *jill;
	jill = kmalloc(sizeof(*jill), GFP_KERNEL);
	jill->name = "Jill";
	jill->day = 26;
	jill->month = 6;
	jill->year = 1991;
	list_add_tail(&jill->list, &birthday_list);
struct birthday *bart;
	bart = kmalloc(sizeof(*bart), GFP_KERNEL);
	bart->name = "Bart";
	bart->day = 24;
	bart->month = 7;
	bart->year = 1990;
	list_add_tail(&bart->list, &birthday_list);
struct birthday *ptr;
	list_for_each_entry(ptr, &birthday_list, list){
	printk(KERN_INFO "%s: %d/%d/%d", ptr -> name, ptr -> day, ptr -> month, ptr -> year);
}
       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "The module is now removed\n");
struct birthday *ptr, *next;

list_for_each_entry_safe(ptr, next, &birthday_list, list){
	list_del(&ptr -> list);
	kfree(ptr);
}
	list_for_each_entry(ptr, &birthday_list, list){
	printk(KERN_INFO "%s: %d/%d/%d", ptr -> name, ptr -> day, ptr -> month, ptr -> year);
}
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

