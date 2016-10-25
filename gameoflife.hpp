#ifndef GAMEOFLIFE_HEADER
#define GAMEOFLIFE_HEADER


//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <utility>
#include <fstream>
#include <algorithm>
#include <string.h>

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
using namespace std;


#define MAX_SPEED 1000


#define FOR(cont,max) for(int cont=0;cont<(int)max;cont++)
#define FOR2(cont,start,max) for(int cont=start;cont<(int)max;cont++)
#define CLEAR system("clear || cls")
#define MIN(x,y) (((x)<(y))?(x):( y))
#define MAX(x,y) (((x)>(y))?(x):( y))
#define ABS(x)   (((x)> 0 )?(x):-(x))

#define COLOR_BLACK    0
#define COLOR_RED      1
#define COLOR_GREEN    2
#define COLOR_YELLOW   3
#define COLOR_BLUE     4
#define COLOR_MAGENTA  5
#define COLOR_CYAN     6
#define COLOR_WHITE    7
#define COLOR_DEF      9
#define COLOR_BBLACK   60
#define COLOR_BRED     61
#define COLOR_BGREEN   62
#define COLOR_BYELLOW  63
#define COLOR_BBLUE    64
#define COLOR_BMAGENTA 65
#define COLOR_BCYAN    66
#define COLOR_BWHITE   67


#define KEY_ESC			"\x1b"
#define KEY_BCKSP		"\x7f"
#define KEY_UP			"\x1b[A"
#define KEY_LEFT		"\x1b[D"
#define KEY_DOWN		"\x1b[B"
#define KEY_RIGHT		"\x1b[C"
#define KEY_S_UP		"\x1b[1;2A"
#define KEY_S_LEFT		"\x1b[1;2D"
#define KEY_S_DOWN		"\x1b[1;2B"
#define KEY_S_RIGHT		"\x1b[1;2C"
#define KEY_DEL			"\x1b[3~"
#define KEY_INSERT		"\x1b[2~"
#define KEY_HOME		"\x1bOH"
#define KEY_PAGE_UP		"\x1b[5~"
#define KEY_PAGE_DOWN	"\x1b[6~"
#define KEY_END			"\x1bOF"
#define KEY_F1			"\x1bOQ"
#define KEY_F2			"\x1bOQ"
#define KEY_F3			"\x1bOR"
#define KEY_F4			"\x1bOS"
#define KEY_F5			"\x1b[15~"
#define KEY_F6			"\x1b[17~"
#define KEY_F7			"\x1b[18~"
#define KEY_F8			"\x1b[19~"
#define KEY_F9			"\x1b[20~"
#define KEY_F10			"\x1b[21~"
#define KEY_F11			"\x1b[21~"
#define KEY_F12			"\x1b[24~"

const pair<string,string> key_str[] = {
	{KEY_ESC,		"ESC"},
	{KEY_BCKSP,		"Backspace"},
	{KEY_UP,		"↑"},
	{KEY_LEFT,		"←"},
	{KEY_DOWN,		"↓"},
	{KEY_RIGHT,		"→"},
	{KEY_S_UP,		"Shift + ↑"},
	{KEY_S_LEFT,	"Shift + ←"},
	{KEY_S_DOWN,	"Shift + ↓"},
	{KEY_S_RIGHT,	"Shift + →"},
	{KEY_PAGE_UP,	"Page Up"},
	{KEY_PAGE_DOWN,	"Page Down"},
	{KEY_END,		"END"},
	{KEY_F1,		"F1"},
	{KEY_F2,		"F2"},
	{KEY_F3,		"F3"},
	{KEY_F4,		"F4"},
	{KEY_F5,		"F5"},
	{KEY_F6,		"F6"},
	{KEY_F7,		"F7"},
	{KEY_F8,		"F8"},
	{KEY_F9,		"F9"},
	{KEY_F10,		"F10"},
	{KEY_F11,		"F11"},
	{KEY_F12,		"F12"},
};

