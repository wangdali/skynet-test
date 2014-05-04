#include <stdio.h>
#include <stdlib.h>

struct mod{
	int a;
	int b;
	int c;
};

/*
    创建服务
    主要用来分配内存和初始化工作，
    Skynet可能有些服务不需要这个函数。

    返回一个指针，可以自定义数据结构，把它传给mod_init()使用。
*/
struct mod *
mod_create(void){
	struct mod * inst = malloc(sizeof(*inst));
	inst->a = 0;
	inst->b = 0;
	inst->c = 0;
	printf("this is mod_create\n");
	return inst;
}

/*
    释放服务
    主要用来清理 mod_create() 中分配的内存，传入 mod_create() 返回的指针。
*/
void
mod_release(struct mod * inst){
	printf("this is mod_release\n");
	free(inst); // 释放掉 mod_create() 中分配的内存 
}

/*
    初始化服务
    服务的初始化工作，在Skynet中主要用来注册返回函数和执行skynet_command()指令等。
    这里相当于放主要逻辑的地方。

    inst 为 mod_create() 返回的指针
    ctx 这个在Skynet使用，即Skynet_Context上下文结构。
    parm 这个为参数，可以传任意内容给mod_init使用，可给skynet_command使用。

    返回一个int整数，主要用来判断执行是否成功。
*/
int
mod_init(struct mod * inst, void *ctx, const char * parm){
	printf("this is mod_init\n");
	printf("parm=%s\n",parm); // 打印参数parm，可以传递一些参数给skynet_command()等用。
	inst->c = inst->a + inst->b; // 计算 c = a+b

	// 这里买有使用skynet_callback()和 skynet_command()
	// 因为他们是 Skynet 框架的函数，我们没有用到框架的其他东西。
	return 0;
}
