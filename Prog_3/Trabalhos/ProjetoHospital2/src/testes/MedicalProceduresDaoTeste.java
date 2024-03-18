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
      // Cria uma instância do MedicalProceduresDao
      MedicalProceduresDao dao = new MedicalProceduresDao();
      PatientDao patientDao = new PatientDao();
      DoctorDao doctorDao = new DoctorDao();
      RoomDao roomDao = new RoomDao();
      ProcedureTypeDao procedureTypeDao = new ProcedureTypeDao();

      // Cria objetos Patient, Doctor, Room e ProcedureType para teste
      Patient patient = patientDao.getById(1);
      Doctor doctor = doctorDao.getById(1);
      Room room = roomDao.getById(1);
      ProcedureType procedureType = procedureTypeDao.getById(1);

      // Cria um objeto Date para teste
      Date date = new Date(2020, 10, 10);

      // Cria um novo MedicalProcedure
      // MedicalProcedures newProcedure = new MedicalProcedures(0, patient, doctor,
      // date, 115, room,
      // procedureType);

      // // Insere o novo MedicalProcedure no banco de dados
      // dao.insert(newProcedure);
      // System.out.println("MedicalProcedure inserido com sucesso!");

      // Obtém um MedicalProcedure pelo ID
      MedicalProcedures retrievedProcedure = dao.getMedicalProcedureById(5);
      // Atualiza o MedicalProcedure
      System.out.println("MedicalProcedure encontrado: " + retrievedProcedure);

      retrievedProcedure.setDuration(60); // Atualiza a duração para 60 minutos
      dao.updateMedicalProcedure(retrievedProcedure);
      System.out.println("MedicalProcedure atualizado com sucesso!");
      // Obtém todos os MedicalProcedures
      List<MedicalProcedures> allProcedures = dao.getAll();
      System.out.println("Lista de MedicalProcedures:");
      for (MedicalProcedures procedure : allProcedures) {
        System.out.println(procedure);
      }
      // Exclui o MedicalProcedure
      dao.deleteMedicalProcedure(4);
      System.out.println("MedicalProcedure excluído com sucesso!");
    } catch (ClassNotFoundException | SQLException e) {
      e.printStackTrace();
    }
  }
}
