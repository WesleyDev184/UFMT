-- Active: 1684147198273@@127.0.0.1@3306@hospital
INSERT INTO addresses (public_place, number, cep, neighborhood) VALUES
  ('Rua A', 123, 12345, 'Bairro X'),
  ('Avenida B', 456, 54321, 'Bairro Y'),
  ('Praça C', 789, 98765, 'Bairro Z');

INSERT INTO health_insurances (name, monthly_payment) VALUES
  ('Seguro Saúde A', 100.00),
  ('Seguro Saúde B', 150.00),
  ('Seguro Saúde C', 200.00);

INSERT INTO patients (name, cpf, birth_date, address_id, health_insurance_id) VALUES
  ('João Silva', 12345678901, '1990-01-01', 1, 1),
  ('Maria Santos', 98765432109, '1985-05-10', 2, 2),
  ('Pedro Oliveira', 11122233344, '1998-12-15', 3, 3);