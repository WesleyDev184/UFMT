package dao.MedicosDAO;

import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

import dao.ConnectionFactory;
import entidades.Anestesista;
import entidades.Cardiologista;
import entidades.Dermatologista;
import entidades.Endocrinologista;
import entidades.Ginecologia;
import entidades.Medico;
import entidades.Neurologista;
import entidades.Obstetra;
import entidades.Ortopedista;
import entidades.Otorrinolaringologista;
import entidades.Pediatra;

public class MedicoDAO implements MedicoInterface {
	private Connection connection;

	public MedicoDAO() throws ClassNotFoundException, SQLException {
		this.connection = ConnectionFactory.getConnection();
	}

	public List<Medico> listDoctor() {
		String sql = "select m.nome, m.CRM, m.valorHora, e.titulo from Medico as m, Medico_Especialidade as me, Especialidade as e where (me.idmedico = m.crm) and (me.idespecialidade = e.idespecialidade);";

		List<Medico> medicos = new ArrayList<>();

		try {
			PreparedStatement stmt = connection.prepareStatement(sql);
			ResultSet rs = stmt.executeQuery();

			while (rs.next()) {
				String nome = rs.getString("nome");
				int crm = rs.getInt("CRM");
				double valorHora = rs.getDouble("valorHora");
				String specialty = rs.getString("titulo");

				Medico medico = createMedico(nome, crm, valorHora, specialty);
				if (medico != null) {
					medico.setEspecialidade(specialty);
					medicos.add(medico);
				}
			}
			stmt.close();
			return medicos;
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
	}

	public boolean insertDoctor(Medico medico) {
		String sql = "{ CALL PreencherMedicoEspecialidade(?, ?, ?, ?, ?) }";
		try {
			CallableStatement stmt = connection.prepareCall(sql);

			SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
			Date dataNascimento = new Date(dateFormat.parse(medico.getDataNascimento()).getTime());

			stmt.setInt(1, medico.getCRM());
			stmt.setDouble(2, medico.getValorHora());
			stmt.setString(3, medico.getNome());
			stmt.setDate(4, dataNascimento);
			stmt.setString(5, medico.getEspecialidade());

			stmt.close();
			return true;
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
	}

	public Medico searchDoctor(String pesquisa) {
		try {
			String procedureCall = "{ CALL BuscarMedico(?, ?) }";

			CallableStatement statement = connection.prepareCall(procedureCall);
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
				return null;
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
			Medico medico = null;

			if (resultSet.next()) {
				int crmResult = resultSet.getInt("CRM");
				String nomeResult = resultSet.getString("nome");
				double valorHora = resultSet.getDouble("valorHora");
				String especialidade = resultSet.getString("especialidade");
				// Outras colunas do resultado

				// Criar e retornar o objeto Medico
				medico = createMedico(nomeResult, crmResult, valorHora, especialidade);
			}

			statement.close();
			resultSet.close();
			return medico;
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
	}

	public boolean updateDoctor(int crm, double valorHora) {
		String sql = "{ CALL AtualizarMedico(?, ?) }";
		try {
			CallableStatement stmt = connection.prepareCall(sql);

			stmt.setInt(2, crm);
			stmt.setDouble(3, valorHora);

			stmt.close();
			return true;
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
	}

	public boolean deleteDoctor(int crm) {
		String sql = "delete from Medico where CRM = ?";
		try {
			PreparedStatement stmt = connection.prepareStatement(sql);

			stmt.setInt(1, crm);

			stmt.close();
			return true;
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
	}

	Medico createMedico(String nome, int CRM, double valorHora, String especialidade) {
		switch (especialidade) {
			case "Anestesista":
				return new Anestesista(nome, CRM, valorHora);
			case "Pediatra":
				return new Pediatra(nome, CRM, valorHora);
			case "Cardiologista":
				return new Cardiologista(nome, CRM, valorHora);
			case "Dermatologista":
				return new Dermatologista(nome, CRM, valorHora);
			case "Endocrinologista":
				return new Endocrinologista(nome, CRM, valorHora);
			case "Ginecologia":
				return new Ginecologia(nome, CRM, valorHora);
			case "Neurologista":
				return new Neurologista(nome, CRM, valorHora);
			case "Obstetra":
				return new Obstetra(nome, CRM, valorHora);
			case "Ortopedista":
				return new Ortopedista(nome, CRM, valorHora);
			case "Otorrinolaringologista":
				return new Otorrinolaringologista(nome, CRM, valorHora);
			default:
				return null;
		}
	}
}