package Nutzerverwaltung;

/**
 * Schmeißt eine Exception raus, wenn Benutzername oder Passwort nicht richtig gewählt ist
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
 * Schmeißt eine Exception raus, wenn das Passwort nicht richtig gewählt ist
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
 * Meldet diese Exception, falls ein nicht-existierender Benutzer gelöscht werden muss
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
