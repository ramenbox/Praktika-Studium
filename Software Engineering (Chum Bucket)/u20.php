<?php declare(strict_types=1);
session_start();
/*
 * @title Aktivität 20
 * @description Hauptseite des Studierenden anzeigen
 * @author Thanh Dat Tan
 */
require_once __DIR__ . '/includes/db.inc.php';
require_once __DIR__ . '/includes/studienverlaufsplan.php';
/*
require_once $_SERVER['DOCUMENT_ROOT']."/../vendor/autoload.php";

use Monolog\Logger;
use Monolog\Handler\StreamHandler;

function logger(): Logger
{
    $logger = new Logger('swe');
    $logger->pushHandler(new StreamHandler(__DIR__ . '/logs/app.log', Logger::INFO));

    return $logger;
}*/

//$_SESSION['email'] = "steffan.moellbeck@alumni.fh-aachen.de";
//$_SESSION['email'] = "maria.moellbeck@alumni.fh-aachen.de";
//session_start();
if (!isset($_SESSION['email']))
{
    echo "<script>window.location.href = '/' </script>";
}


// Diese Daten gibt es für jeden Studenten
//$studienverlaufsplan_data = db_select_studienverlaufsplanId_studiengangId_from_benutzer($_SESSION['email']);
if(isset($_SESSION['benutzer_id'], $_SESSION['studienverlaufsplan_id'], $_SESSION['studiengang_id'])) {
    $benutzer_id = (int)$_SESSION['benutzer_id'];
    $studienverlaufsplan_id = (int)$_SESSION['studienverlaufsplan_id'];
    $studiengang_id = (int)$_SESSION['studiengang_id'];
} else {
    $studienverlaufsplan_data = db_select_studienverlaufsplanId_studiengangId_from_benutzer($_SESSION['email']);
    $benutzer_id = (int)$studienverlaufsplan_data['benutzer_id'];
    $studienverlaufsplan_id = (int)$studienverlaufsplan_data['studienverlaufsplan_id'];
    $studiengang_id = (int)$studienverlaufsplan_data['studiengang_id'];

    $_SESSION['benutzer_id'] = $benutzer_id;
    $_SESSION['studienverlaufsplan_id'] = $studienverlaufsplan_id;
    $_SESSION['studiengang_id'] = $studiengang_id;
}
/*
// $_SESSION from u41 für Studienverlaufsplan_id
if($studienverlaufsplan_id === 1)
{
    //Dupliziere Regelstudienverlaufplan und dann benutze die id davon
    $studienverlaufsplan = db_select_all_studienverlaufsplan($studienverlaufsplan_id);
    $new_studienverlaufsplan_id = (int)db_duplicate_studienverlaufsplan($studienverlaufsplan);


    $semesters = db_select_all_semester_from($studienverlaufsplan_id);
    foreach($semesters as $semester)
    {
        $new_semester_id = (int)db_duplicate_semester($semester, $new_studienverlaufsplan_id);

        $semestermodules = db_select_all_modules_semester((int)$semester['id']);
        foreach ($semestermodules as $semestermodule)
        {
            db_duplicate_semester_hat_modul($semestermodule, $new_semester_id);
        }
    }

    db_update_student_studienverlaufsplan_id($benutzer_id, $new_studienverlaufsplan_id);

    $data = db_select_all_studienverlaufsplan_data($studienverlaufsplan_id);
    foreach($data as $d)
    {
        db_duplicate_studienverlaufsplan_data($d, $new_studienverlaufsplan_id);
    }

    $studienverlaufsplan_id = $new_studienverlaufsplan_id;
}
*/
/**
 * Trennung vom Model zum Controller
 */
function get_name_veroeffentlichungsjahr_po_from_studienverlaufsplan() {
    global $studienverlaufsplan_id;

    $data = db_select_id_name_veroeffentlichungsjahr_po_from_studienverlaufsplan($studienverlaufsplan_id);

    $praxisprojekt = array_pop($data);

    if ($praxisprojekt) {
        echo implode(' mit Praxissemester (PO ', array_slice($data, 1)) . ')';
    }
    else {
        echo implode(' (PO ', array_slice($data, 1)) . ')';
    }
}

function logged_in() {
    echo $_SESSION['email'];
}

function csrf_token() {
    return bin2hex(random_bytes(35));
}

function create_csrf_token() {
    if (isset($_SESSION['csrf_token'])) {
        // CSRF Token für mindestens 5 Minuten gültig
        if(strtotime('-5 minutes') < $_SESSION['csrf_token_time']) {
            return $_SESSION['csrf_token'];
        }
    }
    $token = csrf_token();
    $_SESSION['csrf_token'] = $token;
    $_SESSION['csrf_token_time'] = time();
    return $token;
}

function csrf_token_tag() {
    $token = create_csrf_token();
    return '<input type="hidden" name="csrf_token" value="' . $token . '">';
}

function db_update_modul_to_new_semester(int $new_semester_id, int $old_semester_id, string $modulname) : bool {
    $link = connectdb();
    $sql = "UPDATE semester_hat_modul JOIN modul m on m.id = semester_hat_modul.modul_id SET semester_id = ? WHERE semester_id = ? AND m.modulname = ?";

    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("iis", $new_semester_id, $old_semester_id, $modulname);
    $result = $stmt->execute();


    $stmt->close();

    $link->close();

    return $result;
}

function db_select_modul_from_semester(string $modulname, int $studienverlaufsplan_id) : int {
    $link = connectdb();

    $sql = "SELECT semester_id FROM semester_hat_modul 
    JOIN modul m ON semester_hat_modul.modul_id = m.id 
    JOIN semester s on semester_hat_modul.semester_id = s.id
    JOIN studienverlaufsplan s2 on s.studienverlaufsplan_id = s2.id
WHERE m.modulname = ? AND s2.id = ?";

    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("si", $modulname, $studienverlaufsplan_id);
    $stmt->execute();

    $result = $stmt->get_result()->fetch_object();


    $stmt->close();

    $link->close();

    return $result->semester_id;
}

function db_delete_old_dummy(int $shm, int $semester_id) : bool {
    $link = connectdb();
    $sql = "DELETE semester_hat_modul, semester FROM semester_hat_modul
                INNER JOIN semester ON semester_hat_modul.semester_id = semester.id WHERE semester_hat_modul.id = ? OR semester.id = ?";

    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("ii", $shm, $semester_id);
    $result = $stmt->execute();


    $stmt->close();

    $link->close();

    return $result;
}

