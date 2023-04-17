package HospitalCare.HospitalAppointments;

import java.time.LocalDate;

import Person.Doctor.Doctor;
import Person.Patient.Patient;

public class HospitalAppointment {

    private LocalDate Date;
    private Patient Patient;
    private Doctor Doctor;

    public HospitalAppointment(LocalDate Date, Patient Patient, Doctor Doctor) {
        this.Date = Date;
        this.Patient = Patient;
        this.Doctor = Doctor;
    }

    public LocalDate getDate() {
        return Date;
    }

    public void setDate(LocalDate Date) {
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
