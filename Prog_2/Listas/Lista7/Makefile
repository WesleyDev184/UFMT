# Nome do executável
TARGET = programa

# Pasta de saída
OUTPUT_FOLDER = output

# Pasta onde os arquivos .cpp e .h estão localizados
CLASSES_FOLDER = classes

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -std=c++11

# Arquivos de código-fonte
SRC = main.cpp $(CLASSES_FOLDER)/Livro.cpp $(CLASSES_FOLDER)/Membro.cpp $(CLASSES_FOLDER)/Biblioteca.cpp
HEADER = $(CLASSES_FOLDER)/Livro.h $(CLASSES_FOLDER)/Membro.h $(CLASSES_FOLDER)/Biblioteca.h

# Arquivos objeto gerados na pasta de saída
OBJ = $(patsubst %.cpp, $(OUTPUT_FOLDER)/%.o, $(notdir $(SRC)))

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