function db_transform_dummy_to_shm(int $shm_id, int $modul_id, int $semester_id) : bool {
    $link = connectdb();
    $sql = "INSERT INTO semester_hat_modul(modul_id, semester_id, modultitel, modulnotiz, pruefungsnote, pruefung_teilnahme, praktikum_teilnahme, vorlesung_teilnahme) 
VALUES(?, ?,
       (SELECT modultitel FROM semester_hat_modul AS s WHERE id = ?),
       (SELECT modulnotiz FROM semester_hat_modul AS s WHERE id = ?),
       (SELECT pruefungsnote FROM semester_hat_modul AS s WHERE id = ?),
       (SELECT pruefung_teilnahme FROM semester_hat_modul AS s WHERE id = ?),
       (SELECT praktikum_teilnahme FROM semester_hat_modul AS s WHERE id = ?),
       (SELECT vorlesung_teilnahme FROM semester_hat_modul  AS s WHERE id = ?))";

    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("iiiiiiii", $modul_id, $semester_id, $shm_id, $shm_id, $shm_id, $shm_id, $shm_id, $shm_id);
    $result = $stmt->execute();


    $stmt->close();

    $link->close();

    return $result;
}

function db_select_cnt_dummy_modul_by_name(string $modulname, int $studienverlaufsplan_id) : array {
    $link = connectdb();

    $sql = "SELECT COUNT(shm.id) AS cnt, shm.id, shm.semester_id FROM semester_hat_modul shm
                    JOIN modul m ON shm.modul_id = m.id
                    JOIN semester s ON s.id = shm.semester_id
                    JOIN studienverlaufsplan p ON s.studienverlaufsplan_id = s.studienverlaufsplan_id
WHERE p.id = ? AND s.semester = 'dummy' AND m.modulname = ?";

    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("is", $studienverlaufsplan_id, $modulname);
    $stmt->execute();

    $result = $stmt->get_result()->fetch_assoc();


    $stmt->close();

    $link->close();

    return $result;
}

function db_find_dummy_semester(int $studienverlaufsplan_id) : int{
    $link = connectdb();

    $sql = "INSERT INTO semester (studienverlaufsplan_id, semestertyp, semester, semesterjahr) 
VALUES (?, 'dummy', 'dummy', 'dummy')";

    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("i", $studienverlaufsplan_id);
    $stmt->execute();

    $result_id = $stmt->insert_id;


    $stmt->close();

    $link->close();

    return $result_id;
}

function db_insert_dummy_semester_hat_modul_row(string $modulname, int $semester_id) : int {
    $link = connectdb();

    $sql = "INSERT INTO semester_hat_modul (modul_id, semester_id, modultitel, modulnotiz, pruefungsnote, praktikum_bestanden, pruefung_teilnahme, praktikum_teilnahme, vorlesung_teilnahme) 
VALUES ((SELECT m.id FROM modul m WHERE m.modulname = ?), ?, '', '', 0, 0, 
        (SELECT pruefung FROM modul WHERE modulname = ?), 
        (SELECT praktikum FROM modul WHERE modulname = ?),
        (SELECT vorlesung FROM modul WHERE modulname = ?))";

    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("sisss", $modulname, $semester_id, $modulname, $modulname, $modulname);
    $stmt->execute();

    $result_id = $stmt->insert_id;


    $stmt->close();

    $link->close();

    return $result_id;
}

function db_select_dummy_modul_entry(int $shm_id) : array {
    $link = connectdb();

    $sql = "SELECT modultitel, modulnotiz, pruefungsnote, praktikum_bestanden FROM semester_hat_modul WHERE id = ?";

    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("i", $shm_id);
    $stmt->execute();

    $result = $stmt->get_result()->fetch_assoc();


    $stmt->close();

    $link->close();

    $result['pruefungsnote'] = (string)$result['pruefungsnote'];
    return $result;
}

function db_select_semestermodul_id(string $modulname, int $studienverlaufsplan_id) : ?int
{
    $link = connectdb();

    $sql = "SELECT shm.id FROM semester_hat_modul shm
                    JOIN modul m ON shm.modul_id = m.id
                    JOIN semester s ON s.id = shm.semester_id
                    JOIN studienverlaufsplan p ON s.studienverlaufsplan_id = s.studienverlaufsplan_id
WHERE p.id = ? AND s.semester = 'dummy' AND m.modulname = ?";

    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("is", $studienverlaufsplan_id, $modulname);
    $stmt->execute();

    $result = $stmt->get_result()->fetch_assoc();


    $stmt->close();

    $link->close();

    if ($result) return $result['id'];
    else return null;
}

function db_modify_module_praktikum(bool $praktikum_bestanden, int $semesterid, int $modul_id) : bool {
    $link = connectdb();
    $sql = "UPDATE semester_hat_modul SET praktikum_bestanden = ? WHERE semester_id = ? AND modul_id = ?";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "iii",$praktikum_bestanden, $semesterid, $modul_id);
    $result = mysqli_stmt_execute($stmt);

    mysqli_stmt_close($stmt);
    mysqli_close($link);
    return $result;
}

function db_modify_module_pruefung(float $pruefungsnote, int $semesterid, int $modul_id) : bool {
    $link = connectdb();
    $sql = "UPDATE semester_hat_modul SET pruefungsnote = ? WHERE semester_id = ? AND modul_id = ?";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "dii",$pruefungsnote, $semesterid, $modul_id);
    $result = mysqli_stmt_execute($stmt);

    mysqli_stmt_close($stmt);
    mysqli_close($link);
    return $result;
}

function db_select_semestermoduldetail(string $modulname, int $semester_id): array
{
    $link = connectdb();

    $sql = "SELECT modultitel, modulnotiz, pruefungsnote, praktikum_bestanden FROM semester_hat_modul s
                JOIN modul m ON m.id = s.modul_id WHERE m.modulname = ? AND s.semester_id = ?";

    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("si", $modulname, $semester_id);
    $stmt->execute();

    $result = $stmt->get_result()->fetch_assoc();


    $stmt->close();

    $link->close();

    $result['pruefungsnote'] = (string)$result['pruefungsnote'];
    return $result;
}

