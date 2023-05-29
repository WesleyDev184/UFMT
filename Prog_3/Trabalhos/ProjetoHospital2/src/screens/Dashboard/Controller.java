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
import screens.PopUps.appointmentPupUps.addAppointment.AppointmentControllerAdd;
import screens.PopUps.appointmentPupUps.updateAppointment.AppointmentControllerUpdate;
import screens.PopUps.patientPopUps.addNewPatient.ControllerPopUp;
import screens.PopUps.patientPopUps.updatePatient.UpdateControllerPopUp;

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
    private TableColumn<Patient, String> patientTableCpf;

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

    @FXML
    private TableView<HospitalAppointment> appointmentTable;

    @FXML
    private TableColumn<HospitalAppointment, Date> appointmentTableDate;

    @FXML
    private TableColumn<HospitalAppointment, String> appointmentTableDoctorName;

    @FXML
    private TableColumn<HospitalAppointment, String> appointmentTableDoctorSpecialty;

    @FXML
    private TableColumn<HospitalAppointment, Integer> appointmentTableId;

    @FXML
    private TableColumn<HospitalAppointment, String> appointmentTablePatientName;

    @FXML
    private Button addNewAppointment;

    @FXML
    private Button addNewDoctor;

    @FXML
    private AnchorPane doctorPanel;

    @FXML
    private TextField appointmentSearch;

    @FXML
    private TextField doctorSearch;

    @FXML
    private TableView<Doctor> doctorTable;

    @FXML
    private TableColumn<Doctor, Date> doctorTableBirthDate;

    @FXML
    private TableColumn<Doctor, Integer> doctorTableCrm;

    @FXML
    private TableColumn<Doctor, Integer> doctorTableId;

    @FXML
    private TableColumn<Doctor, String> doctorTableName;

    @FXML
    private TableColumn<Doctor, String> doctorTableSpecialty;

    private double x, y;
    private List<Patient> allPatients;
    private List<HospitalAppointment> allAppointments;
    private List<Doctor> allDoctors;
    private ObservableList<Patient> observableListPatients;
    private ObservableList<HospitalAppointment> observableListAppointments;
    private PatientDao patientDao;
    private MedicalProceduresDao medicalProceduresDao;
    private HospitalAppointmentDao hospitalAppointmentDao;
    private DoctorDao doctorDao;

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        try {
            AddPatientOnTable();
            AddAppointmentOnTable();
            addDoctorsTable();
            isntaceCounters();

            homePanel.setVisible(true);
            patinetsPanel.setVisible(false);
            doctorPanel.setVisible(false);
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
        doctorPanel.setVisible(false);

        isntaceCounters();
    }

    public void Patients() {
        patinetsPanel.setVisible(true);
        homePanel.setVisible(false);
        doctorPanel.setVisible(false);
    }

    public void Doctors() {
        doctorPanel.setVisible(true);
        homePanel.setVisible(false);
        patinetsPanel.setVisible(false);
    }

    public void addDoctorsTable() throws ClassNotFoundException, SQLException {
        allDoctors = getAllDoctors();
        ObservableList<Doctor> observableListDoctors = FXCollections
                .observableArrayList(allDoctors);

        doctorTableId.setCellValueFactory(new PropertyValueFactory<>("id"));
        doctorTableName.setCellValueFactory(new PropertyValueFactory<>("name"));
        doctorTableBirthDate.setCellValueFactory(new PropertyValueFactory<>("birthDate"));
        doctorTableCrm.setCellValueFactory(new PropertyValueFactory<>("crm"));
        doctorTableSpecialty.setCellValueFactory(new PropertyValueFactory<>("specialtyName"));

        // Create the actions column
        TableColumn<Doctor, Void> actionsColumn = new TableColumn<>("Actions");
        actionsColumn.setCellFactory(param -> new TableCell<Doctor, Void>() {
            private final Button updateButton = new Button("Update");
            private final Button deleteButton = new Button("Delete");

            {
                // Set action for update button
                updateButton.setOnAction(event -> {
                    Doctor doctor = getTableView().getItems().get(getIndex());
                    // Call a function to handle the update action for the patient
                    handleUpdateDoctor(doctor);
                });
                updateButton.setStyle(
                        "-fx-background-color: #f8d16a; -fx-text-fill: #ffffff; -fx-border-radius: 5px; -fx-background-radius: 5px;");

                // Set action for delete button
                deleteButton.setOnAction(event -> {
                    Doctor doctor = getTableView().getItems().get(getIndex());
                    // Call a function to handle the delete action for the patient
                    try {
                        handleDeleteDoctor(doctor);
                    } catch (ClassNotFoundException | SQLException e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                    }
                });
                deleteButton.setStyle(
                        "-fx-background-color: #ff5c5c; -fx-text-fill: #ffffff; -fx-border-radius: 5px; -fx-background-radius: 5px;");
            }

            @Override
            protected void updateItem(Void item, boolean empty) {
                super.updateItem(item, empty);

                if (empty) {
                    setGraphic(null);
                } else {
                    HBox buttonsContainer = new HBox(4); // Adjust the spacing between buttons if needed
                    buttonsContainer.getChildren().addAll(updateButton, deleteButton);
                    setGraphic(buttonsContainer);
                }
            }
        });

        doctorTable.getColumns().add(actionsColumn);
        doctorTable.setItems(observableListDoctors);
        searchDoctorTable();
    }

    public void handleUpdateDoctor(Doctor doctor) {
        System.out.println(doctor);
    }

    public void handleDeleteDoctor(Doctor doctor) throws ClassNotFoundException, SQLException {
        doctorDao = new DoctorDao();
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle("Delete Doctor");
        alert.setHeaderText(null);
        alert.setContentText("Você Quer Mesmo Deletar o Médico " + doctor.getName() + "?");
        Optional<ButtonType> action = alert.showAndWait();

        if (action.get() == ButtonType.OK) {
            doctorDao.delete(doctor.getId());
            updateDoctorTable();
        }
    }

    public void updateDoctorTable() throws ClassNotFoundException, SQLException {
        List<Doctor> updatedDoctors = getAllDoctors();
        ObservableList<Doctor> observableListDoctors = FXCollections
                .observableArrayList(updatedDoctors);
        doctorTable.setItems(observableListDoctors);
    }

    public void searchDoctorTable() {
        doctorSearch.textProperty().addListener((observable, oldValue, newValue) -> {
            try {
                List<Doctor> allDoctors = getAllDoctors();
                ObservableList<Doctor> filteredList = filterDoctors(allDoctors, newValue);
                doctorTable.setItems(filteredList);
            } catch (ClassNotFoundException | SQLException e) {
                e.printStackTrace();
            }
        });
    }

    private ObservableList<Doctor> filterDoctors(List<Doctor> doctors, String searchText) {
        ObservableList<Doctor> filteredList = FXCollections.observableArrayList();
        for (Doctor doctor : doctors) {
            if (doctor.getName().toLowerCase().contains(searchText.toLowerCase())
                    || String.valueOf(doctor.getCrm()).contains(searchText)) {
                filteredList.add(doctor);
            }
        }
        return filteredList;
    }

    public void AddNewPatient() throws IOException {
        FXMLLoader loader = new FXMLLoader(
                getClass().getResource("../PopUps/patientPopUps/addNewPatient/addNewPatientPopUp.fxml"));
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

            {
                // Set action for update button
                updateButton.setOnAction(event -> {
                    Patient patient = getTableView().getItems().get(getIndex());
                    // Call a function to handle the update action for the patient
                    handleUpdatePatient(patient);
                });
                updateButton.setStyle(
                        "-fx-background-color: #f8d16a; -fx-text-fill: #ffffff; -fx-border-radius: 5px; -fx-background-radius: 5px;");

                // Set action for delete button
                deleteButton.setOnAction(event -> {
                    Patient patient = getTableView().getItems().get(getIndex());
                    // Call a function to handle the delete action for the patient
                    handleDeletePatient(patient);
                });
                deleteButton.setStyle(
                        "-fx-background-color: #ff5c5c; -fx-text-fill: #ffffff; -fx-border-radius: 5px; -fx-background-radius: 5px;");
            }

            @Override
            protected void updateItem(Void item, boolean empty) {
                super.updateItem(item, empty);

                if (empty) {
                    setGraphic(null);
                } else {
                    HBox buttonsContainer = new HBox(4); // Adjust the spacing between buttons if needed
                    buttonsContainer.getChildren().addAll(updateButton, deleteButton);
                    setGraphic(buttonsContainer);
                }
            }
        });

        patientTable.getColumns().add(actionsColumn);

        patientTable.setItems(observableListPatients);
        SearchTablePatients();
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
        FXMLLoader loader = new FXMLLoader(
                getClass().getResource("../PopUps/patientPopUps/updatePatient/updatePatientPopUp.fxml"));
        try {
            Parent root = loader.load();

            // Get the scene2 controller so that it will update the table at the end
            UpdateControllerPopUp UpdatePatientController = loader.getController();
            UpdatePatientController.setDashboardController(this); // Definir a referência do controlador da tela
                                                                  // principal
            UpdatePatientController.setPatient(patient); // Definir o paciente que será atualizado
            UpdatePatientController.setFields();

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
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void updatePatientTable() throws ClassNotFoundException, SQLException {
        List<Patient> updatedPatients = getAllPatients();
        observableListPatients.setAll(updatedPatients);
        patientTable.setItems(observableListPatients);
    }

    public void AddAppointmentOnTable() throws ClassNotFoundException, SQLException {
        allAppointments = getAllAppointments();
        observableListAppointments = FXCollections
                .observableArrayList(allAppointments);

        appointmentTableId.setCellValueFactory(new PropertyValueFactory<>("id"));
        appointmentTableDate.setCellValueFactory(new PropertyValueFactory<>("date"));
        appointmentTablePatientName.setCellValueFactory(new PropertyValueFactory<>("patientName"));
        appointmentTableDoctorName.setCellValueFactory(new PropertyValueFactory<>("doctorName"));
        appointmentTableDoctorSpecialty.setCellValueFactory(new PropertyValueFactory<>("specialtyName"));

        TableColumn<HospitalAppointment, Void> actionsColumn = new TableColumn<>("Actions");
        actionsColumn.setCellFactory(param -> new TableCell<HospitalAppointment, Void>() {
            private final Button updateButton = new Button("Update");
            private final Button deleteButton = new Button("Delete");

            {
                // Set action for update button
                updateButton.setOnAction(event -> {
                    HospitalAppointment appointment = getTableView().getItems().get(getIndex());
                    // Call a function to handle the update action for the patient
                    handleUpdateAppointment(appointment);
                });
                updateButton.setStyle(
                        "-fx-background-color: #f8d16a; -fx-text-fill: #ffffff; -fx-border-radius: 5px; -fx-background-radius: 5px;");

                // Set action for delete button
                deleteButton.setOnAction(event -> {
                    HospitalAppointment appointment = getTableView().getItems().get(getIndex());
                    // Call a function to handle the delete action for the appointment
                    try {
                        handleDeleteAppointment(appointment);
                    } catch (ClassNotFoundException | SQLException e) {
                        e.printStackTrace();
                    }
                });
                deleteButton.setStyle(
                        "-fx-background-color: #ff5c5c; -fx-text-fill: #ffffff; -fx-border-radius: 5px; -fx-background-radius: 5px;");
            }

            @Override
            protected void updateItem(Void item, boolean empty) {
                super.updateItem(item, empty);

                if (empty) {
                    setGraphic(null);
                } else {
                    HBox buttonsContainer = new HBox(4); // Adjust the spacing between buttons if needed
                    buttonsContainer.getChildren().addAll(updateButton, deleteButton);
                    setGraphic(buttonsContainer);
                }
            }
        });

        appointmentTable.getColumns().add(actionsColumn);

        appointmentTable.setItems(observableListAppointments);
        SearchTableAppointment();
    }

    public void AddNewAppointment() throws IOException {
        FXMLLoader loader = new FXMLLoader(
                getClass().getResource("../PopUps/appointmentPupUps/addAppointment/addNewAppointmentPopUp.fxml"));
        Parent root = loader.load();

        // Get the scene2 controller so that it will update the table at the end
        AppointmentControllerAdd addNewAppointmentController = loader
                .getController();
        addNewAppointmentController.setDashboardController(this); // Definir a referência do controlador da tela
                                                                  // principal

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

    public void SearchTableAppointment() {
        appointmentSearch.textProperty().addListener((observable, oldValue, newValue) -> {
            try {
                List<HospitalAppointment> allAppointments = getAllAppointments();
                ObservableList<HospitalAppointment> filteredList = filterAppointment(allAppointments, newValue);
                appointmentTable.setItems(filteredList);
            } catch (ClassNotFoundException | SQLException e) {
                e.printStackTrace();
            }
        });
    }

    private ObservableList<HospitalAppointment> filterAppointment(List<HospitalAppointment> HospitalAppointments,
            String searchText) {
        ObservableList<HospitalAppointment> filteredList = FXCollections.observableArrayList();
        for (HospitalAppointment hospitalAppointment : HospitalAppointments) {
            if (hospitalAppointment.getDoctorName().toLowerCase().contains(searchText.toLowerCase())
                    || hospitalAppointment.getPatientName().toLowerCase().contains(searchText)) {
                filteredList.add(hospitalAppointment);
            }
        }
        return filteredList;
    }

    public void handleUpdateAppointment(HospitalAppointment hospitalAppointment) {
        FXMLLoader loader = new FXMLLoader(
                getClass().getResource("../PopUps/appointmentPupUps/updateAppointment/updateAppointmentPopUp.fxml"));
        try {
            Parent root = loader.load();

            // Get the scene2 controller so that it will update the table at the end
            AppointmentControllerUpdate UpdateAppointmentController = loader
                    .getController();
            UpdateAppointmentController.setDashboardController(this); // Definir a referência do controlador da tela
                                                                      // principal
            UpdateAppointmentController.setAppointment(hospitalAppointment); // Definir o paciente que será atualizado
            UpdateAppointmentController.setFields();

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
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void handleDeleteAppointment(HospitalAppointment hospitalAppointment)
            throws ClassNotFoundException, SQLException {
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle("Delete Appointment");
        alert.setHeaderText(null);
        alert.setContentText("Você Quer Mesmo Deletar o Agendamento " + hospitalAppointment.getId() + "?");
        Optional<ButtonType> action = alert.showAndWait();

        try {
            if (action.get() == ButtonType.OK) {
                hospitalAppointmentDao = new HospitalAppointmentDao();
                hospitalAppointmentDao.delete(hospitalAppointment.getId());
                UpdateAppointmentTable();
            }
        } catch (Exception e) {
            System.out.println(e);
        }
        AppointmentCounter();
    }

    public void UpdateAppointmentTable() throws ClassNotFoundException, SQLException {
        List<HospitalAppointment> updatedAppointments = getAllAppointments();
        observableListAppointments.setAll(updatedAppointments);
        appointmentTable.setItems(observableListAppointments);
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
