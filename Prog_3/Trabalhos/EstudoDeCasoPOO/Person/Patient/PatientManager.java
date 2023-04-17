package Person.Patient;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

import HospitalCare.HospitalAppointments.AppointmentManager;
import HospitalCare.HospitalAppointments.HospitalAppointment;
import Person.Address;
import Person.DateOfBirth;
import Person.Doctor.Doctor;

public class PatientManager {
    private List<Patient> patients;
    private AppointmentManager appointmentManager;

    public PatientManager(AppointmentManager appointmentManager) {
        this.patients = new ArrayList<>();
        this.appointmentManager = appointmentManager;
    }

    public void addPatient(String name, DateOfBirth birthDate, Address address, String cpf,
            HealthInsurance healthInsurance) {
        Patient patient = new Patient(name, birthDate, address, cpf, healthInsurance);
        this.patients.add(patient);
    }

    public void updatePatient(Patient patientToUpdate, String name, DateOfBirth birthDate, Address address, String cpf,
            HealthInsurance healthInsurance) {
        patientToUpdate.setName(name);
        patientToUpdate.setBirthDate(birthDate);
        patientToUpdate.setAddress(address);
        patientToUpdate.setCPF(cpf);
        patientToUpdate.setHealthInsurance(healthInsurance);
    }

    public void removePatient(Patient patientToRemove) {
        this.patients.remove(patientToRemove);
    }

    public void scheduleAppointment(Patient patient, Doctor doctor, LocalDate date) {
        HospitalAppointment appointment = new HospitalAppointment(date, patient, doctor);
        patient.addAppointment(appointment);
        this.appointmentManager.addAppointment(appointment);
    }

    public void cancelAppointment(Patient patient, HospitalAppointment appointment) {
        if (patient.getAppointmentList().contains(appointment)) {
            patient.getAppointmentList().remove(appointment);
            appointment.getDoctor().getAppointmentList().remove(appointment);
            this.appointmentManager.cancelAppointment(appointment);
        }
    }

    public List<Patient> getPatients() {
        return this.patients;
    }
}
