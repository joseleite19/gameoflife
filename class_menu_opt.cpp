menu_opt::menu_opt(const string&,const string&,int&);
void menu_opt::print();
void menu_opt::click();

menu_opt_toogle::menu_opt_toogle(const string,const string&,int&);
void menu_opt_toogle::click();
void menu_opt_toogle::print();


menu_opt_select::menu_opt_select(const string,const vector<string>&,void(game::*)(const string&)){

}
void menu_opt_select::click();
void menu_opt_select::print();


menu_opt_write::menu_opt_write(const string&,int(const string),void(const string));
void menu_opt_write::click();


menu_opt_button(const string&,void());
void menu_opt_button::click();
