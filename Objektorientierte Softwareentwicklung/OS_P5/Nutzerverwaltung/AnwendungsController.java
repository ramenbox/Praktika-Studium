package Nutzerverwaltung;

import javafx.fxml.FXML;
import javafx.application.Platform;

/**
 * Verwaltet das Anwendungsfenster
 * @author Harun
 */
public class AnwendungsController {
	
	/**
     * Wird ausgef�hrt, wenn "Abbrechen" geklickt wird
     */
    @FXML
    public void abbrechen() {
        System.out.println("Fenster wird geschlossen!");
        Platform.exit();
    }
}
