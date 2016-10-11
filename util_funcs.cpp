#include "gameoflife.h"

void clear(){
	system("clear || cls");
}

void changeFGcolor(int x){
	printf("\x1b[%dm",30+x);
}

void changeBGcolor(int x){
	printf("\x1b[%dm",40+x);
}

void resetColor(){
	printf("\x1b[0m");
}

void quit(){
	exit(0);
}

int readIntInRange(int a, int b){//le um inteiro entre a e b
	int x;
	if(a == b){//a até infinito
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

vector<string> getArqNames(string dir,string ext){
	ifstream arq;
	vector<string> s;
	string line,out = "ls " + dir + " > " + dir + "arqs.txt";
	system(out.c_str());
	arq.open(dir + "arqs.txt");
	if(arq.is_open()){
		while(getline(arq,line)){
			if(line.substr(line.size()-ext.size())==ext){
				s.push_back(line.substr(0,line.size()-ext.size()));
			}
		}
	}
	return s;
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

bool checkValidPatternName(string s){
	vector<string> v=getArqNames("./patterns/",".life");
	return find(v.begin(),v.end(),s)==v.end();
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

