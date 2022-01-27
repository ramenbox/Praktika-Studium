import java.io.Serializable;

/**Represent Benutzer mit UserId und PassWort
 *
 * @author Harun
 * @version 0.3
 * @since 0.2
 */
public class Benutzer implements Serializable {
	private String userId = "";
	private char[] passWort = {};

	/**
	 * Default-Konstruktor
	 */
	Benutzer() {}

	/** Konstruktor initialisert Attribute
	 *
	 * @param uid UserId des Benutzers
	 * @param pw PassWort des Benutzers
	 */
	Benutzer(String uid, char[] pw) {
		this.userId = uid;
		this.passWort = pw;
	}

	/**
	 * Setter für UserId
	 *
	 * @param uid UserId
	 */
	public void setUserId(String uid) {
		this.userId = uid;
	}

	/**
	 * Getter für UserId
	 * @return UserId
	 */
	public String getUserId() {
		return this.userId;
	}

	/**
	 * Setter für Password
	 *
	 * @param pw PassWort
	 */
	public void setPassWort(String pw) {
		this.passWort = pw.toCharArray();
	}

	/**
	 * Getter für PassWort
	 * @return PassWort
	 */
	public String getPassWort() {
		return new String().copyValueOf(this.passWort);
	}

	/** Methode zum Vergleich der Attribute zweier Benutzer-Objekte
	 *
	 * @param obj Parameter von der Klasse Object
	 * @return true bei gleichen oder false bei NICHT gleichen Attrib. (userId, PassWort)
	 */
	@Override
	public boolean equals(Object obj) {
		// Kein null Objekt
		if (obj == null) {
			return false;
		}
		// Vergleich eines Objektes mit sich selber ist autom. true
		if (obj == this) {
			return true;
		}

		// Objekt obj ist keine Instanz von Benutzer ist autom. false
		if (!(obj instanceof Benutzer)) {
			return false;
		}

		// Typecast für den eigentlichen Vergleich
		Benutzer that = (Benutzer) obj;

		// Exception sollten hier auch ausgegeben werden in Methoden, die dies hier aufrufen
		if (this.userId == null || that.userId == null) {
			return false;
		}
		/*
		// UserId muss nicht leer sein
		if (this.userId.length() == 0 || that.userId.length() == 0) {
			return false;
		}
		// UserId darf nicht unterschiedlich lang sein
		if (this.userId.length() != that.userId.length()) {
			return false;
		}
		*/

		// Kein Null bitte
		if (this.passWort == null || that.passWort == null) {
			return false;
		}

		/*
		// Passwort muss nicht leer sein
		if (this.passWort.length == 0 || that.passWort.length == 0) {
			return false;
		}
		*/

		// Unterschiedliche Länge von Passwörtern führt zum Ausschluss
		if (this.passWort.length != that.passWort.length) {
			return false;
		}

		// char-Array hat keine Überlagerung der equals Methode
		// Deswegen die Umwandlung in ein String Objekt
		String thisPW = String.copyValueOf(this.passWort);
		String thatPW = String.copyValueOf(that.passWort);
		// Attribute der Benutzer-Objekte vergleichen
		return this.userId.equals(that.userId) && thisPW.equals(thatPW);
	}

	/** Methode zur Konvertierung des Benutzer-Objekt zum String
	 *
	 * @return String aus Attributen
	 */
	@Override
	public String toString() {
		// Fehler durch Exception abfangen
		return "UserId ist " + this.userId + " und PassWort ist " + String.copyValueOf(this.passWort); //((this.passWort != null) ? String.copyValueOf(this.passWort) : "null");
	}
}