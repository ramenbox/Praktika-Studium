<?php declare(strict_types=1);
/**
 * @title Aktivität 417
 * @description Abfrage ob Hochschulwechsler
 * @author Marco Catulo
 */
session_start();
include_once 'includes/studienverlaufsplan.php';
$studienverlaufsplan_data = db_select_studienverlaufsplanId_studiengangId_from_benutzer($_SESSION['email']);
$benutzer_id = (int)$studienverlaufsplan_data['benutzer_id'];
$studienverlaufsplan_id = (int)$studienverlaufsplan_data['studienverlaufsplan_id'];
$studiengang_id = (int)$studienverlaufsplan_data['studiengang_id'];

$_SESSION['benutzer_id'] = $benutzer_id;
$_SESSION['studienverlaufsplan_id'] = $studienverlaufsplan_id;
$_SESSION['studiengang_id'] = $studiengang_id;

include_once 'u20.php';

// $_SESSION from u41 für Studienverlaufsplan_id
if($studienverlaufsplan_id === 1)
{
    // Dupliziere Regelstudienverlaufplan und dann benutze die id davon
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

    $_SESSION['studiengang_id'] = $new_studienverlaufsplan_id;
}

/**
 * abfragen ob Hochschulwechsler
 */
function hochschulwechslerAbfrage() {
    if (isset($_POST['submit'])) {
        if ($_POST['submit'] == "Bestätigen") {
            if ($_POST['hochschulwechsler'] == "true") {
                echo '<script>setTimeout(function(){window.location.href="/a422.php"}, 1)</script>';
                Header("Location: /u422.php");   //Zur Modulanerkennung
            } elseif ($_POST['hochschulwechsler'] == "false") {
                // Reset config flag
                $link = connectdb();
                $sql = "UPDATE student JOIN benutzer ON benutzer.id = student.benutzer_id SET no_config_flag = false WHERE benutzer.email = '${_SESSION['email']}'";
                $result = $link->query($sql);
                echo '<script>setTimeout(function(){window.location.href="/mainpage.php"}, 1)</script>';
                Header("Location: /mainpage.php");    //zur Hauptseite des Studenten
            }

            //Header("Location: /mainpage.php");
        } else if ($_POST['submit'] == "Zurück") {
            echo '<script>setTimeout(function(){window.location.href="/a410.php"}, 1)</script>';
            Header("Location: /a410.php");   //zurück zur Studienverlaufsplaner Konfiguration
        }
    }
}

?>

<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <title>Studienverlaufsplaner</title>

    <style>
        * {
            font-family: Verdana, sans-serif;
        }
        h3 {
            display: grid;
            justify-content: center;
        }
        #formular {
            display: grid;
            justify-content: center;
        }
        form {
            display: block;
            border: thin solid black;
            width: fit-content;
            padding-top: 40px;
            padding-bottom: 20px;
            padding-left: 40px;
            padding-right: 40px;
        }
        #ja {
            margin-left: 40px;
            margin-bottom: 40px;
        }
        #nein {
            margin-left: 80px;
            margin-top: 40px;
        }
        #back {
            margin-left: 10px;
            margin-bottom: 10px;
        }
        #ok {
            margin-left: 80px;
            background-color: #40beaa;
            color: white;
        }
    </style>
</head>
<body>
<h3>Konfiguration des Studienverlaufplans</h3>
<div id="formular">
<form method="post">
    <label>Sind Sie Hochschulwechsler?</label><br>
    <label id="ja" for="ja">Ja</label>
    <input type="radio" name="hochschulwechsler" value="true">
    <label id="nein" for="nein">Nein</label>
    <input type="radio" name="hochschulwechsler" value="false">
    <br>
    <input id="back" type="submit" value="Zurück" name="submit"><input id="ok" type="submit" value="Bestätigen" name="submit">
    <?php hochschulwechslerAbfrage(); ?>
</form>
</div>
</body>
</html>
