package Connection;

import java.sql.Connection;
import java.sql.SQLException;

public class testecon {
  public static void main(String[] args) {
    try {
      Connection connection = CreateConnection.getConnection();
      if (connection != null) {
        System.out.println("Conexão com o banco de dados estabelecida com sucesso!");
        // Faça as operações necessárias no banco de dados aqui
      } else {
        System.out.println("Falha ao estabelecer conexão com o banco de dados.");
      }
    } catch (ClassNotFoundException | SQLException e) {
      System.out.println("Erro ao conectar-se ao banco de dados: " + e.getMessage());
    }
  }
}
