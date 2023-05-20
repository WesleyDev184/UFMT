CREATE TABLE addresses (
  id INT PRIMARY KEY AUTO_INCREMENT,
  public_place VARCHAR(255) NOT NULL,
  number INT NOT NULL,
  cep INT NOT NULL,
  neighborhood VARCHAR(255) NOT NULL
);

CREATE TABLE specialties (
  id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(255) NOT NULL
);

CREATE TABLE doctors (
  id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(255) NOT NULL,
  birth_date DATE NOT NULL,
  crm INT NOT NULL UNIQUE,
  timeValue FLOAT NOT NULL,
  specialty_id INT NOT NULL,
  address_id INT NOT NULL,
  FOREIGN KEY (specialty_id) REFERENCES specialties(id),
  FOREIGN KEY (address_id) REFERENCES addresses(id)
);

CREATE TABLE health_insurances (
  id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(255) NOT NULL,
  monthly_payment FLOAT NOT NULL
);

CREATE TABLE patients (
  id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(255) NOT NULL,
  cpf BIGINT NOT NULL UNIQUE,
  birth_date DATE NOT NULL,
  address_id INT NOT NULL,
  health_insurance_id INT NOT NULL,
  FOREIGN KEY (address_id) REFERENCES addresses(id),
  FOREIGN KEY (health_insurance_id) REFERENCES health_insurances(id)
);

CREATE TABLE hospital_appointments (
  id INT PRIMARY KEY AUTO_INCREMENT,
  appointment_date DATE NOT NULL,
  patient_id INT,
  doctor_id INT,
  FOREIGN KEY (patient_id) REFERENCES patients(id),
  FOREIGN KEY (doctor_id) REFERENCES doctors(id)
);

CREATE TABLE rooms (
  id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(255) NOT NULL
);

CREATE TABLE procedure_types (
  id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(255) NOT NULL,
  cost FLOAT NOT NULL
);

CREATE TABLE medical_procedures (
  id INT PRIMARY KEY AUTO_INCREMENT,
  patient_id INT,
  doctor_id INT,
  date DATE NOT NULL,
  duration INT NOT NULL,
  room_id INT,
  procedure_type_id INT NOT NULL,
  FOREIGN KEY (procedure_type_id) REFERENCES procedure_types(id),
  FOREIGN KEY (patient_id) REFERENCES patients(id),
  FOREIGN KEY (doctor_id) REFERENCES doctors(id),
  FOREIGN KEY (room_id) REFERENCES rooms(id)
);
