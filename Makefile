# Compilatore da dover usare 
CC = gcc

# Lista dei file sorgente
SRC = main.c function_sphere.c function_space.c

# Headers del progetto
HEADERS = function.h

# Opzioni di compilazione (aggiungi -Wall per warning, -g per debug)
# Indica la cartella degli include di MSYS2 MinGW64
CFLAGS = -Wall -I/mingw64/include

# Nome dell'eseguibile
TARGET = space_simulation

# Librerie Linux / Windows
# Aggiungo -L per indicare la cartella delle librerie di MSYS2 MinGW64
LIBS_LINUX = -lSDL2 -lGL -lGLEW -lm
LIBS_WINDOWS = -L/mingw64/lib -lmingw32 -lSDL2main -lSDL2 -lglew32 -lopengl32 -lm

# Rileva il sistema operativo
ifeq ($(OS),Windows_NT)
	LIBS = $(LIBS_WINDOWS)
	TARGET_EXT = .exe
	RM = del
else
	LIBS = $(LIBS_LINUX)
	TARGET_EXT =
	RM = rm -f
endif

# Regola predefinita
all: $(TARGET)$(TARGET_EXT)

# Regola per creare l'eseguibile
$(TARGET)$(TARGET_EXT): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET)$(TARGET_EXT) $(SRC) $(LIBS)

# Pulizia dei file generati
.PHONY: clean
clean:
	@echo "Pulizia dei file generati..."
	-$(RM) $(TARGET)$(TARGET_EXT)
