# Makefile para o projeto javaRpc
# Compila os fontes em src/ usando os jars em lib/ e coloca as classes em bin/


JAVAC=javac
JFLAGS=-d bin -cp "lib/*:bin"
SOURCES=$(wildcard src/*.java)
CLASSPATH=lib/*:bin

# Dependências JAR necessárias (coloque em lib/)
REQUIRED_JARS = lib/commons-logging-1.2.jar

.PHONY: all check-deps compile run-server run-client run-server-bg stop-server clean

all: compile

COMMONS_LOGGING_VERSION=1.2
COMMONS_LOGGING_URL=https://repo1.maven.org/maven2/commons-logging/commons-logging/$(COMMONS_LOGGING_VERSION)/commons-logging-$(COMMONS_LOGGING_VERSION).jar

.PHONY: deps
deps:
	mkdir -p lib
	@if [ ! -f lib/commons-logging-$(COMMONS_LOGGING_VERSION).jar ]; then \
		echo "Baixando commons-logging-$(COMMONS_LOGGING_VERSION).jar..."; \
		if command -v curl >/dev/null 2>&1; then \
			curl -L -o lib/commons-logging-$(COMMONS_LOGGING_VERSION).jar $(COMMONS_LOGGING_URL); \
		else \
			wget -O lib/commons-logging-$(COMMONS_LOGGING_VERSION).jar $(COMMONS_LOGGING_URL); \
		fi; \
	else \
		echo "commons-logging-$(COMMONS_LOGGING_VERSION).jar já presente"; \
	fi

compile: deps
	mkdir -p bin
	$(JAVAC) $(JFLAGS) $(SOURCES)


run-server: compile
	@echo "Iniciando servidor (foreground) na porta 8080..."
	java -cp "$(CLASSPATH)" ServidorFilial

run-client: compile
	@echo "Executando ClienteMonitoramento..."
	java -cp "$(CLASSPATH)" ClienteMonitoramento

stop-server:
	@if [ -f bin/server.pid ]; then kill `cat bin/server.pid` && rm -f bin/server.pid; else echo "Nenhum PID (bin/server.pid) encontrado"; fi

clean:
	rm -rf bin/*
