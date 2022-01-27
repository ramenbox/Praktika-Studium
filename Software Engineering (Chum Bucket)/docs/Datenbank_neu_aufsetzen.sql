delete from verwalter;
delete from studienverlaufsplan_data;
delete from studiengang_hat_modul;
delete from semester_hat_modul;
delete from student;
delete from semester;
delete from benutzer;
delete from studiengang;
delete from studienverlaufsplan;
delete from modul;

ALTER TABLE benutzer AUTO_INCREMENT = 1;
ALTER TABLE modul AUTO_INCREMENT = 1;
ALTER TABLE semester AUTO_INCREMENT = 1;
ALTER TABLE semester_hat_modul AUTO_INCREMENT = 1;
ALTER TABLE student AUTO_INCREMENT = 1;
ALTER TABLE studiengang AUTO_INCREMENT = 1;
ALTER TABLE studiengang_hat_modul AUTO_INCREMENT = 1;
ALTER TABLE studienverlaufsplan AUTO_INCREMENT = 1;
ALTER TABLE studienverlaufsplan_data AUTO_INCREMENT = 1;
ALTER TABLE verwalter AUTO_INCREMENT = 1;

INSERT INTO benutzer(kontotyp, email, passwort, vorname, nachname) VALUES
('Student', 'steffan.moellbeck@alumni.fh-aachen.de', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4', 'Steffan', 'Möllbeck'),
('Student', 'maria.moellbeck@alumni.fh-aachen.de', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4', 'Maria', 'Möllbeck'),
('Student', 'florian.heisenberg@alumni.fh-aachen.de', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4', 'Florian', 'Heisenberg'),
('Verwalter', 'kirsten.gerte@alumni.fh-aachen.de', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4', 'Kirsten', 'Gerte'),
('Verwalter', 'verwalter@alumni.fh-aachen.de', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4', 'Sarah', 'Gerte'),
('Verwalter', 'lukas.skywalker@alumni.fh-aachen.de', '03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4', 'Lukas', 'Skywalker');

INSERT INTO modul(modulcode, modulname, anzeigename_veraenderbar, pruefung, praktikum, vorlesung, wintersemester, sommersemester, leistungspunkte, pruefungsordnung) VALUES
(51101, 'HM1' ,false, true, false, true, true, false, 9, '2018/19'),
(51104, 'GIP', false, true, true, true, true, false, 10, '2018/19'),
(52105, 'TI', false, true, true, true, true, false, 8, '2018/19'),
(52108, 'HM2', false, true, true, true, false, true, 6, '2018/19'),
(52110, 'DNIS', false, true, true, true, false, true, 8, '2018/19'),
(52106, 'ADS', false, true, true, true, false, true, 8, '2018/19'),
(53105, 'TILO', false, true, true, true, false, true, 7, '2018/19'),
(53106, 'DBWT', false, true, true, true, true, false, 8, '2018/19'),
(53107, 'ARBKVS', false, true, true, true, true, false, 8, '2018/19'),
(55107, 'SWE', false, true, true, true, true, false, 5, '2018/19'),
(53111, 'OOS', false, true, true, true, true, false, 5, '2018/19'),
(55301, 'BWL', false, true, true, true, true, false, 4, '2018/19');

INSERT INTO studienverlaufsplan(studienbeginn, anzahl_fachsemester, name, veroeffentlichungsjahr_po, einschreibung, praxisprojekt, public, credits) VALUES
('2020', 7, 'Informatik B.Sc.', '2018/19', 'WS', true, true, 210),
('2020', 7, 'Informatik B.Sc.', '2019/20', 'WS', true, true, 210),
('2020', 7, 'Informatik B.Sc.', '2020/21', 'WS', true, true, 210);

INSERT INTO studiengang(studienverlaufsplan_id, name) VALUES
(1, 'Informatik');

INSERT INTO student(benutzer_id, matrikelnummer, studienverlaufsplan_id, studiengang_id) VALUES
(1, 1000, 1, 1),
(2, 1001, 2, 1),
(3, 1002, 3, 1);

INSERT verwalter(benutzer_id) VALUES
(4),
(5),
(6);

INSERT INTO semester(studienverlaufsplan_id, semesterjahr, semestertyp, semester) VALUES
(1, '2020/21', 'Vorlesungssemester', 'Wintersemester'),
(1, '2021', 'Vorlesungssemester', 'Sommersemester'),
(1, '2021/22', 'Vorlesungssemester', 'Wintersemester'),
(1, '2022', 'Vorlesungssemester', 'Sommersemester'),
(1, '2022/23', 'Vorlesungssemester', 'Wintersemester'),
(1, '2023', 'Vorlesungssemester', 'Sommersemester'),
(1, '2023/24', 'Praxissemester', 'Wintersemester'),
(2, '2020/21', 'Vorlesungssemester', 'Wintersemester'),
(2, '2021', 'Vorlesungssemester', 'Sommersemester'),
(2, '2021/22', 'Vorlesungssemester', 'Wintersemester'),
(2, '2022', 'Vorlesungssemester', 'Sommersemester'),
(2, '2022/23', 'Vorlesungssemester', 'Wintersemester'),
(2, '2023', 'Vorlesungssemester', 'Sommersemester'),
(2, '2023/24', 'Praxissemester', 'Wintersemester'),
(3, '2020/21', 'Vorlesungssemester', 'Wintersemester'),
(3, '2021', 'Vorlesungssemester', 'Sommersemester'),
(3, '2021/22', 'Vorlesungssemester', 'Wintersemester'),
(3, '2022', 'Vorlesungssemester', 'Sommersemester'),
(3, '2022/23', 'Vorlesungssemester', 'Wintersemester'),
(3, '2023', 'Vorlesungssemester', 'Sommersemester'),
(3, '2023/24', 'Praxissemester', 'Wintersemester');



INSERT INTO semester_hat_modul(modul_id, semester_id, modultitel, pruefungsnote, pruefung_teilnahme, praktikum_teilnahme, vorlesung_teilnahme) VALUES
(1, 1, 'HM1', 0, true, false, true),
(2, 1, 'GIP', 0, true, true, true),
(3, 1, 'TI', 0, true, true, true),
(4, 2, 'HM2', 0, true, true, true),
(5, 2, 'DNIS', 0, true, true, true),
(6, 2, 'ADS', 0, true, true, true),
(7, 2, 'TILO', 0, true, true, true),
(1, 8, 'HM1', 0, true, false, true),
(2, 8, 'GIP', 0, true, true, true),
(3, 8, 'TI', 0, true, true, true),
(4, 9, 'HM2', 0, true, true, true),
(5, 9, 'DNIS', 0, true, true, true),
(6, 9, 'ADS', 0, true, true, true),
(7, 9, 'TILO', 0, true, true, true),
(1, 15, 'HM1', 0, true, false, true),
(2, 15, 'GIP', 0, true, true, true),
(3, 15, 'TI', 0, true, true, true),
(4, 16, 'HM2', 0, true, true, true),
(5, 16, 'DNIS', 0, true, true, true),
(6, 16, 'ADS', 0, true, true, true),
(7, 16, 'TILO', 0, true, true, true);

INSERT INTO studiengang_hat_modul(modul_id, studiengang_id) VALUES
(1, 1),
(2, 1),
(3, 1),
(4, 1),
(5, 1),
(6, 1),
(7, 1),
(8, 1),
(9, 1),
(10, 1),
(11, 1),
(12, 1);

INSERT INTO studienverlaufsplan_data Values (1, 1, 1);
INSERT INTO studienverlaufsplan_data Values (1, 2, 1);
INSERT INTO studienverlaufsplan_data Values (1, 3, 1);
INSERT INTO studienverlaufsplan_data Values (1, 4, 2);
INSERT INTO studienverlaufsplan_data Values (1, 5, 2);
INSERT INTO studienverlaufsplan_data Values (1, 6, 2);
INSERT INTO studienverlaufsplan_data Values (1, 7, 2);
INSERT INTO studienverlaufsplan_data Values (1, 8, 3);
INSERT INTO studienverlaufsplan_data Values (1, 9, 3);
INSERT INTO studienverlaufsplan_data Values (1, 10, 3);
INSERT INTO studienverlaufsplan_data Values (1, 11, 3);
INSERT INTO studienverlaufsplan_data Values (1, 12, 3);

INSERT INTO studienverlaufsplan_data Values (2, 1, 3);
INSERT INTO studienverlaufsplan_data Values (2, 2, 3);
INSERT INTO studienverlaufsplan_data Values (2, 3, 5);
INSERT INTO studienverlaufsplan_data Values (2, 4, 2);
INSERT INTO studienverlaufsplan_data Values (2, 5, 3);
INSERT INTO studienverlaufsplan_data Values (2, 6, 2);
INSERT INTO studienverlaufsplan_data Values (2, 7, 2);
INSERT INTO studienverlaufsplan_data Values (2, 8, 3);
INSERT INTO studienverlaufsplan_data Values (2, 9, 1);
INSERT INTO studienverlaufsplan_data Values (2, 10, 3);
INSERT INTO studienverlaufsplan_data Values (2, 11, 5);
INSERT INTO studienverlaufsplan_data Values (2, 12, 3);

INSERT INTO studienverlaufsplan_data Values (3, 1, 0);
INSERT INTO studienverlaufsplan_data Values (3, 2, 0);
INSERT INTO studienverlaufsplan_data Values (3, 3, 0);
INSERT INTO studienverlaufsplan_data Values (3, 4, 0);
INSERT INTO studienverlaufsplan_data Values (3, 5, 0);
INSERT INTO studienverlaufsplan_data Values (3, 6, 0);
INSERT INTO studienverlaufsplan_data Values (3, 7, 0);
INSERT INTO studienverlaufsplan_data Values (3, 8, 0);
INSERT INTO studienverlaufsplan_data Values (3, 9, 0);
INSERT INTO studienverlaufsplan_data Values (3, 10, 0);
INSERT INTO studienverlaufsplan_data Values (3, 11, 0);
INSERT INTO studienverlaufsplan_data Values (3, 12, 0);