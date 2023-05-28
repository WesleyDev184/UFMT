package screens.Dashboard;

import java.io.IOException;
import java.net.URL;
import java.sql.Date;
import java.sql.SQLException;
import java.util.List;
import java.util.Optional;
import java.util.ResourceBundle;

import Dao.HospitalCare.HospitalAppointments.HospitalAppointmentDao;
import Dao.Person.Doctor.DoctorDao;
import Dao.Person.Patient.PatientDao;
import Entities.Person.Patient.Patient;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Label;
import javafx.scene.control.MenuButton;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

public class Controller implements Initializable {

    @FXML
    private StackPane window;

    @FXML
    private AnchorPane mainPanel;

    @FXML
    private Button btnClose;

    @FXML
    private Button btnMinimize;

    @FXML
    private Label cardAppointmentCount;

    @FXML
    private Label cardDoctorCount;

    @FXML
    private Label cardPatientCount;

    @FXML
    private Label cardProcedureCount;

    @FXML
    private AnchorPane homePanel;

    @FXML
    private AnchorPane navbar;

    @FXML
    private TextField patientSearch;

    @FXML
    private TableView<Patient> patientTable;

    @FXML
    private TableColumn<Patient, Date> patientTableBirthDate;

    @FXML
    private TableColumn<Patient, Long> patientTableCpf;

    @FXML
    private TableColumn<Patient, String> patientTableHealthInsuranceName;

    @FXML
    private TableColumn<Patient, Integer> patientTableId;

    @FXML
    private TableColumn<Patient, String> patientTableName;

    @FXML
    private AnchorPane patinetsPanel;

    @FXML
    private AnchorPane sideMenu;

    @FXML
    private MenuButton sideMenuDoctorsBtn;

    @FXML
    private Button sideMenuHomeBtn;

    @FXML
    private Button sideMenuLogOutBtn;

    @FXML
    private MenuButton sideMenuPatientsBtn;

    private double x, y;
    private List<Patient> allPatients;
    private ObservableList<Patient> observableListPatients;

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        try {
            AddPatientOnTable();
            isntaceCounters();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void Close() {
        System.exit(0);
    }

    public void Minimize() {
        Stage stage = (Stage) mainPanel.getScene().getWindow();
        stage.setIconified(true);
    }

    public void Home() throws ClassNotFoundException, SQLException {
        homePanel.setVisible(true);
        patinetsPanel.setVisible(false);

        isntaceCounters();
    }

    public void Patients() {
        patinetsPanel.setVisible(true);
        homePanel.setVisible(false);
    }

    public void AddPatientOnTable() throws ClassNotFoundException, SQLException {
        PatientDao patientDao = new PatientDao();
        allPatients = patientDao.getAll();
        observableListPatients = FXCollections.observableArrayList(allPatients);

        patientTableId.setCellValueFactory(new PropertyValueFactory<>("id"));
        patientTableName.setCellValueFactory(new PropertyValueFactory<>("name"));
        patientTableBirthDate.setCellValueFactory(new PropertyValueFactory<>("birthDate"));
        patientTableCpf.setCellValueFactory(new PropertyValueFactory<>("CPF"));
        patientTableHealthInsuranceName.setCellValueFactory(new PropertyValueFactory<>("healthInsuranceName"));

        patientTable.setItems(observableListPatients);
    }

    public void LogOut() throws IOException {
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle("Log Out");
        alert.setHeaderText(null);
        alert.setContentText("Você Quer Mesmo Sair?");
        Optional<ButtonType> action = alert.showAndWait();

        try {
            if (action.get() == ButtonType.OK) {
                sideMenuLogOutBtn.getScene().getWindow().hide();
                Parent root = FXMLLoader.load(getClass().getResource("../LoginPage/LoginPage.fxml"));
                Stage mainStage = new Stage();
                Scene scene = new Scene(root);
                mainStage.setScene(scene);

                mainStage.initStyle(StageStyle.UNDECORATED);
                // drag it here
                root.setOnMousePressed(event -> {
                    x = event.getSceneX();
                    y = event.getSceneY();
                });
                root.setOnMouseDragged(event -> {

                    mainStage.setX(event.getScreenX() - x);
                    mainStage.setY(event.getScreenY() - y);

                });
                mainStage.show();
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void isntaceCounters() throws ClassNotFoundException, SQLException {
        PatientCounter();
        DoctorCounter();
        ProcedureCounter();
        AppointmentCounter();
    }

    public void PatientCounter() throws ClassNotFoundException, SQLException {
        PatientDao patientDao = new PatientDao();
        int patientCount = patientDao.getAll().size();
        cardPatientCount.setText(String.valueOf(patientCount));
    }

    public void DoctorCounter() throws ClassNotFoundException, SQLException {
        DoctorDao doctorDao = new DoctorDao();
        int doctorCount = doctorDao.getAll().size();
        cardDoctorCount.setText(String.valueOf(doctorCount));
    }

    public void ProcedureCounter() {
        cardProcedureCount.setText("5");
    }

    public void AppointmentCounter() throws ClassNotFoundException, SQLException {
        HospitalAppointmentDao hospitalAppointmentDao = new HospitalAppointmentDao();
        int appointmentCount = hospitalAppointmentDao.getAll().size();
        cardAppointmentCount.setText(String.valueOf(appointmentCount));
    }

}