function db_duplicate_studienverlaufsplan_data(array $d, int $new_studienverlaufsplan_id)
{
    $d['verlaufsplan_id'] = intval($d['verlaufsplan_id']);
    $d['modul_id'] = intval($d['modul_id']);
    $d['fachsemester'] = intval($d['fachsemester']);


    $link = connectdb();

    $sql = "INSERT INTO studienverlaufsplan_data(verlaufsplan_id, modul_id, fachsemester) VALUES (?, ?, ?)";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "iii",
        $new_studienverlaufsplan_id,
        $d['modul_id'],
        $d['fachsemester']
    );
    mysqli_stmt_execute($stmt);
    mysqli_stmt_close($stmt);

    $res = mysqli_query($link, 'SELECT LAST_INSERT_ID()');
    $row = mysqli_fetch_array($res);
    $semester_id = $row[0];


    mysqli_close($link);
    return $semester_id;
}

function db_select_all_studienverlaufsplan_data(int $verlaufsplan_id) {
    $link = connectdb();

    $sql = "SELECT * FROM studienverlaufsplan_data WHERE verlaufsplan_id = $verlaufsplan_id";

    $result = mysqli_query($link, $sql);

    $data = mysqli_fetch_all($result, MYSQLI_ASSOC);

    mysqli_free_result($result);
    mysqli_close($link);
    return $data;
}

function db_update_student_studienverlaufsplan_id(int $benutzer_id, int $new_studienverlaufsplan_id)
{
    $link = connectdb();

    $sql = "UPDATE student SET studienverlaufsplan_id = ? WHERE benutzer_id = ?";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "ii",
    $new_studienverlaufsplan_id,
    $benutzer_id
    );
    $result = mysqli_stmt_execute($stmt);
    mysqli_stmt_close($stmt);


    mysqli_close($link);
    return $result;
}

function db_select_all_modules_semester(int $semester_id) {
    $link = connectdb();

    $sql = "SELECT modul_id, semester_id, modultitel, modulnotiz, pruefungsnote, praktikum_bestanden, pruefung_teilnahme, praktikum_teilnahme, vorlesung_teilnahme FROM semester_hat_modul
WHERE semester_id = $semester_id";

    $result = mysqli_query($link, $sql);

    $data = mysqli_fetch_all($result, MYSQLI_ASSOC);

    mysqli_free_result($result);
    mysqli_close($link);
    return $data;
}

function db_duplicate_semester_hat_modul(array $semestermodule, int $semester_id)
{
    $semestermodule['modul_id'] = (int)$semestermodule['modul_id'];
    $semestermodule['pruefungsnote'] = (double)  $semestermodule['pruefungsnote'];

    // PHP does not convert string "1" to true, wtf php manual?!
    if($semestermodule['praktikum_bestanden'])
        $semestermodule['praktikum_bestanden'] = true;
    else if($semestermodule['praktikum_bestanden'] === null)
        $semestermodule['praktikum_bestanden'] = null;
    else $semestermodule['praktikum_bestanden'] = false;


    if($semestermodule['pruefung_teilnahme'])
        $semestermodule['pruefung_teilnahme'] = true;
    else
        $semestermodule['pruefung_teilnahme'] = false;
    if($semestermodule['praktikum_teilnahme'])
        $semestermodule['praktikum_teilnahme'] = true;
    else
        $semestermodule['praktikum_teilnahme'] = false;
    if($semestermodule['vorlesung_teilnahme'])
        $semestermodule['vorlesung_teilnahme'] = true;
    else
        $semestermodule['vorlesung_teilnahme'] = false;
    $link = connectdb();

    $sql = "INSERT INTO semester_hat_modul(modul_id, semester_id, modultitel, modulnotiz, pruefungsnote, praktikum_bestanden, pruefung_teilnahme, praktikum_teilnahme, vorlesung_teilnahme) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "iissdiiii",
        $semestermodule['modul_id'],
        $semester_id,
        $semestermodule['modultitel'],
        $semestermodule['modulnotiz'],
        $semestermodule['pruefungsnote'],
        $semestermodule['praktikum_bestanden'],
        $semestermodule['pruefung_teilnahme'],
        $semestermodule['praktikum_teilnahme'],
        $semestermodule['vorlesung_teilnahme']
    );
    mysqli_stmt_execute($stmt);
    mysqli_stmt_close($stmt);

    $res = mysqli_query($link, 'SELECT LAST_INSERT_ID()');
    $row = mysqli_fetch_array($res);
    $semester_hat_modul_id = $row[0];


    mysqli_close($link);
    return $semester_hat_modul_id;
}


function db_select_all_semester_from(int $studienverlaufsplan_id) {
    $link = connectdb();

    $sql = "SELECT id, studienverlaufsplan_id, semestertyp, semester, semesterjahr FROM semester WHERE studienverlaufsplan_id = $studienverlaufsplan_id";

    $result = mysqli_query($link, $sql);

    $data = mysqli_fetch_all($result, MYSQLI_ASSOC);

    mysqli_free_result($result);
    mysqli_close($link);
    return $data;
}

function db_duplicate_semester(array $semester, int $studienverlaufsplan_id)
{
    $link = connectdb();

    $sql = "INSERT INTO semester(studienverlaufsplan_id, semestertyp, semester, semesterjahr) VALUES (?, ?, ?, ?)";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "isss",
        $studienverlaufsplan_id,
        $semester['semestertyp'],
        $semester['semester'],
        $semester['semesterjahr']
    );
    mysqli_stmt_execute($stmt);
    mysqli_stmt_close($stmt);

    $res = mysqli_query($link, 'SELECT LAST_INSERT_ID()');
    $row = mysqli_fetch_array($res);
    $semester_id = $row[0];


    mysqli_close($link);
    return $semester_id;
}


function db_select_all_studienverlaufsplan(int $studienverlaufsplan_id) {
    $link = connectdb();

    $sql = "SELECT studienbeginn, anzahl_fachsemester, name, veroeffentlichungsjahr_po, einschreibung, praxisprojekt, public FROM studienverlaufsplan

WHERE studienverlaufsplan.id = $studienverlaufsplan_id";

    $result = mysqli_query($link, $sql);

    $data = mysqli_fetch_all($result, MYSQLI_ASSOC);

    mysqli_free_result($result);
    mysqli_close($link);
    return $data[0];
}

