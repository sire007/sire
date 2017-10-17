#include "boss.h"
#include "databases.h"

extern MYSQL *conn;
extern MYSQL_RES *res;
extern MYSQL_ROW row;


void Boss::setNotice()
{
	char buff[200];
	char words[300];
	cout<<"请输入公告内容:\n";
	cin>>words;
	sprintf(buff,"update pub_Notice set speak='%s'",words);
	if(mysql_query(conn,buff))
	{
		cout<<"set failed\n";
		exit(1);
	}
}
void Boss::setSalManagerMonthPay(int id)
{
	char buf[200];
	float salary;
	cout<<"请输入该经理的月薪:";
	cin>>salary;
	sprintf(buf,"update manager_Sal set m_salManagerMonthPay='%f' where m_uiId='%d'",salary,id);
	if(mysql_query(conn,buf))
	{
		cout<<"设置信息失败"<<endl;
		exit(1);
	}
}
void Boss::getSalManagerSaledMoney(int id)
{
	char bufs[200];
	float saledMoney;
	if(mysql_query(conn,"select * from partTime_Sal"))
	{
		cout<<"查找失败\n";
		exit(1);
	}
	res=mysql_use_result(conn);
	if((row=mysql_fetch_row(res))!=NULL)
	{
		mysql_free_result(res);
		sprintf(bufs,"select sum(m_fMonthSaledMoney) from partTime_Sal where m_salLeaderId='%d'",id);
		if(mysql_query(conn,bufs))
		{
			cout<<"查询信息失败"<<endl;
			exit(1);
		}
		else
		{
			res=mysql_use_result(conn);
			row=mysql_fetch_row(res);
			saledMoney=atof(row[4]);
			mysql_free_result(res);
			memset(bufs,0,sizeof(bufs));
			sprintf(bufs,"update manager_Sal set m_salManagerMonthSaledMoney='%f'",saledMoney);
			if(mysql_query(conn,bufs))
			{
				cout<<"设置信息失败"<<endl;
				exit(1);
			}	
		}
	}
	else
	{
		cout<<"请先添加该经理的下属信息\n";
	}
}
void Boss::setSalManagerPercentage(int id)
{
	char buff[200];
	cout<<"请输入该销售经理的提成:";
	float percentage;
	cin>>percentage;
	sprintf(buff,"update manager_Sal set m_salManagerPercentage='%f'",percentage);
	if(mysql_query(conn,buff))
	{
		cout<<"设置信息失败"<<endl;
		exit(1);
	}
}
void Boss::calSalManagerMonthSalary(int id)
{
	char buff[200];
	sprintf(buff,"update manager_Sal set m_salManagerMonthSalary=m_salManagerMonthSaledMoney*m_salManagerPercentage+m_salManagerMonthPay where m_uiId='%d'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"查询信息失败"<<endl;
		exit(1);
	}
}
void Boss::setTecManagerSalary(int id)
{	
	char buf[200];
	float salary;
	cout<<"请输入该经理的月薪:";
	cin>>salary;
	sprintf(buf,"update manager_Tc set m_fSalary='%0.2f' where m_uiId='%d'",salary,id);
	if(mysql_query(conn,buf))
	{
		cout<<"设置月薪失败"<<endl;
		exit(1);
	}
}
void Boss::promoteTecPartTime()
{
	char buff[200];
	int id;
	cout<<"请输入要升职的技术员工的原始ID:\n";
	cin>>id;
	sprintf(buff,"insert into manager_Tc(m_strName,m_strPwd) select m_strName,m_strPwd from partTime_Tc where m_uiId='%d'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"failed\n";
		exit(1);
	}
	if(mysql_query(conn,"select max(m_uiId) from manager_Tc"))
	{
		cout<<"failed\n";
		exit(1);
	}
	int ids;
	res=mysql_use_result(conn);
	row=mysql_fetch_row(res);
	ids=atoi(row[0]);
	mysql_free_result(res);
	setTecManagerSalary(ids);
	memset(buff,0,sizeof(buff));
	sprintf(buff,"delete from partTime_Tc where m_uiId='%d'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"failed\n";
		exit(1);
	}
}

