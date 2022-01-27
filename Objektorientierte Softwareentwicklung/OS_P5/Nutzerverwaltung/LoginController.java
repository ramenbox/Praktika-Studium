package Nutzerverwaltung;

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
	
	private boolean neuAnmeldung = false;
	
	private MainApplication application;
	
	/**
	 * Jeder UI-Control-Node besitzt ein gleichnamiges Tag in der Controller-Klasse
	 */
	@FXML private CheckBox cbNeuAnmeldung;
	@FXML private Button btAusfuehren;
    @FXML private TextField tfUserID;
    @FXML private PasswordField pfPasswort;
    
    /**
     * Um auf die Methoden der MainApplication zuzugreifen, referenzierung
     * @param application
     */
    void setMainApplication(MainApplication application ) {
    	this.application = application;
    }

    /**
     * Wird aufgerufen, wenn die Checkbox angeklickt wird
     */
    @FXML
    private void neuAnmeldung() {
    	this.neuAnmeldung = this.cbNeuAnmeldung.isSelected();
        System.out.println("neuAnmeldung = " + this.neuAnmeldung); // Aufgabe 4 1.Ereignis
    }
    
    /**
     * Wird aufgerufen, wenn "Ausfuehren" angeklickt wird
     */
    @FXML
    private void ausfuehren() {
    	// Neuen Benutzer anlegen und ausgeben in der Konsole
        if(this.neuAnmeldung == true) {
        	this.application.neuAnmeldung();
        } else { //false, überprüfe ob vorhanden
        	Benutzer benutzer = new Benutzer(tfUserID.getText(), pfPasswort.getText().toCharArray());
        	System.out.println(benutzer.toString());
        	this.application.benutzerLogin(benutzer);
        }
        //Platform.exit();
    }
}
