#include "./include/game.hpp"
#include "./include/config.hpp"
#include "./include/util.hpp"

#include <stdlib.h> //WARNING: couldn't find which header does srand belongs to in old gameoflife.hpp
#include <unistd.h>

#define MAX_SPEED 1000

using namespace std;

int main(){
	srand(time(NULL));

	game::pGame = NULL;
	cfg::pCfg = NULL;

	string in;
	while(1){
		clear();
		game::jogo()->print();
		if(cfg::config()->speed>=0){
			cfg::config()->sleep();
			if(!kbhit()){
				game::jogo()->next();
				continue;
			}
		}

		in = getchLine();
		if(in == cfg::config()->next){
			game::jogo()->next();
		}
		else if(in == cfg::config()->nextx10){
			FOR(i,9){
				usleep(100000);
				game::jogo()->next();
				clear();
				game::jogo()->print();
			}
			game::jogo()->next();
		}
		else if(in == cfg::config()->back){
			game::jogo()->back();
		}
		else if(in == cfg::config()->pauseKey){
			cfg::config()->speed *= -1;
		}
		else if(in == cfg::config()->speedUp){
			cfg::config()->speed = MIN(MAX_SPEED, ABS(cfg::config()->speed)+1);
		}
		else if(in == cfg::config()->speedUpx10){
			cfg::config()->speed = MIN(MAX_SPEED, ABS(cfg::config()->speed)+10);
		}
		else if(in == cfg::config()->speedDown){
			cfg::config()->speed = MAX(1, ABS(cfg::config()->speed)-1);
		}
		else if(in == cfg::config()->speedDownx10){
			cfg::config()->speed = MAX(1, ABS(cfg::config()->speed)-10);
		}
		else if(in == cfg::config()->move[0]){
			cfg::config()->moveCamera(0);
		}
		else if(in == cfg::config()->move[1]){
			cfg::config()->moveCamera(1);
		}
		else if(in == cfg::config()->move[2]){
			cfg::config()->moveCamera(2);
		}
		else if(in == cfg::config()->move[3]){
			cfg::config()->moveCamera(3);
		}
		else if(in == cfg::config()->moveCursor[0]){
			cfg::config()->moveCurs(0);
		}
		else if(in == cfg::config()->moveCursor[1]){
			cfg::config()->moveCurs(1);
		}
		else if(in == cfg::config()->moveCursor[2]){
			cfg::config()->moveCurs(2);
		}
		else if(in == cfg::config()->moveCursor[3]){
			cfg::config()->moveCurs(3);
		}
		else if(in == cfg::config()->optionKey){
			cfg::config()->pause();
			cfg::config()->optionScreen();
		}
	}
	clear();
	return 0;
}