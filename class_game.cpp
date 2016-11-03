//NOTE: compiler needs -std=c++11
#include "./include/game.hpp"
#include "./include/util.hpp"
#include "./include/config.hpp"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

//INFO: static pointer to a game object must be declared here
game* game::pGame;

/**
 *  \brief Initalizate a default game environment
 *  
 *  Set default rule as Conway's one and creates a random board
 */
game::game(){
	int boardSizeX, boardSizeY;
	string survive="23", born="3";
	
	
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	boardSizeX=(w.ws_col-20)/2;
	boardSizeY=w.ws_row-12;
	
	rS=ruleStringToInt(survive);
	rB=ruleStringToInt(born);
	board = tab(boardSizeX,boardSizeY);
	prevBegin=0;
	prevEnd=0;
	randomize();
}

game::~game(){
	delete[] pGame;
	pGame=NULL;
}	

game* pJogo{
	if(!pGame)
		pGame = new game;
		
	return pGame;
}

/**
 *  \brief Converts a string to proper internal game rule format
 *  \return A valid rule format
 */
short int game::ruleStringToInt(string s){
	short int	x;
	
	x = 0;
	for(auto i:s){
		if(i<'0' || i>='9')
			continue;
			
		i-='0';
		x |= 1<<i;
	}
	
	return x;
}

/**
 *  \brief Replaces current cell world from a file
 *  \return False if the file cannot be opened or it is invalid. True if the board was loaded sucessfully.
 */
bool game::readArq(const string &arqName){
	string		line;
	char 		c;
	int 		boardSizeX, boardSizeY;
	ifstream	arq;

	
	printf("Reading file named \"%s\"\n", arqName.c_str());
	arq.open("./patterns/" + arqName + ".life");
	
	if (! arq.is_open()){
		fprintf(stderr, "Error in opening file \"%s\".\n", arqName.c_str());
		return false;
	}
	
	arq >> boardSizeX >> boardSizeY;
	if (boardSizeX < 0 || boardSizeY < 0){
		fprintf(stderr, "File parameters boardSizeX, boardSizeY are invalid.\n");
		return false;
	}
	board = tab(boardSizeX, boardSizeY);
	
	getline(arq,line);
	getline(arq,line);
	c = line[0];
	FOR(j,boardSizeY){
		getline(arq,line);
		FOR(i,boardSizeX){
			if(line[i]==c){
				board.v[i][j]=10;
				board.cont++;
			}
		}
	}
	
	arq.close();
	printf("Arquivo lido com sucesso.\n");
	
	//TODO: we can still make this faster using current logic
	FOR(i,10)prev[i]=board;
	usleep(20000);
	
	return true;
}

/**
 *  \brief Saves current cell world into a file
 *  \return False if the destination file cannot be opened. True if the board was saved sucessfully.
 */
bool game::saveArq(const string &arqName){
	ofstream	arq;
	
	
	printf("Saving to file named \"%s\"\n", arqName.c_str());
	arq.open("./patterns/" + arqName + ".life");
	
	if (! arq.is_open()){
		fprintf(stderr, "Erro ao ler arquivo \"%s\".\n", arqName.c_str());
		return false;
	}
	
	
	arq << board.lar << " " << board.alt << "\n#\n";
	FOR(j,board.alt){
		FOR(i,board.lar){
			if(board.v[i][j])arq << "#";
			else			 arq << "-";
		}
		arq << endl;
	}
	
	arq.close();
	printf("Arquivo salvo com sucesso.\n");
	usleep(20000);
	
	return true;
}

/**
 *  \brief Reads a .rule file
 *  \return False if the destination file cannot be opened. True if the rule was loaded sucessfully.
 */
