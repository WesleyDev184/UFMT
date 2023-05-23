package Entities.HospitalCare.MedicalProcedures;

import java.sql.Date;

import Entities.Person.Doctor.Doctor;
import Entities.Person.Patient.Patient;

public abstract class MedicalProcedures {
  private int id;
  private Patient patient;
  private Doctor doctor;
  private Date date;
  private int duration;
  private double cost;
  private Room room;
  private ProcedureType procedureType;

  public MedicalProcedures(int id, Patient patient, Doctor doctor, Date date, int duration, double cost, Room room,
      ProcedureType procedureType) {
    this.id = id;
    this.patient = patient;
    this.doctor = doctor;
    this.date = date;
    this.duration = duration;
    this.cost = cost;
    this.room = room;
    this.procedureType = procedureType;
  }

  public int getId() {
    return id;
  }

  public Patient getPatient() {
    return patient;
  }

  public Doctor getDoctor() {
    return doctor;
  }

  public Date getDate() {
    return date;
  }

  public int getDuration() {
    return duration;
  }

  public double getCost() {
    return cost;
  }

  public Room getRoom() {
    return room;
  }

  public ProcedureType getProcedureType() {
    return procedureType;
  }

  public void setId(int id) {
    this.id = id;
  }

  public void setPatient(Patient patient) {
    this.patient = patient;
  }

  public void setDoctor(Doctor doctor) {
    this.doctor = doctor;
  }

  public void setDate(Date date) {
    this.date = date;
  }

  public void setDuration(int duration) {
    this.duration = duration;
  }

  public void setCost(double cost) {
    this.cost = cost;
  }

  public void setRoom(Room room) {
    this.room = room;
  }

  public void setProcedureType(ProcedureType procedureType) {
    this.procedureType = procedureType;
  }

  @Override
  public String toString() {
    return "MedicalProcedure{" +
        "id=" + id +
        ", patient=" + patient +
        ", doctor=" + doctor +
        ", date=" + date +
        ", duration=" + duration +
        ", cost=" + cost +
        ", room=" + room +
        ", procedureType=" + procedureType +
        '}';
  }
}