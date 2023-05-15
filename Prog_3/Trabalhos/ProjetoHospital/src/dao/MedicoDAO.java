package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.LinkedList;
import java.util.List;

import entidades.Medico;

public class MedicoDAO {
	private Connection c;

	public MedicoDAO() throws ClassNotFoundException, SQLException {
		c = ConnectionFactory.getConnection();
	}

	public Medico consulta(int CRM) throws SQLException {
		PreparedStatement st = c.prepareStatement("SELECT * FROM Medico WHERE CRM like ?;");
		st.setInt(1, CRM);
		ResultSet rs = st.executeQuery();

		// Recupera especialidade do medico na table Medico_Especialidade
		// Instancia objeto apropriado
		Medico m = new Medico();
		if (rs.next()) {
			m.setCRM(CRM);
			// m.setIdade(rs.getInt("idade"));
			// m.setNome(rs.getString("nome"));
		}
		return m;
	}

	public void insere(Medico medico) {
		// TODO: implementar este metodo
	}

	public List<Medico> consultaMedicos() throws SQLException {
		List<Medico> medicos = new LinkedList<Medico>();

		// // Cria uma Statement(ETAPA 5)
		Statement st = (Statement) c.createStatement();
		// // Executa o comando SQL (ETAPA 6)
		ResultSet r = st.executeQuery("SELECT * FROM Medico"); //
		// // Itera sobre os resultados (ETAPA 7)
		while (r.next()) {
			// medicos.add(new Medico(r.getInt("CRM") , r.getString("nome"),
			// r.getInt("idade")));
		}

		st.close();
		return medicos;
	}
}
