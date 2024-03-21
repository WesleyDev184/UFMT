package screens.PopUps.appointmentPupUps.addAppointment;

import java.net.URL;
import java.sql.Date;
import java.sql.SQLException;
import java.util.List;
import java.util.ResourceBundle;

import Dao.HospitalCare.HospitalAppointments.HospitalAppointmentDao;
import Dao.Person.Doctor.DoctorDao;
import Dao.Person.Patient.PatientDao;
import Entities.HospitalCare.HospitalAppointments.HospitalAppointment;
import Entities.Person.Doctor.Doctor;
import Entities.Person.Patient.Patient;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.DatePicker;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import screens.Dashboard.Controller;

public class AppointmentControllerAdd implements Initializable {
    @FXML
    private DatePicker ConsultationDate;

    @FXML
    private ComboBox<Doctor> doctorSelector;

    @FXML
    private Button btnClose;

    @FXML
    private Button btnSave;

    @FXML
    private Button newDoctorBtn;

    @FXML
    private Button newPactientBtn;

    @FXML
    private ComboBox<Patient> pactientSelector;

    private Controller dashboardController;
    private DoctorDao doctorDao;
    private PatientDao patientDao;
    private HospitalAppointmentDao hospitalAppointmentDao;
    private List<Doctor> doctors;
    private List<Patient> patients;

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        try {
            doctors = getDoctors();
            patients = getPatients();
            setDoctorComboBox();
            setPatientComboBox();
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
    }

    public void close() {
        btnClose.getScene().getWindow().hide();
    }

    public void setDashboardController(Controller controller) {
        this.dashboardController = controller;
    }

    public void addNewAppointment() throws ClassNotFoundException, SQLException {
        hospitalAppointmentDao = new HospitalAppointmentDao();
        Date date = Date.valueOf(ConsultationDate.getValue());
        Patient patient = pactientSelector.getSelectionModel().getSelectedItem();
        Doctor doctor = doctorSelector.getSelectionModel().getSelectedItem();

        HospitalAppointment hospitalAppointment = new HospitalAppointment(0, date, patient, doctor);

        hospitalAppointmentDao.insert(hospitalAppointment);

        dashboardController.UpdateAppointmentTable();
        dashboardController.AppointmentCounter();
        close();
    }

    public void setPatientComboBox() {
        pactientSelector.getItems().addAll(patients);
        pactientSelector.setCellFactory((ListView<Patient> l) -> new ListCell<Patient>() {
            @Override
            protected void updateItem(Patient patient, boolean empty) {
                super.updateItem(patient, empty);
                if (patient == null || empty) {
                    setText(null);
                } else {
                    setText(patient.getName());
                }
            }
        });
        pactientSelector.setButtonCell(new ListCell<Patient>() {
            @Override
            protected void updateItem(Patient patient, boolean empty) {
                super.updateItem(patient, empty);
                if (patient == null || empty) {
                    setText(null);
                } else {
                    setText(patient.getName());
                }
            }
        });
    }

    public void setDoctorComboBox() {
        doctorSelector.getItems().addAll(doctors);
        doctorSelector.setCellFactory((ListView<Doctor> l) -> new ListCell<Doctor>() {
            @Override
            protected void updateItem(Doctor doctor, boolean empty) {
                super.updateItem(doctor, empty);
                if (doctor == null || empty) {
                    setText(null);
                } else {
                    setText(doctor.getName());
                }
            }
        });
        doctorSelector.setButtonCell(new ListCell<Doctor>() {
            @Override
            protected void updateItem(Doctor doctor, boolean empty) {
                super.updateItem(doctor, empty);
                if (doctor == null || empty) {
                    setText(null);
                } else {
                    setText(doctor.getName());
                }
            }
        });
    }

    public List<Doctor> getDoctors() throws ClassNotFoundException, SQLException {
        doctorDao = new DoctorDao();
        return doctorDao.getAll();
    }

    public List<Patient> getPatients() throws ClassNotFoundException, SQLException {
        patientDao = new PatientDao();
        return patientDao.getAll();
    }
}
