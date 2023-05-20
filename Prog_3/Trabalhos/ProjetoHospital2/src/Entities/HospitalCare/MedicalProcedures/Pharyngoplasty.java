package Entities.HospitalCare.MedicalProcedures;

import Entities.Person.Doctor.Doctor;
import Entities.Person.Patient.Patient;

public class Pharyngoplasty extends MedicalProcedures {

  protected Pharyngoplasty(Patient patient, Doctor doctor, String date, int duration, double cost, Room room) {
    super(patient, doctor, date, duration, cost, room);
  }

}
