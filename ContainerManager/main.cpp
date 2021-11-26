#include <cstdio>
#include <stdlib.h>
#include <hiredis/adapters/libevent.h>
#include <hiredis/hiredis.h>
#include <event.h>
#include <hiredis/async.h>
#include <string>
#include <iostream>

using namespace std;

void my_callback(struct redisAsyncContext* pc, void* reply, void* privdata)
{
    string port, IP, room_no;
    // 若指定的服务器是自己才创建房间
    redisReply* my_reply = (redisReply*)reply;
    if (string(my_reply->element[0]->str) != "message") {
        return;
    }
    // reply 中包含 IP:房间号
    string orig_content(my_reply->element[2]->str);
    int pos = orig_content.find(':');
    IP = orig_content.substr(0, pos);
    room_no = orig_content.substr(pos + 1);
    // string IP(my_reply->element[2]->str);
    string my_IP(getenv("MY_IP"));
    if (IP != my_IP) {
        return;
    }

    string cmd = "~/nginx_test/create_room.sh " + room_no;
    FILE* pf = popen(cmd.c_str(), "r");
    if (pf != nullptr) {
        char buff[1024];
        fread(buff, 1, sizeof(buff), pf);
        port.append(buff);
        cout << "callback port : " << port << endl;
        pclose(pf);
    }

    // 这边异步调用会有问题，说是 vs 调试说是缺少 async.c 但是 subscribe 没问题，官方示例也没有关于 publish 的例子
    // redisAsyncCommand(pc, NULL, NULL, "publish server_port %s", port.c_str());
    // 还是说回调函数不能设置异步

    redisContext* spc = redisConnect("192.168.153.131", 6379);
    if (spc != nullptr) { 
        freeReplyObject(redisCommand(spc, "publish server_port %s", port.c_str()));
        redisFree(spc);
    }
}

int main()
{
    event_base* base = event_base_new();
    // 登陆服务器 IP
    redisAsyncContext* pc = redisAsyncConnect("192.168.153.131", 6379);
    redisLibeventAttach(pc, base);
     
    redisAsyncCommand(pc, my_callback, NULL, "subscribe create_room");

    event_base_dispatch(base);

    return 0;
}