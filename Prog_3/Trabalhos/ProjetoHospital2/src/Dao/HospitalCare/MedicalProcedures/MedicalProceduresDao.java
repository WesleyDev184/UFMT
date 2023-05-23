package Dao.HospitalCare.MedicalProcedures;

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
import Entities.HospitalCare.MedicalProcedures.MedicalProcedures;
import Entities.HospitalCare.MedicalProcedures.NeuroSurgery;
import Entities.HospitalCare.MedicalProcedures.Pharyngoplasty;
import Entities.HospitalCare.MedicalProcedures.ProcedureType;
import Entities.HospitalCare.MedicalProcedures.Room;
import Entities.Person.Doctor.Doctor;
import Entities.Person.Patient.Patient;

public class MedicalProceduresDao {
  private Connection connection;
  private RoomDao roomDao;
  private ProcedureTypeDao procedureTypeDao;
  private PatientDao patientDao;
  private DoctorDao doctorDao;

  public MedicalProceduresDao() throws ClassNotFoundException, SQLException {
    // Obter uma conexão com o banco de dados
    connection = CreateConnection.getConnection();
    roomDao = new RoomDao();
    patientDao = new PatientDao();
    doctorDao = new DoctorDao();
    procedureTypeDao = new ProcedureTypeDao();
  }

  public void insert(MedicalProcedures medicalProcedure) throws SQLException {
    String query = "INSERT INTO medical_procedures (patient_id, doctor_id, date, duration, room_id, procedure_type_id) VALUES (?, ?, ?, ?, ?, ?)";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, medicalProcedure.getPatient().getId());
    statement.setInt(2, medicalProcedure.getDoctor().getId());
    statement.setDate(3, medicalProcedure.getDate());
    statement.setInt(4, medicalProcedure.getDuration());
    statement.setInt(5, medicalProcedure.getRoom().getId());
    statement.setInt(6, medicalProcedure.getProcedureType().getId());
    statement.executeUpdate();
  }

  public MedicalProcedures getById(int id) throws SQLException, ClassNotFoundException {
    String query = "SELECT * FROM medical_procedures WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, id);
    ResultSet resultSet = statement.executeQuery();

    if (resultSet.next()) {
      MedicalProcedures medicalProcedure = createMedicalProcedureFromResultSet(resultSet);
      return medicalProcedure;
    }

    return null; // Procedimento médico não encontrado
  }

  public List<MedicalProcedures> getAll() throws SQLException, ClassNotFoundException {
    String query = "SELECT * FROM medical_procedures";
    PreparedStatement statement = connection.prepareStatement(query);
    ResultSet resultSet = statement.executeQuery();

    List<MedicalProcedures> medicalProcedures = new ArrayList<>();

    while (resultSet.next()) {
      MedicalProcedures medicalProcedure = createMedicalProcedureFromResultSet(resultSet);
      medicalProcedures.add(medicalProcedure);
    }

    return medicalProcedures;
  }

  public void update(MedicalProcedures medicalProcedure) throws SQLException {
    String query = "UPDATE medical_procedures SET patient_id = ?, doctor_id = ?, date = ?, duration = ?, room_id = ?, procedure_type_id = ? WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, medicalProcedure.getPatient().getId());
    statement.setInt(2, medicalProcedure.getDoctor().getId());
    statement.setDate(3, medicalProcedure.getDate());
    statement.setInt(4, medicalProcedure.getDuration());
    statement.setInt(5, medicalProcedure.getRoom().getId());
    statement.setInt(6, medicalProcedure.getProcedureType().getId());
    statement.setInt(7, medicalProcedure.getId());
    statement.executeUpdate();
  }

  public void delete(int id) throws SQLException {
    String query = "DELETE FROM medical_procedures WHERE id = ?";
    PreparedStatement statement = connection.prepareStatement(query);
    statement.setInt(1, id);
    statement.executeUpdate();
  }

  private MedicalProcedures createMedicalProcedureFromResultSet(ResultSet resultSet)
      throws SQLException, ClassNotFoundException {
    int id = resultSet.getInt("id");
    int patientId = resultSet.getInt("patient_id");
    Patient patient = patientDao.getById(patientId);

    int doctorId = resultSet.getInt("doctor_id");
    Doctor doctor = doctorDao.getById(doctorId);

    Date date = resultSet.getDate("date");
    int duration = resultSet.getInt("duration");

    int roomId = resultSet.getInt("room_id");
    int procedureTypeId = resultSet.getInt("procedure_type_id");

    Room room = roomDao.getById(roomId);
    ProcedureType procedureType = procedureTypeDao.getById(procedureTypeId);

    // Determinar o tipo de procedimento médico com base no tipo
    // do objeto ProcedureType recuperado do banco de dados
    if (procedureType.getName().equals("NeuroSurgery")) {
      return new NeuroSurgery(id, patient, doctor, date, duration, procedureType.getCost(), room, procedureType);
    } else if (procedureType.getName().equals("Pharyngoplasty")) {
      return new Pharyngoplasty(id, patient, doctor, date, duration, procedureType.getCost(), room, procedureType);
    } else {
      throw new IllegalArgumentException("Tipo de procedimento médico inválido");
    }
  }
}
