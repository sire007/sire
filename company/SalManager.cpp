#include "SalManager.h"
#include "databases.h"

extern MYSQL *conn;
extern MYSQL_RES *res;
extern MYSQL_ROW row;
bool SaleManager::judgeSalManagerEmpty()
{
	bool empty=false;
	if(mysql_query(conn,"select * from manager_Sal"))
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
void SaleManager::displayAllSalPartTimeInfo()
{
	if(mysql_query(conn,"select * from partTime_Sal"))
	{
		cout<<"打印兼职销售人员表的信息失败"<<endl;
		exit(1);
	}
	res=mysql_use_result(conn);
	cout<<"编号\t姓名\t密码\t级别\t月销售额\t提成\t\t月总工资\t上级\t备注\n";
	while((row=mysql_fetch_row(res))!=NULL)
	{
		printf("%s\t%s\t%s\t%s\t%s\t\t%s\t\t%s\t\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8]);
	}
	mysql_free_result(res);
}
void SaleManager::setMonthSaledMoney(int id)
{
	char buff[200];
	float monthMoney;
	cout<<"请输入该销售员工的月销售额:";
	cin>>monthMoney;
	sprintf(buff,"update partTime_Sal set m_fMonthSaledMoney='%f' where m_uiId='%d'",monthMoney,id);
	if(mysql_query(conn,buff))
	{
		cout<<"设置失败"<<endl;
		exit(1);
	}
}
void SaleManager::setSalPercentage(int id)
{
	char buff[200];
	float percentage;
	cout<<"请输入该销售员工的月薪提成:";
	cin>>percentage;
	sprintf(buff,"update partTime_Sal set m_fPercentage='%f' where m_uiId='%d'",percentage,id);
	if(mysql_query(conn,buff))
	{
		cout<<"设置失败"<<endl;
		exit(1);
	}
}
void SaleManager::calSalPartTimeMonthSalary(int id)
{
	char buff[200];
	sprintf(buff,"select * from partTime_Sal where m_uiId='%d'",id);
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
		sprintf(buff,"update partTime_Sal set m_fMonthSalary=m_fMonthSaledMoney*m_fPercentage+500 where m_uiId='%d'",id);
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
		sprintf(buff,"update partTime_Sal set m_fMonthSalary=m_fMonthSaledMoney*m_fPercentage-100 where m_uiId='%d'",id);
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
		sprintf(buff,"update partTime_Sal set m_fMonthSalary=m_fMonthSaledMoney*m_fPercentage where m_uiId='%d'",id);
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
void SaleManager::modifySalNote(int id)
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
		sprintf(buff,"update partTime_Sal set m_strNote='%s' where m_uiId='%d'",note,id);
		break;
		case 2:
		strcpy(note,"迟到较多,表现较差");
		sprintf(buff,"update partTime_Sal set m_strNote='%s' where m_uiId='%d'",note,id);
		break;
		case 0:
		strcpy(note,"无");
		sprintf(buff,"update partTime_Sal set m_strNote='%s' where m_uiId='%d'",note,id);
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
void SaleManager::addSalPartTime(int id)
{
	char buff[200];
	int ids;
	char name[32];
	int num;
	if(mysql_query(conn,"select * from partTime_Sal"))
	{
		cout<<"connect failed\n";
		exit(1);
	}
	res=mysql_use_result(conn);
	if((row=mysql_fetch_row(res))==NULL)
	{
		cout<<"请输入要添加的销售员工的ID:";
		cin>>ids;
		cout<<"请输入要添加的销售员工的姓名:";
		cin>>name;
		memset(buff,0,sizeof(buff));
		mysql_free_result(res);
		sprintf(buff,"insert into partTime_Sal(m_uiId,m_strName,m_salLeaderId) values('%d','%s','%d')",ids,name,id);
		if(mysql_query(conn,buff))
		{
			cout<<"插入失败"<<endl;
			exit(1);
		}
		setSalPercentage(ids);
		setMonthSaledMoney(ids);
		modifySalNote(ids);
		calSalPartTimeMonthSalary(ids);
		
	}
	else
	{
		cout<<"请输入要添加的销售员工的姓名:";
		cin>>name;
		mysql_free_result(res);
		sprintf(buff,"insert into partTime_Sal(m_strName,m_salLeaderId) values('%s','%d')",name,id);
		if(mysql_query(conn,buff))
		{
			cout<<"插入失败"<<endl;
			exit(1);
		}
	if(mysql_query(conn,"select max(m_uiId) from partTime_Sal"))
	{
		cout<<"查询信息失败"<<endl;
		exit(1);
	}
	res=mysql_use_result(conn);
	row=mysql_fetch_row(res);
	num=atoi(row[0]);
	mysql_free_result(res);
	setSalPercentage(num);
	setMonthSaledMoney(num);
	modifySalNote(num);
	calSalPartTimeMonthSalary(num);
	}
}
void SaleManager::delSalPartTimeById()
{
	cout<<"请输入要删除的销售员工的ID:";
	char id[32];
	cin>>id;
	char buff[200];
	sprintf(buff,"delete from partTime_Sal where m_uiId='%s'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"删除失败"<<endl;
		exit(1);
	}
}
void SaleManager::modifySalPartTime()
{
	int num;
	int id;
	cout<<"请输入要修改的销售员工的ID:";
	cin>>id;
	cout<<"1->修改该销售员工的提成\n";
	cout<<"2->修改该销售员工的月销售额\n";
	cout<<"3->修改该销售员工的备注\n";
	cout<<"请选择要修改的项目:";
	cin>>num;
	int flag=1;
	while(flag)
	{
		switch(num)
		{
			case 1:
				setSalPercentage(id);
				calSalPartTimeMonthSalary(id);
				flag=0;
				break;
			case 2:
				setMonthSaledMoney(id);
				calSalPartTimeMonthSalary(id);
				flag=0;
				break;
			case 3:
				modifySalNote(id);
				calSalPartTimeMonthSalary(id);
				flag=0;
				break;
			default:
				cout<<"输入错误,请重新输入\n";
				break;
		}
	}
}
void SaleManager::querySalPartTimeInfo()
{
	cout<<"请输入要查看的销售员工的ID:";
	int id;
	cin>>id;
	char buff[200];
	sprintf(buff,"select * from partTime_Sal where m_uiId='%d'",id);

	if(mysql_query(conn,buff))
	{
		cout<<"打印兼职销售人员表的信息失败"<<endl;
		exit(1);
	}
	res=mysql_use_result(conn);
	cout<<"编号\t姓名\t密码\t级别\t月销售额\t提成\t月总工资\t上级\t备注\n";
	while((row=mysql_fetch_row(res))!=NULL)
	{
		printf("%s\t%s\t%s\t%s\t%s\t\t%s\t%s\t\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8]);
	}
	mysql_free_result(res);
}
void SaleManager::update_passwd_salManager(int id)
{
	char pwd[32];
	cout<<"请输入新密码:"<<endl;
	cin>>pwd;
	char buff[200];
	sprintf(buff,"update manager_Sal set m_strPwd='%s' where m_uiId='%d'",pwd,id);
	if(mysql_query(conn,buff))
	{
		cout<<"更新密码失败"<<endl;
		exit(1);
	}
}
void SaleManager::querySalManagerinfo(int id)
{
	char buff[200];
	sprintf(buff,"select * from manager_Sal where m_uiId='%d'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"打印销售经理表的信息失败"<<endl;
		exit(1);
	}
	res=mysql_use_result(conn);
	cout<<"编号\t姓名\t密码\t级别\t月销售额\t提成\t月固定工资\t月总工资\t备注\n";
	while((row=mysql_fetch_row(res))!=NULL)
	{
		printf("%s\t%s\t%s\t%s\t%s\t\t%s\t%s\t\t%s\t\t%s\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8]);
	}
	mysql_free_result(res);
}

