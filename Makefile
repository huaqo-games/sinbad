COMPILER = gcc

# COMPILER FLAGS
C_FLAG_STD_C99             = -std=c99              # Use the C99 language standard
C_FLAG_DEBUG_INFO          = -g                    # Include debug information
#C_FLAG_HEADERS             = -H                    # Prints paths of all headers
C_FLAG_ALL_WARNINGS        = -Wall                 # Enable most common warning
C_FLAG_PEDANTIC            = -Wpedantic            # Enforce ISO C standard strictly
C_FLAG_SHADOW              = -Wshadow              # Warn if a local variable shadows another
C_FLAG_STRICT_PROTOS       = -Wstrict-prototypes   # Warn if function declarations are missing parameter types
C_FLAG_NO_UNKNOWN_PRAGMAS  = -Wno-unknown-pragmas  # Suppress warnings about unknown pragmas

C_FLAGS = \
    $(C_FLAG_STD_C99) \
    $(C_FLAG_DEBUG_INFO) \
    $(C_FLAG_HEADERS) \
    $(C_FLAG_ALL_WARNINGS) \
    $(C_FLAG_PEDANTIC) \
    $(C_FLAG_SHADOW) \
	$(C_FLAG_STRICT_PROTOS) \
    $(C_FLAG_NO_UNKNOWN_PRAGMAS)

# INCLUDE FLGAS
INCLUDE_FLAGS = -Iinclude

# EXTERNAL FLAGS
EXTERNAL_RAYGUI = -Iexternal/raygui
EXTERNAL_RINI = -Iexternal/rini
EXTERNAL_FLAGS = \
	$(EXTERNAL_RINI) \
	$(EXTERNAL_RAYGUI)

# CROSS PLATTFORM
ifeq ($(OS), Windows_NT)
	SRC = $(wildcard src\*.c)
	TARGET = bin\win\game.exe
	RAYLIB_FLAGS = -I%RAYLIB% -L%RAYLIB% -lraylib -lopengl32 -lgdi32 -lwinmm
else
	SRC = $(wildcard src/*.c)
	TARGET = bin/unix/game
	RAYLIB_FLAGS = $(shell pkg-config --libs --cflags raylib) -lm
endif

# CREATE BIN DIR
$(shell mkdir -p bin/unix bin/win)

# COMMANDS
build: $(SRC)
	$(COMPILER) $(SRC) -o $(TARGET) $(C_FLAGS) $(INCLUDE_FLAGS) $(EXTERNAL_FLAGS) $(RAYLIB_FLAGS) 

clean:
	rm -rf $(TARGET)

run: clean build
	./$(TARGET)
