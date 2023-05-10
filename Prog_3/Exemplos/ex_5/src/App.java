import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class App {
    public static void main(String[] args) {
        try {
            // Carrega o driver JDBC do MySQL
            Class.forName("com.mysql.jdbc.Driver");

            // Cria uma conexão com o banco de dados
            String url = "jdbc:mysql://localhost:3306/teste";
            String usuario = "root";
            String senha = "123456";
            Connection conexao = DriverManager.getConnection(url, usuario, senha);

            // Utiliza a conexão para acessar o banco de dados
            System.out.println("Conectado ao banco de dados!");

            // Fecha a conexão
            conexao.close();
        } catch (ClassNotFoundException e) {
            System.err.println("Não foi possível carregar o driver JDBC: " + e.getMessage());
        } catch (SQLException e) {
            System.err.println("Não foi possível conectar ao banco de dados: " + e.getMessage());
        }
    }
}
