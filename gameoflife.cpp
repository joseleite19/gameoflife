#include "gameoflife.h"

#include "class_config.cpp"
#include "class_tab.cpp"
#include "class_game.cpp"



void clear(){

	system("clear || cls");
}

int readIntInRange(int a,int b){//le um inteiro entre a e b
	int x;
	if(a==b){//a até infinito
		while(1){
			x=a-1;
			scanf(" %d",&x);
			while(getchar()!='\n');
			if(x>=a)return x;
		}
	}
	if(a>b){//-infinito até b
		while(1){
			x=b+1;
			scanf(" %d",&x);
			while(getchar()!='\n');
			if(x<=b)return x;
		}
	}
	while(1){
		x=a-1;
		scanf(" %d",&x);
		while(getchar()!='\n');
		if(a<=x && x<=b)return x;
	}
}

vector<string> printArqNames(string dir,string ext){//imprime na tela todos os arquivos com extensão ext no diretório dir
	ifstream arq;
	vector<string> s;
	string line,out = "ls " + dir + " > " + dir + "arqs.txt";
	system(out.c_str());
	arq.open(dir + "arqs.txt");
	if(arq.is_open()){
		while(getline(arq,line)){
			if(line.substr(line.size()-ext.size())==ext){
				s.push_back(line.substr(0,line.size()-ext.size()));
				printf("%s\n",line.substr(0,line.size()-ext.size()).c_str());
			}
		}
	}
	return s;
}

bool canOpen(string arqName){//checa se é possivel abrir o arquivo
	ifstream arq;
	arq.open(arqName);
	if(arq.is_open()){
		arq.close();
		return true;
	}
	return false;
}

bool kbhit(){//checa se existe algo na entrada padrão
	struct termios oldt, newt;
	int ch, oldf;
	tcgetattr(STDIN_FILENO,&oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF){
		ungetc(ch,stdin);
		return true;
	}
	return false;
}

char getch(){//le um caracter da entrada padrão sem o bloqueio de entrada(nao necessita apertar enter)
	int ch;
	struct termios oldt;
	struct termios newt;
	tcgetattr(STDIN_FILENO,&oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

string getchAll(){//le um caracter da entrada padrão sem o bloqueio de entrada até a entrada estar vazia(nao necessita apertar enter)
	string s="";
	s+=getch();
	while(kbhit())s+=getch();
	return s;
}

string getchLine(){//le um caracter da entrada padrão sem o bloqueio de entrada até a entrada estar vazia ou até a quebra de linha(nao necessita apertar enter)
	char c;
	string s="";
	s+=getch();
	while(kbhit()){
		c=getch();
		if(c=='\n')break;
		s+=c;
	}
	return s;
}

int main(){
	srand(time(NULL));

	game::pGame=NULL;
	cfg::pCfg=NULL;

	string in;
	while(1){
		clear();
		game::jogo()->print();
		cout << "Speed " << ABS(cfg::config()->speed) << endl;
		if(cfg::config()->speed<0)cout << "Paused" << endl;
		else cout << endl;
		if(cfg::config()->speed>0){
			cfg::config()->sleep();
			if(!kbhit()){
				game::jogo()->next();
				continue;
			}
		}
		in = getchLine();
		if(in==cfg::config()->next){
			game::jogo()->next();
			continue;
		}
		else if(in==cfg::config()->nextx10){
			FOR(i,10)game::jogo()->next();
			continue;
		}
		else if(in==cfg::config()->pause){
			cfg::config()->speed*=-1;
			continue;
		}
		else if(in==cfg::config()->speedUp){
			cfg::config()->speed = MIN(MAX_SPEED,ABS(cfg::config()->speed)+1);
			continue;
		}
		else if(in==cfg::config()->speedUpx10){
			cfg::config()->speed = MIN(MAX_SPEED,ABS(cfg::config()->speed)+10);
			continue;
		}
		else if(in==cfg::config()->speedDown){
			cfg::config()->speed = MAX(1,ABS(cfg::config()->speed)-1);
			continue;
		}
		else if(in==cfg::config()->speedDownx10){
			cfg::config()->speed = MAX(1,ABS(cfg::config()->speed)-10);
			continue;
		}
		else if(in==cfg::config()->move[0]){
			cfg::config()->moveCamera(0);
			continue;
		}
		else if(in==cfg::config()->move[1]){
			cfg::config()->moveCamera(1);
			continue;
		}
		else if(in==cfg::config()->move[2]){
			cfg::config()->moveCamera(2);
			continue;
		}
		else if(in==cfg::config()->move[3]){
			cfg::config()->moveCamera(3);
			continue;
		}
		else if(in==cfg::config()->moveCursor[0]){
			cfg::config()->moveCurs(0);
			continue;
		}
		else if(in==cfg::config()->moveCursor[1]){
			cfg::config()->moveCurs(1);
			continue;
		}
		else if(in==cfg::config()->moveCursor[2]){
			cfg::config()->moveCurs(2);
			continue;
		}
		else if(in==cfg::config()->moveCursor[3]){
			cfg::config()->moveCurs(3);
			continue;
		}
		else if(in==cfg::config()->configKey){
			cfg::config()->configScreen();
			continue;
		}
	}
	clear();
	return 0;
}
