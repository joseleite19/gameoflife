//NOTE: compiler needs -std=c++11
#include "./include/config.hpp"
#include "./include/util.hpp"
#include "./include/terminal.hpp"
#include "./include/menu.hpp"
#include "./include/game.hpp"

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

cfg* cfg::pCfg = NULL;

/**
 *  \brief Returns new game configuration object
 *  
 *  \details When a game configuration object (cfg) is created, an default configuration set is automatically loaded by code
 */
cfg::cfg(){
	defConfig();
}
cfg::~cfg(){
	delete[] pCfg;
	pCfg = NULL;
}
cfg* pConfig{
	if(!pCfg) 
		pCfg = new cfg;
		
	return pCfg;
}


void cfg::defConfig(){
	editting		= 0;
	speed			= -100;
	curX			= 0;
	cursorX			= 0;
	curY			= 0;
	cursorY			= 0;
	dead			= ".";
	alive			= "#";
	pauseKey		= " ";
	optionKey		= KEY_ESC;
	next			= KEY_RIGHT;
	back			= KEY_LEFT;
	speedUp			= KEY_UP;
	speedDown		= KEY_DOWN;
	nextx10			= KEY_S_RIGHT;
	speedUpx10		= KEY_S_UP;
	speedDownx10	= KEY_S_DOWN;
	move[0]			= "w";
	move[1]			= "a";
	move[2]			= "s";
	move[3]			= "d";
	moveCursor[0]	= "W";
	moveCursor[1]	= "A";
	moveCursor[2]	= "S";
	moveCursor[3]	= "D";
	color[0]		= COLOR_BLACK;
	color[1]		= COLOR_WHITE;
	color[2]		= COLOR_MAGENTA;
	color[3]		= COLOR_RED;
	color[4]		= COLOR_BYELLOW;
	color[5]		= 8;
	color[6]		= COLOR_BBLUE;
	color[7]		= COLOR_BLUE;
	color[8]		= COLOR_BGREEN;
	color[9]		= COLOR_BBLACK;
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	screenLar=w.ws_col-20;
	screenAlt=w.ws_row-12;
}

bool cfg::load(string arqName){return false;}//TODO load configs from file
void cfg::save(){}//TODO save configs in file


void cfg::optionScreen(){
	optMenu menu;
	string in;

	menu.add_button_toogle("Edit cells manually",				"Stop manual editting",	pConfig->editting,		NULL);
	menu.add_button_write ("Save current cell map to a file",	"Invalid file name",	checkValidPatternName,	[](string s){pJogo->saveArq(s);});
	menu.add_button_select("Load a cell map from a file",			getArqNames("./patterns/",".life"),			[](string s){pJogo->readArq(s);});
	menu.add_button_select("Load a new set of rules from a file",	getArqNames("./rules/",".rule"),			[](string s){pJogo->readRule(s);});
	menu.add_button       ("Configs(TODO)",		[](){pConfig->configScreen();});
	menu.add_button       ("Randomize",			[](){pJogo->randomize();});
	menu.add_button       ("Quit GameOfLife",	[](){clear();exit(0);});
	
	while(1){
		clear();
		menu.print();
		
		in = getchLine();
		if(in==KEY_UP)
			menu.selected=MAX(0,menu.selected-1);
		else if(in==KEY_DOWN)
			menu.selected=MIN(menu.size()-1,menu.selected+1);
		else if(in==KEY_ESC)
			break;
		else if(in==KEY_ENTER)
			menu.click();
	}
}

void cfg::configScreen(){}//TODO screen to change configs

void cfg::sleep(){
	usleep(10000000/(pConfig->speed));
};

void cfg::moveCamera(int direction){
	switch (direction){
		case 0:
			curY = ((curY-1)+pJogo->board.alt)%pJogo->board.alt; break;
		case 1:
			curX = ((curX-1)+pJogo->board.lar)%pJogo->board.lar; break;
		case 2:
			curY = (curY+1)%pJogo->board.alt; break;
		case 3:
			curX = (curX+1)%pJogo->board.lar; break;
	}
}

void cfg::moveCurs(int direction){
	switch (direction){
		case 0:
			cursorY = ((cursorY-1)+pJogo->board.alt)%pJogo->board.alt; break;
		case 1:
			cursorX = ((cursorX-1)+pJogo->board.lar)%pJogo->board.lar; break;
		case 2:
			cursorY = (cursorY+1)%pJogo->board.alt; break;
		case 3:
			cursorX = (cursorX+1)%pJogo->board.lar; break;
	}
}

void cfg::pause(){
	speed = ABS(speed)*(-1);
}
