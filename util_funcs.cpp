#include "gameoflife.hpp"

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

void readArq(const string& s){
	game::jogo()->readArq(s);
}

void saveArq(const string& s){
	game::jogo()->saveArq(s);
}

void readRule(const string& s){
	game::jogo()->readRule(s);
}

void openConfigScreen(){
	cfg::config()->configScreen();
}

void openOptionScreen(){
	cfg::config()->optionScreen();
}

void randomize(){
	game::jogo()->randomize();
}

string keyToStr(string key){
	for(auto i:key_str){
		if(key==i.first)return i.second;
	}
	return key;
}

void printConfig () {
	CLEAR;
	printf( "      ╔══════╗        				      ╔══════╗        \n"
			"      ║¹     ║        				      ║⁵     ║        \n"
			"      ║   ");
	cout << cfg::config()->move[0];
	printf( "  ║        				      ║   ");
	cout << cfg::config()->moveCursor[0];
	printf( "  ║        \n"
			"      ║      ║        				      ║      ║        \n"
			"╔═════╩╦═════╩╦══════╗				╔═════╩╦═════╩╦══════╗\n"
			"║²     ║³     ║⁴     ║				║⁶     ║⁷     ║⁸     ║\n"
			"║   ");
	cout << cfg::config()->move[1];
	printf( "  ║   ");cout << cfg::config()->move[2];
	printf( "  ║   ");cout << cfg::config()->move[3];
	printf( "  ║				║   ");cout << cfg::config()->moveCursor[1];
	printf( "  ║   ");cout << cfg::config()->moveCursor[2];
	printf( "  ║   ");cout << cfg::config()->moveCursor[3];
	printf( "  ║\n"
			"║      ║      ║      ║				║      ║      ║      ║\n"
			"╚══════╩══════╩══════╝				╚══════╩══════╩══════╝\n");
}

void changeConfig () {
	string in;
	while (true) {
		printConfig ();
		cout << endl << "Press [ESC] to go back";
		cout << endl << "To change configurations type the corresponding number key: ";
		in = getchLine();
		if (in == KEY_ESC) break;

		const char * foo = in.c_str ();

		switch (*foo) {
			case '1': cfg::config()->move[0]       = getch (); break;
			case '2': cfg::config()->move[1]       = getch (); break;
			case '3': cfg::config()->move[2]       = getch (); break;
			case '4': cfg::config()->move[3]       = getch (); break;
			case '5': cfg::config()->moveCursor[0] = getch (); break;
			case '6': cfg::config()->moveCursor[1] = getch (); break;
			case '7': cfg::config()->moveCursor[2] = getch (); break;
			case '8': cfg::config()->moveCursor[3] = getch (); break;
		}

	}
}

void printBG () {
	CLEAR;
	for (int i = 0; i < 10; i++) {
		cout << "With colour " << i << " the ";
		changeBGcolor (i);
		cout << "Background will look like this\n";
		changeBGcolor (COLOR_DEF);
	}

	for (int i = 60; i < 68; i++) {
		cout << "With colour " << i-50 << " the ";
		changeBGcolor (i);
		cout << "Background will look like this\n";
		changeBGcolor (COLOR_DEF);
	}
}

void changeBackGround () {
	string in;
	while (true) {
		printBG ();
		cout << "\n\n\tType the number of the colour of your choice: ";
		in = getchLine();

		if (in == KEY_ESC) break;
		
		int c;
		do {
			scanf ("%d", &c); getchar ();
		} while (c < 0 || c > 17);

		//QUAL A VARIÁVEL QUE MUDA A COR DO FUNDO????????????????

	}
}

void printFG () {
	CLEAR;

	cout << "\n\n\tAlived cell: \"" << cfg::config()->alive << "\"";
	cout << "\t\t\tDead cell: \"" << cfg::config()->dead << "\"\n\n";
	
	for (int i = 0; i < 10; i++) {
		cout << "\tWith colour " << i << " the ";
		changeFGcolor (i);
		cout << "Cells will look like this\n";
		changeFGcolor (COLOR_DEF);
	}

	for (int i = 60; i < 68; i++) {
		cout << "\tWith colour " << i-50 << " the ";
		changeFGcolor (i);
		cout << "Cells will look like this\n";
		changeFGcolor (COLOR_DEF);
	}
}

void changeCellColour () {
	string in;
	while (true) {
		printFG ();
		cout << "\n\n\tType the number of the colour of your choice: ";
		in = getchLine();

		if (in == KEY_ESC) break;

		int c;
		do {
			scanf ("%d", &c); getchar ();
		} while (c < 0 || c > 17);

		//QUAL A VARIÁVEL QUE MUDA A COR DA CÉLULA????????????????


	}
}

void changeGraphs () {
	optMenu graphMenu;
	string in;

	function<void()> func1;
	function<void()> func2;
	func1 = changeBackGround;
	graphMenu.add_button ("Change background colour", func1);
	func2 = changeCellColour;
	graphMenu.add_button ("Change cell colour", func2);

	while (true) {
		CLEAR;
		graphMenu.print ();
		in = getchLine ();
		if(in==KEY_UP)graphMenu.selected=MAX(0,graphMenu.selected-1);
		else if(in==KEY_DOWN)graphMenu.selected=MIN(graphMenu.size()-1,graphMenu.selected+1);
		else if(in==KEY_ESC)break;
		else if(in=="\n")graphMenu.click();

	}

}