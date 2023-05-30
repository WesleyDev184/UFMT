package screens.PopUps.procedurePopUps.addProcedure;

import java.net.URL;
import java.sql.Date;
import java.sql.SQLException;
import java.util.List;
import java.util.ResourceBundle;

import Dao.HospitalCare.MedicalProcedures.MedicalProceduresDao;
import Dao.HospitalCare.MedicalProcedures.ProcedureTypeDao;
import Dao.HospitalCare.MedicalProcedures.RoomDao;
import Dao.Person.Doctor.DoctorDao;
import Dao.Person.Patient.PatientDao;
import Entities.HospitalCare.MedicalProcedures.MedicalProcedures;
import Entities.HospitalCare.MedicalProcedures.ProcedureType;
import Entities.HospitalCare.MedicalProcedures.Room;
import Entities.Person.Doctor.Doctor;
import Entities.Person.Patient.Patient;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.DatePicker;
import javafx.scene.control.ListCell;
import javafx.scene.control.TextField;
import screens.Dashboard.Controller;

public class ProcedureControllerAdd implements Initializable {
  @FXML
  private Button addBtn;

  @FXML
  private Button closebtn;

  @FXML
  private TextField inputDuration;

  @FXML
  private DatePicker procedureDate;

  @FXML
  private ComboBox<Doctor> selectDoctor;

  @FXML
  private ComboBox<Patient> selectPatient;

  @FXML
  private ComboBox<ProcedureType> selectProcedureType;

  @FXML
  private ComboBox<Room> selectRoom;

  private Controller dashboardController;
  private PatientDao patientDao;
  private DoctorDao doctorDao;
  private ProcedureTypeDao procedureTypeDao;
  private RoomDao roomDao;
  private MedicalProceduresDao medicalProceduresDao;
  private List<Patient> patients;
  private List<Doctor> doctors;
  private List<ProcedureType> procedureTypes;
  private List<Room> rooms;

  @Override
  public void initialize(URL location, ResourceBundle resources) {
    try {
      setPatientsComboBox();
      setDoctorsComboBox();
      setProcedureTypesComboBox();
      setRoomsComboBox();
    } catch (ClassNotFoundException | SQLException e) {
      e.printStackTrace();
    }
  }

  public void close() {
    closebtn.getScene().getWindow().hide();
  }

  public void setDashboardController(Controller dashboardController) {
    this.dashboardController = dashboardController;
  }

  public void addNewMedicalProcedure() {
    try {
      medicalProceduresDao = new MedicalProceduresDao();

      Patient patient = selectPatient.getSelectionModel().getSelectedItem();
      Doctor doctor = selectDoctor.getSelectionModel().getSelectedItem();
      ProcedureType procedureType = selectProcedureType.getSelectionModel().getSelectedItem();
      Room room = selectRoom.getSelectionModel().getSelectedItem();
      int duration = Integer.parseInt(inputDuration.getText());
      Date date = Date.valueOf(procedureDate.getValue());

      if (!validateDuration(inputDuration.getText())) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Erro");
        alert.setHeaderText(null);
        alert.setContentText("Valor de duração inválido!");
        alert.showAndWait();
        return;
      }

      MedicalProcedures medicalProcedure = new MedicalProcedures(0, patient, doctor, date, duration, room,
          procedureType);

      medicalProceduresDao.insert(medicalProcedure);

      dashboardController.updateProcedureTable();

      close();
    } catch (ClassNotFoundException | SQLException e) {
      e.printStackTrace();
    }
  }

  public void setPatientsComboBox() throws ClassNotFoundException, SQLException {
    patients = getAllPatients();

    selectPatient.getItems().addAll(patients);
    selectPatient.setCellFactory(patient -> new ListCell<Patient>() {
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

  public void setDoctorsComboBox() throws ClassNotFoundException, SQLException {
    doctors = getAllDoctors();

    selectDoctor.getItems().addAll(doctors);
    selectDoctor.setCellFactory(doctor -> new ListCell<Doctor>() {
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

  public void setProcedureTypesComboBox() throws ClassNotFoundException, SQLException {
    procedureTypes = getAllProcedureTypes();

    selectProcedureType.getItems().addAll(procedureTypes);
    selectProcedureType.setCellFactory(procedureType -> new ListCell<ProcedureType>() {
      @Override
      protected void updateItem(ProcedureType procedureType, boolean empty) {
        super.updateItem(procedureType, empty);

        if (procedureType == null || empty) {
          setText(null);
        } else {
          setText(procedureType.getName());
        }
      }
    });
  }

  public void setRoomsComboBox() throws ClassNotFoundException, SQLException {
    rooms = getAllRooms();

    selectRoom.getItems().addAll(rooms);
    selectRoom.setCellFactory(room -> new ListCell<Room>() {
      @Override
      protected void updateItem(Room room, boolean empty) {
        super.updateItem(room, empty);

        if (room == null || empty) {
          setText(null);
        } else {
          setText(room.getName());
        }
      }
    });
  }

  public boolean validateDuration(String duration) {
    return duration.matches("[0-9]+");
  }

  public List<Patient> getAllPatients() throws ClassNotFoundException, SQLException {
    patientDao = new PatientDao();
    return patientDao.getAll();
  }

  public List<Doctor> getAllDoctors() throws ClassNotFoundException, SQLException {
    doctorDao = new DoctorDao();
    return doctorDao.getAll();
  }

  public List<ProcedureType> getAllProcedureTypes() throws ClassNotFoundException, SQLException {
    procedureTypeDao = new ProcedureTypeDao();
    return procedureTypeDao.getAll();
  }

  public List<Room> getAllRooms() throws ClassNotFoundException, SQLException {
    roomDao = new RoomDao();
    return roomDao.getAll();
  }
}
