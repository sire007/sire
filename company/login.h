#ifndef LOGIN_H
#define LOGIN_H

#include"databases.h"
#include"TecManager.h"
#include"SalManager.h"
#include"boss.h"
#include"time.h"
extern MYSQL *conn;
extern MYSQL_RES *res;
extern MYSQL_ROW row;
void face_tec()
{
	cout<<"\t\t欢迎来到兼职技术员工操作界面\n";
	cout<<"\t   *********************************\n";
	cout<<"+-------------------+\n";
	cout<<"|1->查看本人的信息  |\n";
	cout<<"|2->修改登录密码    |\n";
	cout<<"|0->退出            |\n";
	cout<<"+-------------------+\n";
}
void opteration_tec(int id,TecPartTime &tec)
{
	int num;
	int flag=0;
	while(flag<3)
	{
		cout<<"请输入你的选择:";
		cin>>num;
		switch(num)
		{
			case 1:
				tec.queryById_tecPartTime(id); 
				face_tec();
				break;
			case 2:
				tec.update_passwd_tecPartTime(id);  	
				face_tec();
				break;
			case 0:
				cout<<"感谢您的本次操作,期待与您的下次见面!"<<endl;
				cout<<"         ****Bey-Bey****\n";
				flag=3;
				break;;
			default:
				cout<<"输入错误,请重新输入\n";
				flag++;
				break;
		}	
	}
}
void face_manager_tec()
{
	cout<<"\t\t欢迎来到技术经理操作界面\n";
	cout<<"\t   ****************************\n";
	cout<<"+-------------------------+\n";
	cout<<"|1->查看本人信息          | \n";
	cout<<"|2->修改登录密码          |\n";
	cout<<"|3->添加兼职技术员工的信息|\n";
	cout<<"|4->删除兼职技术员工的信息|\n";
	cout<<"|5->查看兼职技术员工的信息|\n";
	cout<<"|6->修改兼职技术员工的信息|\n";
	cout<<"|7->显示所有技术员工的信息|\n";
	cout<<"|0->退出                  |\n";
	cout<<"+-------------------------+\n";
}
void opteration_manager_tec(int id,TecManager &TecMana)
{
	int num;
	int flag=0;
	while(flag<3)
	{
		cout<<"请输入你的选择:\n";
		cin>>num;
		switch(num)
		{
			case 1:
				TecMana.queryTecManagerinfo(id);
				face_manager_tec();
				break;
			case 2:
				TecMana.update_passwd_tecManager(id);
				face_manager_tec();
				break;
			case 3:
				TecMana.addTecPartTime(id);
				face_manager_tec();
				break;
			case 4:
				TecMana.delTecPartTimeById();
				face_manager_tec();
				break;
			case 5:
				TecMana.queryTecPartTimeInfo();
				face_manager_tec();
				break;
			case 6:
				TecMana.modifyTecPartTime();
				face_manager_tec();
				break;
			case 7:
				TecMana.displayAllTecPartTimeInfo();
				face_manager_tec();
				break;
			case 0:
				cout<<"感谢您的本次操作,期待与您的下次见面!"<<endl;
				cout<<"         ****Bey-Bey****\n";
				flag=3;
				break;
			default:
				cout<<"输入错误,请重新输入\n";
				flag++;
				break;
		}	
	}
}
void face_sal()
{
	cout<<"\t\t欢迎来到兼职销售员工操作界面\n";
	cout<<"\t   *******************************\n";
	cout<<"+-----------------+\n";
	cout<<"|1->查看本人的信息|\n";
	cout<<"|2->修改登录密码  |\n";
	cout<<"|0->退出          |\n";
	cout<<"+-----------------+\n";
}
void opteration_sal(int id,SalePartTime &Sal)
{
	int num;
	int flag=0;
	while(flag<3)
	{
		cout<<"请输入你的选择:\n";
		cin>>num;
		switch(num)
		{
			case 1:
				Sal.queryById_salPartTime(id);
				face_sal();
				break;
			case 2:
				Sal.update_passwd_salPartTime(id);
				face_sal();
				break;
			case 0:
				cout<<"感谢您的本次操作,期待与您的下次见面!"<<endl;
				cout<<"         ****Bey-Bey****\n";
				flag=3;
				break;
			default:
				cout<<"输入错误,请重新输入\n";
				flag++;
				break;
		}	
	}
}
void face_manager_sal()
{
	cout<<"\t\t欢迎来到销售经理操作界面\n";
	cout<<"\t   ***************************\n";
	cout<<"+-----------------------------+\n";
	cout<<"|1->添加兼职销售员工的信息    |\n";
	cout<<"|2->删除兼职销售员工的信息    |\n";
	cout<<"|3->查找兼职销售员工的信息    |\n";
	cout<<"|4->修改兼职销售员工的信息    |\n";
	cout<<"|5->查看本人信息              |\n";
	cout<<"|6->修改登录密码              |\n";
	cout<<"|7->显示所有兼职销售员工的信息|\n";
	cout<<"|0->退出                      |\n";
	cout<<"+-----------------------------+\n";
}
void opteration_manager_sal(int id,SaleManager &SalMana)
{
	int num;
	int flag=0;
	while(flag<3)
	{
		cout<<"请输入你的选择:\n";
		cin>>num;
		switch(num)
		{
			case 1:
				SalMana.addSalPartTime(id);   
				face_manager_sal();
				break;
			case 2:
				SalMana.delSalPartTimeById();
				face_manager_sal();
				break;
			case 3:
				SalMana.querySalPartTimeInfo(); 
				face_manager_sal();
				break;
			case 4:
				SalMana.modifySalPartTime(); 
				face_manager_sal();
				break;
			case 5:
				SalMana.querySalManagerinfo(id);
				face_manager_sal();
				break;
			case 6:
				SalMana.update_passwd_salManager(id);
				face_manager_sal();
				break;
			case 7:
				SalMana.displayAllSalPartTimeInfo();
				face_manager_sal();
				break;
			case 0:
				cout<<"感谢您的本次操作,期待与您的下次见面!"<<endl;
				cout<<"         ****Bey-Bey****\n";
				flag=3;
				break;
			default:
				cout<<"输入错误,请重新输入\n";
				flag++;
				break;
		}	
	}
}
void face_boss()
{
	cout<<"\t\t\t欢迎来到公司老板操作界面\n";
	cout<<"\t\t   **********************************\n";
	cout<<"+------------------------+--------------------------+----------------------+----------------------+\n";
	cout<<"|1->添加兼职技术员工的信息| 5->添加兼职销售员工的信息| 9->添加销售经理的信息|13->添加技术经理的信息|\n";
	cout<<"|2->删除兼职技术员工的信息| 6->删除兼职销售员工的信息|10->删除销售经理的信息|14->删除技术经理的信息|\n";
	cout<<"|3->查看兼职技术员工的信息| 7->查看兼职销售员工的信息|11->查看销售经理的信息|15->查看技术经理的信息|\n";
	cout<<"|4->修改兼职技术员工的信息| 8->修改兼职销售员工的信息|12->修改销售经理的信息|16->修改技术经理的信息|\n";
	cout<<"|21->显示所有兼职技术员工 |22->显示所有兼职销售员工  |20->显示所有销售经理  |19->显示所有技术经理  |\n"; 
	cout<<"+------------------------+--------------------------+----------------------+----------------------+\n";
	cout<<"+-----------------+----------------+--------+\n";
	cout<<"|17->查看本人的信息|18->修改登录密码|0->退出|\n";
	cout<<"+------------------+------------------+-----+-----+\n";
	cout<<"|23->技术部门升降职|24->销售部门升降职|25->发公告|\n";
	cout<<"+------------------+------------------+----------+\n";
}
void opteration_boss(int id,Boss &boss)
{
	int num;
	int flag=0;
	bool judge;
	while(flag<3)
	{
		cout<<"请输入你的选择:\n";
		cin>>num;
		switch(num)
		{
			case 1:
				boss.addTecPartTime(id); 
				face_boss();
				break;
			case 5:
				boss.addSalPartTime(id); 
				face_boss();
				break;
			case 2:
				boss.delTecPartTimeById();
				face_boss();
				break;
			case 6:
				boss.delSalPartTimeById();
				face_boss();
				break;
			case 3:
				judge=boss.judgeTecPartTimeEmpty();
				if(judge)
				{
					cout<<"数据库表中没数据,请先添加数据\n";
					face_boss();
					break;
				}
				boss.queryTecPartTimeInfo();
				face_boss();
				break;
			case 7:
				judge=boss.judgeSalPartTimeEmpty();
				if(judge)
				{
					cout<<"数据库表中没数据,请先添加数据\n";
					face_boss();
					break;
				}
				boss.querySalPartTimeInfo();
				face_boss();
				break;
			case 4:
				boss.modifyTecPartTime(); 
				face_boss();
				break;
			case 8:
				boss.modifySalPartTime();
				face_boss();
				break;
			case 13:
				boss.addTecManager();
				face_boss();
				break;
			case 9:
				boss.addSalManager();
				face_boss();
				break;
			case 14:
				boss.delTecManagerById();
				face_boss();
				break;
			case 10:
				boss.delSalManagerById();
				face_boss();
				break;
			case 15:
				judge=boss.judgeTecManagerEmpty();
				if(judge)
				{
					cout<<"数据库表中没数据,请先添加数据\n";
					face_boss();
					break;
				}
				boss.queryTecManagerInfo(); 
				face_boss();
				break;
			case 11:
				judge=boss.judgeSalManagerEmpty();
				if(judge)
				{
					cout<<"数据库表中没数据,请先添加数据\n";
					face_boss();
					break;
				}
				boss.querySalManagerInfo();
				face_boss();
				break;
			case 16:
				boss.modifyTecManager();  
				face_boss();
				break;
			case 12:
				boss.modifySalManager(); 
				face_boss();
				break;
			case 17:
				boss.queryBoss(id);
				face_boss();
				break;
			case 18:
				boss.updateBossPwd(id);
				face_boss();
				break;
			case 19:
				boss.displayAllTecManagerInfo();
				face_boss();
				break;
			case 20:
				boss.displayAllSalManagerInfo();
				face_boss();
				break;
			case 21:
				boss.displayAllTecPartTimeInfo();
				face_boss();
				break;
			case 22:
	            boss.displayAllSalPartTimeInfo();
				face_boss();
				break;
			case 23:
				boss.tecSectionPromoteOrDemotion(boss);
				face_boss();
				break;
			case 24:
				boss.SalSectionPromoteOrDemotion(boss);
				face_boss();
				break;
			case 25:
				boss.setNotice();
				face_boss();
				break;
			case 0:
				cout<<"感谢您的本次操作,期待与您的下次见面!"<<endl;
				cout<<"         ****Bey-Bey****\n";
				flag=3;
				break;
			default:
				cout<<"输入错误,请重新输入\n";
				flag++;
				break;
		}	
	}
}
void login_part_tec()
{
	TecPartTime tec;
	if(mysql_query(conn,"select m_uiId,m_strName,m_strPwd from partTime_Tc"))
	{
		cout<<"显示兼职技术人员表的信息失败\n";
		exit(1);
	}
	res=mysql_use_result(conn);
	char name[20];
	char passwd[20];
	int flag=0;
	int id;
	while(flag<3)
	{
		cout<<"请输入登录者的名字:\n";
		cin>>name;
		cout<<"请输入登录者的密码:\n";
		system("stty -echo");
		cin>>passwd;
		system("stty echo");
		while((row=mysql_fetch_row(res))!=NULL)
		{
			id=atoi(row[0]);
			if((strcmp(name,row[1])==0) &&(strcmp(passwd,row[2])==0))
			{
				mysql_free_result(res);
				LoginTime();
				if(mysql_query(conn,"select * from pub_Notice"))
				{
					cout<<"failed\n";
					exit(1);
				}
				res=mysql_use_result(conn);
				row=mysql_fetch_row(res);
				if(*row!=NULL)
				{
					cout<<"请注意:老板有话说!\n";
					cout<<row[0]<<endl;
				}
				mysql_free_result(res);
				face_tec();
				opteration_tec(id,tec);
				flag=3;
				break;
			}
		}
		flag++;
		if(flag<3)
		{
			cout<<"输入的员工名或密码有误,请重新输入"<<endl;
		}
		if(flag==3)
		{
			cout<<"对比起,您登录三次都错,系统将自动关闭!\n";
			exit(1);
		}
	}
}
void login_manager_tec()
{
	TecManager Tma;
	if(mysql_query(conn,"select m_uiId,m_strName,m_strPwd from manager_Tc"))
	{
		cout<<"显示技术经理表的信息失败\n";
		exit(1);
	}
	res=mysql_use_result(conn);
	char name[20],passwd[20];
	int flag=0;
	int id;
	while(flag<3)
	{
		cout<<"请输入登录者的名字:\n";
		cin>>name;
		cout<<"请输入登录者的密码:\n";
		system("stty -echo");
		cin>>passwd;
		system("stty echo");
		while((row=mysql_fetch_row(res))!=NULL)
		{
			id=atoi(row[0]);
			if((strcmp(name,row[1])==0) && (strcmp(passwd,row[2])==0))
			{
				mysql_free_result(res);
				LoginTime();
				if(mysql_query(conn,"select * from pub_Notice"))
				{
					cout<<"failed\n";
					exit(1);
				}
				res=mysql_use_result(conn);
				while((row=mysql_fetch_row(res))!=NULL)
				{
					cout<<"请注意:老板有话说!\n";
					printf("%s\n",row[0]);
				}
				mysql_free_result(res);
				face_manager_tec();
				opteration_manager_tec(id,Tma);
				flag=3;
				break;
			}
		}
		flag++;
		if(flag<3)
		{
			cout<<"输入的员工名或密码有误,请重新输入"<<endl;
		}
		if(flag==3)
		{
			cout<<"对比起,您登录三次都错,系统将自动关闭!\n";
			exit(1);
		}
	}
}
void login_part_sal()
{
	SalePartTime Sal;
	if(mysql_query(conn,"select m_uiId,m_strName,m_strPwd from partTime_Sal"))
	{
		cout<<"显示兼职销售人员表的信息失败\n";
		exit(1);
	}
	res=mysql_use_result(conn);
	char name[20],passwd[20];
	int flag=0;
	int id;
	while(flag<3)
	{
		cout<<"请输入登录者的名字:\n";
		cin>>name;
		cout<<"请输入登录者的密码:\n";
		system("stty -echo");
		cin>>passwd;
		system("stty echo");
		while((row=mysql_fetch_row(res))!=NULL)
		{
			id=atoi(row[0]);
			if((strcmp(name,row[1])==0)&&(strcmp(passwd,row[2])==0))
			{
				mysql_free_result(res);
				LoginTime();
				if(mysql_query(conn,"select * from pub_Notice"))
				{
					cout<<"failed\n";
					exit(1);
				}
				res=mysql_use_result(conn);
				row=mysql_fetch_row(res);
				if(*row!=NULL)
				{
					cout<<"请注意:老板有话说!\n";
					cout<<row[0]<<endl;
				}
				mysql_free_result(res);
				face_sal();
				opteration_sal(id,Sal);
				flag=3;
				break;
			}
		}
		flag++;
		if(flag<3)
		{
			cout<<"输入的员工名或密码有误,请重新输入"<<endl;
		}
		if(flag==3)
		{
			cout<<"对比起,您登录三次都错,系统将自动关闭!\n";
			exit(1);
		}
	}
}
void login_manager_sal()
{
	SaleManager Sma;
	if(mysql_query(conn,"select m_uiId,m_strName,m_strPwd from manager_Sal"))
	{
		cout<<"显示销售经理表的信息失败\n";
		exit(1);
	}
	res=mysql_use_result(conn);
	char name[20],passwd[20];
	int flag=0;
	int id;
	while(flag<3)
	{
		cout<<"请输入登录者的名字:\n";
		cin>>name;
		cout<<"请输入登录者的密码:\n";
		system("stty -echo");
		cin>>passwd;
		system("stty echo");
		while((row=mysql_fetch_row(res))!=NULL)
		{
			id=atoi(row[0]);
			if((strcmp(name,row[1])==0)&&(strcmp(passwd,row[2])==0))
			{
				mysql_free_result(res);
				LoginTime();
				if(mysql_query(conn,"select * from pub_Notice"))
				{
					cout<<"failed\n";
					exit(1);
				}
				res=mysql_use_result(conn);
				row=mysql_fetch_row(res);
				if(*row!=NULL)
				{
					cout<<"请注意:老板有话说!\n";
					cout<<row[0]<<endl;
				}
				mysql_free_result(res);
				face_manager_sal();
				opteration_manager_sal(id,Sma);
				flag=3;
				break;
			}
		}
		flag++;
		if(flag<3)
		{
			cout<<"输入的员工名或密码有误,请重新输入"<<endl;
		}
		if(flag==3)
		{
			cout<<"对比起,您登录三次都错,系统将自动关闭!\n";
			exit(1);
		}
	}
}
void login_boss()
{
	Boss boss;
	if(mysql_query(conn,"select m_uiId,m_strName,m_strPwd from boss"))
	{
		cout<<"显示老板表的信息失败\n";
		exit(1);
	}
	char name[20];
	char passwd[20];
	int flag=0;
	int id;
	res=mysql_use_result(conn);
	while(flag<3)
	{
		cout<<"请输入登录者的名字:\n";
		cin>>name;
		cout<<"请输入登录者的密码:\n";
		system("stty -echo");
		cin>>passwd;
		system("stty echo");
		while((row=mysql_fetch_row(res))!=NULL)
		{
			id=atoi(row[0]);
			if((strcmp(name,row[1])==0) && (strcmp(passwd,row[2])==0))
			{
				mysql_free_result(res);
				LoginTime();
				face_boss();
				opteration_boss(id,boss);
				flag=3;
				break;
			}
		}
		flag++;
		if(flag<3)
		{
			cout<<"输入的员工名或密码有误,请重新输入"<<endl;
		}
		if(flag==3)
		{
			cout<<"对比起,您登录三次都错,系统将自动关闭!\n";
			exit(1);
		}
	}
}
void login_face()
{
	cout<<"\t\t***欢迎来到XXX公司人员管理系统***\n";
	cout<<"1->兼职技术人员登录"<<endl;
	cout<<"2->技术经理登录"<<endl;
	cout<<"3->兼职销售人员登录"<<endl;
	cout<<"4->销售经理登录"<<endl;
	cout<<"5->公司老板登录"<<endl;
	cout<<"0->退出"<<endl;
}
void login_work()
{
	int num;
	int flag=0;
	while(flag<3)
	{
		cout<<"请选择你要进行的操作:\n";
		cin>>num;
		switch(num)
		{
			case 1:
			 	login_part_tec();
				flag=3;
				break;
			case 2:
				login_manager_tec();
				flag=3;
				break;
			case 3:
				login_part_sal();
				flag=3;
				break;
			case 4:
				login_manager_sal();
				flag=3;
				break;
			case 5:
				login_boss();
				flag=3;
				break;
			case 0:
				cout<<"感谢您的本次操作,期待与您的下次见面!"<<endl;
				cout<<"         ****Bey-Bey****\n";
				flag=3;
				break;
			default:
				cout<<"输入错误,请重新输入\n";
				flag++;
		}
	}
	if(flag==3)
	{
		exit(1);
	}
}
#endif