void Boss::demoteTecManager(Boss &boss)
{
	char buff[200];
	int id;
	cout<<"请输入要降职的技术经理的原始ID:\n";
	cin>>id;
	sprintf(buff,"insert into partTime_Tc(m_strName,m_strPwd) select m_strName,m_strPwd from manager_Tc where m_uiId='%d'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"failed\n";
		exit(1);
	}
	if(mysql_query(conn,"select max(m_uiId) from partTime_Tc"))
	{
		cout<<"failed\n";
		exit(1);
	}
	int ids;
	res=mysql_use_result(conn);
	row=mysql_fetch_row(res);
	ids=atoi(row[0]);
	mysql_free_result(res);
	boss.setWorkHour(ids);
	boss.modifyTecNote(ids);
	boss.setPartTimePerHourPay(ids);
    boss.calTecPartTimeMonthSalary(ids);
	cout<<"请为该降职员工分配上级(经理ID):";
	int num;
	cin>>num;
	memset(buff,0,sizeof(buff));
	sprintf(buff,"update partTime_Tc set m_tecLeaderId='%d'",num);
	if(mysql_query(conn,buff))
	{
		cout<<"failed\n";
		exit(1);
	}
	memset(buff,0,sizeof(buff));
	sprintf(buff,"delete from manager_Tc where m_uiId='%d'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"failed\n";
		exit(1);
	}
}

void Boss::promoteSalPartTime()
{
	char buff[200];
	int id;
	cout<<"请输入要升职的销售员工的原始ID:";
	cin>>id;
	sprintf(buff,"insert into manager_Sal(m_strName,m_strPwd) select m_strName,m_strPwd from partTime_Sal where m_uiId='%d'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"failed\n";
		exit(1);
	}
	if(mysql_query(conn,"select max(m_uiId) from manager_Sal"))
	{
		cout<<"failed\n";
		exit(1);
	}
	int ids;
	res=mysql_use_result(conn);
	row=mysql_fetch_row(res);
	ids=atoi(row[0]);
	mysql_free_result(res);
	setSalManagerMonthPay(ids);
	getSalManagerSaledMoney(ids);
	setSalManagerPercentage(ids);
	calSalManagerMonthSalary(ids);
	sprintf(buff,"delete from partTime_Sal where m_uiId='%d'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"failed\n";
		exit(1);
	}
}
	
