#include "gameoflife.hpp"


game* game::pGame;
game::game(){
	int l=62,a=29;
	string survive="23", born="3";

	rS=ruleStringToInt(survive);
	rB=ruleStringToInt(born);
	board = tab(l,a);
	randomize();
}
game::~game(){
	delete[] pGame;
	pGame=NULL;
}	
game* game::jogo(){
	if(!pGame)return pGame=new game;
	return pGame;
}
short int game::ruleStringToInt(string s){
	short int x=0;
	for(auto i:s){
		if(i<'0' || i>='9')continue;
		i-='0';
		x |= 1<<i;
	}
	return x;
}
void game::readArq(const string &arqName){
	printf("Reading file named \"%s\"\n",arqName.c_str());
	string line;
	char c;
	int lar,alt;
	ifstream arq;
	arq.open("./patterns/" + arqName + ".life");
	if(arq.is_open()){
		arq >> lar >> alt;
		board = tab(lar,alt);
		getline(arq,line);
		getline(arq,line);
		c = line[0];
		FOR(j,alt){
			getline(arq,line);
			FOR(i,lar){
				if(line[i]==c)board.v[i][j]=1;
			}
		}
		arq.close();
		printf("Arquivo lido com sucesso.\n");
		usleep(20000);
	}
	else printf("Erro ao ler arquivo...\n");
}
void game::saveArq(const string &arqName){
	printf("Saving to file named \"%s\"\n",arqName.c_str());
	ofstream arq;
	arq.open("./patterns/" + arqName + ".life");
	if(arq.is_open()){
		arq << board.lar << board.alt << "\n#\n";
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
	}
	else printf("Erro ao ler arquivo...\n");
}
bool game::isAlive(int x,int y){
	return board.v[x][y];
}
bool game::willSurvive(int x,int y,int neigh){
	return rS & (1 << neigh);
}
bool game::willBeBorn(int x,int y,int neigh){
	return rB & (1 << neigh);
}
void game::next(){
	tab nxt(board.lar,board.alt);
	FOR(i,board.lar){
		FOR(j,board.alt){
			int neigh=board.neigh(i,j);
			if((isAlive(i,j) && willSurvive(i,j,neigh)) || (!isAlive(i,j) && willBeBorn(i,j,neigh))){
				if((isAlive(i,j) && willSurvive(i,j,neigh)))cout << i << " " << j << " alive and survive" << endl;
				if((!isAlive(i,j) && willBeBorn(i,j,neigh)))cout << i << " " << j << " dead and born" << endl;
				//cout << "survive = " << rS << " born = " << rB << " neigh = " << neigh << endl;
				nxt.v[i][j]=neigh+1;
				nxt.cont++;
			}
		}
	}
	board = nxt;
};
void game::print(){
	board.print();
};
void game::randomize(){
	board.randomize();
};
