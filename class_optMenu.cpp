#include "gameoflife.hpp"


optMenu::optMenu():selected{0}{}
optMenu::~optMenu(){
	FOR(i,options.size()){
		cout << options[i] << endl;
		delete options[i];
	}
}

void optMenu::add_button_toogle(string s,string s2,int& val){
	menu_opt *p = new menu_opt_toogle(s,s2,val);
	options.push_back(p);
}

void optMenu::add_button_select(string s,vector<string> opts,function<void(const string&)> func){
	menu_opt *p = new menu_opt_select(s,opts,func);
	options.push_back(p);
}

void optMenu::add_button_write (string s,string s3,function<bool(string)> checkFunc,function<void(const string&)> func){
	menu_opt *p = new menu_opt_write(s,s3,checkFunc,func);
	options.push_back(p);
}

void optMenu::add_button       (string s,function<void()> func){
	menu_opt *p = new menu_opt_button(s,func);
	options.push_back(p);
}


void optMenu::print(){
	int cont=0;
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	int scrLar=w.ws_col;
	int scrAlt=w.ws_row;

	FOR(i,(scrAlt-cfg::config()->screenAlt-2)/2)printf("\n");

	FOR(i,(scrLar-cfg::config()->screenLar-2)/2)printf(" ");
	changeBGcolor(COLOR_YELLOW);
	printf("┌");FOR(i,cfg::config()->screenLar/2)printf("──");printf("┐");
	resetColor();
	printf("\n");

	FOR(i,(scrLar-cfg::config()->screenLar-2)/2)printf(" ");
	changeBGcolor(COLOR_YELLOW);printf("│");
	changeBGcolor(COLOR_GREEN);FOR(i,cfg::config()->screenLar/2)printf("  ");
	changeBGcolor(COLOR_YELLOW);printf("│");
	resetColor();
	printf("\n");

	FOR(i,(scrLar-cfg::config()->screenLar-2)/2)printf(" ");
	changeBGcolor(COLOR_YELLOW);printf("│");
	changeBGcolor(COLOR_GREEN);FOR(i,cfg::config()->screenLar/2)printf("  ");
	changeBGcolor(COLOR_YELLOW);printf("│");
	resetColor();
	printf("\n");

	for(auto i:options){
		i->print(selected==cont++);
	}


	FOR(i,(scrLar-cfg::config()->screenLar-2)/2)printf(" ");
	changeBGcolor(COLOR_YELLOW);printf("│");
	changeBGcolor(COLOR_GREEN);FOR(i,cfg::config()->screenLar/2)printf("  ");
	changeBGcolor(COLOR_YELLOW);printf("│");
	resetColor();
	printf("\n");

	FOR(i,(scrLar-cfg::config()->screenLar-2)/2)printf(" ");
	changeBGcolor(COLOR_YELLOW);printf("│");
	changeBGcolor(COLOR_GREEN);FOR(i,cfg::config()->screenLar/2)printf("  ");
	changeBGcolor(COLOR_YELLOW);printf("│");
	resetColor();
	printf("\n");

	FOR(i,(scrLar-cfg::config()->screenLar-2)/2)printf(" ");
	changeBGcolor(COLOR_YELLOW);
	printf("└");FOR(i,cfg::config()->screenLar/2)printf("──");printf("┘");
	resetColor();
	printf("\n\n");

	FOR(i,(scrAlt-cfg::config()->screenAlt-2)/2)printf("\n");
}

int optMenu::size(){
	return options.size();
}

void optMenu::click(){
	options[selected]->click(*this);
}
