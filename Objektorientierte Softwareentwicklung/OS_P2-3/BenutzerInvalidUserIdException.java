/**Benutzer hat kein valide UserId Exception.
 *
 * @author Harun
 * @version 0.1
 * @since 0.1
 */
public class BenutzerInvalidUserIdException extends Exception {
	/**
	 * Benutzer hat kein valide UserId Exception.
	 * 
	 * @param ausgabe Fehlermeldung: "Benutzer hat keine gueltige UserId!"
	 */
	BenutzerInvalidUserIdException(String ausgabe) {
		super(ausgabe);
	}
}
