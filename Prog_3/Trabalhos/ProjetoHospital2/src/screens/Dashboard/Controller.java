package screens.Dashboard;

import java.io.IOException;
import java.net.URL;
import java.sql.Date;
import java.sql.SQLException;
import java.util.List;
import java.util.Optional;
import java.util.ResourceBundle;

import Dao.HospitalCare.HospitalAppointments.HospitalAppointmentDao;
import Dao.HospitalCare.MedicalProcedures.MedicalProceduresDao;
import Dao.Person.Doctor.DoctorDao;
import Dao.Person.Patient.PatientDao;
import Entities.HospitalCare.HospitalAppointments.HospitalAppointment;
import Entities.HospitalCare.MedicalProcedures.MedicalProcedures;
import Entities.Person.Doctor.Doctor;
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
import javafx.scene.control.TableCell;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import screens.PopUps.addNewPatient.ControllerPopUp;

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

    @FXML
    private Button addNewPatient;

    private double x, y;
    private List<Patient> allPatients;
    private ObservableList<Patient> observableListPatients;
    private PatientDao patientDao;
    private MedicalProceduresDao medicalProceduresDao;
    private HospitalAppointmentDao hospitalAppointmentDao;
    private DoctorDao doctorDao;

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

    public void AddNewPatient() throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("../PopUps/addNewPatient/addNewPatientPopUp.fxml"));
        Parent root = loader.load();

        // Get the scene2 controller so that it will update the table at the end
        ControllerPopUp addNewPatientController = loader.getController();
        addNewPatientController.setDashboardController(this); // Definir a referência do controlador da tela principal

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

    public void SearchTablePatients() {
        patientSearch.textProperty().addListener((observable, oldValue, newValue) -> {
            try {
                List<Patient> allPatients = getAllPatients();
                ObservableList<Patient> filteredList = filterPatients(allPatients, newValue);
                patientTable.setItems(filteredList);
            } catch (ClassNotFoundException | SQLException e) {
                e.printStackTrace();
            }
        });
    }

    private ObservableList<Patient> filterPatients(List<Patient> patients, String searchText) {
        ObservableList<Patient> filteredList = FXCollections.observableArrayList();
        for (Patient patient : patients) {
            if (patient.getName().toLowerCase().contains(searchText.toLowerCase())
                    || String.valueOf(patient.getCPF()).contains(searchText)) {
                filteredList.add(patient);
            }
        }
        return filteredList;
    }

    private List<Patient> getAllPatients() throws ClassNotFoundException, SQLException {
        patientDao = new PatientDao();
        return patientDao.getAll();
    }

    private List<Doctor> getAllDoctors() throws ClassNotFoundException, SQLException {
        doctorDao = new DoctorDao();
        return doctorDao.getAll();
    }

    private List<HospitalAppointment> getAllAppointments() throws ClassNotFoundException, SQLException {
        hospitalAppointmentDao = new HospitalAppointmentDao();
        return hospitalAppointmentDao.getAll();
    }

    private List<MedicalProcedures> getAllProcedures() throws ClassNotFoundException, SQLException {
        medicalProceduresDao = new MedicalProceduresDao();
        return medicalProceduresDao.getAllMedicalProcedures();
    }

    public void AddPatientOnTable() throws ClassNotFoundException, SQLException {
        allPatients = getAllPatients();
        observableListPatients = FXCollections.observableArrayList(allPatients);

        patientTableId.setCellValueFactory(new PropertyValueFactory<>("id"));
        patientTableName.setCellValueFactory(new PropertyValueFactory<>("name"));
        patientTableBirthDate.setCellValueFactory(new PropertyValueFactory<>("birthDate"));
        patientTableCpf.setCellValueFactory(new PropertyValueFactory<>("CPF"));
        patientTableHealthInsuranceName.setCellValueFactory(new PropertyValueFactory<>("healthInsuranceName"));
        // Create the actions column
        TableColumn<Patient, Void> actionsColumn = new TableColumn<>("Actions");
        actionsColumn.setCellFactory(param -> new TableCell<Patient, Void>() {
            private final Button updateButton = new Button("Update");
            private final Button deleteButton = new Button("Delete");

            updateButton.setStyle("-fx-background-color: #00bfff; -fx-text-fill: #ffffff");

            {
                // Set action for update button
                updateButton.setOnAction(event -> {
                    Patient patient = getTableView().getItems().get(getIndex());
                    // Call a function to handle the update action for the patient
                    handleUpdatePatient(patient);
                });

                // Set action for delete button
                deleteButton.setOnAction(event -> {
                    Patient patient = getTableView().getItems().get(getIndex());
                    // Call a function to handle the delete action for the patient
                    handleDeletePatient(patient);
                });
            }

            @Override
            protected void updateItem(Void item, boolean empty) {
                super.updateItem(item, empty);

                if (empty) {
                    setGraphic(null);
                } else {
                    HBox buttonsContainer = new HBox(5); // Adjust the spacing between buttons if needed
                    buttonsContainer.getChildren().addAll(updateButton, deleteButton);
                    setGraphic(buttonsContainer);
                }
            }
        });

        patientTable.getColumns().add(actionsColumn);

        patientTable.setItems(observableListPatients);
        SearchTablePatients();
    }

    public void handleDeletePatient(Patient patient) {
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle("Delete Patient");
        alert.setHeaderText(null);
        alert.setContentText("Você Quer Mesmo Deletar o Paciente " + patient.getName() + "?");
        Optional<ButtonType> action = alert.showAndWait();

        try {
            if (action.get() == ButtonType.OK) {
                patientDao = new PatientDao();
                patientDao.delete(patient);
                updatePatientTable();
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void handleUpdatePatient(Patient patient) {
        System.out.println("Update" + patient.getName());
    }

    public void updatePatientTable() throws ClassNotFoundException, SQLException {
        List<Patient> updatedPatients = getAllPatients();
        observableListPatients.setAll(updatedPatients);
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
        int patientCount = getAllPatients().size();
        cardPatientCount.setText(String.valueOf(patientCount));
    }

    public void DoctorCounter() throws ClassNotFoundException, SQLException {
        int doctorCount = getAllDoctors().size();
        cardDoctorCount.setText(String.valueOf(doctorCount));
    }

    public void ProcedureCounter() throws ClassNotFoundException, SQLException {
        int procedureCount = getAllProcedures().size();
        cardProcedureCount.setText(String.valueOf(procedureCount));
    }

    public void AppointmentCounter() throws ClassNotFoundException, SQLException {
        int appointmentCount = getAllAppointments().size();
        cardAppointmentCount.setText(String.valueOf(appointmentCount));
    }

}
