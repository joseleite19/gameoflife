#include "gameoflife.hpp"


game* game::pGame;
game::game(){
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	int l=(w.ws_col-20)/2;
	int a=w.ws_row-12;
	string survive="23", born="3";

	rS=ruleStringToInt(survive);
	rB=ruleStringToInt(born);
	board = tab(l,a);
	prevBegin=0;
	prevEnd=0;
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
				if(line[i]==c){
					board.v[i][j]=10;
					board.cont++;
				}
			}
		}
		arq.close();
		printf("Arquivo lido com sucesso.\n");
		FOR(i,10)prev[i]=board;
		usleep(20000);
	}
	else printf("Erro ao ler arquivo...\n");
}
void game::saveArq(const string &arqName){
	printf("Saving to file named \"%s\"\n",arqName.c_str());
	ofstream arq;
	arq.open("./patterns/" + arqName + ".life");
	if(arq.is_open()){
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
	}
	else printf("Erro ao ler arquivo...\n");
}
void game::readRule(const string& arqName){
	printf("Reading file named \"%s\"\n",arqName.c_str());
	string line;
	ifstream arq;
	arq.open("./rules/" + arqName + ".rule");
	if(arq.is_open()){
		getline(arq,line);
		game::jogo()->rS = game::jogo()->ruleStringToInt(line);
		getline(arq,line);
		game::jogo()->rB = game::jogo()->ruleStringToInt(line);
		arq.close();
		printf("Arquivo lido com sucesso.\n");
		usleep(20000);
	}
	else printf("Erro ao ler arquivo...\n");
}
bool game::isAlive(int x,int y){
	return board.v[x][y];
}
bool game::willSurvive(int neigh){
	return rS & (1 << neigh);
}
bool game::willBeBorn(int neigh){
	return rB & (1 << neigh);
}
void game::next(){
	tab nxt(board.lar,board.alt);
	FOR(i,board.lar){
		FOR(j,board.alt){
			int neigh=board.neigh(i,j);
			if((isAlive(i,j) && willSurvive(neigh)) || (!isAlive(i,j) && willBeBorn(neigh))){
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
};
void game::back(){
	if(prevBegin!=prevEnd){
		prevEnd=(prevEnd+9)%10;
		board=prev[prevEnd];
	}
}
void game::print(){
	board.print();

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

	cout << "Speed " << ABS(cfg::config()->speed) << endl;
	if(cfg::config()->speed<0) cout << "Paused" << endl;
	else cout << endl;
};
void game::randomize(){
	board.randomize();
};