function db_duplicate_studienverlaufsplan(array $studienverlaufsplan) {
    $link = connectdb();

    $sql = "INSERT INTO studienverlaufsplan(studienbeginn, anzahl_fachsemester, name, veroeffentlichungsjahr_po, einschreibung, praxisprojekt, public) VALUES (?, ?, ?, ?, ?, ?, ?)";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "sisssii",
        $studienverlaufsplan['studienbeginn'],
        $studienverlaufsplan['anzahl_fachsemester'],
        $studienverlaufsplan['name'],
        $studienverlaufsplan['veroeffentlichungsjahr_po'],
        $studienverlaufsplan['einschreibung'],
        $studienverlaufsplan['praxisprojekt'],
        $studienverlaufsplan['public']
    );
    mysqli_stmt_execute($stmt);
    mysqli_stmt_close($stmt);

    $res = mysqli_query($link, 'SELECT LAST_INSERT_ID()');
    $row = mysqli_fetch_array($res);
    $studienverlaufsplan_id = $row[0];


    mysqli_close($link);
    return $studienverlaufsplan_id;
}




function db_select_modul_veranstaltungen_teilnahme(int $studienverlaufsplan_id) {
    $link = connectdb();

    $sql = "SELECT semester_hat_modul.id, modulname, vorlesung_teilnahme, praktikum_teilnahme, pruefung_teilnahme FROM semester_hat_modul
    INNER JOIN modul
        ON semester_hat_modul.modul_id = modul.id
    INNER JOIN semester s on semester_hat_modul.semester_id = s.id WHERE studienverlaufsplan_id = $studienverlaufsplan_id";

    $result = mysqli_query($link, $sql);

    $data = mysqli_fetch_all($result, MYSQLI_ASSOC);

    mysqli_free_result($result);
    mysqli_close($link);
    return $data;
}

function db_semester_hat_modul_add_teilnahme($modul_id, $semester_id, $veranstaltung) {
    $link = connectdb();

    $sql = "UPDATE semester_hat_modul SET ${veranstaltung}_teilnahme = true WHERE semester_id = ? AND modul_id = ?";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "ii", $semester_id, $modul_id);
    $result = mysqli_stmt_execute($stmt);

    mysqli_stmt_close($stmt);
    mysqli_close($link);
    return $result;
}

function db_semester_hat_modul_remove_teilnahme($modul_id, $semester_id, $veranstaltung) {
    $link = connectdb();

    $sql = "UPDATE semester_hat_modul SET ${veranstaltung}_teilnahme = false WHERE semester_id = ? AND modul_id = ?";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "ii", $semester_id, $modul_id);
    $result = mysqli_stmt_execute($stmt);

    mysqli_stmt_close($stmt);
    mysqli_close($link);
    return $result;
}

function db_semester_hat_modul_delete_modul($modul_id, $semester_id) {
    $link = connectdb();

    $sql = "DELETE FROM semester_hat_modul WHERE semester_id = ? AND modul_id = ?";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "ii", $semester_id, $modul_id);
    $result = mysqli_stmt_execute($stmt);

    mysqli_stmt_close($stmt);
    mysqli_close($link);
    return $result;
}

function db_select_modulId_by_name($modulname) {
    $link = connectdb();

    $sql = "SELECT id FROM modul WHERE modulname = ?";

    /*
    $result = mysqli_query($link, $sql);

    $row_data = mysqli_fetch_assoc($result);

    mysqli_free_result($result);
    mysqli_close($link);
    return $row_data;*/

    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("s", $modulname);
    $stmt->execute();

    $result = $stmt->get_result()->fetch_assoc();


    $stmt->close();

    $link->close();
    return $result;
}

function db_select_semesterId_by_jahr(string $semesterjahr, int $studienverlaufsplan_id) {
    $link = connectdb();

    $sql = "SELECT id FROM semester WHERE semesterjahr = ? AND studienverlaufsplan_id = ?";
    /*
    $result = mysqli_query($link, $sql);

    $row_data = mysqli_fetch_assoc($result);

    mysqli_free_result($result);
    mysqli_close($link);
    return $row_data;*/

    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("si", $semesterjahr, $studienverlaufsplan_id);
    $stmt->execute();

    $result = $stmt->get_result()->fetch_assoc();


    $stmt->close();

    $link->close();
    return $result;
}

function db_add_modules_semester($modulname, $vorlesung, $praktikum, $pruefung, $semesterjahr, $studienverlaufsplan_id) {
    $link = connectdb();
    $pruefungsnote = 0.0;

    $modul_id = (int)db_select_modulId_by_name($modulname)['id'];
    $semester_id = (int)db_select_semesterId_by_jahr($semesterjahr, $studienverlaufsplan_id)['id'];


    $sql = "INSERT INTO semester_hat_modul(modul_id, semester_id, modultitel, pruefungsnote, pruefung_teilnahme, praktikum_teilnahme, vorlesung_teilnahme) VALUES(?, ?, ?, ?, ?, ?, ?)";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "iisdiii", $modul_id, $semester_id, $modulname, $pruefungsnote, $pruefung, $praktikum, $vorlesung);
    $result = mysqli_stmt_execute($stmt);


    mysqli_stmt_close($stmt);

    mysqli_close($link);
    return $result;
}

function db_verify_modul(string $modulname, int $studienverlaufsplan_id) {
    $link = connectdb();

    $sql = "SELECT anzeigename_veraenderbar, wintersemester, sommersemester, fachsemester FROM modul
    JOIN studienverlaufsplan_data ON modul.id = studienverlaufsplan_data.modul_id
WHERE modul.modulname = ? AND verlaufsplan_id = ?";

    /*
    $result = mysqli_query($link, $sql);

    $row_data = mysqli_fetch_assoc($result);

    mysqli_free_result($result);
    mysqli_close($link);
    return $row_data;*/


    $stmt = $link->stmt_init();
    $stmt->prepare($sql);
    $stmt->bind_param("si", $modulname, $studienverlaufsplan_id);
    $stmt->execute();

    $result = $stmt->get_result()->fetch_assoc();


    $stmt->close();

    $link->close();
    return $result;
}

function db_verify_veranstaltung_modul_semester($modulname, $semesterjahr, $studienverlaufsplan) {
    $link = connectdb();

    $sql = "SELECT wintersemester, sommersemester, semestertyp, vorlesung_teilnahme, praktikum_teilnahme, pruefung_teilnahme FROM semester_hat_modul
        JOIN semester s on semester_hat_modul.semester_id = s.id AND s.semesterjahr = '$semesterjahr'
        JOIN modul m on m.id = semester_hat_modul.modul_id AND m.modulname = '$modulname' AND studienverlaufsplan_id = '$studienverlaufsplan'";

    $result = mysqli_query($link, $sql);

    $data = mysqli_fetch_all($result, MYSQLI_ASSOC);

    mysqli_free_result($result);
    mysqli_close($link);
    return $data;
}


