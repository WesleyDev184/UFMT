package Entities.HospitalCare.MedicalProcedures;

import java.sql.Date;

import Entities.Person.Doctor.Doctor;
import Entities.Person.Patient.Patient;

public class Pharyngoplasty extends MedicalProcedures {

  protected Pharyngoplasty(Patient patient, Doctor doctor, Date date, int duration, double cost, Room room) {
    super(patient, doctor, date, duration, cost, room);
  }

}
