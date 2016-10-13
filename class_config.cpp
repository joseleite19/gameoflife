#include "gameoflife.hpp"

cfg* cfg::pCfg;
cfg::cfg(){
	defConfig();
}
cfg::~cfg(){
	delete[] pCfg;
	pCfg = NULL;
}
cfg* cfg::config(){
	if(!pCfg) return pCfg = new cfg;
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
	//((7*v[xx][yy])%9)
	color[0]		= COLOR_BLACK;
	color[1]		= COLOR_WHITE;
	color[2]		= COLOR_MAGENTA;
	color[3]		= COLOR_RED;
	color[4]		= COLOR_YELLOW;
	color[5]		= 8;
	color[6]		= COLOR_CYAN;
	color[7]		= COLOR_BLUE;
	color[8]		= COLOR_GREEN;
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
	function<void(const string&)> func1;
	function<bool(const string&)> func2;
	function<void()> func3;
	menu.add_button_toogle("Edit cells manually(TODO)","Stop manual editting(TODO)",cfg::config()->editting);
	func1 = readArq;
	menu.add_button_select("Load a cell map from a file",getArqNames("./patterns/",".life"),func1);
	func1 = saveArq;
	func2 = checkValidPatternName;
	menu.add_button_write ("Save current cell map to a file","Invalid file name",func2,func1);
	func3 = openConfigScreen;
	menu.add_button       ("Configs(TODO)",func3);
	func3 = quit;
	menu.add_button       ("Quit GameOfLife",func3);
	while(1){
		clear();
		menu.print();
		in = getchLine();
		if(in==KEY_UP)menu.selected=MAX(0,menu.selected-1);
		else if(in==KEY_DOWN)menu.selected=MIN(menu.size()-1,menu.selected+1);
		else if(in==KEY_ESC)break;
		else if(in=="\n")menu.click();
	}
}
void cfg::configScreen(){}//TODO screen to change configs
void cfg::sleep(){
	usleep(10000000/(cfg::config()->speed));
}
void cfg::moveCamera(int dir){
	if(dir==0) curY = ((curY-1)+game::jogo()->board.alt)%game::jogo()->board.alt;
	if(dir==1) curX = ((curX-1)+game::jogo()->board.lar)%game::jogo()->board.lar;
	if(dir==2) curY = (curY+1)%game::jogo()->board.alt;
	if(dir==3) curX = (curX+1)%game::jogo()->board.lar;
}
void cfg::moveCurs(int dir){
	if(dir==0) cursorY = ((cursorY-1)+game::jogo()->board.alt)%game::jogo()->board.alt;
	if(dir==1) cursorX = ((cursorX-1)+game::jogo()->board.lar)%game::jogo()->board.lar;
	if(dir==2) cursorY = (cursorY+1)%game::jogo()->board.alt;
	if(dir==3) cursorX = (cursorX+1)%game::jogo()->board.lar;
}
void cfg::pause(){
	speed = ABS(speed)*-1;
}
