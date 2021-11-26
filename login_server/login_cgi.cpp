#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "user_opt.h"
#include "CJsonObject.hpp"
#include <fcgi_stdio.h>
#include <hiredis/hiredis.h>

using namespace std;

static int cur_room_no = 1;

int main(int argc, char* argv[]){
	while(FCGI_Accept() >= 0) {
		int json_len = atoi(getenv("CONTENT_LENGTH"));
		string username;
		string password;
		char * buff = (char *)calloc(1UL, json_len);

		fread(buff, 1, json_len, stdin);
		string json_string(buff);
		neb::CJsonObject json(json_string);

		json.Get("username", username);
		json.Get("password", password);

		printf("Content-Type:application/json\r\n");

		neb::CJsonObject reply;
		if(CheckUser(username.c_str(), password.c_str()) == true) {
			// reply ok to client
			reply.Add("login_result", "OK");
			string opt;
			json.Get("opt", opt);
			if (opt == "create_room") {
				string room_info = CreateContainer(cur_room_no);
// 				string room_no = CreateContainer();
// 				add a record : {room_no : room_info}
//
//
 				auto pc = redisConnect("127.0.0.1", 6379);
				if(pc != nullptr) {	
					freeReplyObject(redisCommand(pc, "set room_no%d %s", cur_room_no, room_info.c_str()));
					redisFree(pc);
				}


				reply.Add("server_IP", room_info.substr(0, room_info.find(' ')));
				reply.Add("server_PORT", room_info.substr(room_info.find(' ') + 1));
				reply.Add("room_no", cur_room_no);
				++ cur_room_no;
			}
			else if(opt == "follow_room") {
 				string room_no;
				json.Get("room_no", room_no);
				string room_info = CheckRoom(room_no.c_str());
				if(room_info.empty()) {	
					reply.Add("follow_result", "Failed");
				} else {	
					reply.Add("follow_result", "OK");
					reply.Add("server_IP", room_info.substr(0, room_info.find(' ')));
					reply.Add("server_PORT", room_info.substr(room_info.find(' ') + 1));
				}
				/*
				if(CheckRoom(room_no.c_str()) == true) {
					reply.Add("follow_result", "OK");
				} else {	
					reply.Add("follow_result", "Failed");
				}
				*/
			}
		} 
		else {
			// reply failed to client
			reply.Add("login_result", "Failed");
		}
		string reply_string = reply.ToFormattedString();
		printf("Content-Length:%d\r\n\r\n", reply_string.size());
		
		printf("%s\r\n", reply_string.c_str());
		
		free(buff);
	}
    return 0;
}

