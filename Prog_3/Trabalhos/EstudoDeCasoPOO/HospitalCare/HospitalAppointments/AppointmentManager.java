package HospitalCare.HospitalAppointments;

import java.util.ArrayList;
import java.util.List;
import java.time.LocalDate;
import Person.Doctor.Doctor;
import Person.Patient.Patient;

public class AppointmentManager {
    private List<HospitalAppointment> appointments;

    public AppointmentManager() {
        this.appointments = new ArrayList<>();
    }

    public void scheduleAppointment(LocalDate date, Patient patient, Doctor doctor) {
        HospitalAppointment appointment = new HospitalAppointment(date, patient, doctor);
        this.appointments.add(appointment);
    }

    public void cancelAppointment(HospitalAppointment appointment) {
        this.appointments.remove(appointment);
    }

    public List<HospitalAppointment> searchAppointmentsByPatient(Patient patient) {
        List<HospitalAppointment> appointmentsForPatient = new ArrayList<>();
        for (HospitalAppointment appointment : this.appointments) {
            if (appointment.getPatient().equals(patient)) {
                appointmentsForPatient.add(appointment);
            }
        }
        return appointmentsForPatient;
    }

    public void addAppointment(HospitalAppointment appointment) {
        this.appointments.add(appointment);
    }
}
