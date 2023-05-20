package Entities.HospitalCare.HospitalAppointments;

import java.sql.Date;

import Entities.Person.Doctor.Doctor;
import Entities.Person.Patient.Patient;

public class HospitalAppointment {

  private Date Date;
  private Patient Patient;
  private Doctor Doctor;

  public HospitalAppointment(Date Date, Patient Patient, Doctor Doctor) {
    this.Date = Date;
    this.Patient = Patient;
    this.Doctor = Doctor;
  }

  public Date getDate() {
    return Date;
  }

  public void setDate(Date Date) {
    this.Date = Date;
  }

  public Patient getPatient() {
    return Patient;
  }

  public void setPatient(Patient Patient) {
    this.Patient = Patient;
  }

  public Doctor getDoctor() {
    return Doctor;
  }

  public void setDoctor(Doctor Doctor) {
    this.Doctor = Doctor;
  }

}