<?php

include_once ('dbconfig/config.php');



    $link = dbconnect();

    $sql = "DELETE FROM studienverlaufsplan_data where verlaufsplan_id = 5";
    mysqli_query($link, $sql);