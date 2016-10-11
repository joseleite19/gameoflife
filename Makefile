CPP = g++

OBJS = gameoflife.cpp util_funcs.cpp class_config.cpp class_tab.cpp class_game.cpp class_optMenu.cpp class_menu_opt.cpp

FLAGS = -std=c++11 -Wall -Wno-unused-result -O2

TARGET = game

all:
	$(CPP) $(FLAGS) $(OBJS) -o $(TARGET)
