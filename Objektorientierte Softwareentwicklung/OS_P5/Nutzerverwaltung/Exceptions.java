package Nutzerverwaltung;

/**
 * Schmei�t eine Exception raus, wenn Benutzername oder Passwort nicht richtig gew�hlt ist
 * @author Harun
 */
class BenutzerdatenRichtlinieException extends Exception {
	private static final long serialVersionUID = 1L;
	public BenutzerdatenRichtlinieException() {}
	/**
	 * Erzeugt eine BenutzerdatenRichtlinieException
	 * @param ausgabe Exception-Beschreibung in der Konsole
	 */
	public BenutzerdatenRichtlinieException(String ausgabe) {
		super(ausgabe);
	}
}

/**
 * Schmei�t eine Exception raus, wenn das Passwort nicht richtig gew�hlt ist
 * @author Harun
 */
class BenutzerVorhandenException extends Exception {
	private static final long serialVersionUID = 1L;
	public BenutzerVorhandenException() {}
	/**
	 * Erzeugt eine BenutzerVorhandenException
	 * @param ausgabe Exception-Beschreibung in der Konsole
	 */
	public BenutzerVorhandenException(String ausgabe) {
		super(ausgabe);
	}
}

/**
 * Meldet diese Exception, falls ein nicht-existierender Benutzer gel�scht werden muss
 * @author Harun
 */
class BenutzerNichtVorhandenException extends Exception {
	private static final long serialVersionUID = 1L;
	public BenutzerNichtVorhandenException() {}
	/**
	 * Erzeugt eine BenutzerNichtVorhandenException
	 * @param ausgabe Exception-Beschreibung in der Konsole
	 */
	public BenutzerNichtVorhandenException(String ausgabe) {
		super(ausgabe);
	}
}
