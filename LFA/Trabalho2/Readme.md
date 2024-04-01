# State Machine Project

Este projeto implementa uma máquina de estados finitos juntamente com funcionalidades para operações CRUD (Create, Read, Update, Delete) em estados. Ele também inclui um menu de desenvolvimento para facilitar a gestão dos estados.

## Funcionalidades

- Definição de estados com nome, tipo, token e transições.
- Operações CRUD em estados (criar, listar, ler, atualizar, deletar).
- Processamento de entrada para transitar entre estados na máquina de estados finitos.
- Geração de tokens com base no processamento de entrada.

## Requisitos

- Python 3.x
- Biblioteca TinyDB
- Ambiente virtual (recomendado)

## Instalação

1. Crie a venv (recomendado):

```bash
python3 -m venv venv
```

2. Inicie a venv:

```bash
source venv/bin/activate
```

3. Instale as dependências usando o pip:

```bash
pip install -r requirements.txt
```

4. Sair da venv

```bash
deactivate
```

## Execução do Programa

Para executar o programa, use o seguinte comando:

```bash
python main.py
```

ou

```bash
python main.py dev
```

Habilita o menu de dev

## Operações no Menu de Desenvolvimento

Quando o menu de desenvolvimento for iniciado, você terá as seguintes opções:

1. Listar todos os estados
2. Criar um novo estado
3. Ler detalhes de um estado
4. Atualizar um estado existente
5. Deletar um estado existente
6. Sair