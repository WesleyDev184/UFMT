package Dao.Person.Patient;

import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import Connection.CreateConnection;
import Dao.Person.AddressDao;
import Entities.Person.Address;
import Entities.Person.Patient.HealthInsurance;
import Entities.Person.Patient.Patient;

public class PatientDao {
  private Connection connection;

  public PatientDao() throws ClassNotFoundException, SQLException {
    // Obter uma conexão com o banco de dados
    connection = CreateConnection.getConnection();
  }

  public void insert(Patient patient) throws SQLException {
    String query = "INSERT INTO patients (name, birth_date, address_id, CPF, health_insurance_id) VALUES (?, ?, ?, ?, ?)";
    PreparedStatement statement = connection.prepareStatement(query, PreparedStatement.RETURN_GENERATED_KEYS);
    statement.setString(1, patient.getName());
    statement.setDate(2, patient.getBirthDate());
    statement.setInt(3, patient.getAddress().getId());
    statement.setFloat(4, patient.getCPF());
    statement.setInt(5, patient.getHealthInsurance().getId());
    statement.executeUpdate();

    ResultSet generatedKeys = statement.getGeneratedKeys();
    if (generatedKeys.next()) {
      patient.setId(generatedKeys.getInt(1));
    }
  }

  public Patient getById(int id) throws SQLException, ClassNotFoundException {
    String query = "SELECT * FROM patients WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, id);
    ResultSet resultSet = statement.executeQuery();

    if (resultSet.next()) {
      Patient patient = createPatientFromResultSet(resultSet);
      return patient;
    }

    return null; // Paciente não encontrado
  }

  public List<Patient> getAll() throws SQLException, ClassNotFoundException {
    String query = "SELECT * FROM patients";
    PreparedStatement statement = connection.prepareStatement(query);
    ResultSet resultSet = statement.executeQuery();

    List<Patient> patients = new ArrayList<>();

    while (resultSet.next()) {
      Patient patient = createPatientFromResultSet(resultSet);
      patients.add(patient);
    }

    return patients;
  }

  public void update(Patient patient) throws SQLException {
    String query = "UPDATE patients SET name = ?, birth_date = ?, address_id = ?, CPF = ?, health_insurance_id = ? WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setString(1, patient.getName());
    statement.setDate(2, patient.getBirthDate());
    statement.setInt(3, patient.getAddress().getId());
    statement.setFloat(4, patient.getCPF());
    statement.setInt(5, patient.getHealthInsurance().getId());
    statement.setInt(6, patient.getId());
    statement.executeUpdate();
  }

  public void delete(Patient patient) throws SQLException {
    String query = "DELETE FROM patients WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, patient.getId());
    statement.executeUpdate();
  }

  private Patient createPatientFromResultSet(ResultSet resultSet) throws SQLException, ClassNotFoundException {
    int id = resultSet.getInt("id");
    String name = resultSet.getString("name");
    Date birthDate = resultSet.getDate("birth_date");
    int addressId = resultSet.getInt("address_id");
    int CPF = (int) resultSet.getFloat("CPF");
    int healthInsuranceId = resultSet.getInt("health_insurance_id");

    // Obter o objeto Address relacionado
    AddressDao addressDao = new AddressDao();
    Address address = addressDao.getById(addressId);

    // Obter o objeto HealthInsurance relacionado
    HealthInsuranceDao healthInsuranceDao = new HealthInsuranceDao();
    HealthInsurance healthInsurance = healthInsuranceDao.getById(healthInsuranceId);

    Patient patient = new Patient(id, name, birthDate, address, CPF, healthInsurance);
    return patient;
  }
}