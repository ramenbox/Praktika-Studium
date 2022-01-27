<?php
require_once('../models/gericht.php');

/* Datei: controllers/HomeController.php */
class HomeController
{
    public function index(RequestData $request) {
        // Frage Daten aus kategorie ab:
        // $data = db_kategorie_select_all();
        $data = db_gericht_select_all();
        return view('7_welcome', ['data' => $data ]);
    }

}