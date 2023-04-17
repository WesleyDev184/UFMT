package Person.Patient;

import java.util.ArrayList;
import java.util.List;

import HospitalCare.HospitalAppointments.HospitalAppointment;
import Person.Address;
import Person.DateOfBirth;
import Person.Person;

public class Patient extends Person {
    private String CPF;
    private HealthInsurance healthInsurance;
    private List<HospitalAppointment> appointmentList;

    public Patient(String name, DateOfBirth birthDate, Address address, String CPF, HealthInsurance healthInsurance) {
        super(name, birthDate, address);
        this.CPF = CPF;
        this.healthInsurance = healthInsurance;
        this.appointmentList = new ArrayList<>();
    }

    public String getCPF() {
        return CPF;
    }

    public void setCPF(String CPF) {
        this.CPF = CPF;
    }

    public HealthInsurance getHealthInsurance() {
        return healthInsurance;
    }

    public void setHealthInsurance(HealthInsurance healthInsurance) {
        this.healthInsurance = healthInsurance;
    }

    public List<HospitalAppointment> getAppointmentList() {
        return appointmentList;
    }

    public void setAppointmentList(List<HospitalAppointment> appointmentList) {
        this.appointmentList = appointmentList;
    }

    public void addAppointment(HospitalAppointment appointment) {
        this.appointmentList.add(appointment);
    }

    public void removeAppointment(HospitalAppointment appointment) {
        this.appointmentList.remove(appointment);
    }

    @Override
    public String toString() {
        return "Patient [CPF=" + CPF + ", appointmentList=" + appointmentList + ", healthInsurance=" + healthInsurance
                + ", toString()=" + toString() + "]";
    }
}
