<?php
/**
 * Praktikum DBWT. Autoren:
 * Harun, Karacuban, 3158169
 * Thavarupan, Mahendralingham, 3130383
 */

//Datenbank Verbindungsaufbau
$conn = mysqli_connect("localhost", "root", "root", "emensawerbeseite");
//Falls Verbindung fehlschlägt
if (!$conn) {
    echo ("Verbindung fehlgeschlagen: ") . mysqli_connect_error();
    exit();
}


if(!empty($_POST))
{

    $gericht = $_POST['name'];
    $beschreibung = $_POST['beschreibung'];
    $email = filter_var($_POST['email'], FILTER_SANITIZE_EMAIL);
    $date = date("d-m-y H:i:s");

    $gericht = mysqli_real_escape_string($conn, $gericht);
    $beschreibung = mysqli_real_escape_string($conn, $beschreibung);
    $email = mysqli_real_escape_string($conn, $email);
    //Escape bestimmte Zeichen, \= o.Ä verhindert 'or 1=1;' BSP aus VL

    #Schutz gegen XSS, wandle Sonderzeichen in HTML Format um &euro etc. + konvertiere doppelte und einfache Anführungszeichen
    htmlspecialchars($gericht, ENT_QUOTES, 'UTF-8');
    htmlspecialchars($beschreibung, ENT_QUOTES, 'UTF-8');
    htmlspecialchars($email, ENT_QUOTES, 'UTF-8');

    if (!isset($_POST['erstellerin'])){
        $name = $_POST['erstellerin'];
        htmlspecialchars($name, ENT_QUOTES, 'UTF-8');
        $name = mysqli_real_escape_string($conn, $name);
    } else{
        $name = "anonym";
    }



    $sql = "INSERT INTO wunschgerichte (name,beschreibung,erstelldatum,ersteller,email) VALUES
('$gericht','$beschreibung','$date','$name','$email')";


    if (mysqli_query($conn,$sql)){
        print(  "Das Wunschgericht wurde erfolgreich eingereicht");
        #hier klicken um zurück zu kehren
    } else{
        print(  "Wunschgericht verschicken ist fehlgeschlagen");
    }
    $conn->close();
}


?>

<!DOCTYPE html>
<!--
- Praktikum DBWT. Autoren:
- Harun, Karacuban, 3158169
- Thavarupan, Mahendralingham, 3130383
Praktikum DBWT
-->
<html lang="de">
<head>
    <meta charset="UTF-8">
    <title>Wunschgericht</title>
    <style>
        .container{
            margin-left: 200px;
            margin-right: 200px;
        }
    </style>
</head>
<body>
<div class="container">
<h1>Wunschgericht eingeben!</h1>

    <form method="POST">
    <label for="name">Gericht: </label>
    <input  type="text" id="name" required name="name">
        <br>
    <label for="beschreibung">Beschreibung: </label>
        <input  type="text" required name="beschreibung">
        <br> <label for="erstellerin">Name: </label>
        <input  type="text" name="erstellerin">
        <br><label for="email">E-Mail: </label>
        <input  type="email" required name="email">
        <br>
    <button type="submit" >Wunsch abschicken</button>
</form>
</div>
</body>
</html>