CREATE DATABASE emensawerbeseite
    CHARACTER SET UTF8mb4
    COLLATE utf8mb4_unicode_ci;
use emensawerbeseite;
CREATE TABLE IF NOT EXISTS gericht (
    id INT(8) PRIMARY KEY , -- Primärschlüssel
    name VARCHAR(80) NOT NULL UNIQUE , -- Name des Gerichts. Ein Name ist eindeutig.
    beschreibung VARCHAR(800) NOT NULL, -- Beschreibung des Gerichts.
    erfasst_am DATE NOT NULL , -- Zeitpunkt der ersten Erfassung des Gerichts.
    vegetarisch BOOL NOT NULL DEFAULT false, -- Makierung, ob das Gericht vegetarisch ist. Standard: Nein.
    vegan BOOL NOT NULL DEFAULT false, -- Makierung, ob das Gericht vegan ist. Standard: Nein.
    preis_intern DOUBLE NOT NULL CHECK (preis_intern > 0), -- Preis für interne Personen (wie Studierende). Es gilt immer preis_intern > 0.
    preis_extern DOUBLE NOT NULL CHECK (preis_intern <= preis_extern) -- Preis für externe Personen
    -- Nebenbedingung: preis_intern ist immer kleiner-gleich preis_extern
);
CREATE TABLE IF NOT EXISTS allergen (
    code CHAR(4) PRIMARY KEY , -- Offizieller Abkürzungsbuchstabe für das Allergen
    name VARCHAR(300) NOT NULL , -- Name des Allergens, wie ,,Glutenhaltiges Getreide".
    typ VARCHAR(20) NOT NULL DEFAULT 'allergen' -- Gibt den Typ an. Standard: ,,allergen"
);
CREATE TABLE IF NOT EXISTS kategorie (
    id INT(8) PRIMARY KEY , -- Primärschlüssel
    name VARCHAR(80) NOT NULL , -- Name der Katergorie, z.B. ,,Hauptgericht", ,,Vorspeise", ,,Salat",
    -- ,,Sauce" oder ,,Käsegericht".
    eltern_id INT(8) REFERENCES kategorie(id), -- Referenz auf eine Eltern-Kategorie. Zum Beispiel enthält die Kategorie
    -- ,,Hauptgericht alle Gerichte" alle Gerichte, die als Hauptgang vorgesehen sind.
    bildname VARCHAR(200) -- Name der Bilddatei,die eine Darstellung der Katergorie enthält.
);
CREATE TABLE IF NOT EXISTS gericht_hat_allergen (
    code CHAR(4) REFERENCES allergen, -- Referenz auf Allergen.
    gericht_id INT(8) NOT NULL REFERENCES gericht(id)-- Referenz auf das Gericht.

);
CREATE TABLE IF NOT EXISTS gericht_hat_kategorie (
    gericht_id INT(8) NOT NULL REFERENCES gericht(id), -- Referenz auf Gericht.
    kategorie_id INT(8) NOT NULL REFERENCES kategorie(id)-- Referenz auf Kategorie.
);
SELECT * FROM gericht;
SELECT * FROM allergen;
SELECT * FROM kategorie;
SELECT * FROM gericht_hat_allergen;
SELECT * FROM gericht_hat_kategorie;

DELETE  FROM emensawerbeseite.gericht_hat_allergen WHERE gericht_id;
DELETE  FROM emensawerbeseite.gericht_hat_kategorie WHERE gericht_id;
DELETE  FROM emensawerbeseite.gericht_hat_kategorie WHERE kategorie_id;
SELECT * FROM emensawerbeseite.kategorie;

#Aufgabe 4.5
SELECT COUNT(*) AS anzahl FROM gericht;
SELECT COUNT(*) AS anzahl FROM allergen;
SELECT COUNT(*) AS anzahl FROM kategorie;
SELECT COUNT(*) AS anzahl FROM gericht_hat_allergen;
SELECT COUNT(*) AS anzahl FROM gericht_hat_kategorie;

#Aufgabe 5

ALTER TABLE gericht
    ADD imgdir VARCHAR(200);

SELECT * FROM gericht;

