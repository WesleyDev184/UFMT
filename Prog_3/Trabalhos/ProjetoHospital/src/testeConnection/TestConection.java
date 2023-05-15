package testeConnection;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class TestConection {

	public static void main(String[] args) throws ClassNotFoundException, SQLException {
		// Forço a instanciação da classe Driver da implementação fornecida pela MySQL
		// Carregar o Driver (ETAPA 2)
		Class.forName("com.mysql.jdbc.Driver");

		// Especifica uma URL com informações para acessar o Banco de Dados (ETAPA 3)
		String url = "jdbc:mysql://localhost:3306/teste"; // Nome da base de dados
		String user = "root"; // nome do usuário do MySQL
		String password = "123456"; // senha do MySQL

		// Abre uma conexão com o Banco de Dados (ETAPA 4)
		Connection c = DriverManager.getConnection(url, user, password);
		c.close();
	}

	private static void executePreparedSt(Connection c) throws SQLException {
		PreparedStatement ps = c.prepareStatement("insert into Aluno (nome, idade) values (?, ?);");
		ps.setString(1, "Jose da Silva Sauro");
		ps.setInt(2, 10999);
		ps.executeUpdate();
		ps.close();
	}

	/**
	 * Método que cria uma conexão com o SGBD. Este método por enquanto não está
	 * sendo utilizado.
	 * 
	 * @return
	 * @throws SQLException
	 */
	public static Connection createConnection() throws SQLException {
		// Especifica uma URL com informações para acessar o Banco de Dados (ETAPA 3)
		String url = "jdbc:mysql://localhost:3306/hospital"; // Nome da base de dados
		String user = "sergey"; // nome do usuário do MySQL
		String password = "sergey"; // senha do MySQL

		// Abre uma conexão com o Banco de Dados (ETAPA 4)
		Connection conexao = null;
		conexao = DriverManager.getConnection(url, user, password);

		return conexao;
	}
}
