package Dao.Patient;

import java.sql.Date;
import java.sql.SQLException;
import java.util.List;

import Entities.Person.Address;
import Entities.Person.Patient.HealthInsurance;
import Entities.Person.Patient.Patient;

public class PatientTeste {
  public static void main(String[] args) {
    try {
      // Criando um novo objeto PatientDao
      PatientDao patientDao = new PatientDao();

      // Criando um novo paciente
      Date birthDate = Date.valueOf("2000-01-01");
      Address address = new Address(1, "Rua 12", 123, 777950, "centro");
      HealthInsurance healthInsurance = new HealthInsurance(1, "Unimed", 100.0);
      Patient newPatient = new Patient(5, "João", birthDate, address, 1234567890, healthInsurance);

      // Inserindo o paciente no banco de dados
      patientDao.createPatient(newPatient);

      // Recuperando um paciente pelo ID
      Patient retrievedPatient = patientDao.readPatient(1);
      System.out.println("Paciente recuperado: " + retrievedPatient);

      // Atualizando o paciente
      retrievedPatient.setName("José");
      patientDao.updatePatient(retrievedPatient);

      // Recuperando todos os pacientes
      List<Patient> allPatients = patientDao.getAllPatients();
      System.out.println("Todos os pacientes:");
      for (Patient patient : allPatients) {
        System.out.println(patient);
      }

      // Deletando o paciente
      patientDao.deletePatient(1);

      // Recuperando todos os pacientes novamente após a exclusão
      allPatients = patientDao.getAllPatients();
      System.out.println("Todos os pacientes após exclusão:");
      for (Patient patient : allPatients) {
        System.out.println(patient);
      }
    } catch (ClassNotFoundException | SQLException e) {
      e.printStackTrace();
    }
  }
}
