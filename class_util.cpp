#include "./include/util.hpp"
#include "./include/terminal.hpp"
#include "./include/game.hpp"
#include "./include/config.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <string.h>

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

using namespace std;

void clear(){
	system("clear || cls");
}

void changeFGcolor(int x){
	printf("\x1b[%dm",30+x);
}

void changeBGcolor(int x){
	printf("\x1b[%dm",40+x);
}

void invBGcolor(){
	printf("\x1b[%dm",7);
}

void resetColor(){
	printf("\x1b[0m");
}


/**
 *  \brief Reads an integer that is inside a range
 */
int readIntInRange(int a, int b){
	int x;
	
	if(a == b){//[a,+infinito]
		while(1){
			x=a-1;
			scanf(" %d",&x);
			while(getchar()!='\n');
			if(x>=a)return x;
		}
	}
	if(a>b){//[-infinito,b]
		while(1){
			x=b+1;
			scanf(" %d",&x);
			while(getchar()!='\n');
			if(x<=b)return x;
		}
	}
	while(1){
		x=a-1;
		scanf(" %d",&x);
		while(getchar()!='\n');
		if(a<=x && x<=b)return x;
	}
}

vector<string> getArqNames(string dir,string ext){
	ifstream arq;
	vector<string> s;
	string line,out = "ls " + dir + " > " + dir + "arqs.txt";
	system(out.c_str());
	arq.open(dir + "arqs.txt");
	if(arq.is_open()){
		while(getline(arq,line)){
			if(line.substr(line.size()-ext.size())==ext){
				s.push_back(line.substr(0,line.size()-ext.size()));
			}
		}
	}
	return s;
}

/**
 *  \brief Prints all files that has a given extension inside a directory
 */
vector<string> printArqNames(string dir, string ext){
	ifstream arq;
	vector<string> s;
	string line,out = "ls " + dir + " > " + dir + "arqs.txt";
	system(out.c_str());
	arq.open(dir + "arqs.txt");
	if(arq.is_open()){
		while(getline(arq,line)){
			if(line.substr(line.size()-ext.size())==ext){
				s.push_back(line.substr(0,line.size()-ext.size()));
				printf("%s\n",line.substr(0,line.size()-ext.size()).c_str());
			}
		}
	}
	return s;
}

bool checkValidPatternName(string s){
	vector<string> v=getArqNames("./patterns/",".life");
	return find(v.begin(),v.end(),s)==v.end();
}

/**
 *  \brief Checks if a file can be opened
 */
bool canOpen(string arqName){
	ifstream arq;
	arq.open(arqName);
	if(arq.is_open()){
		arq.close();
		return true;
	}
	return false;
}

/**
 *  \brief Checks if exists something at standard input (stdin)  
 */
bool kbhit(){
	struct termios oldt, newt;
	int ch, oldf;
	tcgetattr(STDIN_FILENO,&oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF){
		ungetc(ch,stdin);
		return true;
	}
	return false;
}

/**
 *  \brief Reads one character from standard input without input block
 *  
 *  Return an character without waiting the user to press enter to confirm the input.
 */
char getch(){
	int ch;
	struct termios oldt;
	struct termios newt;
	tcgetattr(STDIN_FILENO,&oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

//le um caracter da entrada padrão sem o bloqueio de entrada até a entrada estar vazia(nao necessita apertar enter)
string getchAll(){
	string s="";
	s+=getch();
	while(kbhit())s+=getch();
	return s;
}

string getchLine(){//le um caracter da entrada padrão sem o bloqueio de entrada até a entrada estar vazia ou até a quebra de linha(nao necessita apertar enter)
	char c;
	string s="";
	s+=getch();
	while(kbhit()){
		c=getch();
		if(c=='\n')break;
		s+=c;
	}
	return s;
}

void readArq(const string& s){
	game::jogo()->readArq(s);
}

void saveArq(const string& s){
	game::jogo()->saveArq(s);
}

void readRule(const string& s){
	game::jogo()->readRule(s);
}

void openConfigScreen(){
	cfg::config()->configScreen();
}

void openOptionScreen(){
	cfg::config()->optionScreen();
}

void randomize(){
	game::jogo()->randomize();
}


//NOTE: keyCode to keyFriendlyName lookup table
const std::pair<std::string,std::string> key_str[] = {
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

string keyToStr(string key){
	for(auto i:key_str){
		if(key==i.first)
			return i.second;
	}
	return key;
}