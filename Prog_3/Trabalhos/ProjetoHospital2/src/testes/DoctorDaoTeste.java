package testes;

import java.sql.Date;
import java.sql.SQLException;

import Dao.Person.AddressDao;
import Dao.Person.Doctor.DoctorDao;
import Dao.Person.Doctor.SpecialtyDao;
import Entities.Person.Address;
import Entities.Person.Doctor.Doctor;
import Entities.Person.Doctor.Specialty;

public class DoctorDaoTeste {
  public static void main(String[] args) throws ClassNotFoundException, SQLException {

    DoctorDao doctorDao = new DoctorDao();
    AddressDao addressDao = new AddressDao();
    SpecialtyDao specialtyDao = new SpecialtyDao();

    Specialty specialty = specialtyDao.getById(2);

    // criar um endereço
    Address address = addressDao.getById(12);

    Date date = Date.valueOf("1980-01-01");

    // criar um médico
    Doctor doctor = new Doctor(1, "Dr. House", date, address, "123456", specialty, 100.0);
    doctorDao.insert(doctor);

    // Obter um médico por ID

    Doctor retrievedDoctor = doctorDao.getById(1);
    System.out.println("Médico recuperado: " + retrievedDoctor);

    // Atualizar um médico
    retrievedDoctor.setName("Dr. House");
    doctorDao.update(retrievedDoctor);

    // Obter todos os médicos
    System.out.println("Todos os médicos:");
    for (Doctor doc : doctorDao.getAll()) {
      System.out.println(doc);
    }

    // // Deletar um médico
    // doctorDao.delete(1);

  }
}
