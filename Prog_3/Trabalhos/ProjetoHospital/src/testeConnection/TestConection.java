package testeConnection;

import java.sql.CallableStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class TestConection {

	public static void main(String[] args) throws ClassNotFoundException, SQLException {
		try {
			// Forço a instanciação da classe Driver da implementação fornecida pela MySQL
			// Carregar o Driver (ETAPA 2)
			Class.forName("com.mysql.cj.jdbc.Driver");

			// Especifica uma URL com informações para acessar o Banco de Dados (ETAPA 3)
			String url = "jdbc:mysql://localhost:3306/hospital"; // Nome da base de dados
			String user = "root"; // nome do usuário do MySQL
			String password = "123456"; // senha do MySQL

			// Cria uma conexão com o Banco de Dados (ETAPA 4)
			java.sql.Connection connection = java.sql.DriverManager.getConnection(url, user, password);

			String procedureCall = "{ CALL BuscarMedico(?, ?) }";
			CallableStatement statement = connection.prepareCall(procedureCall);

			Scanner scanner = new Scanner(System.in);
			System.out.print("Digite a pesquisa (CRM e/ou nome): ");
			String pesquisa = scanner.nextLine();

			String[] partes = pesquisa.split(" ");
			Integer crm = null;
			String nome = null;

			for (String parte : partes) {
				if (parte.matches("\\d+")) {
					crm = Integer.parseInt(parte);
				} else {
					nome = parte;
				}
			}

			if (crm == null && nome == null) {
				System.out.println("Pesquisa inválida. Forneça pelo menos um valor de pesquisa (CRM ou nome).");
				return;
			}

			if (crm == null) {
				statement.setNull(1, java.sql.Types.INTEGER);
			} else {
				statement.setInt(1, crm);
			}

			if (nome == null) {
				statement.setNull(2, java.sql.Types.VARCHAR);
			} else {
				statement.setString(2, nome);
			}

			// Executar o procedimento
			ResultSet resultSet = statement.executeQuery();

			// Exibir os resultados
			while (resultSet.next()) {
				int crmResult = resultSet.getInt("CRM");
				String nomeResult = resultSet.getString("nome");
				double valorHora = resultSet.getDouble("valorHora");
				String especialidade = resultSet.getString("especialidade");
				// Exibir as informações do médico (ou fazer o que for necessário)
				System.out.println("CRM: " + crmResult + ", Nome: " + nomeResult + ", Valor Hora: " + valorHora
						+ ", Especialidade: " + especialidade);
			}

			// Fechar os recursos
			resultSet.close();
			statement.close();
			connection.close();
		} catch (ClassNotFoundException e) {
			System.out.println("Erro ao carregar o driver");
			e.printStackTrace();
		} catch (SQLException e) {
			System.out.println("Erro ao conectar com o banco");
			e.printStackTrace();
		}
	}
}
