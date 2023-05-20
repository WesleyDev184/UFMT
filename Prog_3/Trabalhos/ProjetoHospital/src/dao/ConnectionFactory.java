package dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public final class ConnectionFactory {
	private static Connection connection = null;

	// Construtor privado para que ninguém possa instanciar a classe
	private ConnectionFactory() {
	}

	private static void createConnection() throws ClassNotFoundException, SQLException {
		Class.forName("com.mysql.cj.jdbc.Driver");

		String url = "jdbc:mysql://localhost:3306/hospital"; // Nome da base de dados
		String user = "root"; // nome do usuário do MySQL
		String password = "123456"; // senha do MySQL
		connection = DriverManager.getConnection(url, user, password);
	}

	public static synchronized Connection getConnection() throws ClassNotFoundException, SQLException {
		if (connection == null)
			createConnection();
		return connection;
	}
}