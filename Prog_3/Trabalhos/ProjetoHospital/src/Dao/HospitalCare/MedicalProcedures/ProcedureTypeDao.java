package Dao.HospitalCare.MedicalProcedures;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import Connection.CreateConnection;
import Entities.HospitalCare.MedicalProcedures.ProcedureType;

public class ProcedureTypeDao {
  private Connection connection;

  public ProcedureTypeDao() throws ClassNotFoundException, SQLException {
    // Obter uma conexão com o banco de dados
    connection = CreateConnection.getConnection();
  }

  public void insert(ProcedureType procedureType) throws SQLException {
    String query = "INSERT INTO procedure_types (name, cost) VALUES (?, ?)";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setString(1, procedureType.getName());
    statement.setDouble(2, procedureType.getCost());
    statement.executeUpdate();
  }

  public ProcedureType getById(int id) throws SQLException {
    String query = "SELECT * FROM procedure_types WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, id);
    ResultSet resultSet = statement.executeQuery();

    if (resultSet.next()) {
      ProcedureType procedureType = createProcedureTypeFromResultSet(resultSet);
      return procedureType;
    }

    return null; // Tipo de procedimento não encontrado
  }

  public List<ProcedureType> getAll() throws SQLException {
    String query = "SELECT * FROM procedure_types";
    PreparedStatement statement = connection.prepareStatement(query);
    ResultSet resultSet = statement.executeQuery();

    List<ProcedureType> procedureTypes = new ArrayList<>();

    while (resultSet.next()) {
      ProcedureType procedureType = createProcedureTypeFromResultSet(resultSet);
      procedureTypes.add(procedureType);
    }

    return procedureTypes;
  }

  public void update(ProcedureType procedureType) throws SQLException {
    String query = "UPDATE procedure_types SET name = ?, cost = ? WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setString(1, procedureType.getName());
    statement.setDouble(2, procedureType.getCost());
    statement.setInt(3, procedureType.getId());
    statement.executeUpdate();
  }

  public void delete(int id) throws SQLException {
    String query = "DELETE FROM procedure_types WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, id);
    statement.executeUpdate();
  }

  private ProcedureType createProcedureTypeFromResultSet(ResultSet resultSet) throws SQLException {
    int id = resultSet.getInt("id");
    String name = resultSet.getString("name");
    double cost = resultSet.getDouble("cost");

    ProcedureType procedureType = new ProcedureType(id, name, cost);
    return procedureType;
  }
}