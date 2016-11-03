#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#define pConfig cfg::config()

class cfg{
	cfg();
	~cfg();
	public:
		static cfg* pCfg;
		static cfg* config();
		
		int 			editting;
		int 			speed; //TODO: Where speed is set
		int 			curX,curY;
		int 			cursorX,cursorY;
		int 			screenLar,screenAlt;
		int 			color[10]; //color pallete
		std::string 	dead,alive; 
		std::string 	move[4],moveCursor[4];
		std::string 	next,back,pauseKey,speedUp,speedDown;
		std::string 	nextx10,speedUpx10,speedDownx10;
		std::string 	optionKey;
		
		bool	load(std::string);
		void 	save();
		void 	optionScreen();
		void 	configScreen();
		void 	sleep();
		void 	moveCamera(int);
		void 	moveCurs(int);
		void 	pause();
		
	private:
		void defConfig();
};

#endif