<?php
include_once ('dbconfig/config.php');

function delete_modul($id)
{
    $sql = "delete from semester_hat_modul where modul_id = '$id'";
    mysqli_query($link, $sql);

    $sql = "delete from studiengang_hat_modul where modul_id = '$id'";
    mysqli_query($link, $sql);

    $sql = "delete from studienverlaufsplan_data where modul_id = '$id'";
    mysqli_query($link, $sql);

    $sql = "delete from modul where modul_id = '$id'";
    mysqli_query($link, $sql);
}