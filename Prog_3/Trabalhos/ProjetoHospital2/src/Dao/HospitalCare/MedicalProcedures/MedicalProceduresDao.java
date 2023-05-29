package Dao.HospitalCare.MedicalProcedures;

import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import Connection.CreateConnection;
import Dao.Person.Doctor.DoctorDao;
import Dao.Person.Patient.PatientDao;
import Entities.HospitalCare.MedicalProcedures.MedicalProcedures;
import Entities.HospitalCare.MedicalProcedures.ProcedureType;
import Entities.HospitalCare.MedicalProcedures.Room;
import Entities.Person.Doctor.Doctor;
import Entities.Person.Patient.Patient;

public class MedicalProceduresDao {
  private Connection connection;
  private ProcedureTypeDao procedureTypeDao;
  private RoomDao roomDao;
  private PatientDao patientDao;
  private DoctorDao doctorDao;

  public MedicalProceduresDao() throws ClassNotFoundException, SQLException {
    connection = CreateConnection.getConnection();
    procedureTypeDao = new ProcedureTypeDao();
    roomDao = new RoomDao();
    patientDao = new PatientDao();
    doctorDao = new DoctorDao();
  }

  public void insert(MedicalProcedures procedure) throws SQLException {
    String query = "INSERT INTO medical_procedures (patient_id, doctor_id, date, duration, room_id, procedure_type_id) "
        +
        "VALUES (?, ?, ?, ?, ?, ?)";

    try (PreparedStatement statement = connection.prepareStatement(query)) {
      statement.setInt(1, procedure.getPatient().getId());
      statement.setInt(2, procedure.getDoctor().getId());
      statement.setDate(3, procedure.getDate());
      statement.setInt(4, procedure.getDuration());
      statement.setInt(5, procedure.getRoom().getId());
      statement.setInt(6, procedure.getProcedureType().getId());

      statement.executeUpdate();
    }
  }

  public void updateMedicalProcedure(MedicalProcedures procedure) throws SQLException {
    String query = "UPDATE medical_procedures SET patient_id = ?, doctor_id = ?, date = ?, duration = ?, room_id = ?, procedure_type_id = ? "
        +
        "WHERE id = ?";

    try (PreparedStatement statement = connection.prepareStatement(query)) {
      statement.setInt(1, procedure.getPatient().getId());
      statement.setInt(2, procedure.getDoctor().getId());
      statement.setDate(3, procedure.getDate());
      statement.setInt(4, procedure.getDuration());
      statement.setInt(5, procedure.getRoom().getId());
      statement.setInt(6, procedure.getProcedureType().getId());
      statement.setInt(7, procedure.getId());

      statement.executeUpdate();
    }
  }

  public void deleteMedicalProcedure(int id) throws SQLException {
    String query = "DELETE FROM medical_procedures WHERE id = ?";

    try (PreparedStatement statement = connection.prepareStatement(query)) {
      statement.setInt(1, id);
      statement.executeUpdate();
    }
  }

  public MedicalProcedures getMedicalProcedureById(int id) throws SQLException, ClassNotFoundException {
    String query = "SELECT * FROM medical_procedures WHERE id = ?";

    try {
      PreparedStatement statement = connection.prepareStatement(query);
      statement.setInt(1, id);
      ResultSet resultSet = statement.executeQuery();

      if (resultSet.next()) {
        return createMedicalProcedureFromResultSet(resultSet);
      }
    } catch (Exception e) {
      System.out.println(e.getMessage());
    }

    return null;
  }

  public List<MedicalProcedures> getAllMedicalProcedures() throws SQLException, ClassNotFoundException {
    List<MedicalProcedures> procedures = new ArrayList<>();
    String query = "SELECT * FROM medical_procedures";

    try (Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery(query)) {
      while (resultSet.next()) {
        MedicalProcedures procedure = createMedicalProcedureFromResultSet(resultSet);
        procedures.add(procedure);
      }
    }

    return procedures;
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

    return new MedicalProcedures(id, patient, doctor, date, duration, room, procedureType);
  }
}