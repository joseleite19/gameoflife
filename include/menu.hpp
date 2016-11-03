#ifndef MENU_CPP
#define MENU_CPP

#include <string>
#include <vector>
#include <functional>

//WARNING: It is not a good pratice to use namespaces in headers. In exchange you need to use std:: prefix to adress a string. However in this scenario it turns out impossible to read this header. So a temporary fix was done using macros.
#define string std::string
#define vector std::vector
#define function std::function

class menu_opt;

class optMenu{
	public:
		optMenu();
		~optMenu();
		vector<menu_opt*> options;
		int 	selected;
		void 	add_button_toogle	(string,string,int&,function<void(int&)>);
		void 	add_button_select	(string,vector<string>,function<void(const string&)>);
		void 	add_button_write 	(string,string,function<bool(string)>,function<void(const string&)>);
		void 	add_button       	(string,function<void()>);
		void 	print();
		void 	click();
		int 	size();
};

class menu_opt{
	public:
		menu_opt();
		virtual ~menu_opt();
		
		string s;
		virtual void	print(bool)=0; 		//not enough clear that a parameter is initialized as zero
		virtual void 	click(optMenu&)=0;
};

class menu_opt_toogle : public menu_opt{
	public:
		menu_opt_toogle(string,string,int&,function<void(int&)>);
		virtual ~menu_opt_toogle();
		
		string				on,off;
		int& 				val;
		function<void(int)>	func;
		virtual void 	click(optMenu&);
		virtual void 	print(bool);
};

class menu_opt_select : public menu_opt{
	public:
		menu_opt_select(string,vector<string>&,function<void(const string&)>);
		virtual ~menu_opt_select();
		
		int 					select;
		vector<string> 			v;
		function<void(string)>	func;
		virtual void 	print(bool);
		virtual void 	click(optMenu&);
};

class menu_opt_write : public menu_opt{
	public:
		menu_opt_write(string,string,function<bool(string)>,function<void(const string&)>);
		string 					s,message,error;
		function<bool(string)>	checkFunc;
		function<void(string)> 	func;
		virtual ~menu_opt_write();
		virtual void 	print(bool);
		virtual void 	click(optMenu&);
};

class menu_opt_button : public menu_opt{
	public:
		menu_opt_button(string,function<void()>);
		virtual ~menu_opt_button();
		
		function<void()>	func;
		virtual void 	print(bool);
		virtual void 	click(optMenu&);
};


#undef string
#undef vector
#undef functional
#endif