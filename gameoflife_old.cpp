#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;


struct board_{
	int lar,alt,cont;
	char** v;
	board_():lar{-1},alt{-1},cont{-1},v{NULL}{}
	board_(int l,int a):lar{l},alt{a},cont{0}{
		allocBoard();
	}
	~board_(){
		deallocBoard();
	}
	void allocBoard(){
		v=new char*[lar];
		for(int i=0;i<lar;i++){
			v[i]=new char[alt];
			memset(v[i],0,alt*sizeof(char));
		}
	}
	void deallocBoard(){
		for(int i=0;i<lar;i++)delete[] v[i];
		delete[] v;
	}
	void operator=(const board_ &other){
		if(lar!=other.lar || alt!=other.alt){
			deallocBoard();
			alt=other.alt;
			lar=other.lar;
			allocBoard();
		}
		for(int j=0;j<alt;j++){
			for(int i=0;i<lar;i++){
				v[i][j] = other.v[i][j];
			}
		}
		cont = other.cont;
	}
	bool operator==(const board_ &other)const{
		if(cont!=other.cont)return false;
		if(lar!=other.lar)return false;
		if(alt!=other.alt)return false;
		for(int j=0;j<alt;j++){
			for(int i=0;i<lar;i++){
				if(v[i][j]!=other.v[i][j])return false;
			}
		}
		return true;
	}
	int neigh(int x,int y){
		int cnt=0;
		//cout<<"aaaa"<<endl;
		for(int i=-1;i<2;i++){
			for(int j=-1;j<2;j++){
				if(!i && !j)continue;
				int xx=(x+i)%lar, yy=(y+j)%alt;
				if(xx<0)xx+=lar;
				if(yy<0)yy+=alt;
				if(v[xx][yy])cnt++;
			}
		}
		//cout<<"aaaaaaa"<<endl;
		return cnt;
	};
	void print(){
		printf("\n\n");
		for(int j=0;j<alt;j++){
			for(int i=0;i<lar;i++){
				printf("\x1b[%dm",((7*v[i][j])%9)+30);
				if(v[i][j])printf("%d ",v[i][j]);
				else       printf(". ");
			}
			printf("\x1b[0m\n");
		}
		printf("\n");
	};
	void randomize(){
		cont=0;
		for(int j=0;j<alt;j++){
			for(int i=0;i<lar;i++){
				v[i][j]=rand()%2;
				cont+=v[i][j];
			}
		}
	};
};

struct tab{
	short int rS,rB;
	board_ board;
	tab(string arq,int l,int a,string survive,string born){
		//cout << "aaa" << endl;
		rS=ruleStringToInt(survive);
		//cout << "aaa" << endl;
		rB=ruleStringToInt(born);
		//cout << "aaa" << endl;
		if(arq=="-"){
			board = board_(l,a);
		//cout << "aaaa" << endl;
			randomize();
		}
		else{
		//cout << "aaaaa" << endl;
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
		//cout << "bbb" << endl;
		char c;
		int lar,alt;
		ifstream arq;
		arq.open("./patterns/" + arqName + ".life");
		//cout << "bbb1" << endl;
		if(arq.is_open()){
		//cout << "bbb2" << endl;
			arq >> lar >> alt;
		//cout << "bbb3" << endl;
			board = board_(lar,alt);
		//cout << "bbb4" << endl;
			getline(arq,line);
			getline(arq,line);
			c = line[0];
		//cout << "bbb5" << endl << line << endl;
			for(int j=0;j<alt;j++){
				getline(arq,line);
				for(int i=0;i<lar;i++){
					if(line[i]==c)board.v[i][j]=1;
				}
			}
		//cout << "bbb" << endl;
			arq.close();
			printf("Arquivo lido com sucesso.\n");
			usleep(20000);
		}
		else printf("Erro ao ler arquivo...\n");
	}

	void next(){
		board_ nxt(board.lar,board.alt);
		for(int i=0;i<board.lar;i++){
			for(int j=0;j<board.alt;j++){
				int neigh=board.neigh(i,j);
				//cout << "neigh " << neigh << " x " << i << " y " << j << endl;
				if(board.v[i][j]){
					if(rS & (1 << neigh)){
						nxt.v[i][j]=neigh+1;
						nxt.cont++;
					}
				}
				else{
					if(rB & (1 << neigh)){
						nxt.v[i][j]=neigh+1;
						nxt.cont++;
					}
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

int readIntInRange(int a,int b){
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

vector<string> printArqNames(string dir,string ext){
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

bool canOpen(string arqName){
	ifstream arq;
	arq.open(arqName);
	if(arq.is_open()){
		arq.close();
		return true;
	}
	return false;
}

int main(){
	srand(time(NULL));
	while(1){
		int x=-1,lar=-1,alt=-1;
		string ruleS,ruleB,arqName;
		system("clear");
		printf("Selecione a regra que deseja usar.\n");
		vector<string> s = printArqNames("./rules/",".rule");
		printf("%d - Regra custom\n",(int)s.size()+1);
		printf("0 - Sair\n");
		x=readIntInRange(0,s.size()+1);
		if(!x)break;
		else if(x==(int)s.size()+1){
			system("clear");
			printf("Escreva a regra de sobrevivência de células no formato \"046\"(sem aspas) com 0, 4 e 6 sendo os números de vizinhos com os quais as células sobrevivem.\n");
			cin >> ruleS;getchar();
			printf("Escreva a regra de nascimento de células no formato \"046\"(sem aspas) com 0, 4 e 6 sendo os números de vizinhos com os quais as células nascem.\n");
			cin >> ruleB;getchar();
		}
		else{
			x--;
			ifstream arq;
			arq.open("./rules/" + s[x] + ".rule");
			if(arq.is_open()){
				getline(arq,ruleS);
				getline(arq,ruleB);
			}
		}
		while(1){
			system("clear");
			printf("Digite o nome do arquivo de entrada ou '-' para usar entrada aleatoria.\n");
			printArqNames("./patterns/",".life");
			cin >> arqName;while(getchar()!='\n');
			if(arqName=="-"){
				printf("Digite as dimensões do tabuleiro:\n");
				printf("-> Largura(5-60)-> \n");
				lar = readIntInRange(5,60);
				printf("-> Altura(5-35)-> \n");
				alt = readIntInRange(5,35);
				break;
			}
			else{
				if(canOpen("./patterns/" + arqName + ".life"))break;
				else{
					printf("Erro ao ler arquivo.\n");
					getchar();
				}
			}
		}
		system("clear");
		tab tabuleiro(arqName,lar,alt,ruleS,ruleB);
		tabuleiro.print();
		getchar();
		board_ prev(tabuleiro.board.lar,tabuleiro.board.alt);
		board_ prev2(tabuleiro.board.lar,tabuleiro.board.alt);
		for(int i=0;i<100000;i++){
			prev2= prev;
			prev = tabuleiro.board;
			tabuleiro.next();
			system("clear");
			tabuleiro.print();
			if(!(tabuleiro.board.cont) || (prev==tabuleiro.board)){
				printf("\n\nPadrão estável.\n");
				getchar();
				break;
			}
			if((prev2==tabuleiro.board)){
				printf("\n\nPadrão em loop.\n");
				getchar();
				break;
			}
			usleep(100000);
		}
	}
	system("clear");
	return 0;
}
