package Entities.Person.Patient;

import java.sql.Date;

import Entities.Person.Address;
import Entities.Person.Person;

public class Patient extends Person {
  private int id;
  private String CPF;
  private HealthInsurance healthInsurance;

  public Patient(int id, String name, Date birthDate, Address address, String CPF, HealthInsurance healthInsurance) {
    super(name, birthDate, address);
    this.id = id;
    this.CPF = CPF;
    this.healthInsurance = healthInsurance;
  }

  public void setId(int id) {
    this.id = id;
  }

  public int getId() {
    return id;
  }

  public String getCPF() {
    return CPF;
  }

  public void setCPF(String CPF) {
    this.CPF = CPF;
  }

  public HealthInsurance getHealthInsurance() {
    return healthInsurance;
  }

  public void setHealthInsurance(HealthInsurance healthInsurance) {
    this.healthInsurance = healthInsurance;
  }

  public String getHealthInsuranceName() {
    if (healthInsurance != null) {
      return healthInsurance.getHealthInsuranceName(); // Supondo que o nome do seguro de saúde seja obtido através do
    } else {
      return ""; // Retornar uma string vazia caso o seguro de saúde seja nulo
    }
  }

  @Override
  public String toString() {
    return getName();
  }
}