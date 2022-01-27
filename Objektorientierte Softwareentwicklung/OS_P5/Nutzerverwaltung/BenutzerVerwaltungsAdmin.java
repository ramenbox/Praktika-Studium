package Nutzerverwaltung;
import java.io.*; // Für Eingabe- und Ausgabeströme
import java.util.Vector;

/**
 * Admin kann Benutzer eintragen sowie entfernen
 * @author Harun
 *
 */
public class BenutzerVerwaltungsAdmin implements BenutzerVerwaltung {

	private Vector<Benutzer> datenHaltung;

	BenutzerVerwaltungsAdmin() throws IOException { // VERÄNDERUNG dbInit entfernt datenhaltung initialisierung eingefügt
		this.datenHaltung = new Vector<Benutzer>();
		this.dbLesen();
	}

	/**
	 * Neuer Benutzer wird versucht zu registrieren
	 * @param benutzer
	 * @throws IOException 
	 */
	@Override
	public void benutzerEintragen(Benutzer benutzer) throws BenutzerdatenRichtlinieException, BenutzerVorhandenException, IOException {
		String großbuchstaben = "(.*[A-Z].*)";
		String kleinbuchstaben = "(.*[a-z].*)";
		String zahlen = "(.*[0-9].*)";
		String sonderzeichen = "(.*[@,#,$,%,=,~,+,-,/,_,(,),[,],{,},:,;,!,?].*)";
		this.dbLesen();
		if (benutzerVorhanden(benutzer))
			throw new BenutzerVorhandenException("Der Benutzername existiert bereits!");
		else {
			if (benutzer.passWort.length < 4) {
				throw new BenutzerdatenRichtlinieException("Das Passwort ist zu kurz!");
			} else if (benutzer.passWort.length > 8) {
				throw new BenutzerdatenRichtlinieException("Das Passwort ist zu lang!");
			} else if (!String.copyValueOf(benutzer.passWort).matches(großbuchstaben)) {
				throw new BenutzerdatenRichtlinieException("Das Passwort muss mind. 1 Großbuchstaben haben!");
			} else if (!String.copyValueOf(benutzer.passWort).matches(kleinbuchstaben)) {
				throw new BenutzerdatenRichtlinieException("Das Passwort muss mind. 1 Kleinbuchstaben haben!");
			} else if (!String.copyValueOf(benutzer.passWort).matches(zahlen)) {
				throw new BenutzerdatenRichtlinieException("Das Passwort muss mind. 1 Zahl haben!");
			} else if (String.copyValueOf(benutzer.passWort).matches(sonderzeichen)) {
				throw new BenutzerdatenRichtlinieException("Das Passwort darf keine Sonderzeichen haben!");
			} else if (benutzer.userID.matches(sonderzeichen)) {
				throw new BenutzerdatenRichtlinieException("Der Benutzername darf keine Sonderzeichen enthalten!");
			} else if (benutzer.userID.length() < 4) {
				throw new BenutzerdatenRichtlinieException("Der Benutzername ist zu kurz!");
			} else if (benutzer.userID.length() > 8) {
				throw new BenutzerdatenRichtlinieException("Der Benutzername ist zu lang!");
			}
		}
		this.datenHaltung.add(benutzer);
        this.dbSchreiben();
	}

	/**
	 * Gibt an, ob der Benutzer vorhanden ist
	 * @param benutzer
	 * @return Gibt an, ob der Benutzer vorhanden ist oder nicht
	 * @throws IOException 
	 */
	@Override
	public boolean benutzerVorhanden(Benutzer benutzer) throws IOException {
		this.dbLesen();
		return datenHaltung.contains(benutzer);
	}
		
	/**
	 * Löscht einen Benutzer, insofern er existiert
	 * 
	 * @param benutzer
	 * @throws BenutzerNichtVorhandenException Der Benutzer existiert nicht in der
	 *                                Datenhaltung
	 * @throws IOException 
	 */
	void benutzerLoeschen(Benutzer benutzer) throws BenutzerNichtVorhandenException, IOException {
		this.dbLesen();
		if (benutzerVorhanden(benutzer)) {
			datenHaltung.remove(benutzer);
			this.dbSchreiben(); // NEU
		}
		else
			throw new BenutzerNichtVorhandenException("Dieser Benutzer existiert nicht in der Datenhaltung!!");
	}
	//JAVA DOC TEST / FÄLLE EXCEPTION / DATEI SCHLIE?EN
	/**
	 * Liest Datei in die Datenstruktur ein
	 * @author Harun
	 * @throws IOException 
	 */
	void dbLesen() throws IOException {
		ObjectInputStream in = null;
        try {
            in = new ObjectInputStream(
                    new FileInputStream("database.db"));
            this.datenHaltung = (Vector<Benutzer>) in.readObject();
            in.close();
        } catch (IOException e) {
            System.out.println("dbLesen: " + e.getMessage() + " try again.");
        } catch (ClassNotFoundException e) {
            System.err.println(e.getMessage());
        } finally {
        	if (in != null) in.close();
        }
    }
	
	/**
	 * Erstellt neue Datenstruktur, serialisert dies und legt es in der Datei "database.db" ab
	 * @Harun
	 * @throws IOException
	 */
	void dbInit() throws IOException {
		this.datenHaltung = new Vector<Benutzer>();
		this.dbSchreiben();
	}
	
	/**
	 * (Über)schreibt in die Datei, die Objekte
	 * @throws IOException 
	 * @Author Harun
	 */
	void dbSchreiben() throws IOException {
		ObjectOutputStream out = null;
		try {
            out = new ObjectOutputStream(new FileOutputStream("database.db"));
            out.writeObject(datenHaltung);
            out.close();
        } catch (IOException e) {
            System.err.println("dbSchreiben " + e.getMessage());
        } finally {
        	if (out != null) out.close();
        }
	}
	
	/**
	 * Löscht die Datei
	 * @throws Exception
	 */
	void dbLoeschen() throws Exception {
        File file = new File("database.db");
        if (!file.delete()) {
            throw new Exception("Could not delete db file.");
        }
    }

	/**
	 * Gibt die Datenhaltung zurück, da es private ist
	 * @return datenHaltung
	 */
	public Vector<Benutzer> getDatenHaltung() {
		return datenHaltung;
	}
}
