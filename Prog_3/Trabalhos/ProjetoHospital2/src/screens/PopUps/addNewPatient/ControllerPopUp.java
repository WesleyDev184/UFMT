package screens.PopUps.addNewPatient;

import java.net.URL;
import java.sql.Date;
import java.sql.SQLException;
import java.time.LocalDate;
import java.util.List;
import java.util.ResourceBundle;

import Dao.Person.AddressDao;
import Dao.Person.Patient.HealthInsuranceDao;
import Dao.Person.Patient.PatientDao;
import Entities.Person.Address;
import Entities.Person.Patient.HealthInsurance;
import Entities.Person.Patient.Patient;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.DatePicker;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.util.Callback;
import screens.Dashboard.Controller;

public class ControllerPopUp implements Initializable {

  @FXML
  private Button addButon;

  @FXML
  private Button btnClose;

  @FXML
  private TextField inputCep;

  @FXML
  private TextField inputCpf;

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
  private ComboBox<HealthInsurance> selectInsurance;

  private Controller dashboardController;
  private List<HealthInsurance> healthInsurances;
  private HealthInsuranceDao healthInsuranceDao;
  private AddressDao addressDao;
  private PatientDao patientDao;

  @Override
  public void initialize(URL location, ResourceBundle resources) {
    try {
      healthInsurances = getHealthInsurances();
      // This code is setting up a ComboBox (selectInsurance) with a list of
      // HealthInsurance objects
      // (healthInsurances) and a custom cell factory.
      selectInsurance.getItems().addAll(healthInsurances);
      selectInsurance.setCellFactory(
          (Callback<ListView<HealthInsurance>, ListCell<HealthInsurance>>) new Callback<ListView<HealthInsurance>, ListCell<HealthInsurance>>() {
            @Override
            public ListCell<HealthInsurance> call(ListView<HealthInsurance> param) {
              return new ListCell<HealthInsurance>() {
                @Override
                protected void updateItem(HealthInsurance item, boolean empty) {
                  super.updateItem(item, empty);
                  if (item != null) {
                    setText(item.getHealthInsuranceName());
                  } else {
                    setText(null);
                  }
                }
              };
            }
          });
    } catch (ClassNotFoundException | SQLException e) {
      e.printStackTrace();
    }
  }

  public void setDashboardController(Controller controller) {
    this.dashboardController = controller;
  }

  public void AddNewPatient() {
    try {
      addressDao = new AddressDao();
      patientDao = new PatientDao();

      String name = inputName.getText().trim();
      String cpf = inputCpf.getText().trim();
      LocalDate dateOfBirth = inputDate.getValue();
      String cep = inputCep.getText().trim();
      String publicPlace = inputPublicPlace.getText().trim();
      String residenceNumber = inputResidenceNumber.getText().trim();
      String neighborhood = inputNeighborhood.getText().trim();
      HealthInsurance selectedInsurance = selectInsurance.getSelectionModel().getSelectedItem();

      if (name.isEmpty() || cpf.isEmpty() || dateOfBirth == null || cep.isEmpty() ||
          publicPlace.isEmpty() || residenceNumber.isEmpty() || neighborhood.isEmpty() || selectedInsurance == null) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Erro");
        alert.setHeaderText(null);
        alert.setContentText("Preencha todos os campos!");
        alert.showAndWait();
        return;
      }

      // Verifying CPF format
      if (!isValidCpf(cpf)) {
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

      // Inserting the patient
      Address address = new Address(0, publicPlace, Integer.parseInt(residenceNumber),
          Integer.parseInt(cep), neighborhood);
      Address newAddress = addressDao.insert(address);

      Date date = Date.valueOf(dateOfBirth);

      Patient patient = new Patient(0, name, date, newAddress, cpf, selectedInsurance);

      patientDao.insert(patient);

      // Updating the patient table in the dashboard
      if (dashboardController != null) {
        dashboardController.updatePatientTable();
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
  private boolean isValidCpf(String cpf) {
    if (cpf.length() != 11) {
      return false; // Verifica se o CPF possui exatamente 11 caracteres
    }

    for (int i = 0; i < cpf.length(); i++) {
      if (!Character.isDigit(cpf.charAt(i))) {
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

  private List<HealthInsurance> getHealthInsurances() throws ClassNotFoundException, SQLException {
    healthInsuranceDao = new HealthInsuranceDao();
    return healthInsuranceDao.getAll();
  }

  public void Close() {
    btnClose.getScene().getWindow().hide();
  }
}