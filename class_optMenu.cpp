#include "gameoflife.hpp"


optMenu::~optMenu(){
	for(auto i:options)delete[] i;
}

void optMenu::add_button_toogle(string s,string s2,int& val){
	menu_opt *p = new menu_opt_toogle(s,s2,val);
	options.push_back(p);
}
void optMenu::add_button_select(string s,vector<string> opts,function<void(const string&)> func){
	menu_opt *p = new menu_opt_select(s,opts,func);
	options.push_back(p);
}
void optMenu::add_button_write (string s,function<bool(string)> checkFunc,function<void(const string&)> func){
	menu_opt *p = new menu_opt_write(s,checkFunc,func);
	options.push_back(p);
}
void optMenu::add_button       (string s,function<void()> func){
	menu_opt *p = new menu_opt_button(s,func);
	options.push_back(p);
}

void optMenu::print(){
	int cont=0;
	for(auto i:options){
		i->print(selected==cont++);
	}
}
