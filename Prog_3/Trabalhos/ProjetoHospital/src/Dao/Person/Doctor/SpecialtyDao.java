package Dao.Person.Doctor;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import Connection.CreateConnection;
import Entities.Person.Doctor.Specialty;

public class SpecialtyDao {
  private Connection connection;

  public SpecialtyDao() throws ClassNotFoundException, SQLException {
    // Obter uma conexão com o banco de dados
    connection = CreateConnection.getConnection();
  }

  public void insert(Specialty specialty) throws SQLException {
    String query = "INSERT INTO specialties (name) VALUES (?)";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setString(1, specialty.getName());
    statement.executeUpdate();
  }

  public Specialty getById(int id) throws SQLException {
    String query = "SELECT * FROM specialties WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, id);
    ResultSet resultSet = statement.executeQuery();

    if (resultSet.next()) {
      Specialty specialty = createSpecialtyFromResultSet(resultSet);
      return specialty;
    }

    return null; // Especialidade não encontrada
  }

  public List<Specialty> getAll() throws SQLException {
    String query = "SELECT * FROM specialties";
    PreparedStatement statement = connection.prepareStatement(query);
    ResultSet resultSet = statement.executeQuery();

    List<Specialty> specialties = new ArrayList<>();

    while (resultSet.next()) {
      Specialty specialty = createSpecialtyFromResultSet(resultSet);
      specialties.add(specialty);
    }

    return specialties;
  }

  public void update(Specialty specialty) throws SQLException {
    String query = "UPDATE specialties SET name = ? WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setString(1, specialty.getName());
    statement.setInt(2, specialty.getId());
    statement.executeUpdate();
  }

  public void delete(int id) throws SQLException {
    String query = "DELETE FROM specialties WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, id);
    statement.executeUpdate();
  }

  private Specialty createSpecialtyFromResultSet(ResultSet resultSet) throws SQLException {
    int id = resultSet.getInt("id");
    String name = resultSet.getString("name");

    Specialty specialty = new Specialty(id, name);
    return specialty;
  }
}
