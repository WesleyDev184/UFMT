package testes;

import java.sql.Date;
import java.sql.SQLException;
import java.util.List;

import Dao.HospitalCare.MedicalProcedures.MedicalProceduresDao;
import Dao.HospitalCare.MedicalProcedures.ProcedureTypeDao;
import Dao.HospitalCare.MedicalProcedures.RoomDao;
import Dao.Person.Doctor.DoctorDao;
import Dao.Person.Patient.PatientDao;
import Entities.HospitalCare.MedicalProcedures.MedicalProcedures;
import Entities.HospitalCare.MedicalProcedures.ProcedureType;
import Entities.HospitalCare.MedicalProcedures.Room;
import Entities.Person.Doctor.Doctor;
import Entities.Person.Patient.Patient;

public class MedicalProceduresDaoTeste {
  public static void main(String[] args) {
    try {

      PatientDao patientDao = new PatientDao();
      DoctorDao doctorDao = new DoctorDao();
      RoomDao roomDao = new RoomDao();
      ProcedureTypeDao procedureTypeDao = new ProcedureTypeDao();

      // Criação de objetos necessários para testar o DAO
      Patient patient = patientDao.getById(1);

      Doctor doctor = doctorDao.getById(1);

      Room room = roomDao.getById(1);

      ProcedureType procedureType = procedureTypeDao.getById(1);

      Date date = Date.valueOf("2023-05-21");
      int duration = 120;

      // Criação de um objeto de NeuroSurgery
      // NeuroSurgery neuroSurgery = new NeuroSurgery(0, patient, doctor, date,
      // duration, procedureType.getCost(), room,
      // procedureType);

      // // Criação de um objeto de Pharyngoplasty
      // Pharyngoplasty pharyngoplasty = new Pharyngoplasty(0, patient, doctor, date,
      // duration, procedureType.getCost(),
      // room,
      // procedureType);

      // // Inserção dos objetos no banco de dados
      MedicalProceduresDao dao = new MedicalProceduresDao();
      // dao.insert(neuroSurgery);
      // dao.insert(pharyngoplasty);

      // Recuperação de todos os procedimentos médicos do banco de dados
      List<MedicalProcedures> medicalProcedures = dao.getAll();

      MedicalProcedures medicalProcedure = dao.getById(2);
      System.out.println(medicalProcedure);

      // // Exibição dos procedimentos médicos recuperados
      // for (MedicalProcedures medicalProcedure : medicalProcedures) {
      // System.out.println(medicalProcedure);
      // }
    } catch (ClassNotFoundException | SQLException e) {
      e.printStackTrace();
    }
  }
}