void Boss::demoteSalManager(Boss &boss)
{
	char buff[200];
	int id;
	cout<<"请输入要降职的销售经理的原始ID:\n";
	cin>>id;
	sprintf(buff,"insert into partTime_Sal(m_strName,m_strPwd) select m_strName,m_strPwd from manager_Sal where m_uiId='%d'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"failed\n";
		exit(1);
	}
	if(mysql_query(conn,"select max(m_uiId) from partTime_Sal"))
	{
		cout<<"failed\n";
		exit(1);
	}
	int ids;
	res=mysql_use_result(conn);
	row=mysql_fetch_row(res);
	ids=atoi(row[0]);
	mysql_free_result(res);
	boss.setSalPercentage(ids);
	boss.setMonthSaledMoney(ids);
	boss.modifySalNote(ids);
	boss.calSalPartTimeMonthSalary(ids);
	cout<<"请为该降职员工分配上级(经理ID):";
	int num;
	cin>>num;
	memset(buff,0,sizeof(buff));
	sprintf(buff,"update partTime_Sal set m_salLeaderId='%d'",num);
	if(mysql_query(conn,buff))
	{
		cout<<"failed\n";
		exit(1);
	}
	memset(buff,0,sizeof(buff));
	sprintf(buff,"delete from manager_Sal where m_uiId='%d'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"failed\n";
		exit(1);
	}
}
void Boss::tecSectionPromoteOrDemotion(Boss &boss)
{
	int flag=1;
	while(flag)
	{
		cout<<"1->升职兼职技术员工\n";
		cout<<"2->降职技术经理\n";
		cout<<"0->退出\n";
		cout<<"请选择:";
		int n;
		cin>>n;
		switch(n)
		{
			case 1:
				promoteTecPartTime();
				flag=0;
				break;
			case 2:
				demoteTecManager(boss); 
				flag=0;
				break;
			case 0:
				flag=0;
				break;
			default:
				cout<<"输入错误,请重新输入\n";
				break;
		}
	}
}
void Boss::SalSectionPromoteOrDemotion(Boss &boss)
{
	int flag=1;
	while(flag)
	{
		cout<<"1->升职兼职销售员工\n";
		cout<<"2->降职销售经理\n";
		cout<<"0->退出\n";
		cout<<"请选择:";
		int n;
		cin>>n;
		switch(n)
		{
			case 1:
				promoteSalPartTime();
				flag=0;
				break;
			case 2:
				demoteSalManager(boss);
				flag=0;
				break;
			case 0:
				flag=0;
				break;
			default:
				cout<<"输入错误,请重新输入\n";
				break;
		}
	}
}
void Boss::displayAllTecManagerInfo()
{
	if(mysql_query(conn,"select * from manager_Tc"))
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

void Boss::displayAllSalManagerInfo()
{
	if(mysql_query(conn,"select * from manager_Sal"))
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
void Boss::queryBoss(int id)
{
	char buff[200];
	sprintf(buff,"select * from boss where m_uiId='%d'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"打印老板表的信息失败"<<endl;
		exit(1);
	}
	res=mysql_use_result(conn);
	cout<<"编号\t姓名\t密码\t级别\n";
	while((row=mysql_fetch_row(res))!=NULL)
	{
		printf("%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3]);
	}
	mysql_free_result(res);
}
void Boss::updateBossPwd(int id)
{
	char pwd[32];
	cout<<"请输入新密码:"<<endl;
	cin>>pwd;
	char buff[200];
	sprintf(buff,"update boss set m_strPwd='%s' where m_uiId='%d'",pwd,id);
	if(mysql_query(conn,buff))
	{
		cout<<"更新密码失败"<<endl;
		exit(1);
	}
	else
	{
		cout<<"修改密码成功\n";
	}
}
void Boss::addTecManager()
{
	char buff[300];
	int ids;
	char name[32];
	int num;
	if(mysql_query(conn,"select * from manager_Tc"))
	{
		exit(1);
	}
	res=mysql_use_result(conn);
	row=mysql_fetch_row(res);
	if(row==NULL)
	{
		mysql_free_result(res);
		cout<<"请输入要添加的技术经理的ID:";
		cin>>ids;
		cout<<"请输入要添加的技术经理的姓名:";
		cin>>name;
		sprintf(buff,"insert into manager_Tc(m_uiId,m_strName) values('%d','%s')",ids,name);
		if(mysql_query(conn,buff))
		{
			cout<<"添加失败\n";
			exit(1);
		}
		else
		{
			setTecManagerSalary(ids);
		}
	}
	else
	{
		mysql_free_result(res);
		cout<<"请输入要添加的技术经理的姓名:";
		cin>>name;
		memset(buff,0,sizeof(buff));
		sprintf(buff,"insert into manager_Tc(m_strName) values('%s')",name);
		if(mysql_query(conn,buff))
		{
			cout<<"添加失败"<<endl;
			exit(1);
		}	
		if(mysql_query(conn,"select max(m_uiId) from manager_Tc"))
		{
			cout<<"查询信息失败"<<endl;
			exit(1);
		}
		res=mysql_use_result(conn);
		row=mysql_fetch_row(res);
		num=atoi(row[0]);
		mysql_free_result(res);
		setTecManagerSalary(num);
	}
}
void Boss::delTecManagerById()
{
	cout<<"请输入要删除的技术经理的ID:";
	char id[32];
	cin>>id;
	char buff[200];
	sprintf(buff,"delete from manager_Tc where m_uiId='%s'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"删除失败"<<endl;
		exit(1);
	}
}
void Boss::modifyTecManager()
{
	int num;
	int id;
	cout<<"请输入要修改的技术经理的ID:";
	cin>>id;
	cout<<"1->修改该经理的月薪\n";
	cout<<"2->修改该经理的备注\n";
	cin>>num;
	int flag=1;
	while(flag)
	{
		switch(num)
		{
			case 1:
				setTecManagerSalary(id);
				flag=0;
				break;
			case 2:
				//modifyTecManagerNote(id);
				flag=0;
				break;
			default:
				cout<<"输入错误,请重新输入\n";
				break;
		}
	}
}
void Boss::queryTecManagerInfo()
{
	cout<<"请输入要查看的技术经理的ID:";
	int id;
	cin>>id;
	char buff[200];
	sprintf(buff,"select * from manager_Tc where m_uiId='%d'",id);

	if(mysql_query(conn,buff))
	{
		cout<<"打印技术经理表的信息失败"<<endl;
		exit(1);
	}
	res=mysql_use_result(conn);
	cout<<"编号\t姓名\t密码\t级别\t月总工资\t备注\n";
	while((row=mysql_fetch_row(res))!=NULL)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4],row[5]);
	}
	mysql_free_result(res);
}


