#include "TecManager.h"
#include "databases.h"

extern MYSQL *conn;
extern MYSQL_RES *res;
extern MYSQL_ROW row;
bool TecManager::judgeTecManagerEmpty()
{
	bool empty=false;
	if(mysql_query(conn,"select * from manager_Tc"))
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
}
void TecManager::displayAllTecPartTimeInfo()
{
	if(mysql_query(conn,"select * from partTime_Tc"))
	{
		cout<<"failed\n";
		exit(1);
	}
	res=mysql_use_result(conn);
	cout<<"编号\t姓名\t密码\t级别\t时薪\t工作时间\t总月工资\t上级\t备注\n";
	while((row=mysql_fetch_row(res))!=NULL)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t\t%s\t\t  %s\t%s\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8]);
	}
	mysql_free_result(res);
}
void TecManager::setWorkHour(int id)
{
	char buff[200];
	int time;
	cout<<"请输入该技术员工的月工作时间(h):";
	cin>>time;
	sprintf(buff,"update partTime_Tc set m_uiWorkHour='%d' where m_uiId='%d'",time,id);
	if(mysql_query(conn,buff))
	{
		cout<<"设置失败"<<endl;
		exit(1);
	}
}
void TecManager::modifyTecNote(int id)
{
	char buff[200];
	char note[128];
	cout<<"1->表现良好\n";
	cout<<"2->迟到较多,表现较差\n";
	cout<<"0->无\n";
	cout<<"请选择:";
	int num;
	cin>>num;
	switch(num)
	{
		case 1:
		strcpy(note,"表现良好");
		sprintf(buff,"update partTime_Tc set m_strNote='%s' where m_uiId='%d'",note,id);
		break;
		case 2:
		strcpy(note,"迟到较多,表现较差");
		sprintf(buff,"update partTime_Tc set m_strNote='%s' where m_uiId='%d'",note,id);
		break;
		case 0:
		strcpy(note,"无");
		sprintf(buff,"update partTime_Tc set m_strNote='%s' where m_uiId='%d'",note,id);
		break;
		default:
			cout<<"输入错误"<<endl;
			break;
	}
	if(mysql_query(conn,buff))
	{
		cout<<"设置失败"<<endl;
		exit(1);
	}
}
void TecManager::setPartTimePerHourPay(int id)
{
	char buff[200];
	float money;
	cout<<"请输入该技术员工的月时薪:";
	cin>>money;
	sprintf(buff,"update partTime_Tc set m_fPerHourPay='%f' where m_uiId='%d'",money,id);
	if(mysql_query(conn,buff))
	{
		cout<<"设置失败"<<endl;
		exit(1);
	}
}
void TecManager::calTecPartTimeMonthSalary(int id)
{
	char buff[200];
	sprintf(buff,"select * from partTime_Tc where m_uiId='%d'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"查找信息失败"<<endl;
		exit(1);
	}
	 res=mysql_use_result(conn);
	row=mysql_fetch_row(res);
	memset(buff,0,sizeof(buff));
	if(strcmp(row[8],"表现良好")==0)
	{
		mysql_free_result(res);
		sprintf(buff,"update partTime_Tc set m_fMonthSalary=m_uiWorkHour*m_fPerHourPay+500 where m_uiId='%d'",id);
		if(mysql_query(conn,buff))
		{
			cout<<"计算月薪失败"<<endl;
			exit(1);
		}
		else
		{
			cout<<"月薪更新成功\n";
		}
	}
	else if(strcmp(row[8],"迟到较多,表现较差")==0)
	{
		mysql_free_result(res);
		memset(buff,0,sizeof(buff));
		sprintf(buff,"update partTime_Tc set m_fMonthSalary=m_uiWorkHour*m_fPerHourPay-100 where m_uiId='%d'",id);
		if(mysql_query(conn,buff))
		{
			cout<<"计算月薪失败"<<endl;
			exit(1);
		}
		else
		{
			cout<<"月薪更新成功\n";
		}
	}
	else
	{
		mysql_free_result(res);
		memset(buff,0,sizeof(buff));
		sprintf(buff,"update partTime_Tc set m_fMonthSalary=m_uiWorkHour*m_fPerHourPay where m_uiId='%d'",id);
		if(mysql_query(conn,buff))
		{
			cout<<"计算月薪失败"<<endl;
			exit(1);
		}
		else
		{
			cout<<"月薪更新成功\n";
		}
	}
}
void TecManager::update_passwd_tecManager(int id)
{
	char pwd[32];
	cout<<"请输入新密码:"<<endl;
	cin>>pwd;
	char buff[200];
	sprintf(buff,"update manager_Tc set m_strPwd='%s' where m_uiId='%d'",pwd,id);
	if(mysql_query(conn,buff))
	{
		cout<<"更新密码失败"<<endl;
		exit(1);
	}
}
void TecManager::addTecPartTime(int id)
{
	char buff[200];
	int ids;
	char name[32];
	int num;
	if(mysql_query(conn,"select * from partTime_Tc"))
	{
		cout<<"connect failed\n";
		exit(1);
	}
	res=mysql_use_result(conn);
	if((row=mysql_fetch_row(res))==NULL)
	{
		cout<<"请输入要添加的技术员工的ID:";
		cin>>ids;
		cout<<"请输入要添加的技术员工的姓名:";
		cin>>name;
		mysql_free_result(res);
		sprintf(buff,"insert into partTime_Tc(m_uiId,m_strName,m_tecLeaderId) values('%d','%s','%d')",ids,name,id);
		if(mysql_query(conn,buff))
		{
			cout<<"插入失败"<<endl;
			exit(1);
		}
		setWorkHour(ids);
		modifyTecNote(ids);
		setPartTimePerHourPay(ids);
        calTecPartTimeMonthSalary(ids);
	}
	else
	{
		mysql_free_result(res);
		cout<<"请输入要添加的技术员工的姓名:";
		cin>>name;
		sprintf(buff,"insert into partTime_Tc(m_strName,m_tecLeaderId) values('%s','%d')",name,id);
		if(mysql_query(conn,buff))
		{
			cout<<"插入失败"<<endl;
			exit(1);
		}
		if(mysql_query(conn,"select max(m_uiId) from partTime_Tc"))
		{
			cout<<"查询信息失败"<<endl;
			exit(1);
		}
		res=mysql_use_result(conn);
		row=mysql_fetch_row(res);
		num=atoi(row[0]);
		mysql_free_result(res);
		setWorkHour(num);
		modifyTecNote(num);
		setPartTimePerHourPay(num);
		calTecPartTimeMonthSalary(num);
	}
}
void TecManager::delTecPartTimeById()
{
	cout<<"请输入要删除的技术员工的ID:";
	char id[32];
	cin>>id;
	char buff[200];
	sprintf(buff,"delete from partTime_Tc where m_uiId='%s'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"删除失败"<<endl;
		exit(1);
	}
}
void TecManager::modifyTecPartTime()
{
	int num;
	int id;
	cout<<"请输入要修改的技术员工的ID:";
	cin>>id;
	cout<<"1->修改该技术员工的时薪\n";
	cout<<"2->修改该技术员工的备注\n";
	cin>>num;
	int flag=1;
	while(flag)
	{
		switch(num)
		{
			case 1:
				setWorkHour(id);
				calTecPartTimeMonthSalary(id);
				flag=0;
				break;
			case 2:
				modifyTecNote(id);
				calTecPartTimeMonthSalary(id);
				flag=0;
				break;
			default:
				cout<<"输入错误,请重新输入\n";
				break;
		}
	}
}
void TecManager::queryTecPartTimeInfo()
{
	cout<<"请输入要查看的技术员工的ID:";
	int id;
	cin>>id;
	char buff[200];
	sprintf(buff,"select * from partTime_Tc where m_uiId='%d'",id);

	if(mysql_query(conn,buff))
	{
		cout<<"打印技术员工表的信息失败"<<endl;
		exit(1);
	}
	res=mysql_use_result(conn);
	cout<<"编号\t姓名\t密码\t级别\t时薪\t工作时间\t总月工资\t上级\t备注\n";
	while((row=mysql_fetch_row(res))!=NULL)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\t\t%s\t\t  %s\t%s\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8]);
	}
	mysql_free_result(res);
}
	
void TecManager::queryTecManagerinfo(int id)
{
	char bufff[200];
	sprintf(bufff,"select * from manager_Tc where m_uiId='%d'",id);
	if(mysql_query(conn,bufff))
	{
		cout<<"打印技术经理表的信息失败"<<endl;
		exit(1);
	}
	res=mysql_use_result(conn);
	cout<<"编号\t姓名\t密码\t级别\t月总工资\t备注\n";
	while((row=mysql_fetch_row(res))!=NULL)
	{
		printf("%s\t%s\t%s\t%s\t%s\t\t%s\n",row[0],row[1],row[2],row[3],row[4],row[5]);
	}
	mysql_free_result(res);
}
	
	

