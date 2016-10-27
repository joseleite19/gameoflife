#ifndef GAME_HPP
#define GAME_HPP

#include "tab.hpp"

#include <string>

#define MAX_UNDO 11 //should be in config

class game{
	game();
	~game();
	public:
		static game* pGame;
		static game* jogo();

		tab 		board;		//TODO:calculate how much memory does this program uses in function of MAX_UNDO
		tab 		prev[MAX_UNDO];
		int 		prevBegin;	//contador usado para guardar a posição de inicio da 'fila' prev.
		int 		prevEnd;	//contador usado para guardar a posição de fim da 'fila' prev.
		void 		next();
		bool 		back();
		void 		print();
		void 		randomize();
		
		bool 		readArq(const std::string&);
		bool 		saveArq(const std::string&);
		bool 		readRule(const std::string&);
		
		short int	rS; /**< rule survive*/
		short int 	rB; /**< rule born*/
		
		bool 		isAlive			(int x,int y);
		bool 		willSurvive		(int neigh);
		bool 		willBeBorn		(int neigh);
	private:
		short int 	ruleStringToInt	(std::string); //WARNING: didn't understand yet
};

#endif