/**Benutzer hat keine UserId Exception
 *
 * @author Harun
 * @version 0.1
 * @since 0.1
 */
public class BenutzerNoUserIdException extends Exception{
	/**
	 * Benutzer hat keine UserId Exception
	 * 
	 * @param ausgabe Fehlermeldung: "Benutzer hat keine UserId!"
	 */
	BenutzerNoUserIdException(String ausgabe) {
		super(ausgabe);
	}
}