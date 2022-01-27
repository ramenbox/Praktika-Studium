<?php declare(strict_types=1);
/**
 * @title Aktivität 22
 * @description Modulstatus anpassen
 * @author Marco Catulo
 */
//require_once __DIR__ . '/includes/db.inc.php';
//require_once __DIR__ . '/includes/studienverlaufsplan.php';

/**
 * Notiz, Note und Titel zu Modul hinzufügen
 * @param
 */
function db_modify_module_id(string $modultitel, string $modulnotiz, float $pruefungsnote, bool $praktikum_bestanden, int $id) : bool {
    $link = connectdb();
    $sql = "UPDATE semester_hat_modul SET modultitel = ?, modulnotiz = ?, pruefungsnote = ?, praktikum_bestanden = ? WHERE id = ?";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "ssdii",$modultitel,$modulnotiz, $pruefungsnote, $praktikum_bestanden, $id);
    $result = mysqli_stmt_execute($stmt);

    mysqli_stmt_close($stmt);
    mysqli_close($link);
    return $result;
}

function db_modify_module(string $modultitel, string $modulnotiz, float $pruefungsnote, bool $praktikum_bestanden, int $semesterid, int $modul_id) : bool {
    $link = connectdb();
    $sql = "UPDATE semester_hat_modul SET modultitel = ?, modulnotiz = ?, pruefungsnote = ?, praktikum_bestanden = ? WHERE semester_id = ? AND modul_id = ?";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "ssdiii",$modultitel,$modulnotiz, $pruefungsnote, $praktikum_bestanden, $semesterid, $modul_id);
    $result = mysqli_stmt_execute($stmt);

    mysqli_stmt_close($stmt);
    mysqli_close($link);
    return $result;
}
?>