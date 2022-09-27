-- Active: 1662482481446@@127.0.0.1@3306@lab_bd_compras
CREATE PROCEDURE insert_client(in id_client int,in nome varchar(50),in cpf int)
    BEGIN
        insert into cliente(id_cli, nome, cpf) values (id_client, nome, cpf);
    END