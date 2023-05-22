package testes;

import java.sql.SQLException;
import java.util.List;

import Dao.Person.AddressDao;
import Dao.Person.Patient.HealthInsuranceDao;
import Dao.Person.Patient.PatientDao;
import Entities.Person.Patient.Patient;

public class PatientDaoTeste {
  public static void main(String[] args) throws ClassNotFoundException, SQLException {
    PatientDao patientDao = new PatientDao();
    HealthInsuranceDao healthInsuranceDao = new HealthInsuranceDao();
    AddressDao addressDao = new AddressDao();

    try {
      // Buscar um plano de saúde por ID
      // HealthInsurance healthInsurance = healthInsuranceDao.getById(1);

      // // criar um endereço
      // Address address = new Address(0, "Rua teste", 1666, 77950123, "centro");
      // addressDao.create(address);
      // Address patientAddress = addressDao.getById(11);

      // Date birthDate = Date.valueOf("1990-01-01");

      // // Criar um paciente
      // Patient patient = new Patient(0, "John Doe", birthDate, patientAddress,
      // 12345678901L, healthInsurance);
      // patientDao.insert(patient);

      // Obter um paciente por ID
      Patient retrievedPatient = patientDao.getById(6);
      System.out.println("Paciente recuperado: " + retrievedPatient);

      // // Atualizar o nome do paciente
      // retrievedPatient.setName("Jane Doe");
      // patientDao.update(retrievedPatient);
      // System.out.println("Paciente atualizado com sucesso!");

      // Obter todos os pacientes
      List<Patient> allPatients = patientDao.getAll();
      System.out.println("Todos os pacientes:");
      for (Patient p : allPatients) {
        System.out.println(p);
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
