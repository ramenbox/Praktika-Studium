package Nutzerverwaltung;

import java.io.IOException;

/**
 * Verwaltet die Funktionen der Benutzerverwaltung
 * @author Harun
 */

public interface BenutzerVerwaltung {
	/**
	 * Neuer Benutzer wird registriert
	 * @param benutzer
	 * 				Der hinzuzuf�gende Benutzer
	 * @throws BenutzerdatenRichtlinieException 
	 * 				Benutzerdatenrichtlinie ist verletzt
	 * @throws BenutzerVorhandenException
	 * 				Der Benutzernatme existiert bereits
	 * @throws IOException
	 */	
	void benutzerEintragen(Benutzer benutzer) throws BenutzerdatenRichtlinieException, BenutzerVorhandenException, IOException; // Exceptions werden durch throw weitergeleitet
	
	/**
	 * �berpr�ft, ob der Benutzer bereits registriert ist
	 * @param benutzer
	 * 				Der hinzuzuf�gende Benutzer
	 * @return true, falls Benuzer existiert 
	 * 				sonst false
	 * @throws IOException 
	 */
	boolean benutzerVorhanden(Benutzer benutzer) throws IOException;
}
