#include <stdio.h>
#include "user_opt.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <hiredis/hiredis.h>
#include <string>

void AddUser(const char* _name, const char* _password)
{
	char buff[1024] = {0};

	sprintf(buff, "./add_user.sh %s %s", _name, _password);

	system(buff);
}

bool CheckUser(const char* _name, const char* _password_dgst)
{
	bool bRet = false;
	if(fork() > 0) {
		int iStatus = 0;
		wait(&iStatus);
		if(iStatus == 0) {
			bRet = true;
		}
	}			
	else {
		execlp("./check_user.sh", "./check_user.sh", _name, _password_dgst,  NULL);
	}

	return bRet;
}

static int g_cur_select = 0;
std::string CreateContainer(int _room_no)
{
	//return "x.x.x.x xxxx";
	//
	// 1 confirm which server t o create container
	// 其实这俩是一套，但是没装第二个系统假装两个主机
	std::string port;
	// 先暂时不测分布式了
	std::string server_array[2] = {"192.168.153.131", "192.168.153.132"};
	std::string cur_server = server_array[g_cur_select];
	++ g_cur_select;
	g_cur_select %= (sizeof(server_array) / sizeof(server_array[0]));
	// 2 send create container req to that server
	// publish a piece of message to channel "create_room"
	auto pc = redisConnect("127.0.0.1", 6379);	
//	auto pc = redisConnect(cur_server.c_str(), 6379);
	if(pc != nullptr) {
		// message contains IP only
		freeReplyObject(redisCommand(pc, "publish create_room %s:%d", cur_server.c_str(), _room_no));
		// 3 wait for new container's port
		freeReplyObject(redisCommand(pc, "subscribe server_port"));
		redisReply *reply = nullptr;
		if(redisGetReply(pc, (void**)&reply) == REDIS_OK) {
			port.append(reply->element[2]->str);
			freeReplyObject(reply);
		}
		redisFree(pc);
	}
	return cur_server + " " + port;
	
	// 4 return IP + PORT
	/*
	std::string ret;
	FILE *pf = popen("./create_room.sh", "r");
	if(pf != NULL) {
		char buff[1024];
		fread(buff, 1, sizeof(buff), pf);
		ret = std::string(buff);
		pclose(pf);
	}
	return ret;
	*/
}

std::string CheckRoom(const char* _room_no) {
	//return "x.x.x.x xxxx"
	std::string ret;

	auto pc = redisConnect("127.0.0.1", 6379);
	if(pc != nullptr) {
		redisReply *reply = (redisReply*)redisCommand(pc, "get room_no%s", _room_no);
		if(reply->str != nullptr)
			ret.append(reply->str);
		freeReplyObject(reply);
		redisFree(pc);
	}
	return ret;

	/*	
	if(fork() > 0) {
		int iStatus = 0;
		wait(&iStatus);
		if(iStatus == 0) {
			bRet = true;
		}
	} 
	else {
		execlp("./check_room.sh", "./check_room.sh", _room_no, NULL);
	}
	return bRet;
	*/
}
