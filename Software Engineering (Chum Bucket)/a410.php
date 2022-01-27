<?php declare(strict_types=1);
/**
 * @title Aktivität 410
 * @description Studienverlaufsplan konfigurieren
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
 * angebenene Daten übernehmen
 * @param
 */
function StudiengangAuswahl(int $user_id) {
    if(isset($_POST['submit'])) {
        if ($_POST['submit'] == "Bestätigen") {
            $link = connectdb();
            $sql = "UPDATE student SET studiengang_id = ?, fachsemester = ? WHERE benutzer_id = ? ";

            $studiengang = (int)$_POST['studiengang'];
            $aktsemester = (int)$_POST['aktsemester'];

            $stmt = mysqli_stmt_init($link);
            mysqli_stmt_prepare($stmt, $sql);
            mysqli_stmt_bind_param($stmt, "iii", $studiengang, $aktsemester, $user_id);
            mysqli_stmt_execute($stmt);

            mysqli_stmt_close($stmt);
            mysqli_close($link);

            echo '<script>setTimeout(function(){window.location.href="/a417.php"}, 1)</script>';
            Header("Location: /a417.php");   //zur Hochschulwechsler Abfrage<
        } else if ($_POST['submit'] == "Zurück") {
            echo '<script>setTimeout(function(){window.location.href="/index.php"}, 1)</script>';
            Header("Location: /index.php");  //zurück zur Loginseite
        }
    }
}

/**
 * Studiengänge in Array laden
 * @return array
 */
function getStudiengaenge() {
    $link = connectdb();
    $array = array();
    $sql = mysqli_query($link,"SELECT id, name FROM studiengang");
    while($row = mysqli_fetch_array($sql)) {
        $array[] = $row;
    }
    return $array;
}
$listStudiengaenge = getStudiengaenge();

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
            padding-top: 10px;
            padding-bottom: 10px;
            padding-left: 10px;
            padding-right: 30px;
        }
        #aktsemester {
            width: 50px;
            margin-bottom: 10px;
        }
        select {
            width: 150px;
            margin-left: 10px;
            margin-bottom: 10px;
        }
        #back {
            margin-left: 20px;
            margin-bottom: 10px;
        }
        #ok {
            margin-left: 50px;
            background-color: #40beaa;
            color: white;
        }
    </style>
</head>
<body>
    <h3>Konfiguration des Studienverlaufplans</h3>
    <div id="formular">
    <form method="post">
        <label for="aktsemester">Aktuelles Semester: </label>
        <input type="number" id="aktsemester" name="aktsemester" value="1">
        <br>
        <select id="studiengangWahl" name="studiengang" size="5">
            <?php   //Liste alle Studiengänge auf
            foreach($listStudiengaenge as $studiengang) {
                echo '<option name="studiengang" value='.$studiengang['id'].' selected >'.$studiengang['name'].'</option>';
            }
            ?>
        </select><br>
        <input id="back" type="submit" value="Zurück" name="submit"><input id="ok" type="submit" value="Bestätigen" name="submit">
        <?php StudiengangAuswahl($user_id); ?>
    </form>
    </div>
</body>
</html>