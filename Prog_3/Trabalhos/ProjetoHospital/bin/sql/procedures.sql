-- Procedimento para preencher as tabelas Medico e Medico_Especialidade
DELIMITER //
CREATE PROCEDURE PreencherMedicoEspecialidade(
    IN p_CRM INT,
    IN p_ValorHora DOUBLE,
    IN p_Nome VARCHAR(45),
    IN p_DataNascimento DATETIME,
    IN p_TituloEspecialidade VARCHAR(45)
)
BEGIN
    DECLARE v_EspecialidadeID INT;
    
    -- Verificar se a especialidade já existe na tabela
    SELECT idEspecialidade INTO v_EspecialidadeID
    FROM Especialidade
    WHERE titulo = p_TituloEspecialidade;
    
    -- Se a especialidade não existir, inserir um novo registro na tabela Especialidade
    IF v_EspecialidadeID IS NULL THEN
        INSERT INTO Especialidade (titulo)
        VALUES (p_TituloEspecialidade);
        
        SET v_EspecialidadeID = LAST_INSERT_ID();
    END IF;
    
    -- Inserir um novo registro na tabela Medico
    INSERT INTO Medico (CRM, valorHora, nome, dataNascimento)
    VALUES (p_CRM, p_ValorHora, p_Nome, p_DataNascimento);
    
    -- Inserir um novo registro na tabela Medico_Especialidade
    INSERT INTO Medico_Especialidade (idMedico, idEspecialidade)
    VALUES (p_CRM, v_EspecialidadeID);
    
    -- Exibir mensagem de sucesso
    SELECT 'Valores inseridos com sucesso.' AS Mensagem;
END //
DELIMITER ;

-- Procedimento para buscar médico por CRM ou nome
DELIMITER //

CREATE PROCEDURE BuscarMedico(
    IN p_CRM INT,
    IN p_Nome VARCHAR(45)
)
BEGIN
    IF p_CRM IS NOT NULL THEN
        SELECT m.*, e.titulo AS especialidade
        FROM Medico AS m
        INNER JOIN Medico_Especialidade AS me ON me.idMedico = m.CRM
        INNER JOIN Especialidade AS e ON e.idEspecialidade = me.idEspecialidade
        WHERE m.CRM = p_CRM;
    ELSEIF p_Nome IS NOT NULL THEN
        SELECT m.*, e.titulo AS especialidade
        FROM Medico AS m
        INNER JOIN Medico_Especialidade AS me ON me.idMedico = m.CRM
        INNER JOIN Especialidade AS e ON e.idEspecialidade = me.idEspecialidade
        WHERE m.nome LIKE CONCAT('%', p_Nome, '%');
    END IF;
END //

DELIMITER ;

-- Procedure para atualizar um médico
DELIMITER //

CREATE PROCEDURE AtualizarMedico(
    IN p_CRM INT,
    IN p_ValorHora DOUBLE
)
BEGIN
    UPDATE Medico
    SET valorHora = p_ValorHora
    WHERE CRM = p_CRM;
END //

DELIMITER ;
