package testes;

import java.sql.Date;

import Dao.HospitalCare.HospitalAppointments.HospitalAppointmentDao;
import Dao.Person.Doctor.DoctorDao;
import Dao.Person.Patient.PatientDao;
import Entities.Person.Doctor.Doctor;
import Entities.Person.Patient.Patient;

public class HospitalAppointmentDaoTeste {
  public static void main(String[] args) {

    try {
      HospitalAppointmentDao appointmentDao = new HospitalAppointmentDao();

      PatientDao patientDao = new PatientDao();
      Patient patient = patientDao.getById(1);

      DoctorDao doctorDao = new DoctorDao();
      Doctor doctor = doctorDao.getById(1);

      Date date = new Date(2021, 10, 10);

      // HospitalAppointment appointment = new HospitalAppointment(1, date, patient,
      // doctor);
      // appointmentDao.insert(appointment);

      // List<HospitalAppointment> appointments = appointmentDao.getAll();
      System.out.println(appointmentDao.getByPatientId(1));
    } catch (Exception e) {
      // TODO: handle exception
      e.printStackTrace();
    }

  }
}
