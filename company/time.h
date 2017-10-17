#ifndef TIME_H
#define TIME_H

#include<fstream>
char *getCurrentTime(char *str)
{
	time_t t;
	//拿到一个相对的时间，相对1900的某个时间点的时间
	time(&t);
	//本地化的时间
	struct tm *l=localtime(&t);
	sprintf(str,"%d-%d-%d %d:%d:%d",
	l->tm_year+1900,l->tm_mon+1,l->tm_mday,
	l->tm_hour,l->tm_min,l->tm_sec);
	return str;
}
void LoginTime()
{
	char a[140]="d";
	ifstream LookTime("time.txt",ios::in);
	LookTime.getline(a,140);
	LookTime.close();
	if(strcmp(a,"\0")==0)
	{
		cout<<"\t上次登录时间过于久远！！！"<<endl;
		cout<<endl;
	}
	else
	{
		cout<<"上次登录时间：　";
		cout<<a<<endl;
	}
	char *p;
	char s[150];
    p=getCurrentTime(s);
	ofstream Time("time.txt");
	Time<<p;
	Time.close();
	cout<<"本次登录时间：";
	cout<<p<<endl;
}
#endif
