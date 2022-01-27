import static org.junit.jupiter.api.Assertions.*;

import java.io.IOException;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

/**
 *
 * @author Harun
 * @version 0.1
 */
class TestJunit {
	
	 // Admin muss die Benutzer verwalten
	private BenutzerVerwaltungAdmin admin;
	
	/**
	 * Methode wird ausgeführt bevor jeden Test
	 * 
	 * @throws Exception
	 */
	@BeforeEach
	void beforeEach() throws Exception {
		admin = new BenutzerVerwaltungAdmin("data"); //Datenbank "main"
		//admin.dbInit(); //Leeres Oject der Datenstruktur ArrayList in Datei
	}
	
	/** Instanziiert Objekte der Klasse Benutzer-Konstruktor mit Parameter
	 * und prüft die Methoden equals und toString auf richtige Funktionalitäten.
	 * 
	 */
	@Test
	void testBenutzer() {
		// Teste Konstruktor mit Parameterübergabe von einem String und einem Char-Array
		Benutzer alice = new Benutzer("alice", "OfWonderlande!".toCharArray());
		Benutzer bob = new Benutzer("bob123", "4566774".toCharArray());
		
		// Teste equals-Methode
		assertEquals(alice.equals(alice), true);		 // Selbe Instanz von Benutzer
		assertEquals(alice.equals(bob), false);			 // Verschiedene Instanz
		
		assertEquals(bob.equals(bob), true);		 
		assertEquals(bob.equals(alice), false);		
		
		// Teste toString-Methode
		assertEquals(alice.toString(), "UserId ist alice und PassWort ist OfWonderlande!");
		assertNotEquals(alice.toString(), "UserId ist alice123 und PassWort ist Passwort123");
		assertNotEquals(alice.toString(), "UserId ist bob123 und PassWort ist 4566774");
		
		assertEquals(bob.toString(), "UserId ist bob123 und PassWort ist 4566774");
		assertNotEquals(bob.toString(), "UserId ist alice123 und PassWort ist Passwort123");
		assertNotEquals(bob.toString(), "UserId ist null und PassWort ist null");
		
		// Teste Default-Konstruktor
		Benutzer userZero = new Benutzer();
		assertEquals(userZero.equals(new Benutzer()), true);
		assertEquals(userZero.toString(), "UserId ist  und PassWort ist ");
	}
	
	/** Teste Methoden der BenutzerVerwaltungAdmin Klasse
	 * 
	 * @throws BenutzerAlreadyExistsException 
	 * @throws BenutzerNotFoundException 
	 * @throws BenutzerNoPasswortException
	 * @throws BenutzerNoUserIdException
	 * @throws BenutzerInvalidPassWortException
	 * @throws BenutzerInvalidUserIdException 
	 * @throws IOException 
	 * @throws ClassNotFoundException 
	 */
	@Test
	void testAdd() throws BenutzerAlreadyExistsException, BenutzerNoPasswortException, BenutzerNoUserIdException, BenutzerInvalidPassWortException, BenutzerInvalidUserIdException, ClassNotFoundException, IOException {
		// Erstelle 100 neue Benutzer
		for(int i = 0; i < 100; i++) {
			Benutzer user = new Benutzer("user"+i, ("useruseruser"+i).toCharArray());
			admin.benutzerEintragen(user);
		}
		
		// Prüfe ob 100 Benutzer alle existieren
		for(int i = 0; i < 100; i++) {
			Benutzer user = new Benutzer("user"+i, ("useruseruser"+i).toCharArray());
			assertEquals(admin.benutzerVorhanden(user), true);
		}
	}
	
	/**
	 * Teste BenutzerAlreadyExistsException Exception der Methode benutzerEintragen
	 * 
	 * @throws BenutzerAlreadyExistsException
	 * @throws BenutzerNotFoundException
	 * @throws BenutzerNoPasswortException
	 * @throws BenutzerNoUserIdException
	 * @throws BenutzerInvalidPassWortException
	 * @throws BenutzerInvalidUserIdException
	 * @throws IOException 
	 * @throws ClassNotFoundException 
	 */
	@Test
	void testBenutzerAlreadyExistsException() throws BenutzerAlreadyExistsException, BenutzerNoPasswortException, BenutzerNoUserIdException, BenutzerInvalidPassWortException, BenutzerInvalidUserIdException, ClassNotFoundException, IOException {
		Benutzer testUser = new Benutzer("tester0", "IchBinAlpha!".toCharArray());
		Benutzer testUserKlon = testUser; // Wir klonen die Testperson
		
		admin.benutzerEintragen(testUser);
		// Wurde richtig in Datenhaltung eingefügt?
		assertEquals(admin.benutzerVorhanden(testUser), true);
		
		// Teste BenutzerAlreadyExistsException
		assertThrows(BenutzerAlreadyExistsException.class, () -> {
			admin.benutzerEintragen(testUserKlon); // Klon sollte nicht eingetragen werden können
		});
	}
	
