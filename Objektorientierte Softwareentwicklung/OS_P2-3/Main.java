import java.io.IOException;
import java.util.Scanner;

/**Hautprogramm für Benutzerverwaltung
 *
 * @author Harun
 * @version 0.1
 */
public class Main {
	/**Entrypoint for Anwendung
	 * 
	 * @param args Argumente extern
	 */
	public static void main(String []args) {
		// Admin muss die Benutzer verwalten
		BenutzerVerwaltungAdmin admin = null;
		try {
			admin = new BenutzerVerwaltungAdmin("data");
			admin.dbInit();
		} catch (IOException e1) {
			System.out.println("Daten konnten nicht persistent gespeichert werden: " + e1);
		}
		
		// Erstelle 13 neue Benutzer
		for(int i = 0; i < 13; i++) {
			Benutzer user = new Benutzer("user"+i, ("useruseruser"+i).toCharArray());
			try {
				admin.benutzerEintragen(user);
				System.out.println(user);
			} catch(BenutzerAlreadyExistsException e) {
				System.out.println(e);
			} catch (BenutzerNoPasswortException e) {
				e.printStackTrace();
			} catch (BenutzerNoUserIdException e) {
				e.printStackTrace();
			} catch (BenutzerInvalidPassWortException e) {
				e.printStackTrace();
			} catch (BenutzerInvalidUserIdException e) {
				e.printStackTrace();
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		
		// Testcase with expected and actual output
		
		// Prüfe ob 13 Benutzer alle existieren
		for(int i = 0; i < 13; i++) {
			Benutzer user = new Benutzer("user"+i, ("useruseruser"+i).toCharArray());
			try {
				if (admin.benutzerVorhanden(user)) {
					System.out.println(user + " existiert.");
				}
				else {
					System.out.println(user + " existiert nicht.");
				}
			} catch (ClassNotFoundException | IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		System.out.println("---------------------------------------------------------");
		
		System.out.println("Expected: Ein Benutzer wurde entfernt.");
		System.out.print("Actual: ");
		// Benutzer einfügen und löschen
		Benutzer testUser = new Benutzer("testUser", "testUser1234567".toCharArray());
		
		try {
			admin.benutzerEintragen(testUser);
			admin.benutzerLoeschen(testUser);
			if (!admin.benutzerVorhanden(testUser)) {
				System.out.println("Ein Benutzer wurde entfernt.");
			}
			
			System.out.println();
			
			// Teste das Löschen eines nicht existierenden Benutzer
			System.out.println("Expected: BenutzerNotFoundException: Benutzer existiert nicht!\r\n"
					+ "	at BenutzerVerwaltungAdmin.benutzerLoeschen(BenutzerVerwaltungAdmin.java:109)\r\n"
					+ "	at Main.main(Main.java:80)");
			System.out.print("Actual: ");
			
			admin.benutzerLoeschen(testUser);
			// Runtime exception
		} catch (BenutzerAlreadyExistsException e) {
			e.printStackTrace();
		} catch (BenutzerNotFoundException e) {
			e.printStackTrace();
		} catch (BenutzerNoPasswortException e) {
			e.printStackTrace();
		} catch (BenutzerNoUserIdException e) {
			e.printStackTrace();
		} catch (BenutzerInvalidPassWortException e) {
			e.printStackTrace();
		} catch (BenutzerInvalidUserIdException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println();
		
		System.out.println("Expected: Leere UserID erkannt: BenutzerNoUserIdException: Benutzer hat keine UserId!");
		System.out.print("Actual: ");
		// Teste leere UserID
		try {
			admin.benutzerEintragen(new Benutzer("", "DasStarkePassword".toCharArray()));
		} catch (BenutzerAlreadyExistsException e) {
			e.printStackTrace();
		} catch (BenutzerNoPasswortException e) {
			e.printStackTrace();
		} catch (BenutzerNoUserIdException e) {
			System.err.println("Leere UserID erkannt: " + e);
		} catch (BenutzerInvalidPassWortException e) {
			e.printStackTrace();
		} catch (BenutzerInvalidUserIdException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		System.out.println("Expected: Lange UserID erkannt: BenutzerInvalidUserIdException: Benutzer hat keine gueltige UserId!");
		System.out.print("Actual: ");
		
		// Teste lange UserID
		try {
			admin.benutzerEintragen(new Benutzer("MeinUserIdIstZuLang1234", "DasStarkePassword".toCharArray()));
		} catch (BenutzerAlreadyExistsException e) {
			e.printStackTrace();
		} catch (BenutzerNoPasswortException e) {
			e.printStackTrace();
		} catch (BenutzerNoUserIdException e) {
			e.printStackTrace();
		} catch (BenutzerInvalidPassWortException e) {
			e.printStackTrace();
		} catch (BenutzerInvalidUserIdException e) {
			System.err.println("Lange UserID erkannt: " + e);
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		System.out.println("Expected: Kurze UserID erkannt: BenutzerInvalidUserIdException: Benutzer hat keine gueltige UserId!");
		System.out.print("Actual: ");
		
		// Teste kurze UserID
		try {
			admin.benutzerEintragen(new Benutzer("a", "DasStarkePassword".toCharArray()));
		} catch (BenutzerAlreadyExistsException e) {
			e.printStackTrace();
		} catch (BenutzerNoPasswortException e) {
			e.printStackTrace();
		} catch (BenutzerNoUserIdException e) {
			e.printStackTrace();
		} catch (BenutzerInvalidPassWortException e) {
			e.printStackTrace();
		} catch (BenutzerInvalidUserIdException e) {
			System.err.println("Kurze UserID erkannt: " + e);
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println();
		
		System.out.println("Expected: Leeres Passwort erkannt: BenutzerNoPasswortException: Benutzer hat kein Passwort!");
		System.out.print("Actual: ");
		
		// Teste leeres Passwort
		try {
			admin.benutzerEintragen(new Benutzer("TestUser", "".toCharArray()));
		} catch (BenutzerAlreadyExistsException e) {
			e.printStackTrace();
		} catch (BenutzerNoPasswortException e) {
			System.err.println("Leeres Passwort erkannt: " + e);
		} catch (BenutzerNoUserIdException e) {
			e.printStackTrace();
		} catch (BenutzerInvalidPassWortException e) {
			e.printStackTrace();
		} catch (BenutzerInvalidUserIdException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println("Expected: Kurzes Passwort erkannt: BenutzerInvalidPasswortException: Benutzer hat kein gueltige Passwort!");
		System.out.print("Actual: ");
		
		// Teste kurzes Passwort
		try {
			admin.benutzerEintragen(new Benutzer("TestUser", "1234".toCharArray()));
		} catch (BenutzerAlreadyExistsException e) {
			e.printStackTrace();
		} catch (BenutzerNoPasswortException e) {
			e.printStackTrace();
		} catch (BenutzerNoUserIdException e) {
			e.printStackTrace();
		} catch (BenutzerInvalidPassWortException e) {
			System.err.println("Kurzes Passwort erkannt: " + e);
		} catch (BenutzerInvalidUserIdException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		System.out.println("Expected: Langes Passwort erkannt: BenutzerInvalidPasswortException: Benutzer hat kein gueltige Passwort!");
		System.out.print("Actual: ");
		
		// Teste langes Passwort
		String longPassword = "";
		for(int i = 0; i < 513; i++)
			longPassword += 'a';
		try {
			admin.benutzerEintragen(new Benutzer("TestUser", longPassword.toCharArray()));
		} catch (BenutzerAlreadyExistsException e) {
			e.printStackTrace();
		} catch (BenutzerNoPasswortException e) {
			e.printStackTrace();
		} catch (BenutzerNoUserIdException e) {
			e.printStackTrace();
		} catch (BenutzerInvalidPassWortException e) {
			System.err.println("Langes Passwort erkannt: " + e);
		} catch (BenutzerInvalidUserIdException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println("---------------------------------------------------");
		
		// User menu
		boolean quit = false;
		Scanner in = new Scanner(System.in);
		do {
			System.out.print("Admin Panel\n"
					+ "1) Benutzer eintragen\n"
					+ "2) Benutzer loeschen\n"
					+ "3) Benutzer suchen\n"
					+ "4) Beenden\n"
					+ "?>");
			
			int choice = in.nextInt();
			
			String userid = "";
			String password = "";
			
			switch(choice) {
			case 1:
				System.out.print("USERID: ");
				userid = in.next();
				System.out.print("PASSWORT: ");
				password = in.next();
				
				Benutzer new_user = new Benutzer(userid, password.toCharArray());
				try {
					if (admin.benutzerVorhanden(new_user)) {
						System.out.println("[-] Benutzer ist schon vorhanden!");
					}
					else {
						try {
							admin.benutzerEintragen(new_user);
							System.out.println("[+] Benutzer wurde hinzugefuegt.");
						} catch (BenutzerAlreadyExistsException e) {
							e.printStackTrace();
						} catch (BenutzerNoPasswortException e) {
							e.printStackTrace();
						} catch (BenutzerNoUserIdException e) {
							e.printStackTrace();
						} catch (BenutzerInvalidPassWortException e) {
							e.printStackTrace();
						} catch (BenutzerInvalidUserIdException e) {
							e.printStackTrace();
						} catch (ClassNotFoundException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						} catch (IOException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						
					}
				} catch (ClassNotFoundException | IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				break;
			case 2:
				System.out.print("USERID: ");
				userid = in.next();
				System.out.print("PASSWORT: ");
				password = in.next();
				
				
				Benutzer user_to_be_deleted = new Benutzer(userid, password.toCharArray());
				try {
					admin.benutzerLoeschen(user_to_be_deleted);
					System.out.println("[+] Benutzer wurde geloescht.");
				} catch (BenutzerNotFoundException e) {
					e.printStackTrace();
				} catch (ClassNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				
				break;
			case 3:
				System.out.print("USERID: ");
				userid = in.next();
				System.out.print("PASSWORT: ");
				password = in.next();
				
				
				Benutzer user_to_be_searched = new Benutzer(userid, password.toCharArray());
				try {
					if (admin.benutzerVorhanden(user_to_be_searched)) {
						System.out.println("[+] Benutzer wurde gefunden.");
					}
					else {
						System.out.println("[-] Benutzer wurde nicht gefunden.");
					}
				} catch (ClassNotFoundException | IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				break;
			case 4:
				quit = true;
				break;
			default:
				break;
			}
			
		} while (!quit);
		
	}
}
