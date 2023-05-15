package dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public final class ConnectionFactory {
	private static Connection connection = null;

	// Construtor privado para que ninguem possa instanciar a classe
	private ConnectionFactory() {
	}

	private static void createConnection() throws ClassNotFoundException, SQLException {
		Class.forName("com.mysql.jdbc.Driver");

		String url = "jdbc:mysql://localhost:3306/hospital"; // Nome da base de dados
		String user = "sergey"; // nome do usuário do MySQL
		String password = "sergey"; // senha do MySQL
		connection = DriverManager.getConnection(url, user, password);
	}

	public static synchronized Connection getConnection() throws ClassNotFoundException, SQLException {
		if (connection == null)
			createConnection();
		return connection;
	}
}
