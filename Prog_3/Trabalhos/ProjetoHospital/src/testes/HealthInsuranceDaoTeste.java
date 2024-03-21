package testes;

import java.sql.SQLException;
import java.util.List;

import Dao.Person.Patient.HealthInsuranceDao;
import Entities.Person.Patient.HealthInsurance;

public class HealthInsuranceDaoTeste {
  public static void main(String[] args) throws ClassNotFoundException, SQLException {
    HealthInsuranceDao healthInsuranceDAO = new HealthInsuranceDao();

    try {
      // Obter um plano de saúde por ID
      HealthInsurance retrievedHealthInsurance = healthInsuranceDAO.getById(1);
      System.out.println("Plano de saúde recuperado: " + retrievedHealthInsurance);

      // Atualizar um plano de saúde
      retrievedHealthInsurance.setHealthInsuranceName("Plano B");
      healthInsuranceDAO.update(retrievedHealthInsurance);
      System.out.println("Plano de saúde atualizado com sucesso!");

      // Obter todos os planos de saúde
      List<HealthInsurance> allHealthInsurances = healthInsuranceDAO.getAll();
      System.out.println("Todos os planos de saúde:");
      for (HealthInsurance insurance : allHealthInsurances) {
        System.out.println(insurance);
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