void Boss::addSalManager()
{
	char buff[200];
	int ids;
	char name[32];
	int num;
	if(mysql_query(conn,"select * from manager_Sal"))
	{
		cout<<"connect failed\n";
		exit(1);
	}
	res=mysql_use_result(conn);
	if((row=mysql_fetch_row(res))==NULL)
	{
		cout<<"请输入要添加的销售经理的ID:";
		cin>>ids;
		cout<<"请输入要添加的销售经理的姓名:";
		cin>>name;
		//memset(buff,0,sizeof(buff));
		mysql_free_result(res);
		sprintf(buff,"insert into manager_Sal(m_uiId,m_strName) values('%d','%s')",ids,name);
		if(mysql_query(conn,buff))
		{
			cout<<"插入失败"<<endl;
			exit(1);
		}
		else
		{
			setSalManagerMonthPay(ids);
			getSalManagerSaledMoney(ids);
			setSalManagerPercentage(ids);
			calSalManagerMonthSalary(ids);
		}
	}
	else
	{
		cout<<"请输入要添加的销售经理的姓名:";
		cin>>name;
		mysql_free_result(res);
		sprintf(buff,"insert into manager_Sal(m_strName) values('%s')",name);
		if(mysql_query(conn,buff))
		{
			cout<<"插入失败"<<endl;
			exit(1);
		}
		if(mysql_query(conn,"select max(m_uiId) from manager_Sal"))
		{
			cout<<"查询信息失败"<<endl;
			exit(1);
		}
		res=mysql_use_result(conn);
		row=mysql_fetch_row(res);
		num=atoi(row[0]);
		mysql_free_result(res);
		setSalManagerMonthPay(num);
		setSalManagerPercentage(num);
		calSalManagerMonthSalary(num);
		getSalManagerSaledMoney(num);
	}
}
void Boss::delSalManagerById()
{
	cout<<"请输入要删除的销售经理的ID:";
	char id[32];
	cin>>id;
	char buff[200];
	sprintf(buff,"delete from manager_Sal where m_uiId='%s'",id);
	if(mysql_query(conn,buff))
	{
		cout<<"删除失败"<<endl;
		exit(1);
	}
}
void Boss::modifySalManager()
{
	int num;
	int id;
	cout<<"请输入要修改的销售经理的ID:";
	cin>>id;
	cout<<"1->修改该经理的提成\n";
	cout<<"2->修改该经理的月固定月薪\n";
	cout<<"3->修改该员工的备注\n";
	cout<<"请选择要修改的项目:";
	cin>>num;
	int flag=1;
	while(flag)
	{
		switch(num)
		{
			case 1:
				setSalManagerPercentage(id);
				calSalManagerMonthSalary(id);
				flag=0;
				break;
			case 2:
				setSalManagerMonthPay(id);
				calSalManagerMonthSalary(id);
				break;
			case 3:
				//modifySalNote(id);
				flag=0;
				break;
			default:
				cout<<"输入错误,请重新输入\n";
				break;
		}
	}
}
void Boss::querySalManagerInfo()
{
	cout<<"请输入要查询的销售经理的ID:";
	int id;
	cin>>id;
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
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8]);
	}
	mysql_free_result(res);
}
