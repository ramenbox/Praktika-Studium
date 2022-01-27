use test_datenbank;

SELECT * FROM benutzer;

SELECT * FROM student;

SELECT * FROM verwalter;

/* Get all data on students */
SELECT * FROM student INNER JOIN benutzer ON student.benutzer_id = benutzer.id;
/* Get all data on verwalter */
SELECT * FROM verwalter INNER JOIN benutzer ON verwalter.benutzer_id = benutzer.id;

SELECT * FROM modul;

SELECT * FROM studienverlaufsplan;

SELECT * FROM studiengang;

SELECT * FROM semester;

/* Get all semester with studienverlaufsplan */
SELECT * FROM semester INNER JOIN studienverlaufsplan ON studienverlaufsplan.id = semester.studienverlaufsplan_id;

SELECT semester, semestertyp, studienbeginn, anzahl_fachsemester, name FROM semester INNER JOIN studienverlaufsplan ON studienverlaufsplan.id = semester.studienverlaufsplan_id;

SELECT * FROM semester_hat_modul;

/* Alle zugehörigen Modulen zu Semestern */
SELECT * FROM semester_hat_modul INNER JOIN semester ON semester_hat_modul.semester_id = semester.id;

SELECT * FROM semester_hat_modul INNER JOIN semester ON semester_hat_modul.semester_id = semester.id INNER JOIN modul ON semester_hat_modul.modul_id = modul.id;