-- Active: 1684147198273@@127.0.0.1@3306@teste
create table User_Table (
	  cpf int AUTO_INCREMENT not null,
	  telefone varchar(12) not null,
    nome varchar(50) not null,
  primary key (cpf)
);