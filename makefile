DEBUG=yes
VERBOSE=yes

#compilateur utilisé
CC=gcc

# SDL options
#CC_SDL= `pkg-config --cflags --libs sdl2`
#CC_SDL=`sdl2-config --cflags --libs`
#LIBS= `sdl2-config --libs` -L/usr/lib -lSDL2_ttf -lSDL2_image
#CFLAGS:=$(shell pkg-config --cflags sdl2 SDL2_image)

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings

BUILD_DIR := ./build
SRC_DIR := ./sources
HED_DIR := ./headers

ifeq ($(DEBUG), yes)
#options de compilation
	CFLAGS=-W -Wall -pedantic -g
#option editeur de lien
	LDFLAGS=
else
	CFLAGS=-W -Wall -ansi -pedantic
	LDFLAGS=
endif
#executables
EXEC=prog

#liste des fichiers sources
#SRC := main.c $($(SRC_DIR)/ wildcard *.c)
#SRC := $(wildcard */*.c) main.c
#SRC = main.c hello.c
SRC := $(wildcard *.c)

#liste des fichiers objets
#OBJ= main.o hello.o
#OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)
OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)

ec:
	@echo 'SRC = $(value SRC)'
	@echo 'OBJ = $(value OBJ)'

LIBS= -lm -lSDL2 -lSDL2_ttf

#all -> ensemble des executables a produire
all:$(EXEC)

ifeq ($(DEBUG), yes)
	@echo "Build in debug mode"
else
	@echo "Build in release mode"
endif

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE), yes)
    HIDE =  
else
    HIDE = @
endif

$(EXEC): $(OBJ)
	$(HIDE)$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

#@... parmet de ne pas afficher la ligne
#La variable $^ représente toutes les dépendances d'une règle
#$< Le nom de la première dépendance

#main.o sera reconstruit si hello.h est modifié
main.o: calcul.h

$(BUILD_DIR)/%.o: %.c
	$(HIDE)$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clear

#clear all file who can regenerate
clear:
	@echo "Cleaning up"
	$(HIDE)rm -rf $(BUILD_DIR)/*.o
	$(HIDE)rm -rf $(EXEC)