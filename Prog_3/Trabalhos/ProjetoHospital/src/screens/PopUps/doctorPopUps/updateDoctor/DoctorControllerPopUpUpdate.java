package screens.PopUps.doctorPopUps.updateDoctor;

import java.net.URL;
import java.sql.Date;
import java.sql.SQLException;
import java.time.LocalDate;
import java.util.List;
import java.util.ResourceBundle;

import Dao.Person.AddressDao;
import Dao.Person.Doctor.DoctorDao;
import Dao.Person.Doctor.SpecialtyDao;
import Entities.Person.Address;
import Entities.Person.Doctor.Doctor;
import Entities.Person.Doctor.Specialty;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.DatePicker;
import javafx.scene.control.ListCell;
import javafx.scene.control.TextField;
import screens.Dashboard.Controller;

public class DoctorControllerPopUpUpdate implements Initializable {

  @FXML
  private Button addButon;

  @FXML
  private Button btnClose;

  @FXML
  private TextField inputCep;

  @FXML
  private TextField inputCrm;

  @FXML
  private DatePicker inputDate;

  @FXML
  private TextField inputName;

  @FXML
  private TextField inputNeighborhood;

  @FXML
  private TextField inputPublicPlace;

  @FXML
  private TextField inputResidenceNumber;

  @FXML
  private TextField inputTimeValue;

  @FXML
  private ComboBox<Specialty> selectSpecialty;

  private Controller dashboardController;
  private List<Specialty> specialties;
  private SpecialtyDao specialtyDao;
  private AddressDao addressDao;
  private DoctorDao doctorDao;
  private Doctor doctor;

  @Override
  public void initialize(URL location, ResourceBundle resources) {
    try {
      specialties = getSpecialties();
      setSpecialtiesComboBox();
    } catch (ClassNotFoundException | SQLException e) {
      e.printStackTrace();
    }
  }

  public void setDashboardController(Controller controller) {
    this.dashboardController = controller;
  }

  public void setDoctor(Doctor doctor) {
    this.doctor = doctor;
  }

  public void setFields() {
    inputName.setText(doctor.getName());
    inputCrm.setText(doctor.getCrm());
    inputDate.setValue(doctor.getBirthDate().toLocalDate());
    inputCep.setText(String.valueOf(doctor.getAddress().getCEP()));
    inputTimeValue.setText(String.valueOf(doctor.getTimeValue()));
    inputPublicPlace.setText(doctor.getAddress().getPublicPlace());
    inputResidenceNumber.setText(String.valueOf(doctor.getAddress().getNumber()));
    inputNeighborhood.setText(doctor.getAddress().getNeighborhood());
    selectSpecialty.getSelectionModel().select(doctor.getSpecialty());
  }

  public void setSpecialtiesComboBox() {
    selectSpecialty.getItems().addAll(specialties);
    selectSpecialty.setCellFactory(lv -> new ListCell<Specialty>() {
      @Override
      protected void updateItem(Specialty specialty, boolean empty) {
        super.updateItem(specialty, empty);
        setText(empty ? "" : specialty.getName());
      }
    });
    selectSpecialty.setButtonCell(new ListCell<Specialty>() {
      @Override
      protected void updateItem(Specialty specialty, boolean empty) {
        super.updateItem(specialty, empty);
        setText(empty ? "" : specialty.getName());
      }
    });
  }

