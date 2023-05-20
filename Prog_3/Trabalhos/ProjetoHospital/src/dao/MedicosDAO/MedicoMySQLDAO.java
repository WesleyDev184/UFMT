package dao.MedicosDAO;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.LinkedList;
import java.util.List;

import dao.ConnectionFactory;
import entidades.Anestesista;
import entidades.Medico;
import entidades.Pediatra;

/**
 * Esta classe é a implementação do DAO para o banco de dados MySQL.
 * 
 * @author thiago
 *
 */
public class MedicoMySQLDAO implements MedicoInterface {
	private Connection c;

	public MedicoMySQLDAO() throws ClassNotFoundException, SQLException {
		c = ConnectionFactory.getConnection();
	}

	public boolean insere(Medico med) {
		Connection c = null;
		try {
			c = ConnectionFactory.getConnection();
		} catch (ClassNotFoundException | SQLException e) {
			e.printStackTrace();
			return false;
		}
		PreparedStatement ps = null;
		try {
			ps = c.prepareStatement("insert into Medico(CRM, valorHora, nome, dataNascimento) values (?, ?, ?, ?);");

			ps.setInt(1, med.getCRM());
			ps.setDouble(2, med.getValorHora());
			ps.setString(3, med.getNome());
			java.util.Date nascimento = med.getDataNascimento();
			ps.setDate(4, new java.sql.Date(nascimento.getTime()));
			ps.executeUpdate();
			ps.close();
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
		return true;
	}

	public Medico buscaMedico(int CRM) {
		return null;
	}

	public List<Medico> medicos() {
		List<Medico> medicos = new LinkedList<Medico>();

		Statement st;
		try {
			st = (Statement) c.createStatement();
			ResultSet r = st.executeQuery(
					"select m.nome, m.CRM, m.valorHora, e.titulo from Medico as m, Medico_Especialidade as me, Especialidade as e where (me.idmedico = m.crm) and (me.idespecialidade = e.idespecialidade);");
			Medico aux;
			while (r.next()) {

				String especialidade = r.getString("titulo");
				if (especialidade.equals("Pedriatria")) {
					aux = new Pediatra();
					aux.setCRM(r.getInt("CRM"));
					aux.setValorHora(r.getDouble("valorHora"));
					aux.setNome(r.getString("nome"));
					medicos.add(aux);
				} else if (especialidade.equals("Anestesista")) {
					aux = new Anestesista();
					aux.setCRM(r.getInt("CRM"));
					aux.setValorHora(r.getDouble("valorHora"));
					aux.setNome(r.getString("nome"));
					// aux.setEspecialidade(r.getString("especialidade"));
					medicos.add(aux);
				}
				// TODO: deve-se continuar esta implementação para todas as classes concretas.
			}

			st.close();

		} catch (SQLException e) {
			e.printStackTrace();
		}
		return medicos;

	}

}
