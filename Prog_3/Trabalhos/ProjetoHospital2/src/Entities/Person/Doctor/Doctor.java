package Entities.Person.Doctor;

import java.sql.Date;

import Entities.Person.Address;
import Entities.Person.Person;

public class Doctor extends Person {
  private int id;
  private String crm;
  private Specialty specialty;
  private double timeValue;

  public Doctor(int id, String name, Date dateOfBirth, Address address, String crm,
      Specialty specialty, double timeValue) {
    super(name, dateOfBirth, address);
    this.id = id;
    this.crm = crm;
    this.specialty = specialty;
    this.timeValue = timeValue;
  }

  public void setId(int id) {
    this.id = id;
  }

  public int getId() {
    return id;
  }

  public String getCrm() {
    return crm;
  }

  public void setCrm(String crm) {
    this.crm = crm;
  }

  public Specialty getSpecialty() {
    return specialty;
  }

  public void setSpecialty(Specialty specialty) {
    this.specialty = specialty;
  }

  public double getTimeValue() {
    return timeValue;
  }

  public void setTimeValue(double timeValue) {
    this.timeValue = timeValue;
  }

  public String operate() {
    return String.format("Doctor %s is operating", getName());
  } // end of method operate

  @Override
  public String toString() {
    return String.format("Name: %s \nDate Of Birth %s \nAddress: %s \nCRM: %s \nSpecialty: %s \nTime Value: %s",
        getName(),
        getBirthDate(), getAddress(), crm, specialty, timeValue);
  }

}