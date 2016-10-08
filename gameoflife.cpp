#include "gameoflife.h"


struct config_{
	int speed;
	int curX,curY;
	int cursorX,cursorY;
	int screenLar,screenAlt;
	int color[10];
	string dead,alive;
	string move[4],moveCursor[4];
	string next,pause,speedUp,speedDown;
	string nextx10,speedUpx10,speedDownx10;
	string configKey;
	config_(string);
	void defConfig();
	bool load(string);
	void save();
	void configScreen();
	void sleep();
	void moveCamera(int);
	void moveCurs(int);
};

config_ config("");

struct tab{
	int lar,alt,cont;
	char** v;
	tab():lar{-1},alt{-1},cont{-1},v{NULL}{}
	tab(int l,int a):lar{l},alt{a},cont{0}{
		allocBoard();
	}
	~tab(){
		deallocBoard();
	}
	void allocBoard(){
		v=new char*[lar];
		FOR(i,lar){
			v[i]=new char[alt];
			memset(v[i],0,alt*sizeof(char));
		}
	}
	void deallocBoard(){
		FOR(i,lar)delete[] v[i];
		delete[] v;
	}
	void operator=(const tab &other){
		if(lar!=other.lar || alt!=other.alt){
			deallocBoard();
			alt=other.alt;
			lar=other.lar;
			allocBoard();
		}
		FOR(j,alt){
			FOR(i,lar){
				v[i][j] = other.v[i][j];
			}
		}
		cont = other.cont;
	}
	bool operator==(const tab &other)const{
		if(cont!=other.cont)return false;
		if(lar!=other.lar)return false;
		if(alt!=other.alt)return false;
		FOR(j,alt){
			FOR(i,lar){
				if(v[i][j]!=other.v[i][j])return false;
			}
		}
		return true;
	}
	int neigh(int x,int y){
		int cnt=0;
		FOR2(i,-1,2){
			FOR2(j,-1,2){
				if(!i && !j)continue;
				int xx=(x+i)%lar, yy=(y+j)%alt;
				if(xx<0)xx+=lar;
				if(yy<0)yy+=alt;
				if(v[xx][yy])cnt++;
			}
		}
		return cnt;
	};
	void print(){
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);
		int scrLar=w.ws_col;
		int scrAlt=w.ws_row;
		FOR(i,(scrAlt-config.screenAlt-2)/2)printf("\n");
		FOR(i,(scrLar-config.screenLar-2)/2)printf(" ");
		printf("┌");
		FOR(i,config.screenLar/2)printf("──");
		printf("┐\n");
		FOR(j,config.screenAlt){
			FOR(i,(scrLar-config.screenLar-2)/2)printf(" ");
			printf("│");
			FOR(i,config.screenLar/2){
				int xx=(config.curX+i)%lar;
				int yy=(config.curY+j)%alt;
				if     (!xx && yy==alt-1)printf("\x1b[%dm",40+COLOR_BRED);
				else if(!xx || yy==alt-1)printf("\x1b[%dm",40+COLOR_BBLUE);
				printf("\x1b[%dm",30+config.color[(int)(v[xx][yy])%10]);
				if(v[xx][yy])printf("%d ",v[xx][yy]);
				else       printf(". ");
				printf("\x1b[0m");
			}
			printf("│\n");
		}
		FOR(i,(scrLar-config.screenLar-2)/2)printf(" ");
		printf("└");
		FOR(i,config.screenLar/2)printf("──");
		printf("┘\n");
		printf("\n");
		FOR(i,(scrAlt-config.screenAlt-2)/2)printf("\n");
	};
	void randomize(){
		cont=0;
		FOR(j,alt){
			FOR(i,lar){
				v[i][j]=rand()%2;
				cont+=v[i][j];
			}
		}
	};
};

