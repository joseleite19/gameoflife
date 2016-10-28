#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>


#define FOR(cont,max) for(int cont=0;cont<(int)max;cont++)
#define FOR2(cont,start,max) for(int cont=start;cont<(int)max;cont++)
#define CLEAR system("clear || cls")
#define MIN(x,y) (((x)<(y))?(x):( y))
#define MAX(x,y) (((x)>(y))?(x):( y))
#define ABS(x)   (((x)> 0 )?(x):-(x))


void 	clear();
void 	changeFGcolor(int);
void 	changeBGcolor(int);
void 	resetColor();

int 	readIntInRange(int a,int b);
std::vector<std::string> getArqNames(std::string,std::string);
std::vector<std::string> printArqNames(std::string,std::string);
bool 	checkValidPatternName(std::string);
bool 	canOpen(std::string);

/* Windows-native functions */
bool 			kbhit();
char 			getch();
std::string 	getchAll();
std::string 	getchLine();

void 	readArq(const std::string&);
void 	saveArq(const std::string&);
void 	readRule(const std::string&);
void 	openConfigScreen();
void 	openOptionScreen();
std::string 	keyToStr(std::string);
void 	randomize();

#endif