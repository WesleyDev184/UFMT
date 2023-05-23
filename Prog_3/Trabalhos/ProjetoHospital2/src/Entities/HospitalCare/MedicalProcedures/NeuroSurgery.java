package Entities.HospitalCare.MedicalProcedures;

import java.sql.Date;

import Entities.Person.Doctor.Doctor;
import Entities.Person.Patient.Patient;

public class NeuroSurgery extends MedicalProcedures {

  public NeuroSurgery(int id, Patient patient, Doctor doctor, Date date, int duration, double cost, Room room,
      ProcedureType procedureType) {
    super(id, patient, doctor, date, duration, cost, room, procedureType);
  }
}
