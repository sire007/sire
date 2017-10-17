#include "databases.h"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
void mysql_connect()
{
	char server[20]="localhost";
	char user[20]="root";
	char password[20]="123";
	char database[20]="company";
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		cout<<"connect failed\n";
		exit(1);
	}
	mysql_set_character_set(conn,"utf8");

}
