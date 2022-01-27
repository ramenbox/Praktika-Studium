package Nutzerverwaltung;
import java.io.Serializable;

/**
 * Beeinhaltet Daten eines Benutzers im System
 * 
 * @author Harun
 */
public class Benutzer implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 8269994965984722409L;
	/**
	 * Die userID fungiert als Benutzername des Benutzers
	 */
	public String userID;
	/**
	 * Passwort des Benutzers
	 */
	public char[] passWort;

	/**
	 * Default-Konstruktor zur Erstellung eines neuen Benutzers
	 */
	Benutzer() {
		this.userID = "NaN";
		this.passWort = new char[0];
	}

	/**
	 * Erstellung eines neuen Benutzers mit Benutzername und Passwort
	 * @param benutzername
	 * @param passwort
	 */
	Benutzer(String benutzername, char[] passwort) {
		this.userID = benutzername;
		this.passWort = passwort;
	}

	/**
	 * Prüft, ob es sich um gleiche Benutzer handelt
	 * @param benutzer
	 * @return boolean
	 */
	public boolean equals(Object benutzer) {
		if(benutzer instanceof Benutzer) { // prüft ob benutzer auf ein Objekt vom Typ der Klasse Benutzer verweist
			return ((this.userID.equals(((Benutzer) benutzer).userID)) && (String.copyValueOf(this.passWort)
                    .equals(String.copyValueOf(((Benutzer) benutzer).passWort))));
		}
		else
			return false;
	}
	
	/**
	 *  Ausgabe des Benutzers in der Konsole
	 *  @return String
	 */
	public String toString() { // Überlagerung der Object-Methode
		return ("Benutzername: " + this.userID
				+ " Passwort: " + String.copyValueOf(this.passWort));
	}
}
