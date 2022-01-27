# Database


## Purpose

Die Datenbank verwaltet den Studienverlaufsplan mehrerer registrierter Studenten.
Der Studienverlaufsplan umfasst mehrere Semester mit Modulen ausgewählt vom Studenten.
Verwalter können Module hinzufügen, löschen und bearbeiten.


## Required information

Student
- Vollständiger Name (Vor- und Nachname) vlt. Zweiter Name
- Matrikelnummer (muss 7 Ziffern haben)
- Alumni E-Mail-Adresse (Einloggen; besteht aus Vorname, Nachname u. ggf. Zweiter Name)
- Kennwort/Passwort (Einloggen)
- Studienfortschritt darstellen
- Studienverlaufsplan bearbeiten
  - Studienbeginn
  - neue Semester hinzufügen oder bereits vorhandene Semester entfernen 
  - Art des Semester anpassen 
    - Vorlesungssemester 
    - Auslandssemester 
    - Urlaubssemester 
    - Praxissemester 
    - Krankheitssemester
  - Module zuordnen (Moduldetails bearbeiten; Modulfortschritt)
- Regelstudienverlaufsplan (Studienverlaufsplan entspricht bei erste Anmeldung nach Registrierung)
- Praktikum
- Prüfung
- Prüfungsnote eintragen
- Bestanden oder Nicht Bestanden (Praktikum)
- Studiengang als Basis (Module) 
- aktuelles Fachsemester
- Semester (Regelverletzung bezüglich der Einschränkungen)
- Wintersemester oder Sommersemester
- Modul Notiz
- Modultitel (Wahlmodule)
- Credits (ECTS)
- Notendurchschnitt errechnet


Verwalter
- Feste Kennung (Einloggen)
- Kennwort/Passwort (Einloggen)
- Studienverlaufspläne (anlegen, bearbeiten, löschen, veröffentlichen)
  - bereits erstellte Studienverlaufspläne anzeigen oder duplizieren
  - nicht veröffentlichen Studienverlaufspläne können Einstellung eingesehen, bearbeitet, gelöscht, duplizieren oder veröffentlicht werden
  - Anzahl der Fachsemester 
  - Name des Studienverlaufsplan 
  - Veröffentlichungsjahr der Prüfungsordnung 
  - Summe der Leistungspunkte, die für Abschluss des Studiums benötigt werden 
  - Einschreibung in Wintersemester oder Sommersemester 
  - Gibt es ein Praxisprojekt? (vorhanden)
- Module (anlegen, bearbeiten, löschen)
  - Modul ID (Modulcode) 
  - Modulname 
  - Veränderbarkeit des Anzeigenamens 
  - Veranstaltungen (Prüfung, Praktikum, Vorlesung) 
  - Angebot (Wintersemester oder Sommersemester) 
  - Leistungspunkte
- Regeln und Einschränkungen (anlegen, bearbeiten, löschen)
- Regelstudienverlauf einer Prüfungsordnung
- Bei welchen Modulen dürfen Studenten eigenen Titel festlegen?


## Tables

benutzer
- email (PK)
- passwort
- vorname
- nachname

student
- email (Fremdschlüssel)
- matrikelnummer

verwalter
- email (Fremdschlüssel Ref)

modul
- id (PRIMARY KEY - Modulcode ist einzigartig)
- name
- name_veraenderbar (Ja oder Nein)
- pruefung (Veranstaltung)
- praktikum (Veranstaltung)
- vorlesung (Veranstaltung)
- wintersemester 
- sommersemester
- leistungspunkte

studiengang
- name (PRIMARY KEY)

studiengang_hat_modul
- modul_id (Fremdschlüssel Ref)
- studiengang_id (Fremdschlüssel Ref)

studienverlaufsplan
- id (PRIMARY KEY)
- anzahl_fachsemester
- name
- veröffentlichungsjahr_po
- gesamtleistungspunkte 
- einschreibung (Winter- oder Sommersemester)
- praxisprojekt_vorhanden (Ja oder Nein)

student_hat_studienverlaufsplan
- student_id (Fremdschlüssel Ref)
- studienverlaufsplan_id (Fremdschlüssel Ref)

studienverlaufsplan_hat_semester
- studienverlaufsplan_id (Fremdschlüssel Ref)
- semester_id (Fremdschlüssel Ref)

semester
- id (PRIMARY KEY)
- semestertyp

semester_hat_modul
- semester_id (Fremdschlüssel Ref)
- modul_id (Fremdschlüssel Ref)