#include <stdio.h>
#include <stdlib.h>

#include "skynet.h"
#include "skynet_module.h"

struct mod{
	int a;
	int b;
	int c;
};

int
main(int argc, char *argv[]){
	skynet_module_init("./?.so"); // 初始化模块，赋予它寻找模块的路径

	struct skynet_module * m = skynet_module_query("mod"); // 查询 获得或者并加载模块

	struct mod *inst= skynet_module_instance_create(m); // 执行模块中的 mod_create() 函数
	inst->a=10; printf("set a=%d\n",inst->a);
	inst->b=34; printf("set b=%d\n",inst->b);

	// 执行模块中的 mod_init() 函数
	if(skynet_module_instance_init(m,inst,NULL,"wangdali")==0) {
		printf("get c=%d (c=a+b)\n",inst->c);
	}

	skynet_module_instance_release(m,inst); // 执行模块中的 mod_release() 函数 
	return 0;
}

/*
  skynet_module 的原理：
	1、先用 skynet_module_init() 分配一个 modules 结构。
	   这个结构主要用来记录有多少个模块在数组中 ，寻找模块的路径;
	   是否上锁，以及一个结构的数组，用来存放每个模块的相关数据。

	2、主要使用 skynet_module_query() 函数来搜索 modules 结构中的模块数组。
	   看看是否模块在数组中，如果存在则直接返回这个模块的数组，否则尝试打开
	   模块的.so文件以及模块内的函数。

	3、还有 skynet_module_insert() 函数主要用来将一个模块的结构，插入
	   modules 结构中数组的最后面。 
*/