function db_select_pruefungsnote_by_semester_id(int $semester_id) {
    $link = connectdb();

    $sql = "SELECT pruefungsnote, m.leistungspunkte FROM semester_hat_modul
                JOIN modul m on m.id = semester_hat_modul.modul_id WHERE semester_id = $semester_id";
    $result = mysqli_query($link, $sql);

    $data = mysqli_fetch_all($result, MYSQLI_ASSOC);

    mysqli_free_result($result);
    mysqli_close($link);
    return $data;
}

/** Alle Module des Studiengangs
 * @param string $studiengang
 * @return array
 */
function db_select_all_moduls_studiengang(int $studiengang_id) : array {
    $link = connectdb();

    $sql = "SELECT modulname, vorlesung, praktikum, pruefung FROM modul";
                
    /*$sql = "SELECT modulname, vorlesung, praktikum, pruefung FROM studiengang_hat_modul
                INNER JOIN studiengang ON studiengang_hat_modul.studiengang_id = '$studiengang_id'
                INNER JOIN modul ON modul.id = studiengang_hat_modul.modul_id";*/
    $result = mysqli_query($link, $sql);

    $data = mysqli_fetch_all($result, MYSQLI_ASSOC);

    mysqli_free_result($result);
    mysqli_close($link);
    return $data;
}


function db_select_veranstaltung_regel(string $modulname): array {
    $link = connectdb();

    $sql = "SELECT vorlesung, praktikum, pruefung, wintersemester, sommersemester FROM modul WHERE modulname = $modulname";
    $result = mysqli_query($link, $sql);

    $data = mysqli_fetch_all($result, MYSQLI_ASSOC);

    mysqli_free_result($result);
    mysqli_close($link);
    return $data;
}

/** Entnimmt alle Module aus der DB.
 * @return array Alle Module
 */
function db_select_veranstaltungen_from_modul() : array{
    $link = connectdb();

    $sql = "SELECT modulname, vorlesung, praktikum, pruefung FROM modul";
    $result = mysqli_query($link, $sql);

    $data = mysqli_fetch_all($result, MYSQLI_ASSOC);

    mysqli_free_result($result);
    mysqli_close($link);
    return $data;
}

/** Entnimmt alle Semester aus dem Studienverlaufsplan vom Student aus DB.
 * @param int $studienverlaufsplan_id ID des Studienverlaufsplans
 * @return array Alle Semester im Studienverlaufsplan vom Student
 */
function db_select_all_semester_from_student(int $studienverlaufsplan_id) {
    $link = connectdb();

    $sql = "
    SELECT semester.id, semester, semestertyp, semesterjahr FROM semester
        INNER JOIN studienverlaufsplan
            ON semester.studienverlaufsplan_id = studienverlaufsplan.id
        INNER JOIN student
            ON student.studienverlaufsplan_id = studienverlaufsplan.id AND student.studienverlaufsplan_id = $studienverlaufsplan_id";//student.benutzer_id


    $result = mysqli_query($link, $sql);

    $data = mysqli_fetch_all($result, MYSQLI_ASSOC);

    mysqli_free_result($result);
    mysqli_close($link);
    return $data;
}

/** Entnimmt alle Module aus dem zugehörigen Semester.
 * @param int $semester_id Semester ID
 * @return array Alle Module zum zugehörigen Semester
 */
function db_select_all_modules_from_semester(int $semester_id) {
    $link = connectdb();

    $sql = "
    SELECT modulname, vorlesung_teilnahme, praktikum_teilnahme, pruefung_teilnahme, praktikum_bestanden, pruefungsnote FROM semester_hat_modul
        INNER JOIN modul
            ON semester_hat_modul.modul_id = modul.id AND semester_id = $semester_id";


    $result = mysqli_query($link, $sql);

    $data = mysqli_fetch_all($result, MYSQLI_ASSOC);

    mysqli_free_result($result);
    mysqli_close($link);
    return $data;
}
// Very dirty ugly code
function show_module_board($module, $col_name, $col_name2, $col_name3, $css_class, $mattrib, $attrib = "", $modul_content = "", $options_class = "", $options = "", $semester_yes = false) {
    echo "<div id='${module['modulname']}_1' class='modulname'><i class='fas fa-grip-vertical'></i> ${module['modulname']} <span class='$options_class'><i class='fas fa-ellipsis-h' onclick='show_moduloptions(this)'></i>$modul_content</span></div>";
    echo "<div class='$css_class' $attrib>";
    // id für DnD Handler
    if($module[$col_name]) {
        echo "<div id='${module['modulname']}_5' class='veranstaltung' $mattrib><i class='fas fa-grip-vertical'></i>Vorlesung <span class='vorlesung_veranstaltung_delete'>$modul_content</span></div>";
    }
    if($module[$col_name2]) {
        if ($semester_yes)
        {
            // Check if Praktikum wurde bestanden
            if ($module['praktikum_bestanden']) {
                echo "<div id='${module['modulname']}_3' class='veranstaltung' style='background-color: green;' $mattrib><i class='fas fa-grip-vertical'></i>Praktikum <span class='$options_class'>$options$modul_content</span></div>";
            }
            else if ($module['praktikum_bestanden'] === null){
                echo "<div id='${module['modulname']}_3' class='veranstaltung' $mattrib><i class='fas fa-grip-vertical'></i>Praktikum <span class='$options_class'>$options$modul_content</span></div>";
            }
            else {
                echo "<div id='${module['modulname']}_3' class='veranstaltung' style='background-color: red;' $mattrib><i class='fas fa-grip-vertical'></i>Praktikum <span class='$options_class'>$options$modul_content</span></div>";
            }
        }
        else {
            echo "<div id='${module['modulname']}_3' class='veranstaltung' $mattrib><i class='fas fa-grip-vertical'></i>Praktikum <span class='$options_class'>$options$modul_content</span></div>";
        }
    }
    if($module[$col_name3]) {
        if ($semester_yes)
        {
            // Check if Pruefung wurde bestanden
            if ($module['pruefungsnote'] >= 1.0 && $module['pruefungsnote'] <= 4.0) {
                echo "<div id='${module['modulname']}_4' class='veranstaltung' style='background-color: green;' $mattrib><i class='fas fa-grip-vertical'></i>Prüfung <span class='$options_class'>$options$modul_content</span></div>";
            }
            else if($module['pruefungsnote'] > 4.0)
            {
                echo "<div id='${module['modulname']}_4' class='veranstaltung' style='background-color: red;' $mattrib><i class='fas fa-grip-vertical'></i>Prüfung <span class='$options_class'>$options$modul_content</span></div>";
            }
            else {
                echo "<div id='${module['modulname']}_4' class='veranstaltung' $mattrib><i class='fas fa-grip-vertical'></i>Prüfung <span class='$options_class'>$options$modul_content</span></div>";
            }
        }
        else {
            echo "<div id='${module['modulname']}_4' class='veranstaltung' $mattrib><i class='fas fa-grip-vertical'></i>Prüfung <span class='$options_class'>$options$modul_content</span></div>";
        }
    }
    echo "</div>";
}

