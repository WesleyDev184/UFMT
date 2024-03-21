package Dao.Person.Patient;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import Entities.Person.Patient.HealthInsurance;

import Connection.CreateConnection;

public class HealthInsuranceDao {
  private Connection connection;

  public HealthInsuranceDao() throws ClassNotFoundException, SQLException {
    this.connection = CreateConnection.getConnection();
  }

  public void insert(HealthInsurance healthInsurance) throws SQLException {
    String query = "INSERT INTO health_insurances (name, monthly_payment) VALUES (?, ?)";
    try (PreparedStatement statement = connection.prepareStatement(query)) {
      statement.setString(1, healthInsurance.getHealthInsuranceName());
      statement.setDouble(2, healthInsurance.getHealthInsuranceMonthlyPayment());
      statement.executeUpdate();
    }
  }

  public HealthInsurance getById(int id) throws SQLException {
    String query = "SELECT * FROM health_insurances WHERE id = ?";
    try (PreparedStatement statement = connection.prepareStatement(query)) {
      statement.setInt(1, id);
      try (ResultSet resultSet = statement.executeQuery()) {
        if (resultSet.next()) {
          return createHealthInsuranceFromResultSet(resultSet);
        }
      }
    }
    return null;
  }

  public List<HealthInsurance> getAll() throws SQLException {
    List<HealthInsurance> healthInsurances = new ArrayList<>();
    String query = "SELECT * FROM health_insurances";
    try (PreparedStatement statement = connection.prepareStatement(query);
        ResultSet resultSet = statement.executeQuery()) {
      while (resultSet.next()) {
        HealthInsurance healthInsurance = createHealthInsuranceFromResultSet(resultSet);
        healthInsurances.add(healthInsurance);
      }
    }
    return healthInsurances;
  }

  public void update(HealthInsurance healthInsurance) throws SQLException {
    String query = "UPDATE health_insurances SET name = ?, monthly_payment = ? WHERE id = ?";
    try (PreparedStatement statement = connection.prepareStatement(query)) {
      statement.setString(1, healthInsurance.getHealthInsuranceName());
      statement.setDouble(2, healthInsurance.getHealthInsuranceMonthlyPayment());
      statement.setInt(3, healthInsurance.getId());
      statement.executeUpdate();
    }
  }

  public void delete(int id) throws SQLException {
    String query = "DELETE FROM health_insurances WHERE id = ?";
    try (PreparedStatement statement = connection.prepareStatement(query)) {
      statement.setInt(1, id);
      statement.executeUpdate();
    }
  }

  private HealthInsurance createHealthInsuranceFromResultSet(ResultSet resultSet) throws SQLException {
    int id = resultSet.getInt("id");
    String healthInsuranceName = resultSet.getString("name");
    double healthInsuranceMonthlyPayment = resultSet.getDouble("monthly_payment");
    return new HealthInsurance(id, healthInsuranceName, healthInsuranceMonthlyPayment);
  }
}
