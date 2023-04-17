package Person.Doctor;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

import HospitalCare.HospitalAppointments.AppointmentManager;
import HospitalCare.HospitalAppointments.HospitalAppointment;
import Person.Address;
import Person.DateOfBirth;
import Person.Patient.Patient;

public class DoctorManager {

    private List<Doctor> doctors;
    private AppointmentManager appointmentManager;

    public DoctorManager(AppointmentManager appointmentManager) {
        this.doctors = new ArrayList<>();
        this.appointmentManager = appointmentManager;
    }

    public void addDoctor(String name, DateOfBirth birthDate, Address address, String crm,
            Specialty specialty, double timeValue) {
        Doctor doctor = new Doctor(name, birthDate, address, crm, specialty, timeValue);
        this.doctors.add(doctor);
    }

    public void updateDoctor(Doctor doctorToUpdate, String name, DateOfBirth birthDate, Address address, String crm,
            Specialty specialty, double timeValue) {
        doctorToUpdate.setName(name);
        doctorToUpdate.setBirthDate(birthDate);
        doctorToUpdate.setAddress(address);
        doctorToUpdate.setCrm(crm);
        doctorToUpdate.setSpecialty(specialty);
        doctorToUpdate.setTimeValue(timeValue);
    }

    public void removeDoctor(Doctor doctorToRemove) {
        this.doctors.remove(doctorToRemove);
    }

    public void scheduleAppointment(Doctor doctor, Patient patient, LocalDate date) {
        HospitalAppointment appointment = new HospitalAppointment(date, patient, doctor);
        doctor.addAppointment(appointment);
        this.appointmentManager.addAppointment(appointment);
    }

    public void cancelAppointment(Doctor doctor, HospitalAppointment appointment) {
        if (doctor.getAppointmentList().contains(appointment)) {
            doctor.getAppointmentList().remove(appointment);
            appointment.getPatient().getAppointmentList().remove(appointment);
            this.appointmentManager.cancelAppointment(appointment);
        }
    }

    public List<Doctor> getDoctors() {
        return this.doctors;
    }
}
