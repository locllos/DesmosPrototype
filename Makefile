MAIN_DIR = src
OBJ_DIR = bin
EXEC = g++
MAIN_FLAGS = -g3 -lSDL2_image -lSDL2_ttf `sdl2-config --cflags --libs`
OBJ_FLAGS = -c -g3
EXEC_NAME = desmosPrototype

main: $(OBJ_DIR)/display.o $(OBJ_DIR)/draw.o $(OBJ_DIR)/coordinate_system.o $(OBJ_DIR)/service.o
	$(EXEC) $(MAIN_DIR)/main.cpp $(OBJ_DIR)/display.o $(OBJ_DIR)/draw.o $(OBJ_DIR)/coordinate_system.o $(OBJ_DIR)/service.o $(MAIN_FLAGS) -o $(EXEC_NAME)

$(OBJ_DIR)/display.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/display.cpp -o $(OBJ_DIR)/display.o

$(OBJ_DIR)/draw.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/draw.cpp -o $(OBJ_DIR)/draw.o

$(OBJ_DIR)/coordinate_system.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/coordinate_system.cpp -o $(OBJ_DIR)/coordinate_system.o

$(OBJ_DIR)/service.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/service.cpp -o $(OBJ_DIR)/service.o


all: main clear
	echo -e "\033[0;32mSuccess!\033[0m"

clear:
	rm -r $(OBJ_DIR)/*.o