SELECT erfasst_am FROM gericht;
SELECT erfasst_am, name FROM gericht ORDER BY name DESC;
SELECT name, beschreibung FROM gericht ORDER BY beschreibung ASC;
SELECT name, beschreibung FROM gericht ORDER BY beschreibung ASC LIMIT 5;
SELECT name, beschreibung FROM gericht ORDER BY beschreibung ASC LIMIT 5 offset 5;
SELECT DISTINCT typ FROM allergen;
SELECT name FROM gericht WHERE name LIKE 'K%';
SELECT id , name FROM gericht WHERE name LIKE '%suppe%';
SELECT * FROM kategorie WHERE eltern_id IS NULL;

select g.name, group_concat(a.code separator ', ')as code, group_concat(a.name separator ', ')
    as Allergene, group_concat(a.typ separator ', ') as Art from gericht g
        left join gericht_hat_allergen ha on ha.gericht_id=g.id left join allergen a on ha.code = a.code where ha.code IS NOT NULL
            group by g.id;

select g.name, group_concat(a.code separator ', ')as Code, group_concat(a.name separator ', ')
    as Allergene , group_concat(a.typ separator ', ') as Art  from gericht g
        left join  gericht_hat_allergen ha on ha.gericht_id=g.id left join allergen a on ha.code = a.code
            group by g.id;



SELECT allergen.code, allergen.name, typ, gericht_id FROM  allergen
    LEFT JOIN gericht_hat_allergen gha on allergen.code = gha.code;

SELECT k.name, COUNT(*) as Anzahl FROM kategorie k LEFT JOIN gericht_hat_kategorie ghk ON k.id = ghk.kategorie_id GROUP BY k.name  ORDER BY Anzahl ASC;

SELECT k.name, COUNT(*) as Anzahl FROM kategorie k LEFT JOIN gericht_hat_kategorie ghk ON k.id = ghk.kategorie_id GROUP BY k.name HAVING Anzahl > 2 ORDER BY Anzahl ASC;

UPDATE allergen SET name = 'Kamut' WHERE code = 'a6';

INSERT INTO gericht VALUES
(21, 'Currywurst mit Pommes', 'Kennt man doch', '2020-11-19', 0, 0, 2.3, 4);

INSERT INTO gericht_hat_kategorie (kategorie_id, gericht_id) VALUES
(3, 21);


SELECT * FROM wunschgerichte;

UPDATE gericht SET imgdir = 'spina.jpg' WHERE id = '5';


CREATE TABLE IF NOT EXISTS wunschgerichte (
                                              id INT(8) AUTO_INCREMENT PRIMARY KEY ,
                                              name VARCHAR(200) NOT NULL,
                                              beschreibung VARCHAR(200) NOT NULL ,
                                              erstelldatum datetime NOT NULL,
                                              ersteller VARCHAR(200) NOT NULL DEFAULT 'anonym',
                                              email VARCHAR(200) NOT NULL
);


-- 8.1 --
ALTER TABLE gericht_hat_kategorie
    ADD UNIQUE (gericht_id, kategorie_id);

-- 8.2 --
CREATE UNIQUE INDEX gericht_name_idindex ON gericht(name);

-- 8.3 --
ALTER TABLE gericht_hat_kategorie
    ADD CONSTRAINT con_gericht_hat_kat
        FOREIGN KEY(gericht_id)
            REFERENCES gericht(id)
            ON DELETE CASCADE;

ALTER TABLE gericht_hat_allergen
    ADD CONSTRAINT con_gericht_hat_all
        FOREIGN KEY (gericht_id)
            REFERENCES gericht(id)
            ON DELETE CASCADE;

-- 8.4 --
ALTER TABLE kategorie
    ADD CONSTRAINT con_kategorie
        FOREIGN KEY (eltern_id)
            REFERENCES kategorie(id)
            ON DELETE RESTRICT;

ALTER TABLE gericht_hat_kategorie
    ADD CONSTRAINT con_kategorie2
        FOREIGN KEY (kategorie_id)
            REFERENCES kategorie(id)
            ON DELETE RESTRICT;

-- 8.5 --
ALTER TABLE gericht_hat_allergen
    ADD CONSTRAINT con_changecode
        FOREIGN KEY (code)
            REFERENCES allergen(code)
            ON UPDATE CASCADE;

-- 8.6 --
ALTER TABLE gericht_hat_kategorie
    ADD PRIMARY KEY(gericht_id, kategorie_id);