	/**
	 * Teste BenutzerNotFoundException Exception der Methode benutzerLoeschen
	 * 
	 */
	@Test
	void testBenutzerNotFoundException() {
		Benutzer testUser = new Benutzer(); // In diesem TestCase ist es total egal, ob Benutzer eine UserID oder PassWort hat

		// Wird nicht in die Liste eingetragen

		// Teste BenutzerNotFoundException
		assertThrows(BenutzerNotFoundException.class, () -> {
			admin.benutzerLoeschen(testUser); // Kann gar nicht existieren, kann nicht gelöscht werden
		});
	}
	
	/**
	 * Teste BenutzerNoUserIdException Exception der Methode benutzerEintragen
	 */
	@Test
	void testBenutzerNoUserIdException() {
		// 1. Benutzer hat keine UserID und auch kein PassWort
		Benutzer testUser = new Benutzer();
		// 2. Benutzer hat keine UserID aber ein PassWort
		Benutzer testUserWithPasswort = new Benutzer("", "EinPasswort".toCharArray());
		
		// Teste BenutzerNoUserIdException - ID
		assertThrows(BenutzerNoUserIdException.class, () -> {
			admin.benutzerEintragen(testUser); // Keine UserId
		});
		
		// Teste BenutzerNoUserIdException - ID
		assertThrows(BenutzerNoUserIdException.class, () -> {
			admin.benutzerEintragen(testUserWithPasswort); // Keine UserId - hängt nur von ID ab
		});
	}
	
	/**
	 * Teste BenutzerNoPasswortException Exception der Methode benutzerEintragen
	 * 
	 */
	@Test
	void testBenutzerNoPasswortException() {
		// Benutzer hat eine UserID aber kein PassWort
		Benutzer testUser = new Benutzer("KeinPasswort", "".toCharArray());

		// Teste BenutzerNoPasswortException
		assertThrows(BenutzerNoPasswortException.class, () -> {
			admin.benutzerEintragen(testUser); // Kein Passwort
		});
	}
	
	/**
	 * Teste BenutzerInvalidPassWortException Exception der Methode benutzerEintragen
	 * 
	 */
	@Test
	void testBenutzerInvalidPassWortException() {
		// Benutzer hat eine UserID aber kein PassWort
		Benutzer testUser = new Benutzer("JustATest", "1234".toCharArray());
		
		// Teste BenutzerInvalidPassWortException in benutzerEintragen Methode
		assertThrows(BenutzerInvalidPassWortException.class, () -> {
			admin.benutzerEintragen(testUser); // Passwort muss mindestens > 12
		});

		
		// Teste Benutzer mit über 512 Zeichen langes Passwort
		String longPassword = "";
		for(int i = 0; i < 513; i++)
			longPassword += 'a';

		Benutzer testUser1 = new Benutzer("HabLangesPW", longPassword.toCharArray());
		assertThrows(BenutzerInvalidPassWortException.class, () -> {
			admin.benutzerEintragen(testUser1); // Password über das Maximum ist VERBOTEN!
		});
	}
	
	/**
	 * Teste BenutzerInvalidUserIdException Exception der Methode benutzerEintragen
	 * 
	 */
	@Test
	void testBenutzerInvalidUserIdException() {
		// Benutzer hat eine ungültige UserID (> 20 Zeichen lang)
		String invalidUID = "";
		for(int i = 0; i < 21; i++)
			invalidUID += 'a';
		Benutzer testUser1 = new Benutzer(invalidUID, "testPassword123".toCharArray());
		// Benutzer hat eine ungütlige UserID (kleiner als 1 Zeichen lang)
		Benutzer testUser2 = new Benutzer("a", "testPassword123".toCharArray());
		
		// Teste BenutzerInvalidUserIdException in benutzerEintragen Methode
		assertThrows(BenutzerInvalidUserIdException.class, () -> {
			admin.benutzerEintragen(testUser1); // UserId darf nicht größer 20 Zeichen lang sein
		});

		assertThrows(BenutzerInvalidUserIdException.class, () -> {
			admin.benutzerEintragen(testUser2); // UserId darf nicht kleiner 1 Zeichen lang sein
		});
	}
	}