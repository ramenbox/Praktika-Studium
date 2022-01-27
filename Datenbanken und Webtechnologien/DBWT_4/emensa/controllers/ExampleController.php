<?php
require_once('../models/kategorie.php');
require_once('../models/gerichtename.php');
require_once('../models/gericht.php');


class ExampleController
{
    //6A
    public function m4_6a_queryparameter(RequestData $rd) {
        return view("examples.m4_6a_queryparameter", ['rd' => $rd]);
    }
    //http://localhost:9000/m4_6a_queryparameter?name=harun

    public function m4_6b_kategorie() {
        $data = db_kategorie_select_all();

        return view("examples.m4_6b_kategorie", [
            'kategorien' => $data
        ]);
    }

    public function m4_6c_gerichte() {
        $data = db_gericht_select_all_name();
        $column = array_column($data, 'name');
        array_multisort($column, SORT_DESC, $data);
        return view('examples.m4_6c_gerichte', [
            'meals' => $data
        ]);
    }

    public function m4_6d_layout(RequestData $rd) {
        $choice = $rd->query['no'];
        if($choice == '2')
            return view('examples.pages.md_6d_page_2', ['rd' => $rd]);
        else
            return view('examples.pages.md_6d_page_1', ['rd' => $rd]);
    }
}