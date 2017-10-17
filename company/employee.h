#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_
#include<iostream>
#include <string>

using namespace std;
enum ENUM_EMPLOYEE_LEVEL
{
	ENUM_EMPLOYEE_LEVEL_MIN = 0,
	ENUM_EMPLOYEE_LEVEL_PARTTIME_TEC, //兼职技术人员
	ENUM_EMPLOYEE_LEVEL_MANAGER_TEC, //技术经理
	ENUM_EMPLOYEE_LEVEL_PARTTIME_SALE, //兼职销售人员
	ENUM_EMPLOYEE_LEVEL_MANAGER_SALE, //销售经理
	ENUM_EMPLOYEE_LEVEL_BOSS, //老板
	ENUM_EMPLOYEE_LEVEL_MAX = 0x00ffffff
};


class Employee
{
public:
	int m_uiId; //员工编号
	string m_strPwd; //登入密码
	string m_strName; //姓名
	int m_uiLevel; //级别
	string m_strNote; //备注
};

#endif 
