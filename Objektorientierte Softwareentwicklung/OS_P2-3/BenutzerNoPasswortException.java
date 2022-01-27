/**Benutzer hat kein Passwort Exception
 *
 * @author Harun
 * @version 0.1
 * @since 0.1
 */
public class BenutzerNoPasswortException extends Exception{
	/**
	 * Benutzer hat kein Passwort Exception
	 * 
	 * @param ausgabe Fehlermeldung: "Benutzer hat kein Passwort!"
	 */
	BenutzerNoPasswortException(String ausgabe) {
		super(ausgabe);
	}
}
