#include "gameoflife.h"

void optMenu::add_button_toogle(const string s,const string s2,int& val){
	buttons.push_back(new menu_opt_toogle(s,s2,val));
}
void optMenu::add_button_select(const string s,const vector<string>& options,void(game::*)(const string&)){
	buttons.push_back(new menu_opt_select(s,options,func));
}
void optMenu::add_button_write (const string s,bool(const string&) checkFunc,(void) func (const string)){
	buttons.push_back(new menu_opt_write(s,checkFunc,func));
}
void optMenu::add_button       (const string s,(void) func()){
	buttons.push_back(new menu_opt_button(s,func));
}

void optMenu::print(){
	for(auto &i : buttons){
		i.print(selected);
	}
}
