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

CREATE FUNCTION func(x integer) RETURNS varchar(15) deterministic
    BEGIN
        DECLARE ret varchar(15);
        CASE 
            WHEN x > 10 THEN SET ret = 'Maior';
            WHEN x < 10 THEN SET ret = 'Menor';
            WHEN x = 10 THEN SET ret = 'Igual';
        END CASE;
        RETURN ret;
END

CREATE FUNCTION func(x integer) RETURNS varchar(15) deterministic
    BEGIN
        DECLARE ret varchar(15);
        IF x = 10 THEN
           SET ret = 'dez';
        ELSEIF x = 5 THEN
            SET ret = 'Cinco';
        ELSEIF x = 7 THEN
            SET ret = 'Sete';
        END IF;
        RETURN ret;
END

SELECT func(5)
DROP FUNCTION func

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

CREATE PROCEDURE proc_interate(IN x int, OUT y int)
    BEGIN
        ponto1: LOOP
            SET x = x + 1;
            IF x < 10 THEN
                iterate ponto1;
            END IF;
            leave ponto1;
        END LOOP ponto1;

        SET y = x;
END

CREATE PROCEDURE proc_interate(IN x int, OUT y int)
    BEGIN
    SET y = 0;
        repeat
            SET y = y + 1;
        until y > x
        END repeat;
END

CREATE PROCEDURE proc_interate(IN x int, OUT y int)
    BEGIN
    SET y = 0;
        WHILE y <= x do
            SET y = y + 1;
        END WHILE;
END

CALL proc_interate(10, @res)
SELECT @res

CREATE PROCEDURE get_maior_salario(OUT valor int)
    BEGIN
        DECLARE maior float default 0.0;
        DECLARE aux float;
        DECLARE terminou boolean default false;
        DECLARE um_cursor CURSOR for SELECT preco_unit from produto;
        DECLARE continue handler for NOT FOUND SET terminou = true;

        OPEN um_cursor;

    WHILE terminou <> true do 
        FETCH um_cursor INTO aux;
        IF aux > maior THEN
            SET maior = aux;
        END IF;
    END WHILE;
    CLOSE um_cursor;

   SET valor = maior;
END

CALL get_maior_salario(@v)
SELECT @v