//NOTE: compiler needs -std=c++11
#include "./include/menu.hpp"
#include "./include/game.hpp"
#include "./include/terminal.hpp"
#include "./include/util.hpp"
#include "./include/config.hpp"


#include <stdio.h>
#include <sys/ioctl.h>

using namespace std;

void printBorders(){
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	int scrLar=w.ws_col;
	//int scrAlt=w.ws_row;
	FOR(i,(scrLar-pConfig->screenLar-2)/2)printf(" ");
	changeBGcolor(COLOR_YELLOW);printf("│");
	changeBGcolor(COLOR_GREEN); FOR(i,(pConfig->screenLar))printf(" ");
	changeBGcolor(COLOR_YELLOW);printf("│");
	resetColor();
	printf("\r");
	FOR(i,(scrLar-pConfig->screenLar-2)/2)printf(" ");
	printf("	");
	changeBGcolor(COLOR_GREEN);
}


menu_opt::menu_opt(){}
menu_opt::~menu_opt(){}

menu_opt_toogle::menu_opt_toogle(string str,string str2,int& v,function<void(int&)> f):
	on{str2},off{str},val{v}{f=func;}
menu_opt_toogle::~menu_opt_toogle(){}
void menu_opt_toogle::click(optMenu &menu){
	val = (val+1)%2;
	if(func)func(val);
}
void menu_opt_toogle::print(bool selected){
	printBorders();
	if(selected)changeBGcolor(COLOR_BBLACK);
	if(val)printf("%s",on.c_str());
	else   printf("%s",off.c_str());
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
	printBorders();
	if(selected)changeBGcolor(COLOR_BBLACK);
	printf("%s",s.c_str());
	resetColor();
	printf("\n");
	if(select>0){
		FOR(i,v.size()){
			printBorders();
			if(selected && select-1==i)changeBGcolor(COLOR_BBLACK);
			printf("	%s",v[i].c_str());
			resetColor();
			printf("\n");
		}
	}
}


menu_opt_write::menu_opt_write(string str,string str2,function<bool(string)> check,function<void(const string&)> f):
	s{str},message{""},error{str2}{checkFunc=check;func=f;}
menu_opt_write::~menu_opt_write(){}
void menu_opt_write::click(optMenu &menu){
	string in;
	message=" ";
	clear();
	menu.print();
	message="";
	while(1){
		in = getchLine();
		if(in==KEY_ESC)return;
		else if(in==KEY_BCKSP)message.pop_back();
		else if(in=="\n"){
			if(message=="")continue;
			if(checkFunc(message)){
				func(message);
				message="";
				getchar();
				return;
			}
			else{
				printf("%s\n",error.c_str());
				message="";
				getchar();
			}
		}
		else message+=in;
		clear();
		menu.print();
	}
}
void menu_opt_write::print(bool selected){
	printBorders();
	if(selected)changeBGcolor(COLOR_BBLACK);
	printf("%s",s.c_str());
	resetColor();
	printf("\n");
	if(selected && message!=""){
		printBorders();
		changeBGcolor(COLOR_BBLACK);
		printf("	%s",message.c_str());
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
	printBorders();
	if(selected)changeBGcolor(COLOR_BBLACK);
	printf("%s",s.c_str());
	resetColor();
	printf("\n");
}
