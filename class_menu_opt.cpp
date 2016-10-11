#include "gameoflife.hpp"


menu_opt::menu_opt(){}
menu_opt::~menu_opt(){}

menu_opt_toogle::menu_opt_toogle(string s,string s2,int& v):val{v}{

}
menu_opt_toogle::~menu_opt_toogle(){}
void menu_opt_toogle::click(){

}
void menu_opt_toogle::print(bool selected){

}


menu_opt_select::menu_opt_select(string s,vector<string> &opts,function<void(const string&)> func):v{opts}{

}
menu_opt_select::~menu_opt_select(){}
void menu_opt_select::click(){

}
void menu_opt_select::print(bool selected){

}


menu_opt_write::menu_opt_write(string s,function<bool(string)> checkFunc,function<void(const string&)> func){

}
menu_opt_write::~menu_opt_write(){}
void menu_opt_write::click(){
	
}
void menu_opt_write::print(bool selected){
	
}


menu_opt_button::menu_opt_button(string s,function<void()> func){

}
menu_opt_button::~menu_opt_button(){}
void menu_opt_button::click(){

}
void menu_opt_button::print(bool selected){

}
