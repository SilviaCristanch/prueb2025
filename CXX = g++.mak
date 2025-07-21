## Makefile para Windows con MinGW
CXX = C:\Users\HP AMD RYZEN 3\Desktop\winlibs-x86_64-posix-seh-gcc-15.1.0-mingw-w64msvcrt-12.0.0-r1\mingw64\bin\g++.EXE
CXXFLAGS = -Wall -Wextra -g3 -std=c++11
BUILD_DIR = output
TARGET = main_integrado.exe

# Archivos fuente
SOURCES = main_integrado.cpp astrologia.cpp
OBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
EXECUTABLE = $(BUILD_DIR)/$(TARGET)

# Regla principal
all: $(BUILD_DIR) $(EXECUTABLE)

# Crear directorio de salida
$(BUILD_DIR):
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# Enlazar objetos para crear ejecutable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilar archivos objeto
$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilación directa (más simple)
direct: $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)

# Limpiar archivos generados
clean:
	if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

# Ejecutar programa
run: $(EXECUTABLE)
	$(EXECUTABLE)

.PHONY: all clean run direct