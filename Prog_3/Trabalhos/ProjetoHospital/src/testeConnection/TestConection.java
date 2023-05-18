package testeConnection;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

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

			// Abre uma conexão com o Banco de Dados (ETAPA 4)
			Connection c = DriverManager.getConnection(url, user, password);
			System.out.println("Conexão estabelecida com sucesso!");
			c.close();
		} catch (ClassNotFoundException e) {
			System.out.println("Erro ao carregar o driver");
			e.printStackTrace();
		} catch (SQLException e) {
			System.out.println("Erro ao conectar com o banco");
			e.printStackTrace();
		}
	}
}
