#variables
CXX := g++ SRC_DIR := src OUT_DIR := output BUILD_DIR := build SRC_EXT := cpp

#nombres del ejecutable
TARGET := my_project

#encuentra los archivos fuentes
SOURCES := $(wildcard $(SRC_DIR)/*.$(SRC_EXT))

#generar nombre de archivos objeto
OBJECTS := $(SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(BUILD_DIR)/%.o)

#flags de compilacion
CXXFLAGS := -std=c++11 -Wall -Wextra -g

#regla por defecto
all: $(OUT_DIR)/$(TARGET)

#creacion del directorio de construccion
$(BUILD_DIR): @mkdir -p $(BUILD_DIR)

#creacion del directorio de salida
$(OUT_DIR): @mkdir -p $(OUT_DIR)

#regla para enlazar el ejecutable
$(OUT_DIR)/$(TARGET): $(OBJECTS) | $(OUT_DIR) $(CXX) $(OBJECTS) -o $@

#regla para compilar los archivos fuentes
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT) | $(BUILD_DIR) $(CXX) $(CXXFLAGS) -c $< -o $@

#limpiar los archivos generados
clean: @rm -rf $(BUILD_DIR) $(OUT_DIR)/$(TARGET)

.PHONY: all clean
