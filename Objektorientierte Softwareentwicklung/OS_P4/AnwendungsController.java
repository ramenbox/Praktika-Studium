import javafx.fxml.FXML;
import javafx.application.Platform;
import javafx.scene.control.Button;

/**
 * Verwaltet das Anwendungsfenster
 * @author Harun
 */
public class AnwendungsController {
	
	/**
     * Wird ausgeführt, wenn "Abbrechen" geklickt wird
     */
	@FXML private Button abbrechen;

    @FXML
    public void abbrechen() {
        System.out.println("Fenster wird geschlossen!");
        abbrechen.getScene().getWindow().hide();
    }
}