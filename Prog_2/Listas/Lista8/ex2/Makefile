# Nome do executável
TARGET = programa

# Pasta de saída
OUTPUT_FOLDER = build

# Pasta onde os arquivos .cpp e .h estão localizados
CLASSES_FOLDER = include

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -std=c++11 -I$(CLASSES_FOLDER)

# Arquivos de código-fonte
SRC = $(wildcard $(CLASSES_FOLDER)/*.cpp) main.cpp
HEADER = $(wildcard $(CLASSES_FOLDER)/*.h)

# Arquivos objeto gerados na pasta de saída
OBJ = $(patsubst $(CLASSES_FOLDER)/%.cpp, $(OUTPUT_FOLDER)/%.o, $(SRC))

# Regra padrão
all: $(OUTPUT_FOLDER) $(OUTPUT_FOLDER)/$(TARGET)

# Regra para criar o diretório de saída
$(OUTPUT_FOLDER):
	mkdir -p $(OUTPUT_FOLDER)

# Regra para criar o executável dentro da pasta de saída
$(OUTPUT_FOLDER)/$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

# Regras para compilar arquivos .cpp em .o dentro da pasta de saída
$(OUTPUT_FOLDER)/%.o: $(CLASSES_FOLDER)/%.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Executa o programa
run: all
	@./$(OUTPUT_FOLDER)/$(TARGET)

# Limpeza dos arquivos objeto e executável
clean:
	rm -rf $(OUTPUT_FOLDER)

# Força recompilação completa
rebuild: clean all
