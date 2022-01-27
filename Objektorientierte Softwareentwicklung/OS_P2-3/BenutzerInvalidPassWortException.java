/**Benutzer hat kein valides Passwort Exception
 *
 * @author Harun
 * @version 0.1
 * @since 0.1
 */
public class BenutzerInvalidPassWortException extends Exception{
	/**
	 * Benutzer hat kein valides Passwort Exception
	 * 
	 * @param ausgabe Fehlermeldung: "Benutzer hat kein gueltiges Passwort!"
	 */
	BenutzerInvalidPassWortException(String ausgabe) {
		super(ausgabe);
	}

}
