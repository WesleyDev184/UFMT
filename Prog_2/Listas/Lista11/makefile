# Nome do executável
TARGET = programa

# Pasta de saída
OUTPUT_FOLDER = build

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -std=c++11

# Encontra todos os arquivos .cpp recursivamente, exceto main.cpp
SRC := $(shell find -type f -name '*.cpp')

# Encontra todos os arquivos .h recursivamente
HEADER := $(shell find -type f -name '*.h')

# Gera a lista de arquivos objeto, mantendo a estrutura de pastas
OBJ = $(patsubst %.cpp, $(OUTPUT_FOLDER)/%.o, $(SRC))

# Regra padrão
all: $(OUTPUT_FOLDER) $(OUTPUT_FOLDER)/$(TARGET)

# Regra para criar o diretório de saída
$(OUTPUT_FOLDER):
	mkdir -p $(OUTPUT_FOLDER)

# Regra para criar o executável dentro da pasta de saída
$(OUTPUT_FOLDER)/$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

# Regras para compilar arquivos .cpp (exceto main.cpp) em .o dentro da pasta de saída
$(OUTPUT_FOLDER)/%.o: %.cpp $(HEADER)
	@mkdir -p $(dir $@)  # Garante que os diretórios sejam criados
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra específica para compilar main.cpp
$(OUTPUT_FOLDER)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Executa o programa
run: all
	@./$(OUTPUT_FOLDER)/$(TARGET)

# Limpeza dos arquivos objeto e executável
clean:
	rm -rf $(OUTPUT_FOLDER)

# Força recompilação completa
rebuild: clean all