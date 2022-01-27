import javafx.fxml.FXML;
import javafx.application.Platform;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.control.Label;

/**
 * Verwaltet das Anmeldungsfenster
 * @author Harun
 *
 */
public class AnmeldungsController {

	/**
	 * Jeder UI-Control-Node besitzt ein gleichnamiges Tag in der Controller-Klasse
	 */
	@FXML private Button btAusfuehren;
	@FXML private TextField tfUserID;
	@FXML private PasswordField pfPasswort;
	@FXML private PasswordField pfWiederholung;
	@FXML private Label lbWarnung;

	/**
	 * Wird ausgeführt, wenn Ausführen-Button gedrückt wird
	 */
	@FXML
	private void ausfuehren() {
		if(pfPasswort.getText().equals(pfWiederholung.getText())) {
			lbWarnung.setVisible(false);
			Benutzer neuerBenutzer = new Benutzer(tfUserID.getText(), pfPasswort.getText().toCharArray());
			System.out.println(neuerBenutzer.toString());
			btAusfuehren.getScene().getWindow().hide();
		} else {
			lbWarnung.setVisible(true);
		}
	}
}