#include "TecPartTime.h"
#include "databases.h"

extern MYSQL *conn;
extern MYSQL_RES *res;
extern MYSQL_ROW row;

bool TecPartTime::judgeTecPartTimeEmpty()
{
	bool empty=false;
	if(mysql_query(conn,"select * from partTime_Tc"))
	{
		exit(1);
	}
	res=mysql_use_result(conn);
	row=mysql_fetch_row(res);
	if(row==NULL)
	{
		empty=true;
	}
	mysql_free_result(res);
	return empty;
}

void TecPartTime::queryById_tecPartTime(int id)
{
	char buff[200];
	sprintf(buff,"select * from partTime_Tc where m_uiId='%d'",id);

	if(mysql_query(conn,buff))
	{
		cout<<"打印兼职技术人员表的信息失败"<<endl;
		exit(1);
	}
	res=mysql_use_result(conn);
	cout<<"编号\t姓名\t密码\t级别\t时薪\t工作时间\t总月工资\t上级\t\t备注\n";
	while((row=mysql_fetch_row(res))!=NULL)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t\t%s\t\t%s\t\t%s\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8]);
	}
	mysql_free_result(res);
}

void TecPartTime::update_passwd_tecPartTime(int id)
{
	char pwd[32];
	cout<<"请输入新密码:"<<endl;
	cin>>pwd;
	char buff[200];
	sprintf(buff,"update partTime_Tc set m_strPwd='%s' where m_uiId='%d'",pwd,id);
	if(mysql_query(conn,buff))
	{
		cout<<"更新密码失败"<<endl;
		exit(1);
	}
}





