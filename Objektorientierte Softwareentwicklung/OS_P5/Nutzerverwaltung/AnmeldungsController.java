package Nutzerverwaltung;

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
	
	private MainApplication application;

	/**
	 * Jeder UI-Control-Node besitzt ein gleichnamiges Tag in der Controller-Klasse
	 */
	@FXML private Button btAusfuehren;
	@FXML private TextField tfUserID;
	@FXML private PasswordField pfPasswort;
	@FXML private PasswordField pfWiederholung;
	@FXML private Label lbWarnung;
	
	/**
     * Um auf die Methoden der MainApplication zuzugreifen, referenzierung
     * @param application
     */
	void setMainApplication(MainApplication application) {
		this.application = application;
	}

	/**
	 * Wird ausgeführt, wenn Ausführen-Button gedrückt wird
	 * Call-Back an mainapplication
	 */
	@FXML
	private void ausfuehren() {
		if(pfPasswort.getText().equals(pfWiederholung.getText())) {
			lbWarnung.setVisible(false);
			Benutzer benutzer = new Benutzer(tfUserID.getText(), pfPasswort.getText().toCharArray());
			System.out.println(benutzer.toString());
			this.application.neuerBenutzer(benutzer);
		} else {
			lbWarnung.setVisible(true);
		}
	}
}
