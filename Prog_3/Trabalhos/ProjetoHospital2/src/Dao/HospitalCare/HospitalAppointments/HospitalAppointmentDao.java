package Dao.HospitalCare.HospitalAppointments;

import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import Connection.CreateConnection;
import Dao.Person.Doctor.DoctorDao;
import Dao.Person.Patient.PatientDao;
import Entities.HospitalCare.HospitalAppointments.HospitalAppointment;
import Entities.Person.Doctor.Doctor;
import Entities.Person.Patient.Patient;

public class HospitalAppointmentDao {
  private Connection connection;
  private PatientDao patientDao;
  private DoctorDao doctorDao;

  public HospitalAppointmentDao() throws ClassNotFoundException, SQLException {
    // Obter uma conexão com o banco de dados
    connection = CreateConnection.getConnection();
    patientDao = new PatientDao();
    doctorDao = new DoctorDao();
  }

  public void insert(HospitalAppointment appointment) throws SQLException {
    String query = "INSERT INTO hospital_appointments (appointment_date, patient_id, doctor_id) VALUES (?, ?, ?)";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setDate(1, appointment.getDate());
    statement.setInt(2, appointment.getPatient().getId());
    statement.setInt(3, appointment.getDoctor().getId());
    statement.executeUpdate();
  }

  public List<HospitalAppointment> getAll() throws SQLException, ClassNotFoundException {
    String query = "SELECT * FROM hospital_appointments";
    PreparedStatement statement = connection.prepareStatement(query);
    ResultSet resultSet = statement.executeQuery();

    List<HospitalAppointment> appointments = new ArrayList<>();

    while (resultSet.next()) {
      HospitalAppointment appointment = createAppointmentFromResultSet(resultSet);
      appointments.add(appointment);
    }

    return appointments;
  }

  public List<HospitalAppointment> getByPatientId(int patientId) throws SQLException, ClassNotFoundException {
    String query = "SELECT * FROM hospital_appointments WHERE patient_id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, patientId);
    ResultSet resultSet = statement.executeQuery();

    List<HospitalAppointment> appointments = new ArrayList<>();

    while (resultSet.next()) {
      HospitalAppointment appointment = createAppointmentFromResultSet(resultSet);
      appointments.add(appointment);
    }

    return appointments;
  }

  public List<HospitalAppointment> getByDoctorId(int doctorId) throws SQLException, ClassNotFoundException {
    String query = "SELECT * FROM hospital_appointments WHERE doctor_id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, doctorId);
    ResultSet resultSet = statement.executeQuery();

    List<HospitalAppointment> appointments = new ArrayList<>();

    while (resultSet.next()) {
      HospitalAppointment appointment = createAppointmentFromResultSet(resultSet);
      appointments.add(appointment);
    }

    return appointments;
  }

  private HospitalAppointment createAppointmentFromResultSet(ResultSet resultSet)
      throws SQLException, ClassNotFoundException {
    int appointmentId = resultSet.getInt("id");
    Date date = resultSet.getDate("appointment_date");
    int patientId = resultSet.getInt("patient_id");
    int doctorId = resultSet.getInt("doctor_id");

    Patient patient = patientDao.getById(patientId);
    Doctor doctor = doctorDao.getById(doctorId);

    HospitalAppointment appointment = new HospitalAppointment(appointmentId, date, patient, doctor);
    return appointment;
  }
}