struct game{
	short int rS,rB;
	tab board;
	game(string arq="-",int l=62,int a=29,string survive="23",string born="2"){
		rS=ruleStringToInt(survive);
		rB=ruleStringToInt(born);
		if(arq=="-"){
			board = tab(l,a);
			randomize();
		}
		else{
			readArq(arq);
		}
	}
	short int ruleStringToInt(string s){
		short int x=0;
		for(auto i:s){
			if(i<'0' || i>='9')continue;
			i-='0';
			x |= 1<<i;
		}
		return x;
	}
	void readArq(const string &arqName){
		printf("Reading arquive named \"%s\"\n",arqName.c_str());
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
	bool isAlive(int x,int y){
		return board.v[x][y];
	}
	bool willSurvive(int x,int y,int neigh){
		return rS & (1 << neigh);
	}
	bool willBeBorn(int x,int y,int neigh){
		return rB & (1 << neigh);
	}
	void next(){
		tab nxt(board.lar,board.alt);
		FOR(i,board.lar){
			FOR(j,board.alt){
				int neigh=board.neigh(i,j);
				if((isAlive(i,j) && willSurvive(i,j,neigh)) || willBeBorn(i,j,neigh)){
					nxt.v[i][j]=neigh+1;
					nxt.cont++;
				}
			}
		}
		board = nxt;
	};
	void print(){
		board.print();
	};
	void randomize(){
		board.randomize();
	};
};

game jogo;

config_::config_(string arq=""){
	if(arq!="" && load(arq));
	else defConfig();
}
void config_::defConfig(){
	speed			= -100;
	curX			= 0;
	cursorX			= 0;
	curY			= 0;
	cursorY			= 0;
	dead			= ".";
	alive			= "#";
	pause			= " ";
	configKey		= KEY_ESC;
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
bool config_::load(string arqName){return false;}//TODO load configs from file
void config_::save(){}//TODO save configs in file
void config_::configScreen(){}//TODO screen to change configs
void config_::sleep(){//TODO change this to scale the time with speed
	usleep(10000000/(config.speed));
}
void config_::moveCamera(int dir){
	if(dir==0)curY=((curY-1)+jogo.board.alt)%jogo.board.alt;
	if(dir==1)curX=((curX-1)+jogo.board.lar)%jogo.board.lar;
	if(dir==2)curY=(curY+1)%jogo.board.alt;
	if(dir==3)curX=(curX+1)%jogo.board.lar;
}
void config_::moveCurs(int dir){
	if(dir==0)cursorY=((cursorY-1)+jogo.board.alt)%jogo.board.alt;
	if(dir==1)cursorX=((cursorX-1)+jogo.board.lar)%jogo.board.lar;
	if(dir==2)cursorY=(cursorY+1)%jogo.board.alt;
	if(dir==3)cursorX=(cursorX+1)%jogo.board.lar;
}

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
	string in;
	while(1){
		clear();
		jogo.print();
		cout << "Speed " << ABS(config.speed) << endl;
		if(config.speed<0)cout << "Paused" << endl;
		else cout << endl;
		if(config.speed>0){
			config.sleep();
			if(!kbhit()){
				jogo.next();
				continue;
			}
		}
		in = getchLine();
		if(in==config.next){
			jogo.next();
			continue;
		}
		else if(in==config.nextx10){
			FOR(i,10)jogo.next();
			continue;
		}
		else if(in==config.pause){
			config.speed*=-1;
			continue;
		}
		else if(in==config.speedUp){
			config.speed = MIN(MAX_SPEED,ABS(config.speed)+1);
			continue;
		}
		else if(in==config.speedUpx10){
			config.speed = MIN(MAX_SPEED,ABS(config.speed)+10);
			continue;
		}
		else if(in==config.speedDown){
			config.speed = MAX(1,ABS(config.speed)-1);
			continue;
		}
		else if(in==config.speedDownx10){
			config.speed = MAX(1,ABS(config.speed)-10);
			continue;
		}
		else if(in==config.move[0]){
			config.moveCamera(0);
			continue;
		}
		else if(in==config.move[1]){
			config.moveCamera(1);
			continue;
		}
		else if(in==config.move[2]){
			config.moveCamera(2);
			continue;
		}
		else if(in==config.move[3]){
			config.moveCamera(3);
			continue;
		}
		else if(in==config.moveCursor[0]){
			config.moveCurs(0);
			continue;
		}
		else if(in==config.moveCursor[1]){
			config.moveCurs(1);
			continue;
		}
		else if(in==config.moveCursor[2]){
			config.moveCurs(2);
			continue;
		}
		else if(in==config.moveCursor[3]){
			config.moveCurs(3);
			continue;
		}
		else if(in==config.configKey){
			config.configScreen();
			continue;
		}
	}
	clear();
	return 0;
}
