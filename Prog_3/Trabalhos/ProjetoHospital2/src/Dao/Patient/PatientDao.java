package Dao.Patient;

import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import Connection.CreateConnection;
import Entities.Person.Address;
import Entities.Person.Patient.HealthInsurance;
import Entities.Person.Patient.Patient;

public class PatientDao {
  private Connection connection;

  public PatientDao() throws ClassNotFoundException, SQLException {
    this.connection = CreateConnection.getConnection();
  }

  public void createPatient(Patient patient) throws SQLException {
    String query = "INSERT INTO patients (name, birth_date, cpf, address_id, health_insurance_id) VALUES (?, ?, ?, ?, ?)";
    try (PreparedStatement statement = connection.prepareStatement(query)) {
      statement.setString(1, patient.getName());
      statement.setDate(2, patient.getBirthDate());
      statement.setInt(3, patient.getCPF());
      statement.setInt(4, patient.getAddress().getId());
      statement.setInt(5, patient.getHealthInsurance().getId());
      statement.executeUpdate();
    }
  }

  public Patient readPatient(int id) throws SQLException {
    String query = "SELECT p.id, p.name, p.birth_date, p.cpf, a.id AS address_id, a.public_place, a.number, a.cep, a.neighborhood, "
        +
        "hi.id AS health_insurance_id, hi.name AS health_insurance_name, hi.monthly_payment " +
        "FROM patients p " +
        "JOIN addresses a ON p.address_id = a.id " +
        "JOIN health_insurances hi ON p.health_insurance_id = hi.id " +
        "WHERE p.id = ?";
    try (PreparedStatement statement = connection.prepareStatement(query)) {
      statement.setInt(1, id);
      try (ResultSet resultSet = statement.executeQuery()) {
        if (resultSet.next()) {
          int patientId = resultSet.getInt("id");
          String name = resultSet.getString("name");
          Date birthDate = resultSet.getDate("birth_date");
          int cpf = resultSet.getInt("cpf");

          int addressId = resultSet.getInt("address_id");
          String publicPlace = resultSet.getString("public_place");
          int number = resultSet.getInt("number");
          int cep = resultSet.getInt("cep");
          String neighborhood = resultSet.getString("neighborhood");
          Address address = new Address(addressId, publicPlace, number, cep, neighborhood);

          int insuranceId = resultSet.getInt("health_insurance_id");
          String insuranceName = resultSet.getString("health_insurance_name");
          double monthlyPayment = resultSet.getDouble("monthly_payment");
          HealthInsurance healthInsurance = new HealthInsurance(insuranceId, insuranceName, monthlyPayment);

          return new Patient(patientId, name, birthDate, address, cpf, healthInsurance);
        } else {
          return null; // Patient not found
        }
      }
    }
  }

  public void updatePatient(Patient patient) throws SQLException {
    String query = "UPDATE patients SET name = ?, birth_date = ?, cpf = ?, address_id = ?, health_insurance_id = ? WHERE id = ?";
    try (PreparedStatement statement = connection.prepareStatement(query)) {
      statement.setString(1, patient.getName());
      statement.setDate(2, patient.getBirthDate());
      statement.setInt(3, patient.getCPF());
      statement.setInt(4, patient.getAddress().getId());
      statement.setInt(5, patient.getHealthInsurance().getId());
      statement.setInt(6, patient.getId());
      statement.executeUpdate();
    }
  }

  public void deletePatient(int id) throws SQLException {
    String query = "DELETE FROM patients WHERE id = ?";
    try (PreparedStatement statement = connection.prepareStatement(query)) {
      statement.setInt(1, id);
      statement.executeUpdate();
    }
  }

  public List<Patient> getAllPatients() throws SQLException {
    List<Patient> patients = new ArrayList<>();
    String query = "SELECT p.id, p.name, p.birth_date, p.cpf, a.id AS address_id, a.public_place, a.number, a.cep, a.neighborhood, "
        +
        "hi.id AS health_insurance_id, hi.name AS health_insurance_name, hi.monthly_payment " +
        "FROM patients p " +
        "JOIN addresses a ON p.address_id = a.id " +
        "JOIN health_insurances hi ON p.health_insurance_id = hi.id";
    try (PreparedStatement statement = connection.prepareStatement(query);
        ResultSet resultSet = statement.executeQuery()) {
      while (resultSet.next()) {
        int patientId = resultSet.getInt("id");
        String name = resultSet.getString("name");
        Date birthDate = resultSet.getDate("birth_date");
        int cpf = resultSet.getInt("cpf");

        int addressId = resultSet.getInt("address_id");
        String publicPlace = resultSet.getString("public_place");
        int number = resultSet.getInt("number");
        int cep = resultSet.getInt("cep");
        String neighborhood = resultSet.getString("neighborhood");
        Address address = new Address(addressId, publicPlace, number, cep, neighborhood);

        int insuranceId = resultSet.getInt("health_insurance_id");
        String insuranceName = resultSet.getString("health_insurance_name");
        double monthlyPayment = resultSet.getDouble("monthly_payment");
        HealthInsurance healthInsurance = new HealthInsurance(insuranceId, insuranceName, monthlyPayment);

        Patient patient = new Patient(patientId, name, birthDate, address, cpf, healthInsurance);
        patients.add(patient);
      }
    }
    return patients;
  }
}
