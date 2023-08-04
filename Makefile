# Constantes recebendo os diretórios dos arquivos do projeto.
APPS = ./apps
BIN = ./bin
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SRC = ./src

# Constantes recebendo os diretórios dos arquivos do pacote OpenGL para MinGW.
MINGW_INCLUDE = "C:\Program Files\mingw64\x86_64-w64-mingw32\include"
MINGW_LIB = "C:\Program Files\mingw64\x86_64-w64-mingw32\lib"

# Constantes utilizadas para simplificar o código do programa.
FLAGS = -o3 -Wall
OPENGL_FLAGS = -lopengl32 -lglu32 -lfreeglut -Wl,--subsystem,windows
HEADERS = -I $(INCLUDE) -I $(MINGW_INCLUDE)
LIBS = -l snake -L $(LIB) -L $(MINGW_LIB)

# 1: Dependências de diretivas na target "all:".
#	 "all:" é chamada toda vez que o arquivo "Makefile" for executado.
#	 Em seguida, "all:" irá chamar as targets "lib:" e "myapps:", em ordem de inserção.
all: lib myapps

# 2: Dependências de diretivas na target "lib:".
#	 "lib:" é chamada logo após "all:" iniciar sua execução.
#	 Logo, "lib:" irá chamar a target "$(OBJ)/%.o", através do respectivo arquivo "$(OBJ)/nome_arquivo.o".
lib: $(OBJ)/snake.o \
	 $(OBJ)/fila.o
	ar -rcs $(LIB)/libsnake.a $(OBJ)/*.o

# 3: Dependências de diretivas na target "myapps:".
#	 "myapps:" é chamada após "lib:" finalizar sua execução.
#	 Logo, "myapps:" irá chamar a target "$(BIN)/%", através do respectivo arquivo "$(BIN)/main".
myapps: clean_apps \
	$(BIN)/main

# Target genérica para compilação dos Tipos Abstratos de Dados.
$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

# Target genérica para compilação do programa.
$(BIN)/%: $(APPS)/%.c $(OBJ)/*.o
	gcc -c -o $(OBJ)/main.o $< $(HEADERS)
	gcc $(FLAGS) $< $(LIBS) -I $(INCLUDE) -o $@ $(OPENGL_FLAGS)

# 4: Executa a aplicação.
run:
	$(BIN)/main

# 5: Deleta todos os arquivos dos respectivos diretórios: "./bin", "./lib" e "./obj".
clean:
	rm -rf $(BIN)/* $(LIB)/* $(OBJ)/*

# 6: Target utilizada por "myapps" para recompilação do programa.
clean_apps:
	rm -rf $(BIN)/*
