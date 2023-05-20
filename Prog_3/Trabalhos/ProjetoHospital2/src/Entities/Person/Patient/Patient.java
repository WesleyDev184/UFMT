package Entities.Person.Patient;

import Entities.Person.Address;
import Entities.Person.Person;

public class Patient extends Person {
  private String CPF;
  private HealthInsurance healthInsurance;

  public Patient(String name, String birthDate, Address address, String CPF, HealthInsurance healthInsurance) {
    super(name, birthDate, address);
    this.CPF = CPF;
    this.healthInsurance = healthInsurance;
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

  @Override
  public String toString() {
    return "Patient [CPF=" + CPF + ", healthInsurance=" + healthInsurance
        + ", toString()=" + toString() + "]";
  }
}