<?php declare(strict_types=1);
/**
 * Diese Datei enthält alle SQL-Abfrage zur Tabelle "studienverlaufsplan"
 */

include_once 'db.inc.php';

/** Get Name vom Studienverlaufsplan
 * @param int $studienverlaufsplan_id ID
 * @return array Name des Studienverlaufsplan
 */
function db_select_id_name_veroeffentlichungsjahr_po_from_studienverlaufsplan(int $studienverlaufsplan_id): array
{
    $link = connectdb();

    $sql = "SELECT studienverlaufsplan.id, name, veroeffentlichungsjahr_po, praxisprojekt FROM studienverlaufsplan 
        INNER JOIN student 
            ON studienverlaufsplan.id = studienverlaufsplan_id AND studienverlaufsplan.id = ?";


    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("i", $studienverlaufsplan_id);
    $stmt->execute(); //mysqli_query($link, $sql);
    $result = $stmt->get_result()->fetch_assoc();

    $stmt->close();
    $link->close();
    return $result;
}

/** Entnehme die benötigten Informationen für das Management des Studienverlaufsplans
 * @param string $email Email des angemeldeten Benutzers
 * @return array Studienverlaufsplan ID und Studiengang ID
 */
function db_select_studienverlaufsplanId_studiengangId_from_benutzer(string $email): array
{
    $link = connectdb();

    $sql = "SELECT benutzer_id, studienverlaufsplan_id, studiengang_id FROM benutzer JOIN student ON student.benutzer_id = benutzer.id AND benutzer.email = ?";


    //$result = mysqli_query($link, $sql);

    //$row_data = mysqli_fetch_row($result);

    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("s", $email);
    $stmt->execute();
    $result = $stmt->get_result()->fetch_assoc();

    $stmt->close();
    $link->close();
    return $result;
}