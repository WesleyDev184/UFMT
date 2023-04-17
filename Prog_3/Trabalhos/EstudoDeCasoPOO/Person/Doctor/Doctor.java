package Person.Doctor;

import java.util.ArrayList;
import java.util.List;

import HospitalCare.HospitalAppointments.HospitalAppointment;
import Person.Person;
import Person.Address;
import Person.DateOfBirth;

public class Doctor extends Person {

    private String crm;
    private Specialty specialty;
    private double timeValue;
    private List<HospitalAppointment> appointmentList;

    public Doctor(String name, DateOfBirth dateOfBirth, Address address, String crm,
            Specialty specialty, double timeValue) {
        super(name, dateOfBirth, address);
        this.crm = crm;
        this.specialty = specialty;
        this.timeValue = timeValue;
        this.appointmentList = new ArrayList<>();
    }

    public String getCrm() {
        return crm;
    }

    public void setCrm(String crm) {
        this.crm = crm;
    }

    public Specialty getSpecialty() {
        return specialty;
    }

    public void setSpecialty(Specialty specialty) {
        this.specialty = specialty;
    }

    public double getTimeValue() {
        return timeValue;
    }

    public void setTimeValue(double timeValue) {
        this.timeValue = timeValue;
    }

    public List<HospitalAppointment> getAppointmentList() {
        return appointmentList;
    }

    public void addAppointment(HospitalAppointment hospitalAppointment) {
        appointmentList.add(hospitalAppointment);
    }

    public void removeAppointment(HospitalAppointment hospitalAppointment) {
        appointmentList.remove(hospitalAppointment);
    }

    @Override
    public String toString() {
        return String.format("Name: %s \nDate Of Birth %s \nAddress: %s \nCRM: %s \nSpecialty: %s \nTime Value: %s",
                getName(),
                getBirthDate(), getAddress(), crm, specialty, timeValue);
    }

}
