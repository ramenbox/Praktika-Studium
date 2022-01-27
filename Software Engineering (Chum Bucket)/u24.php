<?php declare(strict_types=1);
/**
 * @title Aktivität 24
 * @description Modulstatus anpassen
 * @author Marco Catulo
 */
//require_once __DIR__ . '/includes/db.inc.php';
//require_once __DIR__ . '/includes/studienverlaufsplan.php';

/**
 * Semestertyp auswählen
 * @param
 */
function db_modify_semestertype(string $semestertyp, int $semesterid) : bool {
    $link = connectdb();
    $sql = "UPDATE semester SET semestertyp = ? WHERE id = ?";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "si", $semestertyp, $semesterid);
    $result = mysqli_stmt_execute($stmt);

    mysqli_stmt_close($stmt);
    mysqli_close($link);
    return $result;
}

?>