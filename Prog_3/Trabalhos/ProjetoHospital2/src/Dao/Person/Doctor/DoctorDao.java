package Dao.Person.Doctor;

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
import Entities.Person.Doctor.Doctor;
import Entities.Person.Doctor.Specialty;

public class DoctorDao {
  private Connection connection;
  private SpecialtyDao specialtyDao;

  public DoctorDao() throws ClassNotFoundException, SQLException {
    // Obter uma conexão com o banco de dados
    connection = CreateConnection.getConnection();
    specialtyDao = new SpecialtyDao();
  }

  public void insert(Doctor doctor) throws SQLException {
    String query = "INSERT INTO doctors (name, birth_date, address_id, crm, specialty_id, timeValue) VALUES (?, ?, ?, ?, ?, ?)";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setString(1, doctor.getName());
    statement.setDate(2, doctor.getBirthDate());
    statement.setInt(3, doctor.getAddress().getId());
    statement.setString(4, doctor.getCrm());
    statement.setInt(5, doctor.getSpecialty().getId());
    statement.setDouble(6, doctor.getTimeValue());
    statement.executeUpdate();
  }

  public Doctor getById(int id) throws SQLException, ClassNotFoundException {
    String query = "SELECT * FROM doctors WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, id);
    ResultSet resultSet = statement.executeQuery();

    if (resultSet.next()) {
      Doctor doctor = createDoctorFromResultSet(resultSet);
      return doctor;
    }

    return null; // Médico não encontrado
  }

  public List<Doctor> getAll() throws SQLException, ClassNotFoundException {
    String query = "SELECT * FROM doctors";
    PreparedStatement statement = connection.prepareStatement(query);
    ResultSet resultSet = statement.executeQuery();

    List<Doctor> doctors = new ArrayList<>();

    while (resultSet.next()) {
      Doctor doctor = createDoctorFromResultSet(resultSet);
      doctors.add(doctor);
    }

    return doctors;
  }

  public void update(Doctor doctor) throws SQLException {
    String query = "UPDATE doctors SET name = ?, birth_date = ?, address_id = ?, crm = ?, specialty_id = ?, timeValue = ? WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setString(1, doctor.getName());
    statement.setDate(2, doctor.getBirthDate());
    statement.setInt(3, doctor.getAddress().getId());
    statement.setString(4, doctor.getCrm());
    statement.setInt(5, doctor.getSpecialty().getId());
    statement.setDouble(6, doctor.getTimeValue());
    statement.setInt(7, doctor.getId());
    statement.executeUpdate();
  }

  public void delete(int id) throws SQLException {
    String query = "DELETE FROM doctors WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, id);
    statement.executeUpdate();
  }

  private Doctor createDoctorFromResultSet(ResultSet resultSet) throws SQLException, ClassNotFoundException {
    int id = resultSet.getInt("id");
    String name = resultSet.getString("name");
    Date dateOfBirth = resultSet.getDate("birth_date");
    String crm = resultSet.getString("crm");
    double timeValue = resultSet.getDouble("timeValue");
    int specialtyId = resultSet.getInt("specialty_id");
    int addressId = resultSet.getInt("address_id");

    AddressDao addressDao = new AddressDao();
    Address address = addressDao.getById(addressId);

    Specialty specialty = specialtyDao.getById(specialtyId);

    Doctor doctor = new Doctor(id, name, dateOfBirth, address, crm, specialty, timeValue);
    return doctor;
  }
}
