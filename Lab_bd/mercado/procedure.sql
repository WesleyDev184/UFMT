Active: 1662482481446@@127.0.0.1@3306@lab_bd_compras
CREATE PROCEDURE insert_client(in id_client int,in nome varchar(50),in cpf int)
    BEGIN
        insert into cliente(id_cli, nome, cpf) values (id_client, nome, cpf);
    END

CREATE PROCEDURE insert_produto(in id_prod int, in nome varchar(50), in preco_unit float, IN qtd int)
    BEGIN
        insert into produto (id_prod, nome, preco_unit, qtd) values (id_prod, nome, preco_unit, qtd);
    END

CREATE PROCEDURE insert_compra(in id_prod int, IN id_cli int, IN id int, in data_compra date, in qtd_compra int)
    BEGIN
        insert into Compras (id_prod, id_cli, id, data_compra, qtd_compra) values (id_prod,id_cli,id,data_compra,qtd_compra);
        update Produto set qtd = qtd - qtd_compra where id_prod = id_prod;
    END
