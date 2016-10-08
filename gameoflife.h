#include <bits/stdc++.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
using namespace std;




#define MAX_SPEED 1000


#define FOR(cont,max) for(int cont=0;cont<(int)max;cont++)
#define FOR2(cont,start,max) for(int cont=start;cont<(int)max;cont++)
#define CLEAR system("clear || cls")
#define MIN(x,y) (((x)<(y))?(x):( y))
#define MAX(x,y) (((x)>(y))?(x):( y))
#define ABS(x)   (((x)> 0 )?(x):-(x))

#define COLOR_BLACK    0
#define COLOR_RED      1
#define COLOR_GREEN    2
#define COLOR_YELLOW   3
#define COLOR_BLUE     4
#define COLOR_MAGENTA  5
#define COLOR_CYAN     6
#define COLOR_WHITE    7
#define COLOR_DEF      9
#define COLOR_BBLACK   60
#define COLOR_BRED     61
#define COLOR_BGREEN   62
#define COLOR_BYELLOW  63
#define COLOR_BBLUE    64
#define COLOR_BMAGENTA 65
#define COLOR_BCYAN    66
#define COLOR_BWHITE   67


#define KEY_ESC			"\x1b"
#define KEY_BCKSP		"\x1b["
#define KEY_UP			"\x1b[A"
#define KEY_LEFT		"\x1b[D"
#define KEY_DOWN		"\x1b[B"
#define KEY_RIGHT		"\x1b[C"
#define KEY_S_UP		"\x1b[1;2A"
#define KEY_S_LEFT		"\x1b[1;2D"
#define KEY_S_DOWN		"\x1b[1;2B"
#define KEY_S_RIGHT		"\x1b[1;2C"
#define KEY_DEL			"\x1b[3~"
#define KEY_INSERT		"\x1b[2~"
#define KEY_HOME		"\x1bOH"
#define KEY_PAGE_UP		"\x1b[5~"
#define KEY_PAGE_DOWN	"\x1b[6~"
#define KEY_END			"\x1bOF"
#define KEY_F1			"\x1bOQ"
#define KEY_F2			"\x1bOQ"
#define KEY_F3			"\x1bOR"
#define KEY_F4			"\x1bOS"
#define KEY_F5			"\x1b[15~"
#define KEY_F6			"\x1b[17~"
#define KEY_F7			"\x1b[18~"
#define KEY_F8			"\x1b[19~"
#define KEY_F9			"\x1b[20~"
#define KEY_F10			"\x1b[21~"
#define KEY_F11			"\x1b[21~"
#define KEY_F12			"\x1b[24~"
