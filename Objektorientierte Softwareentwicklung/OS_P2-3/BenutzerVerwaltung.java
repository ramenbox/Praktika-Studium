import java.io.IOException;

/**Interface für Benutzerverwaltung
 *
 * @author Harun
 * @version 0.2
 * @since 0.1
 */
public interface BenutzerVerwaltung {
	/**Der Benutzer wird in die Datenhaltung eingetragen.
	 * 
	 * @param benutzer Benutzer mit UserId und PassWort
	 * 
	 * @throws BenutzerAlreadyExistsException
	 * @throws BenutzerNoPasswortException
	 * @throws BenutzerNoUserIdException
	 * @throws BenutzerInvalidPassWortException
	 * @throws BenutzerInvalidUserIdException
	 * @throws IOException
	 * @throws ClassNotFoundException
	 * @see BenutzerAlreadyExistsException
	 * @see BenutzerNoPasswortException
	 * @see BenutzerNoUserIdException
	 * @see BenutzerInvalidPassWortException
	 * @see BenutzerInvalidUserIdException
	 * @see IOException
	 * @see ClassNotFoundException
	 */
	abstract void benutzerEintragen(Benutzer benutzer) throws BenutzerAlreadyExistsException, BenutzerNoPasswortException, BenutzerNoUserIdException, BenutzerInvalidPassWortException, BenutzerInvalidUserIdException, ClassNotFoundException, IOException;
	
	/**Prüft ob Benutzer in Datenhaltung vorhanden ist.
	 * 
	 * @param benutzer Der Benutzer mit UserId und PassWort
	 * @return true if benutzer in Datenhaltung vorhanden, sonst false
	 * @throws IOException
	 * @throws ClassNotFoundException
	 */
	abstract boolean benutzerVorhanden(Benutzer benutzer) throws ClassNotFoundException, IOException;
}
