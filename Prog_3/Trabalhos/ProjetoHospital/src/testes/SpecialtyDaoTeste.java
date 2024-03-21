package testes;

import java.sql.SQLException;
import java.util.List;

import Dao.Person.Doctor.SpecialtyDao;
import Entities.Person.Doctor.Specialty;

public class SpecialtyDaoTeste {
  public static void main(String[] args) {
    SpecialtyDao specialtyDao;

    try {
      specialtyDao = new SpecialtyDao();

      // // Inserir uma especialidade
      // Specialty specialty1 = new Specialty(0, "Cardiologia");
      // specialtyDao.insert(specialty1);
      // System.out.println("Especialidade inserida com sucesso!");

      // Obter uma especialidade por ID
      Specialty retrievedSpecialty = specialtyDao.getById(2);
      System.out.println("Especialidade recuperada: " + retrievedSpecialty);

      // // Atualizar uma especialidade
      // retrievedSpecialty.setName("Neurologia");
      // specialtyDao.update(retrievedSpecialty);
      // System.out.println("Especialidade atualizada com sucesso!");

      // Obter todas as especialidades
      List<Specialty> allSpecialties = specialtyDao.getAll();
      System.out.println("Todas as especialidades:");
      for (Specialty specialty : allSpecialties) {
        System.out.println(specialty);
      }

      // // Deletar uma especialidade
      // specialtyDao.delete(1);
      // System.out.println("Especialidade deletada com sucesso!");

    } catch (ClassNotFoundException | SQLException e) {
      e.printStackTrace();
    }
  }
}