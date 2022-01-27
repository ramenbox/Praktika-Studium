import java.util.Scanner;
import javafx.fxml.FXMLLoader;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.Parent;
import javafx.stage.Stage;

/**
 * Übernimmt den Aufruf aller Fenster
 * @author Harun
 *
 */
public class MainApplication extends Application {
	/**
	 * Dieser Methode wird das erse Fenster übergeben und wird nach Eingabe überschrieben
	 */
	@Override
	public void start(Stage stage) throws Exception {
			Parent root3 = FXMLLoader.load(getClass().getResource("anwendung.fxml"));
	       	stage.setTitle("Benutzerverwaltung");
	        stage.setScene(new Scene(root3));
	        stage.show();
	        

	        Stage Stage2 = new Stage();
			Parent root4 = FXMLLoader.load(getClass().getResource("login.fxml"));
	        Stage2.setTitle("Benutzerverwaltung");
	        Stage2.setScene(new Scene(root4));
	        Stage2.show();

			Stage Stage3 = new Stage();
			Parent root5 = FXMLLoader.load(getClass().getResource("anmeldung.fxml"));
	        Stage3.setTitle("Benutzerverwaltung");
			Stage3.setScene(new Scene(root5));
			Stage3.show();
	}

	/**
	 * Fährt zum Start von start(Stage stage)
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
	}
}
