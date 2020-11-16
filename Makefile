.PHONY:clean

INCDIR:=./include/
SRCDIR:=./source/
LIBS:=./libs/

SRC:=$(wildcard $(SRCDIR)*.cpp)
OBJ:=$(patsubst $(SRCDIR)%.cpp,$(SRCDIR)%.o,$(SRC))


CC:=g++
CFLAGS:= -g -w -std=c++11
LNK:= -L$(LIBS) -lmuduo_base -lmuduo_net -lpthread -ldl
TAG:=./bin/app

$(TAG):$(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LNK)  -o $@

$(OBJ):$(SRCDIR)%.o:$(SRCDIR)%.cpp
	$(CC) -c $(CFLAGS) -I$(INCDIR) $< -o $@ 

clean:
	@rm -rf $(SRCDIR)*.o $(TAG)
	@echo clean
