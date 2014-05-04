#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "socket_server.h"

struct socket_server * ss;

/*
    收到到网络数据
    将接收到的客户端数据直接打印返回去(echo)

    result为网络消息的结构
*/
void
OnReceive(struct socket_message result){
	// 发送数据到客户端
	socket_server_send(ss, result.id, result.data, result.ud);
}

int
main(int argc, char *argv[]){
	// 创建 socket_server
	ss = socket_server_create(); 

	// 监听 127.0.0.1 8000
	int listen_id = socket_server_listen(ss, 100, "127.0.0.1", 8000, 32); 

	// 纳入事件管理
        socket_server_start(ss, 200, listen_id); 
	
	struct socket_message result; // 声明一个soket消息的结构
        for (;;)
        {

            int type = socket_server_poll(ss, &result, NULL); // 事件循环

		switch (type)
		{
		case SOCKET_EXIT: // 退出Socket
			goto EXIT_LOOP;

		case SOCKET_DATA: // Socket有数据到来
			OnReceive(result);
			printf("data(%lu) [id=%d] %s\n", result.opaque, result.id, result.data);
			break;

		case SOCKET_CLOSE: // 关闭Socket
			printf("close(%lu) [id=%d]\n", result.opaque, result.id);
			break;

		case SOCKET_OPEN: // 打开Socket
			printf("open(%lu) [id=%d] %s\n", result.opaque, result.id, result.data);
			break;

		case SOCKET_ERROR: // Socket错误
			printf("error(%lu) [id=%d]\n", result.opaque, result.id);
			break;

		case SOCKET_ACCEPT: // 接受客户端链接
			printf("accept(%lu) [id=%d %s] from [%d]\n", result.opaque, result.ud,
			result.data, result.id);
			socket_server_start(ss, 300, result.ud);
			break;
		}
	}

	// 关闭 socket_server
	EXIT_LOOP: socket_server_release(ss); 
	return 0;
}