  public void UpdateDoctor() {
    try {
      addressDao = new AddressDao();
      doctorDao = new DoctorDao();

      String name = inputName.getText().trim();
      String crm = inputCrm.getText().trim();
      LocalDate dateOfBirth = inputDate.getValue();
      String cep = inputCep.getText().trim();
      String timeValue = inputTimeValue.getText().trim();
      String publicPlace = inputPublicPlace.getText().trim();
      String residenceNumber = inputResidenceNumber.getText().trim();
      String neighborhood = inputNeighborhood.getText().trim();
      Specialty selectedInsurance = selectSpecialty.getSelectionModel().getSelectedItem();

      if (name.isEmpty() || crm.isEmpty() || dateOfBirth == null || cep.isEmpty() ||
          publicPlace.isEmpty() || residenceNumber.isEmpty() || neighborhood.isEmpty() || selectedInsurance == null) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Erro");
        alert.setHeaderText(null);
        alert.setContentText("Preencha todos os campos!");
        alert.showAndWait();
        return;
      }

      // Verifying crm format
      if (!isValidCrm(crm)) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Erro");
        alert.setHeaderText(null);
        alert.setContentText("CPF inválido! Insira um CPF válido.");
        alert.showAndWait();
        return;
      }

      // Verifying CEP format
      if (!isValidCep(cep)) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Erro");
        alert.setHeaderText(null);
        alert.setContentText("CEP inválido! Insira um CEP válido.");
        alert.showAndWait();
        return;
      }

      // Verifying residence number format
      if (!isValidResidenceNumber(residenceNumber)) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Erro");
        alert.setHeaderText(null);
        alert.setContentText("Número de residência inválido! Insira um número válido.");
        alert.showAndWait();
        return;
      }

      // Verifying time value format
      if (!isValidTimeValue(timeValue)) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Erro");
        alert.setHeaderText(null);
        alert.setContentText("Valor da consulta inválido! Insira um valor válido.");
        alert.showAndWait();
        return;
      }

      // Inserting the patient
      Address address = new Address(0, publicPlace, Integer.parseInt(residenceNumber),
          Integer.parseInt(cep), neighborhood);
      Address newAddress = addressDao.insert(address);

      Date date = Date.valueOf(dateOfBirth);

      Doctor updatedDoctor = new Doctor(doctor.getId(), name, date, newAddress, crm, selectedInsurance,
          Double.parseDouble(timeValue));

      doctorDao.update(updatedDoctor);

      // Updating the patient table in the dashboard
      if (dashboardController != null) {
        dashboardController.updateDoctorTable();
      }

      Close();
    } catch (ClassNotFoundException | SQLException e) {
      e.printStackTrace();
    }
  }

  // These are private methods that are used to validate the format of the CPF
  // (Brazilian individual
  // taxpayer registry number), CEP (Brazilian postal code), and residence number
  // input fields. They
  // currently always return true, but they could be modified to perform actual
  // validation logic.
  private boolean isValidCrm(String crm) {

    for (int i = 0; i < crm.length(); i++) {
      if (!Character.isDigit(crm.charAt(i))) {
        return false; // Verifica se todos os caracteres são dígitos numéricos
      }
    }

    return true;
  }

  private boolean isValidCep(String cep) {
    for (int i = 0; i < cep.length(); i++) {
      if (!Character.isDigit(cep.charAt(i))) {
        return false; // Verifica se todos os caracteres são dígitos numéricos
      }
    }

    if (cep.length() != 8) {
      return false; // Verifica se o CEP possui exatamente 8 caracteres
    }

    return true;
  }

  private boolean isValidResidenceNumber(String residenceNumber) {
    for (int i = 0; i < residenceNumber.length(); i++) {
      if (!Character.isDigit(residenceNumber.charAt(i))) {
        return false; // Verifica se todos os caracteres são dígitos numéricos
      }
    }

    return true;
  }

  public boolean isValidTimeValue(String timeValue) {
    for (int i = 0; i < timeValue.length(); i++) {
      char c = timeValue.charAt(i);
      if (!Character.isDigit(c) && c != '.') {
        return false;
      }
    }

    return true;
  }

  private List<Specialty> getSpecialties() throws ClassNotFoundException, SQLException {
    specialtyDao = new SpecialtyDao();
    return specialtyDao.getAll();
  }

  public void Close() {
    btnClose.getScene().getWindow().hide();
  }
}