#include "gameoflife.hpp"


menu_opt::menu_opt(){}
menu_opt::~menu_opt(){}

menu_opt_toogle::menu_opt_toogle(string str,string str2,int& v):
	s2{str2},val{v}{s=str;}
menu_opt_toogle::~menu_opt_toogle(){}
void menu_opt_toogle::click(optMenu &menu){
	val = (val+1)%2;
}
void menu_opt_toogle::print(bool selected){
	if(selected)changeBGcolor(COLOR_BBLACK);
	if(val)printf("%s",s2.c_str());
	else   printf("%s",s.c_str());
	resetColor();
	printf("\n");
}


menu_opt_select::menu_opt_select(string str,vector<string> &opts,function<void(const string&)> f):
	select{-1},v{opts}{s=str;func=f;}
menu_opt_select::~menu_opt_select(){}
void menu_opt_select::click(optMenu &menu){
	string in;
	select*=-1;
	while(1){
		clear();
		menu.print();
		in = getchLine();
		if(in==KEY_UP)select=MAX(1,select-1);
		else if(in==KEY_DOWN)select=MIN((int)v.size(),select+1);
		else if(in==KEY_ESC)break;
		else if(in=="\n"){
			func(v[select-1]);
			break;
		}
	}
	select*=-1;
}
void menu_opt_select::print(bool selected){
	if(selected)changeBGcolor(COLOR_BBLACK);
	printf("%s",s.c_str());
	resetColor();
	printf("\n");
	if(select>0){
		FOR(i,v.size()){
			if(selected && select-1==i)changeBGcolor(COLOR_BBLACK);
			printf("	%s",v[i].c_str());
			resetColor();
			printf("\n");
		}
	}
}


menu_opt_write::menu_opt_write(string str,string str3,function<bool(string)> check,function<void(const string&)> f):
	s2{""},s3{str3}{s=str;checkFunc=check;func=f;}
menu_opt_write::~menu_opt_write(){}
void menu_opt_write::click(optMenu &menu){
	string s;
	s2=" ";
	clear();
	menu.print();
	s2="";
	while(1){
		s = getchLine();
		if(s==KEY_ESC)return;
		else if(s==KEY_BCKSP)s2.pop_back();
		else if(s=="\n"){
			if(s2=="")continue;
			if(checkFunc(s2)){
				func(s2);
				s2="";
				getchar();
				return;
			}
			else{
				printf("%s\n",s3.c_str());
				s2="";
				getchar();
			}
		}
		else s2+=s;
		clear();
		menu.print();
	}
}
void menu_opt_write::print(bool selected){
	if(selected)changeBGcolor(COLOR_BBLACK);
	printf("%s",s.c_str());
	resetColor();
	printf("\n");
	if(selected && s2!=""){
		changeBGcolor(COLOR_BBLACK);
		printf("	%s",s2.c_str());
		resetColor();
		printf("\n");
	}
}


menu_opt_button::menu_opt_button(string str,function<void()> f){s=str;func=f;}
menu_opt_button::~menu_opt_button(){}
void menu_opt_button::click(optMenu &menu){
	func();
}
void menu_opt_button::print(bool selected){
	if(selected)changeBGcolor(COLOR_BBLACK);
	printf("%s",s.c_str());
	resetColor();
	printf("\n");
}
