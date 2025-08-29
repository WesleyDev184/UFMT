# Projetos de Sistemas Distribuídos - UFMT

Este repositório contém três implementações diferentes de um sistema de monitoramento de vendas usando diferentes tecnologias de comunicação distribuída:

1. **javaRpc/** - Implementação em Java usando XML-RPC
2. **pythonTrab/** - Implementação em Python usando RPyC
3. **trabalhoC/** - Implementação em C usando ONC RPC

## 1. Projeto Java XML-RPC (javaRpc/)

#### Linux

```bash
# Instalar Java JDK
sudo apt update
sudo apt install openjdk-11-jdk

# Verificar instalação
java -version
javac -version
```

#### Windows

```cmd
# Baixar e instalar Java JDK do site oficial:
# https://adoptium.net/temurin/releases/
# Ou usar Chocolatey:
choco install openjdk11
```

### Como Executar

#### Linux

```bash
cd javaRpc

# Iniciar o servidor (em outro terminal)
make run-server

# Executar o cliente
make run-client
```

#### Windows

```cmd
cd javaRpc

# Iniciar o servidor (em outro terminal)
make run-server

# Executar o cliente
make run-client
```

### Estrutura do Projeto

- `src/` - Código fonte Java
- `lib/` - Bibliotecas XML-RPC
- `bin/` - Arquivos compilados
- `cliente_monitoramento.py` - Cliente alternativo em Python

---

## 2. Projeto Python RPyC (pythonTrab/)

### Pré-requisitos Específicos

#### Linux

```bash
# Instalar Python (geralmente já instalado)
python3 --version

# Instalar dependências
pip3 install -r req.txt
```

#### Windows

```cmd
# Instalar Python do site oficial:
# https://www.python.org/downloads/

# Instalar dependências
pip install -r req.txt
```

### Como Executar

#### Linux

```bash
cd pythonTrab

# Instalar dependências
pip3 install -r req.txt

# Iniciar o servidor (em outro terminal)
python3 servidor_vendas.py

# Executar o cliente
python3 cliente_monitoramento.py
```

#### Windows

```cmd
cd pythonTrab

# Instalar dependências
pip install -r req.txt

# Iniciar o servidor (em outro terminal)
python servidor_vendas.py

# Executar o cliente
python cliente_monitoramento.py
```

### Arquivos

- `servidor_vendas.py` - Servidor RPyC
- `cliente_monitoramento.py` - Cliente interativo
- `req.txt` - Dependências Python

---

## 3. Projeto C ONC RPC (trabalhoC/)

### Pré-requisitos Específicos

#### Linux

```bash
# Instalar ferramentas RPC
sudo apt update
sudo apt install rpcbind
sudo apt install libc6-dev
sudo apt install gcc

# Instalar rpcgen se não estiver presente
sudo apt install rpcgen
```

#### Windows

```cmd
# Recomendado usar WSL ou Cygwin
# Instalar WSL:
wsl --install

# Dentro do WSL (Ubuntu):
sudo apt update
sudo apt install rpcbind
sudo apt install libc6-dev
sudo apt install gcc
sudo apt install rpcgen
```

### Como Executar

#### Linux

```bash
cd trabalhoC

# Gerar arquivos RPC (se necessário)
rpcgen vendas.x

# Compilar servidor e cliente
make -f Makefile.vendas

# Iniciar rpcbind (se não estiver rodando)
sudo systemctl start rpcbind

# Iniciar o servidor (em outro terminal)
./vendas_server

# Executar o cliente
./vendas_client localhost
```

#### Windows (WSL)

```bash
cd trabalhoC

# Gerar arquivos RPC (se necessário)
rpcgen vendas.x

# Compilar servidor e cliente
make -f Makefile.vendas

# Iniciar rpcbind (se não estiver rodando)
sudo service rpcbind start

# Iniciar o servidor (em outro terminal)
./vendas_server

# Executar o cliente
./vendas_client localhost
```

---

## Notas Gerais

### Conectividade

- **Java XML-RPC**: Porta 8080, protocolo HTTP
- **Python RPyC**: Porta 18861, protocolo RPyC
- **C RPC**: Portas dinâmicas via rpcbind

### Firewall

Para executar os servidores, pode ser necessário configurar o firewall:

#### Linux

```bash
# Permitir portas específicas
sudo ufw allow 8080
sudo ufw allow 18861
sudo ufw allow 111  # rpcbind
```

#### Windows

```cmd
# Configurar Firewall do Windows Defender
# Adicionar regras para as portas 8080, 18861, 111
```
