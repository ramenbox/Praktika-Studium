<?php
include_once ('dbconfig/config.php');

function delete_svp($id)
{
    $link = dbconnect();

    $sql = "DELETE FROM studienverlaufsplan where id = '$id'";
    mysqli_query($link, $sql);

    $sql = "DELETE FROM studienverlaufsplan_data where verlaufsplan_id = '$id'";
    mysqli_query($link, $sql);
}

function publish_svp($id)
{
    $link = dbconnect();

    $sql = "update studienverlaufsplan set public = 1 where id = '$id'";
    mysqli_query($link, $sql);
}

function copy_svp($id)
{
    $link = dbconnect();

    $sql = "insert into studienverlaufsplan (studienbeginn, anzahl_fachsemester, name, veroeffentlichungsjahr_po, einschreibung, praxisprojekt, public, credits)
select studienbeginn, anzahl_fachsemester, name, veroeffentlichungsjahr_po, einschreibung, praxisprojekt, public, credits
from studienverlaufsplan where id = '$id'";
    mysqli_query($link, $sql);

    $last_id = $link->insert_id;

    $result = $link->query("select * from studienverlaufsplan_data where verlaufsplan_id = '$id'");
    while($row = $result->fetch_assoc())
    {
        $modul_id = $row['modul_id'];
        $fachsemester = $row['fachsemester'];

        $sql = "INSERT INTO studienverlaufsplan_data VALUES ('$last_id', '$modul_id', '$fachsemester');";
        mysqli_query($link, $sql);
    }


}


function create_vitem($name, $id)
{
    $string = "
    <div class=\"veröffentlicht-item\"> " . $name . "
        <div class=\"container2\" onclick=\"burger_function(this);\"   id=\"" . $id . "\">
            <div class=\"bar1\"></div>
            <div class=\"bar2\"></div>
            <div class=\"bar3\"></div>
        </div>
    </div>";
    return $string;
}

function create_uvitem($name, $id)
{
    $string = "
    <div class=\"unveröffentlicht-item\"> " . $name . "
        <div class=\"container2\" onclick=\"burger_function(this);\"   id=\"" . $id . "\">
            <div class=\"bar1\"></div>
            <div class=\"bar2\"></div>
            <div class=\"bar3\"></div>
        </div>
    </div>";
    return $string;
}

function get_kontotyp($email)
{
    $link = dbconnect();

    $result = $link->query("select email, kontotyp from benutzer where email = '$email'");
    $row = $result->fetch_assoc();

    return $row["kontotyp"];
}