/** Benutzer existiert bereits Exception
 * 
 * @author Harun
 * @version 0.1
 * @since 0.1
 */
public class BenutzerAlreadyExistsException extends Exception{
	/**
	 * Benutzer existiert bereits Exception
	 * 
	 * @param ausgabe Fehlermeldung: "Benutzer ist schon vorhanden!"
	 */
	BenutzerAlreadyExistsException(String ausgabe) {
			super(ausgabe);
	}
}