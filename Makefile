CPP = g++

OBJS = game_main.cpp class_util.cpp class_config.cpp class_tab.cpp class_game.cpp class_optMenu.cpp class_menu_opt.cpp

#flag -Wno-unused-result is used to ignore warning related to forgetting to check the value retured by printf and scanf
#removed flag: -Wall
FLAGS = -std=c++11 -O2 -Wno-unused-result

TARGET = ./bin/game

all:
	$(CPP) $(FLAGS) $(OBJS) -o $(TARGET)