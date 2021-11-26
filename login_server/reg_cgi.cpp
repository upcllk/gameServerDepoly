#include <stdio.h>
#include "user_opt.h"
#include <string>
#include <fcgi_stdio.h>

using namespace std;

int main(){
	while(FCGI_Accept()>= 0) {
		char buff[1024] = {0};
		fread(buff, 1, sizeof(buff), stdin);
		string orig_string(buff);
		int and_pos = orig_string.find('&');
		string username = orig_string.substr(9, and_pos-9);
		string password = orig_string.substr(and_pos+10);
		printf("Content-Type=text\r\n\r\n");
		if(CheckUser(username.c_str(), NULL) == true) {
			// user exist
			printf("User Exist\r\n");
		}
		else {
			AddUser(username.c_str(), password.c_str());
			// register success
			printf("Success\r\n");
		}
		
	}
    return 0;
}

