#include "gameoflife.hpp"

void optMenu::add_button_toogle(string s,string s2,int& val){
	buttons.push_back(new menu_opt_toogle(s,s2,val));
}
void optMenu::add_button_select(string s,vector<string>& options,function<void(const string&)> func){
	buttons.push_back(new menu_opt_select(s,options,func));
}
void optMenu::add_button_write (string s,function<bool(string)> checkFunc,function<void(string)> func){
	buttons.push_back(new menu_opt_write(s,checkFunc,func));
}
void optMenu::add_button       (string s,function<void()>func){
	buttons.push_back(new menu_opt_button(s,func));
}

void optMenu::print(){
	for(auto &i : buttons){
		i.print(selected);
	}
}