function show_all_modules() : void {
    // TODO: check benutzer Studiengang
    global $studiengang_id;
    global $studienverlaufsplan_id;
    $modules = db_select_all_moduls_studiengang($studiengang_id);//db_select_veranstaltungen_from_modul();


    $modul_teilnahme = db_select_modul_veranstaltungen_teilnahme($studienverlaufsplan_id);
    // TODO: ID für JS event drag
    foreach ($modules as $module) {
        $enable_drag = "draggable='true' ondragstart='drag(event)'";
        $flag = false;

        if(db_select_cnt_dummy_modul_by_name($module['modulname'], $studienverlaufsplan_id)['cnt'] < 1) {

            // Entferne die Modul / Veranstaltung die schon eingeplant sind
            foreach ($modul_teilnahme as $teilnahme) {
                if ($module['modulname'] === $teilnahme['modulname']) {
                    // Modul existiert schon, disable drag von Modul
                    $enable_drag = "";
                    if ($module['vorlesung'] === $teilnahme['vorlesung_teilnahme']) {
                        $module['vorlesung'] = false;
                    }
                    if ($module['praktikum'] === $teilnahme['praktikum_teilnahme']) {
                        $module['praktikum'] = false;
                    }
                    if ($module['pruefung'] === $teilnahme['pruefung_teilnahme']) {
                        $module['pruefung'] = false;
                    }
                    if ($module['vorlesung'] === false && $module['praktikum'] === false && $module['pruefung'] === false) {
                        $flag = true;
                    }
                }
            }
        }
        if ($flag) continue;

        $dummy_smodule_id = db_select_semestermodul_id($module['modulname'], $studienverlaufsplan_id);
        if($dummy_smodule_id !== null) {
            echo "<div id='${module['modulname']}_$dummy_smodule_id' class='module' $enable_drag>";
        }
        else {
            echo "<div id='${module['modulname']}' class='module' $enable_drag>";
        }
        show_module_board($module, "vorlesung", "praktikum", "pruefung", "veranstaltungen", "draggable='true' ondragstart='drag(event)'");
        echo "</div>";
    }
}

function show_all_semester_modules(int $semester_id) {
    // Alle Module aus dem Semester mit der jeweiligen Modul ID
    // TODO: Vereinfachen
    $modules = db_select_all_modules_from_semester($semester_id);

    if(empty($modules)) {
        echo "<button id='$semester_id' class='semester-button-delete' onclick='deleteSemester(this)'>
            <i class='fas fa-minus-circle'>

            </i>
        </button>";
        // TODO: Implementiere Schaltfläche "Entfernen"
    }

    // Ausgabe der Information jedes Modul im Semester
    foreach ($modules as $module) {
        echo "<div id='${module['modulname']}' class='semester-modul' draggable='true' ondragstart='drag(event)'>";
        show_module_board($module, "vorlesung_teilnahme", "praktikum_teilnahme", "pruefung_teilnahme", "sm-veranstaltungen veranstaltungen", "", "ondrop='drop(event)' ondragover='allowDrop(event)'", "<i class='fas fa-times' onclick='deleteSemesterModul(this)'></i>", "sm-options", "<i class='m-options fas fa-ellipsis-h' onclick='show_veranstaltungoptions(this)'></i>", true);
        echo "</div>";
    }
}

function show_all_semesters() : void {
    // Alle Semester im Studienverlaufsplan vom Student
    global $studienverlaufsplan_id;
    $semesters = db_select_all_semester_from_student((int)$studienverlaufsplan_id);

    // Student hat schon Semester geplant
    if (!empty($semesters)) {
        foreach ($semesters as $semester) {
            // Dummy Semester für Modulbearbeitungsnotizen ignorieren, da nur temp bis Einordnung zum Semester
            if ($semester['semester'] === "dummy") continue;
            $semester_fortschritt = db_select_pruefungsnote_by_semester_id((int)$semester['id']);
            $fortschritt = 0;
            $max_credits = 0;
            foreach ($semester_fortschritt as $f) {
                // Prüfung bestanden = Credits angerechnet
                if($f['pruefungsnote'] >= 1.0 && $f['pruefungsnote'] <= 4.0) {
                    $fortschritt += $f['leistungspunkte'];
                }
                $max_credits += $f['leistungspunkte'];
            }

            echo "<div class='semester ${semester['semester']}' ondrop='drop(event)' ondragover='allowDrop(event)'>";
            echo "<div class='semester-information'><h2>${semester['semester']} ${semester['semesterjahr']}</h2>";
            echo "<h3>${semester['semestertyp']}<progress class='fortschritt' value='$fortschritt' max='$max_credits'></progress></h3>";
            echo "<i class='s-options fas fa-ellipsis-h' onclick='show_semesteroptions(this)'></i>";
            echo "</div>";
            echo "<div id='${semester['semesterjahr']}' class='semester-modules'>";
            show_all_semester_modules((int)$semester['id']);
            echo "</div>";
            echo "</div>";
        }
    }
}


// Periodische Abfrage durch js zur Aktualisierung der Daten bzw. sync. mit DB
if (isset($_GET['data'])) {
    if ($_GET['data'] === "module") {
        show_all_modules();
    }

    if ($_GET['data'] === "studienverlaufsplan") {
        show_all_semesters();
    }
}

// TODO: Regel für Module hinzufügen, Fehlermeldung
if(isset($_GET['verify'])) {
    $modulname = htmlspecialchars($_GET['verify'], ENT_QUOTES | ENT_HTML5, 'utf-8');

    $modul_info = db_verify_modul($modulname, $studienverlaufsplan_id);

    echo json_encode($modul_info);
}

