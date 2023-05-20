package Entities.Person.Patient;

import java.sql.Date;

import Entities.Person.Address;
import Entities.Person.Person;

public class Patient extends Person {
  private int id;
  private int CPF;
  private HealthInsurance healthInsurance;

  public Patient(int id, String name, Date birthDate, Address address, int CPF, HealthInsurance healthInsurance) {
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

  public int getCPF() {
    return CPF;
  }

  public void setCPF(int CPF) {
    this.CPF = CPF;
  }

  public HealthInsurance getHealthInsurance() {
    return healthInsurance;
  }

  public void setHealthInsurance(HealthInsurance healthInsurance) {
    this.healthInsurance = healthInsurance;
  }

  @Override
  public String toString() {
    return "Patient [CPF=" + CPF + ", healthInsurance=" + healthInsurance
        + ", toString()=" + toString() + "]";
  }
}