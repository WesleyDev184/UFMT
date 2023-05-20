package Entities.HospitalCare.MedicalProcedures;

import Entities.Person.Doctor.Doctor;
import Entities.Person.Patient.Patient;

public class NeuroSurgery extends MedicalProcedures {

  protected NeuroSurgery(Patient patient, Doctor doctor, String date, int duration, double cost, Room room) {
    super(patient, doctor, date, duration, cost, room);
  }

}
