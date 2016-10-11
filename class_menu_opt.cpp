#include "gameoflife.hpp"


menu_opt_toogle::menu_opt_toogle(string,string&,int&){

}
void menu_opt_toogle::click(){

}
void menu_opt_toogle::print(){

}


menu_opt_select::menu_opt_select(string s,vector<string>& options,function<void(string)> func){

}
void menu_opt_select::click(){

}
void menu_opt_select::print(){

}


menu_opt_write::menu_opt_write(string s,function<bool(string)> checkFunc,function<void(string)> func){

}
void menu_opt_write::click(){
	
}
void menu_opt_write::print(){
	
}


menu_opt_button::menu_opt_button(string s,function<void()>func){

}
void menu_opt_button::click(){

}
void menu_opt_button::print(){

}
