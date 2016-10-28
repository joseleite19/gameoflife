#include "gameoflife.hpp"


tab::tab():lar{-1},alt{-1},cont{-1},v{NULL}{}
tab::tab(int l,int a):lar{l},alt{a},cont{0}{
	allocBoard();
}
tab::~tab(){
	deallocBoard();
}
void tab::allocBoard(){
	v=new char*[lar];
	FOR(i,lar){
		v[i]=new char[alt];
		memset(v[i],0,alt*sizeof(char));
	}
}
void tab::deallocBoard(){
	FOR(i,lar)delete[] v[i];
	delete[] v;
}
void tab::operator=(const tab &other){
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
bool tab::operator==(const tab &other)const{
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
int tab::neigh(int x,int y){
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
void tab::print(){
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	int scrLar=w.ws_col;
	int scrAlt=w.ws_row;
	FOR(i,(scrAlt-cfg::config()->screenAlt-2)/2)printf("\n");
	FOR(i,(scrLar-cfg::config()->screenLar-2)/2)printf(" ");
	changeBGcolor(COLOR_YELLOW);
	printf("┌");
	FOR(i,cfg::config()->screenLar/2)printf("──");
	printf("┐");
	resetColor();
	printf("\n");
	FOR(j, MIN(cfg::config()->screenAlt,scrAlt-12)){
		FOR(i,(scrLar-cfg::config()->screenLar-2)/2)printf(" ");
		changeBGcolor(COLOR_YELLOW);
		printf("│");
		resetColor();
		FOR(i,MIN(cfg::config()->screenLar/2,scrLar-20)){
			int xx=(cfg::config()->curX+i)%lar;
			int yy=(cfg::config()->curY+j)%alt;
			if     (!xx && yy==alt-1)changeBGcolor(COLOR_BRED);
			else if(!xx || yy==alt-1)changeBGcolor(COLOR_BBLUE);
			else					 changeBGcolor(COLOR_GREEN);
			changeFGcolor(cfg::config()->color[(int)(v[xx][yy])%10]);
			if(xx == cfg::config()->cursorX && yy == cfg::config()->cursorY) invBGcolor();
			if(v[xx][yy]==10)	printf("# ");
			else if(v[xx][yy])	printf("%d ",v[xx][yy]);
			else       			printf(". ");
			resetColor();
		}
		changeBGcolor(COLOR_YELLOW);
		printf("│");
		resetColor();
		printf("\n");
	}
	FOR(i,(scrLar-cfg::config()->screenLar-2)/2)printf(" ");
	changeBGcolor(COLOR_YELLOW);
	printf("└");
	FOR(i,cfg::config()->screenLar/2)printf("──");
	printf("┘");
	resetColor();
	printf("\n\n");
	FOR(i,(scrAlt-cfg::config()->screenAlt-10)/2)printf("\n");
};
void tab::randomize(){
	cont=0;
	FOR(j,alt){
		FOR(i,lar){
			v[i][j]=(rand()%2)*10;
			cont+=(v[i][j])/10;
		}
	}
};
void tab::invert(){
	int x = cfg::config()->cursorX;
	int y = cfg::config()->cursorY;
	if(v[x][y] == 0){
		v[x][y] = 10;
		cont++;
	}
	else{
		v[x][y] = 0;
		cont--;
	}
};
