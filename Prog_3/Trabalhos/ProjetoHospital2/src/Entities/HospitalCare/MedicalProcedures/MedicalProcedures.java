package Entities.HospitalCare.MedicalProcedures;

import Entities.Person.Doctor.Doctor;
import Entities.Person.Patient.Patient;

public abstract class MedicalProcedures {
  private Patient patient;
  private Doctor doctor;
  private String date;
  private int duration;
  private double cost;
  private Room room;

  protected MedicalProcedures(Patient patient, Doctor doctor, String date, int duration, double cost, Room room) {
    this.patient = patient;
    this.doctor = doctor;
    this.date = date;
    this.duration = duration;
    this.cost = cost;
    this.room = room;
  }

  public Patient getPatient() {
    return patient;
  }

  public Doctor getDoctor() {
    return doctor;
  }

  public String getDate() {
    return date;
  }

  public int getDuration() {
    return duration;
  }

  public double getCost() {
    return cost;
  }

  public void setPatient(Patient patient) {
    this.patient = patient;
  }

  public void setDoctor(Doctor doctor) {
    this.doctor = doctor;
  }

  public void setDate(String date) {
    this.date = date;
  }

  public void setDuration(int duration) {
    this.duration = duration;
  }

  public void setCost(double cost) {
    this.cost = cost;
  }

  public Room getRoom() {
    return room;
  }

  public void setRoom(Room room) {
    this.room = room;
  }

  public String toString() {
    return "MedicalProcedures{" +
        "patient=" + patient +
        ", doctor=" + doctor +
        ", date='" + date + '\'' +
        ", duration=" + duration +
        ", cost=" + cost +
        '}';
  }

}
