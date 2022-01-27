package Nutzerverwaltung;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
//import java.util.Scanner;
import javafx.fxml.FXMLLoader;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.Parent;
import javafx.stage.Stage;

/**
 * Übernimmt den Aufruf aller Fenster
 * @author Harun
 *
 */
public class MainApplication extends Application {
	
	private BenutzerVerwaltungsAdmin Admin;
	private AnmeldungsController anmeldungsController;
	private LoginController loginController;
	private Stage Pstage;
	
	/**
	 * Dieser Methode wird das erse Fenster übergeben und wird nach Eingabe überschrieben
	 */
	@Override 
	public void start(Stage PrimaryStage) throws Exception {
		this.Admin = new BenutzerVerwaltungsAdmin();
		
		System.out.println("Möchten Sie die Datenbank initialisieren ? (0/1)");
		BufferedReader din = new BufferedReader(new InputStreamReader(System.in));
		int dbInitialisieren = Integer.parseInt(din.readLine());
		if(dbInitialisieren == 1) {
			this.Admin.dbInit();
		} 
		this.Pstage = PrimaryStage; // Wenn nicht, dann NullPointerException, weil leer
		this.stage("login.fxml", "Login") ;
	}
	
	/**
	 * Setzt die Stage-Anforderung um
	 * @param view
	 * Gibt die FXML-Datei weiter
	 * @param title
	 * Gibt den Titel der Stage weiter
	 */
	private void stage(String view, String title) {
		try {
			FXMLLoader loader = new FXMLLoader(getClass().getResource(view));
			Parent Universal = (Parent) loader.load();
			switch(view) {
			case "login.fxml":
				this.loginController = loader.getController();
				this.loginController.setMainApplication(this);
				break;
			case "anmeldung.fxml":
				this.anmeldungsController = loader.getController();
				this.anmeldungsController.setMainApplication(this);
				break;
			}
			this.Pstage.setTitle(title);
			this.Pstage.setScene(new Scene(Universal));
			this.Pstage.show();
		} catch (IOException e) {
            e.printStackTrace();
            System.out.println(e.getMessage());
        }
	}
	
	/**
	 * Bei Neuanmeldung wird die Anmeldescene aufgerufen
	 */
	void neuAnmeldung() {
		this.stage("anmeldung.fxml", "Anmeldung");
	}
	
	/**
	 * Neuer Benutzer wird versucht durch Methode benutzerEintragen(benutzer) zu registrieren
	 * @param benutzer
	 * @throws BenutzerdatenRichtlinieException
	 * @throws BenutzerVorhandenException
	 * @throws IOException
	 */
	void neuerBenutzer(Benutzer benutzer) {
		try {
			this.Admin.benutzerEintragen(benutzer);
			this.stage("login.fxml", "Login");
		} catch (BenutzerdatenRichtlinieException e) {
			e.printStackTrace();
			System.out.println(e.getMessage());
		} catch (BenutzerVorhandenException e) {
			e.printStackTrace();
			System.out.println(e.getMessage());
		} catch (IOException e) {
			e.printStackTrace();
			System.out.println(e.getMessage());
		}
	}
	
	/**
	 * Identifizierung des Benutzerlogins in der Datenbank
	 * @param benutzer
	 */
	void benutzerLogin(Benutzer benutzer) {
		try {
			if(this.Admin.benutzerVorhanden(benutzer))
				this.stage("anwendung.fxml", "Anwendung");
			else
				System.out.println("Benutzer nicht vorhanden!");
		} catch (IOException e) {
			e.printStackTrace();
			System.out.println(e.getMessage());
		}
	}
	
	/**
	 * Führt zum Start von start(Stage stage)
	 */
	public static void main(String[] args) {
		launch(args);
	}
}

/**
	 * Dieser Methode wird das erse Fenster übergeben und wird nach Eingabe überschrieben
	 */
	/*@Override
	public void start(Stage stage) throws Exception {
		Scanner input = new Scanner(System.in);
		System.out.println("Welche Szene soll gezeigt werden ? Bitte 3, 4 oder 5 eingeben. Ihre Eingabe bitte: ");
		String aufgabe = input.next();
		input.close();
		switch(aufgabe) {
		case "3":
			Parent root3 = FXMLLoader.load(getClass().getResource("anwendung.fxml"));
	        stage.setTitle("Benutzerverwaltung");
	        stage.setScene(new Scene(root3));
	        stage.show();
	        break;
		case "4":
			Parent root4 = FXMLLoader.load(getClass().getResource("login.fxml"));
	        stage.setTitle("Benutzerverwaltung");
	        stage.setScene(new Scene(root4));
	        stage.show();
	        break;
		case "5":
			Parent root5 = FXMLLoader.load(getClass().getResource("anmeldung.fxml"));
	        stage.setTitle("Benutzerverwaltung");
	        stage.setScene(new Scene(root5));
	        stage.show();
	        break;*/
