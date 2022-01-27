CREATE SCHEMA IF NOT EXISTS test_datenbank
    CHARACTER SET = 'UTF8mb4'
    COLLATE = 'utf8mb4_unicode_ci';

use test_datenbank;

CREATE TABLE IF NOT EXISTS benutzer(
    id BIGINT PRIMARY KEY AUTO_INCREMENT,
    kontotyp VARCHAR(20) NOT NULL,
    email VARCHAR(80) NOT NULL UNIQUE,
    passwort VARCHAR(255) NOT NULL,
    vorname VARCHAR(80) NOT NULL,
    nachname VARCHAR(80) NOT NULL,
    erstellt_am TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT minPWLen CHECK (LENGTH(passwort) > 8)
);

CREATE TABLE IF NOT EXISTS studienverlaufsplan(
    id BIGINT PRIMARY KEY AUTO_INCREMENT,
    studienbeginn YEAR NOT NULL,
    anzahl_fachsemester INT NOT NULL,
    name VARCHAR(80) NOT NULL,
    veroeffentlichungsjahr_po VARCHAR(8) NOT NULL,
    einschreibung VARCHAR(80) NOT NULL DEFAULT 'Wintersemester',
    praxisprojekt BOOLEAN NOT NULL DEFAULT TRUE,
    public BOOLEAN NOT NULL DEFAULT FALSE
);

/* Jeder Studiengang hat einen oder mehrere Regelstudienverlaufspläne */
CREATE TABLE IF NOT EXISTS studiengang(
    id BIGINT PRIMARY KEY AUTO_INCREMENT,
    studienverlaufsplan_id BIGINT,
    FOREIGN KEY (studienverlaufsplan_id) REFERENCES studienverlaufsplan(id),
    name VARCHAR(80) NOT NULL
);

/* Löschen des Studenten führt zum Löschen des Benutzers und seinem Studienverlaufsplan */
CREATE TABLE IF NOT EXISTS student(
    benutzer_id BIGINT,
    FOREIGN KEY (benutzer_id) REFERENCES benutzer(id) ON DELETE CASCADE,
    matrikelnummer BIGINT NOT NULL UNIQUE,
    studienverlaufsplan_id BIGINT,
    FOREIGN KEY (studienverlaufsplan_id) REFERENCES studienverlaufsplan(id) ON DELETE CASCADE,
    studiengang_id BIGINT,
    FOREIGN KEY (studiengang_id) REFERENCES studiengang(id),
    fachsemester int unsigned not null default 1,
	no_config_flag bool not null default true -- Wenn true dann Verlaufsplan zurücksetzen
);

/* Löschen des Verwalters führt zum Löschen des Benutzers */
CREATE TABLE IF NOT EXISTS verwalter(
    benutzer_id BIGINT,
    FOREIGN KEY (benutzer_id) REFERENCES benutzer(id) ON DELETE CASCADE
);

/* Studienverlaufspläne haben keine, eine oder mehrere Semester */
CREATE TABLE IF NOT EXISTS semester(
    id BIGINT PRIMARY KEY AUTO_INCREMENT,
    studienverlaufsplan_id BIGINT,
    FOREIGN KEY (studienverlaufsplan_id) REFERENCES studienverlaufsplan(id),
    semestertyp VARCHAR(20) NOT NULL DEFAULT 'Vorlesungssemester',
    semester VARCHAR(20) NOT NULL DEFAULT 'Wintersemester',
    semesterjahr VARCHAR(20) NOT NULL
);

/* Module nach Prüfungsordnung */
CREATE TABLE IF NOT EXISTS modul(
    id BIGINT PRIMARY KEY AUTO_INCREMENT,
    modulcode BIGINT UNSIGNED NOT NULL,
    modulname VARCHAR(20) NOT NULL,
    anzeigename_veraenderbar BOOLEAN NOT NULL DEFAULT FALSE,
    pruefung BOOLEAN NOT NULL DEFAULT TRUE,
    praktikum BOOLEAN NOT NULL,
    vorlesung BOOLEAN NOT NULL,
    wintersemester BOOLEAN NOT NULL,
    sommersemester BOOLEAN NOT NULL,
    leistungspunkte INT UNSIGNED NOT NULL,
    pruefungsordnung VARCHAR(8) NOT NULL
);

/* Student hat Zugriff auf seine geplanten Module */
CREATE TABLE IF NOT EXISTS semester_hat_modul(
    id BIGINT PRIMARY KEY AUTO_INCREMENT,
    modul_id BIGINT,
    FOREIGN KEY (modul_id) REFERENCES modul(id),
    semester_id BIGINT,
    FOREIGN KEY (semester_id) REFERENCES semester(id),
    modultitel VARCHAR(80) NOT NULL,
    modulnotiz VARCHAR(255),
    pruefungsnote FLOAT UNSIGNED,
    praktikum_bestanden BOOLEAN DEFAULT NULL,
    pruefung_teilnahme BOOLEAN NOT NULL,
    praktikum_teilnahme BOOLEAN NOT NULL,
    vorlesung_teilnahme BOOLEAN NOT NULL
);

/* Zuordnung der Studiengänge für die Module */
CREATE TABLE IF NOT EXISTS studiengang_hat_modul(
    id BIGINT PRIMARY KEY AUTO_INCREMENT,
    modul_id BIGINT,
    FOREIGN KEY (modul_id) REFERENCES modul(id),
    studiengang_id BIGINT,
    FOREIGN KEY (studiengang_id) REFERENCES studiengang(id)
);

create table studienverlaufsplan_data(
    verlaufsplan_id bigint not null references studienverlaufsplan(id) ON DELETE CASCADE,
    modul_id bigint not null references modul(id) ON DELETE CASCADE,
    fachsemester int not null
);


ALTER TABLE studienverlaufsplan
    ADD credits int default 0 not null