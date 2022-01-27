/**Benutzer wurde nicht gefunden Exception
 *
 * @author Harun
 * @version 0.1
 * @since 0.1
 */
public class BenutzerNotFoundException extends Exception{
	/**
	 * Benutzer wurde nicht gefunden Exception
	 * 
	 * @param ausgabe Fehlermeldung: "Benutzer existiert nicht!"
	 */
	BenutzerNotFoundException(String ausgabe) {
		super(ausgabe);
	}
}
