import javafx.fxml.FXML;
import javafx.application.Platform;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.control.CheckBox;

/**
 * Verwaltet das Loginfenster
 * @author Harun
 *
 */
public class LoginController {
	
	/**
	 * Jeder UI-Control-Node besitzt ein gleichnamiges Tag in der Controller-Klasse
	 */
	@FXML private CheckBox cbNeuAnmeldung;
	@FXML private Button btAusfuehren;
    @FXML private TextField tfUserID;
    @FXML private PasswordField pfPasswort;

    /**
     * Wird aufgerufen, wenn die Checkbox angeklickt wird
     */
    @FXML
    private void neuAnmeldung() {
        System.out.println("neuAnmeldung = " + this.cbNeuAnmeldung.isSelected()); // Aufgabe 4 1.Ereignis
    }
    
    /**
     * Wird aufgerufen, wenn "Ausfuehren" angeklickt wird
     */
    @FXML
    private void ausfuehren() {
    	// Neuen Benutzer anlegen und ausgeben in der Konsole
        Benutzer benutzer = new Benutzer(tfUserID.getText(), pfPasswort.getText().toCharArray());
        System.out.println(benutzer);
        btAusfuehren.getScene().getWindow().hide();
    }
}