bool game::readRule(const string& arqName){
	ifstream 	arq;
	string 		line;
	
	printf("Reading file named \"%s\"\n", arqName.c_str());
	arq.open("./rules/" + arqName + ".rule");
	if(! arq.is_open()){
		fprintf(stderr, "Erro ao ler arquivo \"%s\".\n", arqName.c_str());
		return false;
	}
	
	getline(arq,line);
	pJogo->rS = pJogo->ruleStringToInt(line);
	getline(arq,line);
	pJogo->rB = pJogo->ruleStringToInt(line);
	arq.close();
	printf("Arquivo lido com sucesso.\n");
	usleep(20000);
	
	return true;
}

/**
 *  \brief Checks if a cell is alive
 *  \return Bool indicating whether the cell is living or not
 */
bool game::isAlive(int x,int y){
	return board.v[x][y];
}

/**
 *  \brief Checks if a cell will survive based on it's neighbours
 *  \return Bool indicating whether the cell will survive or not
 */
bool game::willSurvive(int neigh){
	return rS & (1 << neigh);
}

/**
 *  \brief Checks if a cell will born based on it's neighbours
 *  \return Bool indicating whether the cell will born or not
 */
bool game::willBeBorn(int neigh){
	return rB & (1 << neigh);
}

/**
 *  \brief Calculates the next grid iteration
 */
void game::next(){
	tab nxt(board.lar,board.alt);
	FOR(i,board.lar){
		FOR(j,board.alt){
			int neigh=board.neigh(i,j);
			if((isAlive(i,j) && willSurvive(neigh)) || (!isAlive(i,j) && willBeBorn(neigh))){
			
				//TODO: maybe we can add a DEBUG feature that prints those information
				//if((isAlive(i,j) && willSurvive(i,j,neigh)))cout << i << " " << j << " alive and survive" << endl;
				//if((!isAlive(i,j) && willBeBorn(i,j,neigh)))cout << i << " " << j << " dead and born" << endl;
				//cout << "survive = " << rS << " born = " << rB << " neigh = " << neigh << endl;
				nxt.v[i][j]=neigh+1;
				nxt.cont++;
			}
		}
	}
	prev[prevEnd]=board;
	prevEnd = (prevEnd+1)%10;
	if(prevEnd==prevBegin)prevBegin = (prevBegin+1)%10;
	board = nxt;
}

/**
 *  \brief Rollback to previous iteration
 *  \return False if no previous state exists. True otherwise. 
 */
bool game::back(){
	if(prevBegin!=prevEnd){
		prevEnd=(prevEnd+9)%10;
		board=prev[prevEnd];
		
		return true;
	}
	
	return false;
}

/**
 *  \brief Handle every frame rendering of the game
 */
void game::print(){
	board.print();

	if(pConfig->editting){
		cout << "Move the cursor with ("
		<< keyToStr(pConfig->moveCursor[0]) << ","
		<< keyToStr(pConfig->moveCursor[1]) << ","
		<< keyToStr(pConfig->moveCursor[2]) << ","
		<< keyToStr(pConfig->moveCursor[3]) << ") and press ENTER to change the state of the selected Cell.\n\n\n\n\n\n";
		return;
	}
	cout << "Cells stay alive if they have (";
	int first=1;
	FOR(i,9){
		if(willSurvive(i)){
			if(!first)cout << ", ";
			first=0;
			cout << i;
		}
	}
	cout << ") neighbours" << endl;

	cout << "Cells die as if by under/overpopulation if they have (";
	first=1;
	FOR(i,9){
		if(!willSurvive(i)){
			if(!first)cout << ", ";
			first=0;
			cout << i;
		}
	}
	cout << ") neighbours" << endl;

	cout << "Cells are born if they have (";
	first=1;
	FOR(i,9){
		if(willBeBorn(i)){
			if(!first)cout << ", ";
			first=0;
			cout << i;
		}
	}
	cout << ") neighbours" << endl << endl;

	cout << "Speed " << ABS(pConfig->speed) << endl;
	if(pConfig->speed<0) cout << "Paused" << endl;
	else cout << endl;
}

/**
 *  \brief Generates an random cell world
 */
void game::randomize(){
	board.randomize();
}
