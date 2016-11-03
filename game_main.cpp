#include "./include/game.hpp"
#include "./include/config.hpp"
#include "./include/util.hpp"

#include <stdlib.h> //WARNING: couldn't find which header does srand belongs to in old gameoflife.hpp
#include <unistd.h>

#define MAX_SPEED 1000

using namespace std;

int main(){
	srand(time(NULL));

	string in;
	while(1){
		clear();
		pJogo->print();
		if(pConfig->editting){
			in = getchLine();
			if(in == pConfig->moveCursor[0])		pConfig->moveCurs(0);
			else if(in == pConfig->moveCursor[1])	pConfig->moveCurs(1);
			else if(in == pConfig->moveCursor[2])	pConfig->moveCurs(2);
			else if(in == pConfig->moveCursor[3])	pConfig->moveCurs(3);
			else if(in == "\n")						pJogo->board.invert();
			else if(in == pConfig->optionKey)		pConfig->optionScreen();
			continue;
		}
		if(pConfig->speed>=0){
			pConfig->sleep();
			if(!kbhit()){
				pJogo->next();
				continue;
			}
		}

		in = getchLine();
		if(in == pConfig->next){
			pJogo->next();
		}
		else if(in == pConfig->nextx10){
			FOR(i,9){
				usleep(100000);
				pJogo->next();
				clear();
				pJogo->print();
			}
			pJogo->next();
		}
		else if(in == pConfig->back){
			pJogo->back();
		}
		else if(in == pConfig->pauseKey){
			pConfig->speed *= -1;
		}
		else if(in == pConfig->speedUp){
			pConfig->speed = MIN(MAX_SPEED, ABS(pConfig->speed)+1);
		}
		else if(in == pConfig->speedUpx10){
			pConfig->speed = MIN(MAX_SPEED, ABS(pConfig->speed)+10);
		}
		else if(in == pConfig->speedDown){
			pConfig->speed = MAX(1, ABS(pConfig->speed)-1);
		}
		else if(in == pConfig->speedDownx10){
			pConfig->speed = MAX(1, ABS(pConfig->speed)-10);
		}
		else if(in == pConfig->move[0]){
			pConfig->moveCamera(0);
		}
		else if(in == pConfig->move[1]){
			pConfig->moveCamera(1);
		}
		else if(in == pConfig->move[2]){
			pConfig->moveCamera(2);
		}
		else if(in == pConfig->move[3]){
			pConfig->moveCamera(3);
		}
		else if(in == pConfig->optionKey){
			pConfig->pause();
			pConfig->optionScreen();
		}
	}
	clear();
	return 0;
}
