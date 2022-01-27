<?php declare(strict_types=1);
mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);
/*
 * @title Aktivität 25
 * @description Hauptseite des Studierenden anzeigen
 * @author Thanh Dat Tan
 */
require_once __DIR__ . '/includes/db.inc.php';
require_once __DIR__ . '/includes/studienverlaufsplan.php';

/** Zum Entfernen eines Semester aus dem Studienverlaufsplan
 * @param int $semester_id ID des Semesters im Studienverlaufsplan
 * @return bool Erfolgreich gelöscht oder Fehlgeschlagen
 */
function db_delete_semester_from_studienverlaufsplan(int $semester_id) : bool
{
    $link = connectdb();

    $link->begin_transaction();
    $stmt = $link->stmt_init();

    $result = false;

    try {

        $sql = "SELECT COUNT(*) AS anzahl_semester FROM semester sem
    INNER JOIN studienverlaufsplan s on sem.studienverlaufsplan_id = s.id
    INNER JOIN (
        SELECT studienverlaufsplan_id FROM semester WHERE id = ?
    ) tmp WHERE s.id = tmp.studienverlaufsplan_id";


        $stmt->prepare($sql);
        $stmt->bind_param("i", $semester_id);
        $stmt->execute();
        $data = $stmt->get_result();
        $anz_sem = $data->fetch_object()->anzahl_semester;

        $sql = "DELETE sem FROM semester AS sem
    INNER JOIN studienverlaufsplan s on sem.studienverlaufsplan_id = s.id
    WHERE sem.id = ? AND s.anzahl_fachsemester < ?";


        $stmt->prepare($sql);
        $stmt->bind_param("ii", $semester_id, $anz_sem);
        $stmt->execute();
        if ($stmt->affected_rows > 0) $result = true;


        $link->commit();
    } catch (mysqli_sql_exception $exception) {
        $link->rollback();
    }

    $stmt->close();
    $link->close();
    return $result;
}

/** Zum Hinzufügen eines Semester in dem Studienverlaufsplan vom Studenten
 * @param int $studienverlaufsplan_id
 * @param string $semestertyp
 * @param string $semester
 * @param string $semesterjahr
 * @return bool
 */
function db_add_semester_to_studienverlaufsplan(int $studienverlaufsplan_id, string $semestertyp, string $semester, string $semesterjahr)
{
    $link = connectdb();

    $sql = "INSERT INTO semester(studienverlaufsplan_id, semestertyp, semester, semesterjahr) VALUES(?, ?, ?, ?)";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "isss", $studienverlaufsplan_id, $semestertyp, $semester, $semesterjahr);
    mysqli_stmt_execute($stmt);


    mysqli_stmt_close($stmt);

    $res = mysqli_query($link, 'SELECT LAST_INSERT_ID()');
    $row = mysqli_fetch_array($res);
    $semester_id = $row[0];

    mysqli_close($link);
    return $semester_id;
}

function db_select_last_semester_studienverlaufsplan(int $studienverlaufsplan_id) {
    $link = connectdb();

    $sql = "
    SELECT semester.id, semester, semestertyp, semesterjahr FROM semester
    INNER JOIN studienverlaufsplan
        ON semester.studienverlaufsplan_id = studienverlaufsplan.id
    INNER JOIN student
        ON student.studienverlaufsplan_id = studienverlaufsplan.id AND student.studienverlaufsplan_id = $studienverlaufsplan_id AND NOT semesterjahr = 'DUMMY' ORDER BY semesterjahr DESC LIMIT 1;";


    $result = mysqli_query($link, $sql);

    $row_data = mysqli_fetch_assoc($result);

    mysqli_free_result($result);
    mysqli_close($link);
    return $row_data;
}




// TODO: Secure it! Very dangerous operation
if (isset($_GET['semester_delete'])) {
    //db_delete_semester_from_studienverlaufsplan((int)$_GET['semester_delete']);
    $email = htmlspecialchars($_GET['for'], ENT_QUOTES | ENT_HTML5, 'utf-8');
    $semester_id = $_GET['semester_delete'];
    if(db_delete_semester_from_studienverlaufsplan((int)$semester_id)) {
        echo "OK";
    }
}
if (isset($_GET['semester_add'])) {
    $email = htmlspecialchars($_GET['semester_add'], ENT_QUOTES | ENT_HTML5, 'utf-8');
    $studienverlaufsplan_id = (int)db_select_studienverlaufsplanId_studiengangId_from_benutzer($email)['studienverlaufsplan_id'];

    $lastsemester_data = db_select_last_semester_studienverlaufsplan($studienverlaufsplan_id);

    if (!isset($lastsemester_data)) {
        $lastsemester_data['semester'] = "Sommersemester";
        $lastsemester_data['semesterjahr'] = "2020";
    }

    // Nach Wintersemester folgt Sommersemester and vice versa
    $nextsemester_data = [];
    if($lastsemester_data['semester'] === "Wintersemester") {
        $nextsemester_data['semester'] = "Sommersemester";
    } else {
        $nextsemester_data['semester'] = "Wintersemester";
    }

    // Semesterjahr für Winter Jahr/nächstes Jahr
    // Sommersemester
    if(strpos($lastsemester_data['semesterjahr'], "/")) {
        $nextsemesterjahr = preg_split('/\//', $lastsemester_data['semesterjahr'])[0];
        $date = DateTime::createFromFormat('Y', $nextsemesterjahr);
        $date->add(new DateInterval('P1Y'));
        $nextsemesterjahr = $date->format('Y');
        $nextsemester_data['semesterjahr'] = $nextsemesterjahr;
    } else {
        // Wintersemester
        $currentjahr = $lastsemester_data['semesterjahr'];
        $date = DateTime::createFromFormat('Y', $currentjahr);
        $date->add(new DateInterval('P1Y'));
        $nextsemesterjahr = $date->format('Y');
        $nextsemesterjahr = $nextsemesterjahr[2] . $nextsemesterjahr[3];
        $nextsemesterjahr = $currentjahr . '/' . $nextsemesterjahr;
        $nextsemester_data['semesterjahr'] = $nextsemesterjahr;
    }


    if (db_add_semester_to_studienverlaufsplan($studienverlaufsplan_id, "Vorlesungssemester", $nextsemester_data['semester'], $nextsemester_data['semesterjahr'])) {
        echo "OK";
    }


}