if(isset($_GET['action'])) {
    //logger()->info($_SESSION['email'] . " action : " . $_GET['action']);

    if ($_GET['action'] === "semesteroptions") {
        if (($_SERVER['REQUEST_METHOD'] === "POST") && isset($_POST['semestertyp'], $_POST['semesterjahr'])) {
            $new_semestertyp = "";
            if($_POST['semestertyp'] === "vorlesung") {
                $new_semestertyp = "Vorlesungssemester";
            }
            else if($_POST['semestertyp'] === "praxis") {
                $new_semestertyp = "Praxissemester";
            }
            else if($_POST['semestertyp'] === "ausland") {
                $new_semestertyp = "Auslandssemester";
            }
            else if($_POST['semestertyp'] === "urlaub") {
                $new_semestertyp = "Urlaubssemester";
            }
            else if($_POST['semestertyp'] === "krankheit") {
                $new_semestertyp = "Krankheitssemester";
            }

            if (!empty($new_semestertyp)) {
                include_once './u24.php';
                $semester_id = (int)db_select_semesterId_by_jahr(htmlspecialchars($_POST['semesterjahr'], ENT_QUOTES | ENT_HTML5, 'utf-8'), $studienverlaufsplan_id)['id'];
                if (db_modify_semestertype($new_semestertyp, $semester_id)) {
                    echo "OK";
                }
            }
        }
    }
    // Diese Aktion dient zum temp. Speichern der Modulbearbeitungsdetails für Student bis zum Einordnen ins Sem.
    if(($_SERVER['REQUEST_METHOD'] === "POST") && $_GET['action'] === "dummy") {
        if(isset($_POST['modulname'])) {
            $dummy_semester_id = db_find_dummy_semester($studienverlaufsplan_id);
            $id_dummy_entry = db_insert_dummy_semester_hat_modul_row(htmlspecialchars($_POST['modulname'], ENT_QUOTES | ENT_HTML5, 'utf-8'), $dummy_semester_id);
            echo $id_dummy_entry;
        }
    }

    if(($_SERVER['REQUEST_METHOD'] === "POST") && $_GET['action'] === "moduloptions_dummy") {
        if (isset($_POST['shm_id'], $_POST['modultitel'], $_POST['modulnotiz'], $_POST['pruefungsnote'], $_POST['praktikum_bestanden'])) {
            include_once 'u22.php';
            $pruefungsnote = 0;
            if($_POST['pruefungsnote'] >= 1.0 && $_POST['pruefungsnote'] <= 5.0) {
                $pruefungsnote = (float)$_POST['pruefungsnote'];
            }
            $praktikum_bestanden = false;
            if($_POST['praktikum_bestanden'] === "true") {
                $praktikum_bestanden = true;
            }

            if(db_modify_module_id(htmlspecialchars($_POST['modultitel'], ENT_QUOTES | ENT_HTML5, 'utf-8'), htmlspecialchars($_POST['modulnotiz'], ENT_QUOTES | ENT_HTML5, 'utf-8'), $pruefungsnote, $praktikum_bestanden, (int)$_POST['shm_id'])) {
                echo "OK";
            }
        }
    }

    // Hole speziell dummy vom Modul
    if(($_SERVER['REQUEST_METHOD'] === "GET") && $_GET['action'] === "moduldetails_dummy") {
        if (isset($_GET['shm_id'])) {
            echo json_encode($semester_id = db_select_dummy_modul_entry((int)$_GET['shm_id']));
        }
    }

    if(($_SERVER['REQUEST_METHOD'] === "GET") && $_GET['action'] === "moduldetails") {
        if (isset($_GET['semesterjahr'], $_GET['modulname'])) {
            $semester_id = (int)db_select_semesterId_by_jahr(htmlspecialchars($_GET['semesterjahr'], ENT_QUOTES | ENT_HTML5, 'utf-8'), $studienverlaufsplan_id)['id'];
            echo json_encode(db_select_semestermoduldetail(htmlspecialchars($_GET['modulname'], ENT_QUOTES | ENT_HTML5, 'utf-8'), $semester_id));
        }
    }

    if(($_SERVER['REQUEST_METHOD'] === "POST") && $_GET['action'] === "moduloptions") {
        if (isset($_POST['semesterjahr'], $_POST['modulname'], $_POST['modultitel'], $_POST['modulnotiz'], $_POST['pruefungsnote'], $_POST['praktikum_bestanden'])) {
            include_once './u22.php';
            $semester_id = (int)db_select_semesterId_by_jahr($_POST['semesterjahr'], $studienverlaufsplan_id)['id'];
            $modul_id = (int)db_select_modulId_by_name($_POST['modulname'])['id'];
            $pruefungsnote = 0;
            if($_POST['pruefungsnote'] >= 1.0 && $_POST['pruefungsnote'] <= 5.0) {
                $pruefungsnote = (float)$_POST['pruefungsnote'];
            }
            $praktikum_bestanden = false;
            if($_POST['praktikum_bestanden'] === "true") {
                $praktikum_bestanden = true;
            }

            if(db_modify_module(htmlspecialchars($_POST['modultitel'], ENT_QUOTES | ENT_HTML5, 'utf-8'), htmlspecialchars($_POST['modulnotiz'], ENT_QUOTES | ENT_HTML5, 'utf-8'), $pruefungsnote, $praktikum_bestanden, $semester_id, $modul_id)) {
                echo "OK";
            }
        }
    }

    if(($_SERVER['REQUEST_METHOD'] === "POST") && $_GET['action'] === "veranstaltungoption") {
        if(isset($_POST['semesterjahr']))
        {
            $semester_id = (int)db_select_semesterId_by_jahr(htmlspecialchars($_POST['semesterjahr'], ENT_QUOTES | ENT_HTML5, 'utf-8'), $studienverlaufsplan_id)['id'];
            $modul_id = (int)db_select_modulId_by_name(htmlspecialchars($_POST['modulname'], ENT_QUOTES | ENT_HTML5, 'utf-8'))['id'];
            if(isset($_POST['pruefungsnote']))
            {
                $pruefungsnote = 0;
                if((float)$_POST['pruefungsnote'] >= 1.0 && (float)$_POST['pruefungsnote'] <= 5.0) {
                    $pruefungsnote = (float)$_POST['pruefungsnote'];
                }
                if(db_modify_module_pruefung($pruefungsnote, $semester_id, $modul_id)) {
                    echo "OK";
                }
            }
            else if (isset($_POST['praktikum_bestanden']))
            {
                $praktikum_bestanden = false;
                if ($_POST['praktikum_bestanden'] === "true") {
                    $praktikum_bestanden = true;
                }
                if (db_modify_module_praktikum($praktikum_bestanden, $semester_id, $modul_id)) {
                    echo "OK";
                }
            }
            else {
                $praktikum_bestanden = false;
                if (db_modify_module_praktikum($praktikum_bestanden, $semester_id, $modul_id)) {
                    echo "OK";
                }
            }
        }
    }


    if ($_GET['action'] === "add_module") {
        $json = filter_input(INPUT_POST, 'json');
        $decoded_json = json_decode($json);

        $modulname = htmlspecialchars($decoded_json[0], ENT_QUOTES | ENT_HTML5, 'utf-8');
        $semesterjahr = htmlspecialchars($decoded_json[Count($decoded_json)-1], ENT_QUOTES | ENT_HTML5, 'utf-8');

        $result = db_select_cnt_dummy_modul_by_name($modulname, $studienverlaufsplan_id);
        if ($result['cnt'] > 0) {
            // UGLY HACK
            $modul_id = (int)db_select_modulId_by_name($modulname)['id'];
            $semester_id = (int)db_select_semesterId_by_jahr($semesterjahr, $studienverlaufsplan_id)['id'];
            if (db_transform_dummy_to_shm($result['id'], $modul_id, $semester_id)) {
                if (db_delete_old_dummy($result['id'], (int)$result['semester_id'])) {
                    echo "OK";
                    exit();
                }
            }
        }


        // Vorlesung, Praktikum, Prüfung
        $veranstaltungen = array('vorlesung' => false, 'praktikum' => false, 'pruefung' => false);

        // Parsing OP
        for ($i = 1; $i < Count($decoded_json); $i++) {
            if ($decoded_json[$i] === "Vorlesung") {
                $veranstaltungen['vorlesung'] = true;
            } else if ($decoded_json[$i] === "Praktikum") {
                $veranstaltungen['praktikum'] = true;
            } else if ($decoded_json[$i] === "Prüfung") {
                $veranstaltungen['pruefung'] = true;
            }
        }


        if(db_add_modules_semester($modulname, $veranstaltungen['vorlesung'], $veranstaltungen['praktikum'], $veranstaltungen['pruefung'], $semesterjahr, $studienverlaufsplan_id)) {
            echo "OK";
        }
    }

    if ($_GET['action'] === "modul_change_semester") {
        $json = filter_input(INPUT_POST, 'json');
        $decoded_json = json_decode($json);

        $modulname = htmlspecialchars($decoded_json[0], ENT_QUOTES | ENT_HTML5, 'utf-8');
        $semesterjahr = htmlspecialchars($decoded_json[Count($decoded_json)-1], ENT_QUOTES | ENT_HTML5, 'utf-8');
        $old_semester_id = db_select_modul_from_semester($modulname, $studienverlaufsplan_id);
        $new_semester_id = db_select_semesterId_by_jahr($semesterjahr, $studienverlaufsplan_id)['id'];
        if (db_update_modul_to_new_semester($new_semester_id, $old_semester_id, $modulname)) {
            echo "OK";
        }
    }

    if ($_GET['action'] === "add_veranstaltung") {
        $json = filter_input(INPUT_POST, 'json');
        $decoded_json = json_decode($json);

        $modulname = htmlspecialchars(preg_split('/_/',$decoded_json[0])[0], ENT_QUOTES | ENT_HTML5, 'utf-8');
        $veranstaltung = htmlspecialchars($decoded_json[1], ENT_QUOTES | ENT_HTML5, 'utf-8');
        $semesterjahr = htmlspecialchars($decoded_json[2], ENT_QUOTES | ENT_HTML5, 'utf-8');

        if($veranstaltung === "Prüfung") {
            $veranstaltung = "pruefung";
        }
        if($veranstaltung === "Vorlesung") {
            $veranstaltung = strtolower($veranstaltung);
        }
        if($veranstaltung === "Praktikum") {
            $veranstaltung = strtolower($veranstaltung);
        }

        $semester_id = (int)db_select_semesterId_by_jahr($semesterjahr, $studienverlaufsplan_id)['id'];
        $modul_id = (int)db_select_modulId_by_name($modulname)['id'];

        if(db_semester_hat_modul_add_teilnahme($modul_id, $semester_id, $veranstaltung)) {
            echo "OK";
        }
    }

    if ($_GET['action'] === "delete_modul") {
        $json = filter_input(INPUT_POST, 'json');
        $decoded_json = json_decode($json);
        $modulname = htmlspecialchars($decoded_json[1], ENT_QUOTES | ENT_HTML5, 'utf-8');
        $semesterjahr = htmlspecialchars($decoded_json[0], ENT_QUOTES | ENT_HTML5, 'utf-8');

        $semester_id = (int)db_select_semesterId_by_jahr($semesterjahr, $studienverlaufsplan_id)['id'];
        $modul_id = (int)db_select_modulId_by_name($modulname)['id'];

        if (db_semester_hat_modul_delete_modul($modul_id, $semester_id)) {
            echo "OK";
        }

    }

    if ($_GET['action'] === "delete_modulveranstaltung") {
        $json = filter_input(INPUT_POST, 'json');
        $decoded_json = json_decode($json);
        $modulname = htmlspecialchars($decoded_json[0], ENT_QUOTES | ENT_HTML5, 'utf-8');
        $veranstaltung = htmlspecialchars($decoded_json[1], ENT_QUOTES | ENT_HTML5, 'utf-8');
        $semesterjahr = htmlspecialchars($decoded_json[2], ENT_QUOTES | ENT_HTML5, 'utf-8');

        $semester_id = (int)db_select_semesterId_by_jahr($semesterjahr, $studienverlaufsplan_id)['id'];
        $modul_id = (int)db_select_modulId_by_name($modulname)['id'];

        if($veranstaltung === "Prüfung") {
            $veranstaltung = "pruefung";
            db_modify_module_pruefung(0, $semester_id, $modul_id);
            db_modify_module_praktikum(false, $semester_id, $modul_id);
        }
        if($veranstaltung === "Vorlesung") {
            $veranstaltung = strtolower($veranstaltung);
        }
        if($veranstaltung === "Praktikum") {
            $veranstaltung = strtolower($veranstaltung);
            db_modify_module_praktikum(false, $semester_id, $modul_id);
            db_modify_module_pruefung(0, $semester_id, $modul_id);
        }


        if(db_semester_hat_modul_remove_teilnahme($modul_id, $semester_id, $veranstaltung)) {
            echo "OK";
        }
    }
}
?>