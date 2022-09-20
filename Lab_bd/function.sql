-- Active: 1662482481446@@127.0.0.1@3306@lab_bd_compras

-- Funçao armazenada
create FUNCTION tot_vendas(id_produto int) RETURNS int 
 BEGIN
 DECLARE tot int;
 SELECT sum(qtd_compra) INTO tot
 from compras WHERE id_prod = id_produto;
 return tot;
 END

SELECT distinct id_prod FROM compras WHERE tot_vendas(id_prod) >= 5;

CREATE FUNCTION insere_venda(id_p int, id_c int, id int, data date, qtd_v int) RETURNS int
    BEGIN
    INSERT INTO compras(id_prod, id_cli, id, data_compra, qtd_compra) VALUES (id_p , id_c, id, data, qtd_v);
    RETURN 1;
    END

SELECT insere_venda(1,1, 7, '2022-08-20', 4)

-- Procedimento armazenada
CREATE Procedure tot_vendas2(in id_produto int, out tot_vendas int)
    BEGIN
    SELECT sum(qtd_compra) INTO tot_vendas
    FROM compras
    WHERE id_prod = id_produto;
    END

call tot_vendas2(1, @total);

SELECT @total

create PROCEDURE insere_venda2(in id_p int, in id_c int, in id int, in data date, in qtd_v int)
    BEGIN
    INSERT INTO compras(id_prod, id_cli, id, data_compra, qtd_compra) VALUES (id_p , id_c, id, data, qtd_v);
    END

call insere_venda2(1,1,8,'2022-08-20',10)