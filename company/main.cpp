#include "login.h"
int main()
{
	mysql_connect();
	login_face();
	login_work();
	mysql_close(conn);
	return 0;
}
