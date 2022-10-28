from secrets import choice
from sqlite3 import Cursor
import mysql.connector
from mysql.connector import errorcode
import datetime
import sys

def makeConnection(user, password, h, bd):
    try:
        conn = mysql.connector.connect(user=user, password=password, host=h, database=bd)
        print('conexao estabelecida')
        return conn
    except mysql.connector.Error as err:
        if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
            print('User or password is invalid')
            sys.exit(-1)
        if err.errno == errorcode.ER_BAD_DB_ERROR:
            print('Banco nao emcontrado')
            sys.exit(-1)

#cadastrar clente
def cadastrarClientes(con, id, nome, cpf):
    cur = con.cursor()
    cur.callproc('insert_client', [id, nome, cpf])
    cur.close()
    con.commit()
    print('cliente inserido com sucesso')

#cadastrar Produto
def cadastrarProduto(con, id_prod, nome, preco_unit, qtd):
    cur = con.cursor()
    cur.callproc('insert_produto', [id_prod, nome, preco_unit, qtd])
    cur.close()
    con.commit()
    print('Produto inserido com sucesso') 

def buscaClientes(con, first_name): 
    cur = con.cursor()
    cur.callproc('buscar_cliente', [first_name])
    tuplas = cur.fetchall()
    cur.close()
    return tuplas

def buscarProduto (con):
    cur = con.cursor()
    sql = ('select * from Produto')
    cur.execute(sql)
    tuplas = cur.fetchall()
    cur.close()
    return tuplas

#cadastrar venda
def cadastrarVenda(con, id_prod, id_cli, id_venda, data, qtd):
    cur = con.cursor()
    cur.callproc('insert_compra', [id_prod, id_cli, id_venda, data, qtd])
    con.commit()


if __name__ == '__main__':
    conn = makeConnection ('root', '', 'localhost', 'lab_bd_compras')
    while(True): 
        print('************ Menu ************')
        print('(1) Cadastrar clinetes')
        print('(2) Cadastrar produtos')
        print('(3) Cadastrar venda')
        print('(4) Sair')
        print('*******************************')
        choice = input('Opcao: ')

        if choice ==  '1':
            id = int(input('Entre com o id do clinete: '))
            nome = input('Entre com o nome do clinete: ')
            cpf = int(input('Entre com o cpf do clinete: '))
            cadastrarClientes(conn, id, nome, cpf)
        elif choice == '2':
            id_prod = int(input('Entre com o id do produto: '))
            nome = input('Entre com o nome do produto: ')
            preco_unit = float(input('Entre com o preço unitario do produto: '))
            qtd = float(input('Entre com a quantidade do produto: '))
            cadastrarProduto(conn, id_prod, nome, preco_unit, qtd)

        elif choice == '3':
            first_name = input('Peimriro nome: ')
            clientes = buscaClientes(conn, first_name)
            print('Clinetes encontrados: ')
            for tupla in clientes:
                print('id = {}, nome = {}, cpf = {}'.format(tupla[0], tupla[1], tupla[2]))

            produtos = buscarProduto(conn)
            print('Produtos encontrados: ')
            for tupla in produtos:
                print('id = {}, nome = {}, Preco_unitario = {}, Quantidade = {}'.format(tupla[0], tupla[1], tupla[2], tupla[3]))

            id_cli = int(input('Entre com o id so clinete: '))
            id_prod = int(input('Entre com o id so Produto: '))
            id_venda = int(input('Entre com o id da venda: '))
            data = datetime.date.today()
            qtd = int(input('Entre com a quantidade vendida: '))
            cadastrarVenda(conn, id_prod, id_cli, id_venda, data, qtd)

        elif choice == '4':
            print('ate a prixima')
            conn.close()
            sys.exit(-1)
        else: 
            print('Opcao inexistente')

        

    conn.close()
