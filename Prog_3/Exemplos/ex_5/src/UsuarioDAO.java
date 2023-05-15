import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UsuarioDAO {
  private Connection conexao;

  public UsuarioDAO() {
    // Configurar a conexão com o banco de dados
    String url = "jdbc:mysql://localhost:3306/teste";
    String usuario = "root";
    String senha = "123456";

    try {
      conexao = DriverManager.getConnection(url, usuario, senha);
      System.out.println("Conectado ao banco de dados!");
    } catch (SQLException e) {
      System.err.println("Não foi possível conectar ao banco de dados: " + e.getMessage());
    }
  }

  public void fecharConexao() {
    try {
      if (conexao != null) {
        conexao.close();
        System.out.println("Conexão fechada.");
      }
    } catch (SQLException e) {
      System.err.println("Erro ao fechar a conexão com o banco de dados: " + e.getMessage());
    }
  }

  public void inserirUsuario(Usuario usuario) {
    String sql = "INSERT INTO User_Table (cpf, nome, telefone) VALUES (?, ?, ?)";

    try (PreparedStatement stmt = conexao.prepareStatement(sql)) {
      stmt.setInt(1, usuario.getId());
      stmt.setString(2, usuario.getNome());
      stmt.setString(3, usuario.getTelefone());
      stmt.executeUpdate();
      System.out.println("Usuário inserido com sucesso!");
    } catch (SQLException e) {
      System.err.println("Erro ao inserir usuário: " + e.getMessage());
    }
  }

  public void atualizarUsuario(Usuario usuario) {
    String sql = "UPDATE User_Table SET nome = ?, telefone = ? WHERE cpf = ?";

    try (PreparedStatement stmt = conexao.prepareStatement(sql)) {
      stmt.setString(1, usuario.getNome());
      stmt.setString(2, usuario.getTelefone());
      stmt.setInt(3, usuario.getId());
      stmt.executeUpdate();
      System.out.println("Usuário atualizado com sucesso!");
    } catch (SQLException e) {
      System.err.println("Erro ao atualizar usuário: " + e.getMessage());
    }
  }

  public void excluirUsuario(int id) {
    String sql = "DELETE FROM User_Table WHERE cpf = ?";

    try (PreparedStatement stmt = conexao.prepareStatement(sql)) {
      stmt.setInt(1, id);
      stmt.executeUpdate();
      System.out.println("Usuário excluído com sucesso!");
    } catch (SQLException e) {
      System.err.println("Erro ao excluir usuário: " + e.getMessage());
    }
  }

  public Usuario buscarUsuarioPorId(int id) {
    String sql = "SELECT * FROM User_Table WHERE cpf = ?";
    Usuario usuario = null;

    try (PreparedStatement stmt = conexao.prepareStatement(sql)) {
      stmt.setInt(1, id);
      ResultSet rs = stmt.executeQuery();

      if (rs.next()) {
        String nome = rs.getString("nome");
        String telefone = rs.getString("telefone");
        usuario = new Usuario(id, nome, telefone);
      }
    } catch (SQLException e) {
      System.err.println("Erro ao buscar usuário: " + e.getMessage());
    }

    return usuario;
  }
}