class cfg{
	cfg();
	~cfg();
	public:
		static cfg* pCfg;
		static cfg* config();
		int editting;
		int speed;
		int curX,curY;
		int cursorX,cursorY;
		int screenLar,screenAlt;
		int color[10];
		string dead,alive;
		string move[4],moveCursor[4];
		string next,back,pauseKey,speedUp,speedDown;
		string nextx10,speedUpx10,speedDownx10;
		string optionKey;
		void defConfig();
		bool load(string);
		void save();
		void optionScreen();
		void configScreen();
		void sleep();
		void moveCamera(int);
		void moveCurs(int);
		void pause();
};

class tab{
	public:
		int lar,alt,cont;
		char** v;
		tab();
		tab(int,int);
		~tab();
		void allocBoard();
		void deallocBoard();
		void operator=(const tab&);
		bool operator==(const tab&)const;
		int neigh(int,int);
		void print();
		void randomize();
};
class game{
	game();
	~game();
	public:
		static game* pGame;
		static game* jogo();
		short int rS,rB;
		tab board;
		tab prev[11];
		int prevBegin;//contador usado para guardar a posição de inicio da 'fila' prev.
		int prevEnd;//contador usado para guardar a posição de fim da 'fila' prev.
		short int ruleStringToInt(string);
		void readArq(const string&);
		void saveArq(const string&);
		void readRule(const string&);
		bool isAlive(int,int);
		bool willSurvive(int);
		bool willBeBorn(int);
		void next();
		void back();
		void print();
		void randomize();
};

class optMenu;

class menu_opt{
	public:
		menu_opt();
		virtual ~menu_opt();
		string s;
		virtual void print(bool)=0;
		virtual void click(optMenu&)=0;
};
class menu_opt_toogle : public menu_opt{
	public:
		menu_opt_toogle(string,string,int&);
		virtual ~menu_opt_toogle();
		string s2;
		int& val;
		virtual void click(optMenu&);
		virtual void print(bool);
};
class menu_opt_select : public menu_opt{
	public:
		menu_opt_select(string,vector<string>&,function<void(const string&)>);
		virtual ~menu_opt_select();
		int select;
		vector<string> v;
		function<void(string)> func;
		virtual void print(bool);
		virtual void click(optMenu&);
};
class menu_opt_write : public menu_opt{
	public:
		menu_opt_write(string,string,function<bool(string)>,function<void(const string&)>);
		string s2,s3;
		function<bool(string)> checkFunc;
		function<void(string)> func;
		virtual ~menu_opt_write();
		virtual void print(bool);
		virtual void click(optMenu&);
};
class menu_opt_button : public menu_opt{
	public:
		menu_opt_button(string,function<void()>);
		virtual ~menu_opt_button();
		function<void()> func;
		virtual void print(bool);
		virtual void click(optMenu&);
};

class optMenu{
	public:
		optMenu();
		~optMenu();
		vector<menu_opt*> options;
		int selected;
		void add_button_toogle(string,string,int&);
		void add_button_select(string,vector<string>,function<void(const string&)>);
		void add_button_write (string,string,function<bool(string)>,function<void(const string&)>);
		void add_button       (string,function<void()>);
		void print();
		void click();
		int size();
};







void clear();
void changeFGcolor(int);
void changeBGcolor(int);
void resetColor();
void quit();
int readIntInRange(int,int);				//le um inteiro entre a e b
vector<string> getArqNames(string,string);
vector<string> printArqNames(string,string);//imprime na tela todos os arquivos com extensão ext no diretório dir
bool checkValidPatternName(string);
bool canOpen(string);						//checa se é possivel abrir o arquivo
bool kbhit();								//checa se existe algo na entrada padrão
char getch();								//le um caracter da entrada padrão sem o bloqueio de entrada(nao necessita apertar enter)
string getchAll();							//le um caracter da entrada padrão sem o bloqueio de entrada até a entrada estar vazia(nao necessita apertar enter)
string getchLine();							//le um caracter da entrada padrão sem o bloqueio de entrada até a entrada estar vazia ou até a quebra de linha(nao necessita apertar enter)
void readArq(const string&);
void saveArq(const string&);
void readRule(const string&);
void openConfigScreen();
void openOptionScreen();
string keyToStr(string);
void randomize();

#endif	