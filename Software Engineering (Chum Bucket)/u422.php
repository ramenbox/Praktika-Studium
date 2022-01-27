<?php declare(strict_types=1);
/**
 * @title Aktivität 422
 * @description Modul Anerkennung
 * @author Marco Catulo
 */

session_start();
include_once ('config.php');

//$_SESSION['email'] = "steffan.moellbeck@alumni.fh-aachen.de";

/**
 * hole die Benutzer
 */
function getBenutzer(string $email) {
    $link = connectdb();
    $sql = "SELECT id FROM benutzer where email = ? ";

    $stmt = mysqli_stmt_init($link);
    mysqli_stmt_prepare($stmt, $sql);
    mysqli_stmt_bind_param($stmt, "s", $email);
    mysqli_stmt_execute($stmt);

    $result = $stmt->get_result()->fetch_assoc();

    mysqli_stmt_close($stmt);
    mysqli_close($link);
    return (int)$result['id'];
}
$user_id = getBenutzer($_SESSION['email']);

/**
 * hole die StudienverlaufsplanID anhand des eingeloggten Benutzers
 * @param $user_id
 * @return bool|mysqli_result
 */
function getSVP_id(int $user_id) {
    $link = connectdb();
    $result = mysqli_query($link, "SELECT studienverlaufsplan_id FROM student WHERE benutzer_id = $user_id");
    return (int)$result->fetch_assoc()['studienverlaufsplan_id'];
}
$SVP_id = getSVP_id($user_id);

function getStudiengang_id(int $user_id) {
    $link = connectdb();
    $result = mysqli_query($link, "SELECT studiengang_id FROM student WHERE benutzer_id = $user_id");
    return (int)$result->fetch_assoc()['studiengang_id'];
}

$studiengang_id = getStudiengang_id($user_id);

/**
 * Lade alle Module des Studiengangs in Array
 * @param int $studiengang_id
 * @return Array mit Modulen
 */
function getModule(int $studiengang_id) {
    $link = connectdb();
    $array = array();
    $sql = mysqli_query($link,"SELECT a.id, a.modulname, a.pruefung, a.praktikum FROM modul as a join studiengang_hat_modul as shm on a.id = shm.modul_id where shm.studiengang_id = $studiengang_id;");
    while($row = mysqli_fetch_array($sql)) {
        $array[] = $row;
    }
    return $array;
}
$listModule = getModule($studiengang_id);

/**
 * hole die IDs zu semester_hat_modul
 * @param $SVP_id
 * @return array
 */
function getSHM_id(int $SVP_id) {
    $link = connectdb();
    $result = array();
    $sql = mysqli_query($link, "SELECT SHM.id, SHM.modul_id FROM semester_hat_modul as SHM join semester as S on SHM.semester_id = S.id WHERE S.studienverlaufsplan_id = $SVP_id;");

    while($row = mysqli_fetch_array($sql)) {
        $result[$row['modul_id']] = $row['id'];
    }
    return $result;
}
$SHM_id = getSHM_id($SVP_id);

/**
 * eintragen der Prüfungen und Praktika Anerkennung
 * @param array $SHM_id
 */
function setPruefungen(array $SHM_id) {
    if(isset($_POST['submit'])) {
        if ($_POST['submit'] == "Bestätigen") {
            $link = connectdb();


            foreach ($SHM_id as $key => $value) {
                $pruefung = false;
                $praktikum = false;

                if (isset($_POST[$key][0])) {
                    $pruefung = true;
                }
                if (isset($_POST[$key][1])) {
                    $praktikum = true;
                }
                //var_dump($pruefung);

                if ($pruefung and $praktikum) {
                    $sql = "update semester_hat_modul set pruefungsnote = 4, praktikum_bestanden = true where id = $value;";
                } elseif ($pruefung) {
                    $sql = "update semester_hat_modul set pruefungsnote = 4 where id = $value;";
                } elseif ($praktikum) {
                    $sql = "update semester_hat_modul set praktikum_bestanden = true where id = $value;";
                }
                else {
                    $sql = "update semester_hat_modul set pruefungsnote = 0, praktikum_bestanden = NULL where id = $value;";
                }

                mysqli_query($link, $sql);

            }

            // Flag zurücksetzten
            $sql_flag = "UPDATE student JOIN benutzer ON benutzer.id = student.benutzer_id SET no_config_flag = false WHERE benutzer.email = '${_SESSION['email']}'";
            $link->query($sql_flag);

            mysqli_close($link);

            echo '<script>setTimeout(function(){window.location.href="/mainpage.php"}, 1)</script>';
            Header("Location: /u20.php");    //weiterleitung zur Hauptseite des Studenten
        } else if ($_POST['submit'] == "Zurück") {
            echo '<script>setTimeout(function(){window.location.href="/a417.php"}, 1)</script>';
            Header("Location: /a417.php");   //zurück zur Studienverlaufsplaner Konfiguration
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
    <script>
        function filterModule() {
            var search, filter, dl, dd, label, i, txt;
            search = document.getElementById("searchbar");
            filter = search.value.toUpperCase();
            dl = document.getElementById("module");
            dd = dl.getElementsByTagName("tr");

            for(i = 0; i < dd.length; i++) {
                label = dd[i].getElementsByTagName("label")[0]

                txt = label.textContent || label.innerText;
                if (txt.toUpperCase().indexOf(filter) > -1) {
                    dd[i].style.display = "";
                } else {
                    dd[i].style.display = "none";
                }

            }
        }
    </script>


    <style>
        * {
            font-family: Verdana, sans-serif;
        }
        h3 {
            display: grid;
            justify-content: center;
            border-bottom: thin solid black;
            padding-bottom: 10px;
        }
        #formular {
            display: grid;
            justify-content: center;
        }
        #searchbar {
            width: 750px;
        }
        table {
            width: 750px;
            margin-bottom: 20px;
        }
        td:last-child {
            text-align: right;
        }
        td:nth-child(2) {
            text-align: center;
        }
        #footer {
            display: flex;
            justify-content: center;
            padding-top: 10px;
            position: sticky;
        }
        #back {
            margin-left: 20px;
            margin-bottom: 10px;
        }
        #ok {
            margin-left: 50px;
            margin-bottom: 10px;
            background-color: #40beaa;
            color: white;
        }

    </style>
</head>
<body>
<h3>Module</h3>
<div id="formular">
<form method="post">
    <input type="text" id="searchbar" onkeyup="filterModule()" placeholder="Suche Modulnamen..." title="Suche nach einem Modul">
    <?php
    echo '<table id="module">';
    foreach($listModule as $modul) {
        if ($modul['pruefung'] == 1 OR $modul['praktikum'] == 1) {
            echo "<tr><td><label>$modul[modulname]</label></td>";
            if ($modul['pruefung'] == 1) { echo '<td><input type="checkbox" value="pruefung" name="'.$modul['id'].'[0]"><label>Prüfung</label></td>';}
            if ($modul['praktikum'] == 1) { echo '<td><input type="checkbox" value="praktium" name="'.$modul['id'].'[1]"><label>Praktikum</label></td>';}
            else { echo '<td></td>'; }
            echo "</tr>";
        }
    }
    echo '</table><hr>'
    ?>
    <div id="footer"><input id="back" type="submit" value="Zurück" name="submit"><input id="ok" type="submit" value="Bestätigen" name="submit"></div>
    <?php setPruefungen($SHM_id); ?>
</form>
</div>
</body>
</html>
