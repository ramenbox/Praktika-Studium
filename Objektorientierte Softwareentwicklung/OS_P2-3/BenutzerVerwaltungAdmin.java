import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
/**Benutzerverwaltung für Administration der Benutzer mit Persistenz.
 *
 * @author Harun
 * @version 0.2
 * @since 0.1
 */
public class BenutzerVerwaltungAdmin implements BenutzerVerwaltung {
	private ArrayList<Benutzer> benutzerListe; // Zur Datenhaltung
	private String filename; //String Dateiname
	
	
	/**
	 * Default-Konstruktor
	 */
	public BenutzerVerwaltungAdmin() {
	}
	
	/**
	 * Konstruktor mit Initialisierung des Dateipfad-/namen. 
	 * 
	 * @param fn Dateipfad-/name
	 * @throws IOException 
	 */
	public BenutzerVerwaltungAdmin(String fn) { //Übergebe Dateiname
		this.filename = fn;
	}
	
	/**Der Benutzer wird in die Datenhaltung eingetragen.
	 * 
	 * @param benutzer Benutzer mit UserId und PassWort
	 * 
	 * @exception BenutzerAlreadyExistsException Benutzer exsitiert bereits.
	 * @see BenutzerAlreadyExistsException
	 * @exception BenutzerNoPasswortException Benutzer hat kein Passwort.
	 * @see BenutzerNoPasswortException
	 * @exception BenutzerNoUserIdException Benutzer hat keine UserID.
	 * @see BenutzerNoUserIdException
	 * @exception BenutzerInvalidPassWortException Benutzer hat ein ungültiges Passwort.
	 * @see BenutzerInvalidPassWortException
	 * @exception BenutzerInvalidUserIdException Benutzer hat eine ungütlige UserId.
	 * @see BenutzerInvalidUserIdException
	 * @throws IOException 
	 * @see IOException
	 * @throws ClassNotFoundException
	 * @see ClassNotFoundException 
	 */
	public void benutzerEintragen(Benutzer benutzer) throws BenutzerAlreadyExistsException, BenutzerNoPasswortException, BenutzerNoUserIdException, BenutzerInvalidPassWortException, BenutzerInvalidUserIdException, ClassNotFoundException, IOException {
		this.readFromFile();
		
		String uid = benutzer.getUserId();
		String pw = benutzer.getPassWort();
		
		if (benutzerVorhanden(benutzer)) {
			throw new BenutzerAlreadyExistsException("Benutzer ist schon vorhanden!");
		}
		if (uid.length() == 0 || uid == "") {
			throw new BenutzerNoUserIdException("Benutzer hat keine UserId!");
		}
		if (pw.length() == 0 || pw == "") {
			throw new BenutzerNoPasswortException("Benutzer hat kein Passwort!");
		}
		if (pw.length() < 7 || pw.length() > 512) {
			throw new BenutzerInvalidPassWortException("Benutzer hat kein gueltiges Passwort!");
		}
		if (uid.length() < 2 ||uid.length() > 20) {
			throw new BenutzerInvalidUserIdException("Benutzer hat keine gueltige UserId!");
		}
		
		// Addiere Benutzer
		this.benutzerListe.add(benutzer);
		
		// Schreibe die neuen Daten ins Dateisystem
		this.writeToFile();
	}
	
	/**Prüft, ob das Parameterobjekt in der Datenhaltung vorhanden ist.
	 * 
	 * @param benutzer Benutzer mit UserId und PassWort
	 * @return true wenn Benutzer vorhanden, sonst false
	 * @throws IOException 
	 * @throws ClassNotFoundException 
	 */
	public boolean benutzerVorhanden(Benutzer benutzer) throws ClassNotFoundException, IOException {
		this.readFromFile();
		
		if(this.benutzerListe.contains(benutzer)) {
			return true;
		}
		
		return false;
	}
	
	/**Das Parameterobjekt wird aus der Datenhaltung entfernt.
	 * 
	 * @param benutzer Der zu löschender Benutzer
	 * @exception BenutzerNotFoundException Benutzer muss in der Datenhaltung vorhanden sein, damit es daraus gelöscht werden kann.
	 * @see BenutzerNotFoundException
	 * @throws IOException
	 * @throws ClassNotFoundException 
	 */
	public void benutzerLoeschen(Benutzer benutzer) throws BenutzerNotFoundException, IOException, ClassNotFoundException{
		this.readFromFile();
		
		if (!benutzerVorhanden(benutzer)) {
			throw new BenutzerNotFoundException("Benutzer existiert nicht!");
		}
		
		//Lösche Benutzer von Benutzerliste
		this.benutzerListe.remove(benutzer);
		
		
		this.writeToFile();
	}
	
	/**
	 * Legt ein neues leeres Objekt der Datenstruktur an, serialisiert und legt es im Dateisystem ab.
	 * 
	 * @throws IOException Fehlermeldung für Input und Output
	 * 
	 */
	public void dbInit() throws IOException {
		// Legen eines leeren Objekt der Datenstruktur
		this.benutzerListe = new ArrayList<Benutzer>();
		
		// Serialisiert und legt das leere Objekt im Dateisystem ab
		FileOutputStream fs = new FileOutputStream(this.filename);
		ObjectOutputStream os = new ObjectOutputStream(fs);
		
		os.writeObject(this.benutzerListe);

		os.close();
		fs.close();
	}
	
	/**
	 * Liest persistente Daten from Dateisystem und init in Datenstruktur.
	 * 
	 * @throws IOException Fehlermeldung für Input und Output
	 * @throws ClassNotFoundException Klasse Benutzer nicht gefunden
	 */
	public void readFromFile() throws IOException, ClassNotFoundException {
		// Deserialisierung
		FileInputStream fis = new FileInputStream(this.filename);
		ObjectInputStream ois = new ObjectInputStream(fis);
		
		// Initialisierung der persistenten Daten
		Object obj = ois.readObject(); // Liest aus Datei
		
		ois.close();
		fis.close();

		//Typecast des Objects
		this.benutzerListe = (ArrayList<Benutzer>) obj;
	}
	
	/**
	 * Schreibt Daten von Datenstruktur ins Dateisystem persistent.
	 * 
	 * @throws IOException Fehlermeldung für Input und Output
	 * @throws ClassNotFoundException Klasse Benutzer nicht gefunden
	 */
	public void writeToFile() throws IOException {
		// Serialisiert und legt das leere Objekt im Dateisystem ab
		FileOutputStream fs = new FileOutputStream(this.filename);
		ObjectOutputStream os = new ObjectOutputStream(fs);
		
		// Schreibt ins Dateisystem
		os.writeObject(this.benutzerListe);

		os.close();
		fs.close();
	}
}
