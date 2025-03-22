//plantilla

# Nombre del ejecutable
TARGET = bin/arquitectura

# Compilador
CC = g++

# Opciones de compilación
CFLAGS = -Wall -Wextra -Werror

# Directorios
SRC_DIR = src
OBJ_DIR = obj

# Archivos fuente
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Regla por defecto
all: $(TARGET)

# Regla para enlazar el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Regla para compilar los archivos fuente
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)  # Crea el directorio de objetos si no existe
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Regla para limpiar todo
fclean: clean

# Regla para recompilar
re: fclean all

.PHONY: all clean fclean re