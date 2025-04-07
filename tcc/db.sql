CREATE TABLE users (
    id UUID PRIMARY KEY,
    name VARCHAR(255),
    email VARCHAR(255),
    password TEXT,
    phone VARCHAR(20),
    created_at TIMESTAMP,
    updated_at TIMESTAMP
);

CREATE TABLE applicants (
    id UUID PRIMARY KEY,
    name VARCHAR(255),
    cpf VARCHAR(14),
    phone VARCHAR(20),
    email VARCHAR(255),
    address TEXT,
    created_at TIMESTAMP,
    updated_at TIMESTAMP
);

CREATE TABLE beneficiaries (
    id UUID PRIMARY KEY,
    applicant_id UUID,
    name VARCHAR(255),
    cpf VARCHAR(14),
    phone VARCHAR(20),
    created_at TIMESTAMP,
    updated_at TIMESTAMP,
    FOREIGN KEY (applicant_id) REFERENCES applicants(id)
);

CREATE TABLE stock (
    id UUID PRIMARY KEY,
    type VARCHAR(255), -- Pode ser ajustado para ENUM se necessário
    maintenance_qty INT,
    available_qty INT,
    created_at TIMESTAMP,
    updated_at TIMESTAMP
);

CREATE TABLE item (
    id UUID PRIMARY KEY,
    name VARCHAR(255),
    serial_code INT,
    description TEXT,
    stock_id UUID,
    created_at TIMESTAMP,
    updated_at TIMESTAMP,
    FOREIGN KEY (stock_id) REFERENCES stock(id)
);

CREATE TABLE loans (
    id UUID PRIMARY KEY,
    applicant_id UUID,
    responsible UUID, -- user_id
    stock_id UUID,
    return_date TIMESTAMP,
    reason TEXT,
    loaned BOOLEAN,
    created_at TIMESTAMP,
    updated_at TIMESTAMP,
    FOREIGN KEY (applicant_id) REFERENCES applicants(id),
    FOREIGN KEY (responsible) REFERENCES users(id),
    FOREIGN KEY (stock_id) REFERENCES stock(id)
);
