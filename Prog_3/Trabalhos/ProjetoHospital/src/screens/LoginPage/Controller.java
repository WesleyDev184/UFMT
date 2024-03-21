package screens.LoginPage;

import java.io.IOException;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

public class Controller {

    @FXML
    private Button btnClose;

    @FXML
    private Button btnLogin;

    @FXML
    private AnchorPane form;

    @FXML
    private AnchorPane panel;

    @FXML
    private PasswordField passwordInput;

    @FXML
    private TextField userNameInput;

    private double x, y;

    public void Close() {
        System.exit(0);
    }

    public void Login() throws IOException {
        String user = userNameInput.getText();
        String pass = passwordInput.getText();

        if (user.isEmpty() || pass.isEmpty()) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Error");
            alert.setHeaderText(null);
            alert.setContentText("Username or Password is empty");
            alert.showAndWait();
        } else {
            if (user.equals("admin") && pass.equals("admin")) {
                System.out.println("Login Success");

                btnLogin.getScene().getWindow().hide();
                Parent root = FXMLLoader.load(getClass().getResource("../Dashboard/DashboardPage.fxml"));
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

            } else {
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("Error");
                alert.setHeaderText(null);
                alert.setContentText("Username or Password is wrong");
                alert.showAndWait();
            }
        }
    }
}
