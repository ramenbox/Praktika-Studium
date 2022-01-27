/*
 * @title Aktivität u20, u21, u25
 * @description Hauptseite des Studierenden anzeigen
 * @author Thanh Dat Tan
 */
// VERY VERY UGLY
let dragged = false;
let changed = false;

let disabled_semesters = [];
let disabled_semesters_credits = [];
let disabled_modules = [];
let enabled_semesters = [];
let reason;
let dragid = "";

function allowDrop(ev) {
    ev.preventDefault();
}

function drag(ev) {
    ev.dataTransfer.setData("text/html", ev.target.id);
    dragid = ev.target.id;
    const el = document.getElementById(ev.target.id);
    el.classList.add('dragged');
    dragged = true;


    // Benutzer zieht Modul
    if (el.className === 'module dragged' || el.className === 'semester-modul dragged') {
        let modulname = DOMPurify.sanitize(el.id);
        if(el.id.split('_').length > 1) {
            modulname = DOMPurify.sanitize(el.id.split('_')[0]);
        }

        $.ajax({
            type: "GET",
            url: "/u20.php?verify=" + modulname, // Abfrage zu Backend für Modul Informationen
            dataType: "html",
            success: function (response) {
                modul_info = JSON.parse(response);

                // Modul kann nicht im Wintersemester absolviert werden
                if (modul_info['wintersemester'] === 0) {
                    const wintersemesters = document.getElementsByClassName('Wintersemester');

                    for (ws of wintersemesters) {
                        ws.classList.add('deadzone');
                    }
                    disabled_semesters = wintersemesters;
                    // Modul nur im Sommersemester
                    reason = "Sommersemester";


                    var sommersemesters = document.getElementsByClassName('Sommersemester');
                    enabled_semesters = sommersemesters;
                    Array.prototype.forEach.call(sommersemesters, function(el) {
                        let lightzone = document.createElement('div');
                        lightzone.innerText = "DROP MODUL HERE";
                        lightzone.classList.add('lightzone');
                        lightzone.setAttribute('ondrop', 'drop(event)');
                        lightzone.setAttribute('ondragover', 'allowDrop(event)');
                        el.lastChild.appendChild(lightzone);
                    });

                }
                // Modul kann nicht im Sommersemester absolviert werden
                if (modul_info['sommersemester'] === 0) {
                    const sommersemesters = document.getElementsByClassName('Sommersemester');

                    for (ss of sommersemesters) {
                        ss.classList.add('deadzone');
                    }
                    disabled_semesters = sommersemesters;
                    // Modul nur im Wintersemester
                    reason = "Wintersemester";

                    var wintersemesters = document.getElementsByClassName('Wintersemester');
                    enabled_semesters = wintersemesters;
                    Array.prototype.forEach.call(wintersemesters, function(el) {
                        let lightzone = document.createElement('div');
                        lightzone.innerText = "DROP MODUL HERE";
                        lightzone.classList.add('lightzone');
                        lightzone.setAttribute('ondrop', 'drop(event)');
                        lightzone.setAttribute('ondragover', 'allowDrop(event)');
                        el.lastChild.appendChild(lightzone);
                    });
                }

                // Es fehlten die nötigen Credits für die Teilnahme am Modul

                let credits_beschraenkt = 0;
                const fachsemester = parseInt(modul_info['fachsemester']);
                if (fachsemester >= 3 && fachsemester < 4)
                {
                    credits_beschraenkt = 30;
                }
                else if (fachsemester >= 4)
                {
                    credits_beschraenkt = 50;
                }

                if (credits_beschraenkt > 0) {
                    reason = "credits";
                    const progress = document.querySelectorAll('progress');
                    var fortschritt = 0;
                    for (x of progress) {
                        // Entnehme den Fortschritt aus der Progressbar
                        fortschritt += parseInt(x.getAttribute('value'));
                    }

                    // Fortschritt reicht nicht aus, sperre die Dropzonen
                    for (x of progress) {
                        if (fortschritt < credits_beschraenkt) {
                            if (!x.parentNode.parentNode.parentNode.classList.contains('deadzone')) {
                                disabled_semesters_credits.push(x.parentNode.parentNode.parentNode);
                                x.parentNode.parentNode.parentNode.classList.add('deadzone');
                            }
                        }
                    }
                }

            }
        });


    }
    else if (el.className === "veranstaltung dragged") {
        reason = "veranstaltung";
        const modulname = el.id.split('_')[0];

        // Finde von der Veranstaltung alle nicht zugehörigen Module
        const modules = document.querySelectorAll('.modulname');
        for(module of modules) {
            const that_modulname = module.getAttribute('id').split('_')[0];

            if (modulname !== that_modulname) {
                disabled_modules.push(module.parentNode);
                module.parentNode.classList.add('deadzone');
            }
        }

        const semesters = document.getElementsByClassName('semester');

        for (let s of semesters) {
            // Alle Semester sperren außer Semester mit dem zugehörigen Modul
            const m = s.querySelectorAll('.modulname');
            let found = false;
            for (let i of m) {
                if (el.parentNode.parentNode.id === i.id.split('_')[0]) {
                    found = true;
                    break;
                }
            }
            if(!found) {
                s.classList.add('deadzone');
            }
        }
        disabled_semesters = semesters;
    }
}

function drop(ev) {
    ev.preventDefault();

    let valid = true;

    const data = ev.dataTransfer.getData("text/html");
    const el = document.getElementById(data);

    // Wir müssen herausfinden wo die deadzone ist bzw. ob die dropzone eine deadzone ist
    // Wir moven Eltern zu Eltern element
    for(var p = ev.target; p !== null; p = p.parentNode) {
        if (p.classList !== undefined && p.classList.length > 0) {
            if (p.classList.contains('deadzone'))  {
                valid = false;

                var hinweis = document.createElement('div');
                hinweis.classList.add('speech-bubble');
                if (reason === "credits") {
                    hinweis.innerText = el.id + " konnte nicht im gewünschten Semester eingeplant werden, da in diesem, dem aktuellen Studienverlaufsplan zufolge, noch nicht genügend Credit Points vorhanden wären";
                }
                else if (reason === "veranstaltung") {
                    hinweis.innerText = "Die Veranstaltung gehört nicht zu diesem Modul";
                }
                else {
                    hinweis.innerText = el.id + " konnte nicht im gewünschten Semester eingeplant werden, da " + el.id + " nur im " + reason + " angeboten wird";
                }
                hinweis.id = 'hinweis';

                var x = ev.clientX;
                var y = ev.clientY;
                hinweis.style.left = x;
                hinweis.style.top = y;
                document.body.appendChild(hinweis);

                $(document).on('mousemove', function(e){
                    $('.speech-bubble').css('top', e.pageY);
                    $('.speech-bubble').css('left', e.pageX);
                });

                // Nach 3 Sekunden verschwindet der Hinweis
                setTimeout(function () {
                    document.getElementById("hinweis").remove(); //document.body.removeChild(hinweis); kann zu Bugs führen
                }, 3000);
            }
        }
    }

    for (let s of disabled_semesters) {
        s.classList.remove('deadzone');
    }

    for (let s of disabled_semesters_credits) {
        s.classList.remove('deadzone');
    }

    for (let m of disabled_modules) {
        m.classList.remove('deadzone');
    }


    // Es wurde versucht ein Modul oder eine Veranstaltung in einem ungültigem Semester hinzuzufügen
    // Dann keine Modulzuweisung bzw. Modul nicht im Semester einplanen

    if(valid) {
        if(ev.target.parentNode !== null) {
            if (ev.target.parentNode.parentNode.parentNode.parentNode !== null) {
                if (!((ev.target.parentNode.parentNode).classList.contains('modules-board'))) {
                    if (ev.target.className === "lightzone") {
                        if (el.className === "module dragged") {
                            el.classList.remove('module');
                            el.classList.add('semester-modul');
                            el.childNodes[1].classList.add('sm-veranstaltungen');
                            ev.target.before(el);
                            el.classList.remove('dragged');

                            // Prepare json data for backend to update table
                            var d = el.innerText.trim().split('\n');
                            d.push((ev.target.parentNode).id);
                            addModule(d);
                        }

                        // Aus einem Semester in einem anderem droppen
                        if (el.className === "semester-modul dragged") {
                            el.classList.remove('module');
                            el.classList.add('semester-modul');
                            el.childNodes[1].classList.add('sm-veranstaltungen');
                            ev.target.before(el);
                            el.classList.remove('dragged');

                            // Prepare json data for backend to update table
                            var d = el.innerText.trim().split('\n');
                            d.push((ev.target.parentNode).id);
                            addModule(d, true);
                        }
                    }
                    // Modul wird in ein leeres Semester gedroppt
                    else if (ev.target.className === "semester-button-delete") {
                        if (el.className === "module dragged") {
                            el.classList.remove('module');
                            el.classList.add('semester-modul');
                            el.childNodes[1].classList.add('sm-veranstaltungen');
                            ev.target.before(el);
                            el.classList.remove('dragged');

                            // Prepare json data for backend to update table
                            var d = el.innerText.trim().split('\n');
                            d.push((ev.target.parentNode).id);
                            addModule(d);
                        }
                    } else if (ev.target.className === "sm-veranstaltungen veranstaltungen") { // Einzelne Veranstaltungen
                        if (el.className === "veranstaltung dragged") {
                            ev.target.appendChild(el);
                            el.classList.remove('dragged')
                            const veranstaltung = el.innerText.trim();
                            const modul = el.id;

                            const semesterjahr = (ev.target.parentNode.parentNode).id;

                            var d = [];
                            d.push(modul);
                            d.push(veranstaltung);
                            d.push(semesterjahr);

                            addVeranstaltung(d);
                        }
                    } else if (ev.target.className === "modulname") {
                        if (el.className === "module dragged") {
                            el.classList.remove('module');
                            el.classList.add('semester-modul');
                            el.childNodes[1].classList.add('sm-veranstaltungen');
                            ev.target.parentNode.parentNode.appendChild(el);
                            el.classList.remove('dragged');

                            // Prepare json data for backend to update table
                            var d = el.innerText.trim().split('\n');
                            d.push((ev.target.parentNode.parentNode).id);
                            addModule(d);
                        }
                    } else if (ev.target.parentNode.className === "sm-veranstaltungen veranstaltungen") {
                        if (el.className === "module dragged") {
                            el.classList.remove('module');
                            el.classList.add('semester-modul');
                            el.childNodes[1].classList.add('sm-veranstaltungen');
                            ev.target.parentNode.parentNode.parentNode.parentNode.appendChild(el);
                            el.classList.remove('dragged');

                            // Prepare json data for backend to update table
                            var d = el.innerText.trim().split('\n');
                            d.push((ev.target.parentNode.parentNode.parentNode).id);
                            addModule(d);
                        }
                    } else if (ev.target.parentNode.parentNode.parentNode.parentNode.querySelector('div').getAttribute('class') === 'semester' && el.className !== "veranstaltung") {
                        if (ev.target.parentNode.querySelector('div').getAttribute('class') === "modulname") {
                            // TODO: Strange, need to fix
                            if (el.className === "module dragged") {
                                el.classList.remove('module');
                                el.classList.add('semester-modul');
                                el.childNodes[1].classList.add('sm-veranstaltungen');
                                ev.target.parentNode.parentNode.appendChild(el);
                                el.classList.remove('dragged');

                                // Prepare json data for backend to update table
                                const d = el.innerText.trim().split('\n');
                                addModule(d);
                            }
                        } else if (ev.target.parentNode.querySelector('div').getAttribute('class') === "veranstaltung") {
                            // TODO: Strange, need to fix
                            if (el.className === "module dragged") {
                                el.classList.remove('module');
                                el.classList.add('semester-modul');
                                el.childNodes[1].classList.add('sm-veranstaltungen');
                                ev.target.parentNode.parentNode.parentNode.appendChild(el);
                                el.classList.remove('dragged');

                                // Prepare json data for backend to update table
                                const d = el.innerText.trim().split('\n');
                                addModule(d);
                            }
                        } else if (ev.target.className === "semester-modules") {
                            if (el.className === "module dragged") {
                                el.classList.remove('module');
                                el.classList.add('semester-modul');
                                el.childNodes[1].classList.add('sm-veranstaltungen');
                                ev.target.appendChild(el);
                                el.classList.remove('dragged');

                                // Prepare json data for backend to update table
                                const d = el.innerText.trim().split('\n');
                                addModule(d);
                            }
                        } else {
                            el.classList.remove('dragged');
                        }
                    }
                }
            }
        }
    }

    dragged = false;
    el.classList.remove('dragged');

    // Remove greenzones
    for (let s of enabled_semesters) {
        if(s.lastChild.lastChild !== null) {
            if(s.lastChild.lastChild.classList.contains('lightzone')) {
                s.lastChild.lastChild.remove();
            }
        }
    }
}

function addVeranstaltung(obj)
{
    obj.forEach(function (d) {
        DOMPurify.sanitize(d);
    });
    $.ajax({
        type: "POST",
        url: "/u20.php?action=add_veranstaltung",
        data: {
            json: JSON.stringify(obj)
        },
        dataType: "html",
        success: function (response) {
            if(response === "OK") {
                getModules();
                getStudienverlaufsplan();
            }
        }
    });
}

function addModule(obj, from_semester=false) {
    obj.forEach(function (d) {
        DOMPurify.sanitize(d);
    });

    if (!from_semester) {
        $.ajax({
            type: "POST",
            url: "/u20.php?action=add_module",
            data: {
                json: JSON.stringify(obj)
            },
            dataType: "html",
            success: function (response) {
                if (response === "OK") {
                    getStudienverlaufsplan();
                }
            }
        });
    }
    else
    {
        $.ajax({
            type: "POST",
            url: "/u20.php?action=modul_change_semester",
            data: {
                json: JSON.stringify(obj)
            },
            dataType: "html",
            success: function (response) {
                if (response === "OK") {
                    getStudienverlaufsplan();
                }
            }
        });
    }
}


function getModules() {
    // DnD deaktiviert Sync.
    if (dragged === false) {
        $.ajax({
            type: "GET",
            url: "/u20.php",
            data: "data=module",
            dataType: "html",
            success: function (response) {
                $('.modules-board').html(response);

            }
        });
    }
}

function getStudienverlaufsplan() {
    if (dragged === false && changed === false) {
        $.ajax({
            type: "GET",
            url: "/u20.php",
            data: "data=studienverlaufsplan",
            dataType: "html",
            success: function (response) {
                const el = $('#semester-button-add');
                $('.semester-board').html(response);
                $('.semester-board').append(el);
                // TODO: Append "<i class='fas fa-times'></i>"

            }
        });
    }
}



function deleteSemesterModul(ev)
{
    if ((ev.parentNode.parentNode).classList.contains('modulname')) {

        var d = [];
        // GET semesterjahr
        d.push(DOMPurify.sanitize((ev.parentNode.parentNode.parentNode.parentNode).id));
        // GET modulname
        d.push(DOMPurify.sanitize((ev.parentNode.parentNode.id).split('_')[0]));


        $.ajax({
            type: "POST",
            url: "/u20.php?action=delete_modul", // TODO: Security Aspekt beachten
            data: {
                json: JSON.stringify(d)
            },
            dataType: "html",
            success: function (response) {
                if(response === "OK") {
                    getModules();
                    getStudienverlaufsplan();
                }
            }
        });

    } else {
        var d = [];
        d.push(DOMPurify.sanitize((ev.parentNode.parentNode.id).split('_')[0])); // Modulname
        d.push(DOMPurify.sanitize(ev.parentNode.parentNode.innerText)); // Veranstaltung
        d.push(DOMPurify.sanitize((ev.parentNode.parentNode.parentNode.parentNode.parentNode).id)); // Semesterjahr

        $.ajax({
            type: "POST",
            url: "/u20.php?action=delete_modulveranstaltung", // TODO: Security Aspekt beachten
            data: {
                json: JSON.stringify(d)
            },
            dataType: "html",
            success: function (response) {

                if(response === "OK") {
                    getModules();
                    getStudienverlaufsplan();
                }
            }
        });
    }

}

/*
 API call für Schaltfläche "Entfernen von Semester"
 */
function deleteSemester(ev)
{
    const el = document.getElementById('logged_in');
    $.ajax({
        type: "GET",
        url: "/u25.php",
        data: "semester_delete=" + encodeURIComponent(DOMPurify.sanitize(ev.id)) + "&for=" + encodeURIComponent(DOMPurify.sanitize(el.innerText)),
        dataType: "html",
        success: function (response) {
            if(response === "OK") {
                getModules();
                getStudienverlaufsplan();
            }
        }
    });
}

/*
 API call für Schaltfläche "Hinzufügen von Semester"
 */
function addNewSemester() {
    // TODO: get last semester information
    const el = document.getElementById('logged_in');

    $.ajax({
        type: "GET",
        url: "/u25.php",
        data: "semester_add="+encodeURIComponent(DOMPurify.sanitize(el.innerText)),
        dataType: "html",
        success: function (response) {
            if(response === "OK") {
                getModules();
                getStudienverlaufsplan();
            }
        }
    });


}

function change_moduloptionsdummy() {
    const shm_id = document.getElementById('shm_id').value;
    const pruefungsnote = document.querySelector('input[name="note"]').value;
    const modultitel = document.querySelector('input[name="titel"]').value;
    const modulnotiz = document.querySelector('textarea[name="notiz"]').value;
    let praktikum_bestanden = false;
    if (document.querySelector('input[name="praktikum"]:checked')) {
        praktikum_bestanden = true;
    }

    $.ajax({
        type: "POST",
        url: "/u20.php?action=moduloptions_dummy",
        data: "shm_id="+DOMPurify.sanitize(shm_id)+"&pruefungsnote="+DOMPurify.sanitize(pruefungsnote)+"&modultitel="+DOMPurify.sanitize(modultitel)+ "&modulnotiz="+DOMPurify.sanitize(modulnotiz)+ "&praktikum_bestanden="+DOMPurify.sanitize(praktikum_bestanden),
        dataType: "html",
        success: function (response) {
            if (response === "OK")
            {
                getStudienverlaufsplan();
            }
        }
    });

    $('#moduloption').remove();
}

function change_moduloptions() {
    const semesterjahr = document.getElementById('semesterjahr').value;
    const modulname = document.getElementById('modulname').value;
    const pruefungsnote = document.querySelector('input[name="note"]').value;
    const modultitel = document.querySelector('input[name="titel"]').value;
    const modulnotiz = document.querySelector('textarea[name="notiz"]').value;
    let praktikum_bestanden = false;
    if (document.querySelector('input[name="praktikum"]:checked')) {
        praktikum_bestanden = true;
    }

    $.ajax({
        type: "POST",
        url: "/u20.php?action=moduloptions",
        data: "modulname="+DOMPurify.sanitize(modulname)+"&semesterjahr="+DOMPurify.sanitize(semesterjahr)+"&pruefungsnote="+DOMPurify.sanitize(pruefungsnote)+"&modultitel="+DOMPurify.sanitize(modultitel)+ "&modulnotiz="+DOMPurify.sanitize(modulnotiz)+ "&praktikum_bestanden="+DOMPurify.sanitize(praktikum_bestanden),
        dataType: "html",
        success: function (response) {
            if (response === "OK")
            {
                getStudienverlaufsplan();
            }
        }
    });

    $('#moduloption').remove();
}

function show_moduloptions(ev) {
    const board = ev.parentNode.parentNode.parentNode.parentNode;

    if (board.className === "modules-board") {
        const modulname =  ev.parentNode.parentNode.parentNode.id;
        const moduldata = modulname.split('_');
        if(moduldata.length > 1) {
            // Es gibt einen Dummyeintrag für Semester sodass Notizen erhalten bleiben
            $.ajax({
                type: "GET",
                url: "/u20.php?verify=" + moduldata[0], // Abfrage zu Backend für Modul Informationen
                dataType: "html",
                success: function (response) {
                    const modulinfo = JSON.parse(response);
                    let moduldetails = {
                        'modultitel': '',
                        'modulnotiz': 'Notiz...',
                        'pruefungsnote': 0.0,
                        'praktikum_bestanden': false
                    };
                    $.ajax({
                        type: "GET",
                        url: "/u20.php?action=moduldetails_dummy",
                        data: "shm_id=" + encodeURIComponent(moduldata[1]),
                        dataType: "html",
                        success: function (response) {
                            moduldetails = JSON.parse(response);

                            moduldetails['pruefungsnote'] = parseFloat(moduldetails['pruefungsnote']);

                            let dialog = document.createElement('dialog');
                            dialog.innerHTML =
                                '<input type="hidden" id="shm_id" name="shm_id" value="' + DOMPurify.sanitize(moduldata[1]) + '">' +
                                '<div class="topbar">Modul bearbeiten:</div>' +
                                '<button class="X" onclick="$(\'#moduloption\').remove()">X</button>' +
                                '<br>' +
                                '<label for="note" style="position: relative;left: 0px">Note:</label> ' +
                                '<input type="text" style="position: relative; left: 3px" id="note" name="note" value="' + ((moduldetails['pruefungsnote'] >= 1.0 && moduldetails['pruefungsnote'] <= 5.0) ? moduldetails['pruefungsnote'] : '') + '"><br>' +
                                '<label for="titel" style="position: relative; left: 0px; margin-top: 10px">Titel: </label>' +
                                '<input type="text" style="position: relative; left: 6px; margin-top: 10px" id="titel" name="titel" value="' + DOMPurify.sanitize(moduldetails['modultitel']) + '" ' + ((modulinfo['anzeigename_veraenderbar'] === 0) ? 'disabled' : '') + '><br>' +
                                '<br>' +
                                '<label for="notiz" style="position: relative; left: 0px;">Geben Sie eine Notiz für ihr Modul ein: </label><br>' +
                                '<textarea style="position: relative; left: 0px; margin-top: 7px" id="notiz" name="notiz" cols="34" rows="10">' + ((moduldetails['modulnotiz'] !== null) ? DOMPurify.sanitize(moduldetails['modulnotiz']) : "Notiz...") + '</textarea><br>' +
                                '<br>' +
                                '<label for="praktikum">Praktikum bestanden?</label>' +
                                '<input type="checkbox" id="praktikum" name="praktikum" ' + ' value="true" ' + ((moduldetails['praktikum_bestanden']) ? 'checked' : '') + '>' +
                                '<br>' +
                                '<br>' +
                                '<button type="reset" onclick="$(\'#moduloption\').remove();" style="position: relative; left: 0px">Abbrechen</button> <button type="submit" onclick="change_moduloptionsdummy()" style="position: relative; right: 0px;background-color: #40beaa">Best&auml;tigen</button>';

                            dialog.setAttribute('id', 'moduloption');
                            document.body.appendChild(dialog);


                            $('#moduloption').show();
                        }
                    });
                }
            });
        } else {
            // Kein Dummyeintrag - erstelle einen um Notizen zu speichern bis zum Hinzufügen ins Semester
            $.ajax({
                type: "POST",
                url: "/u20.php?action=dummy",
                data: "modulname="+DOMPurify.sanitize(modulname),
                dataType: "html",
                success: function (response) {
                    const shm_id = response;
                    getModules();
                    $.ajax({
                        type: "GET",
                        url: "/u20.php?verify=" + moduldata[0], // Abfrage zu Backend für Modul Informationen
                        dataType: "html",
                        success: function (response) {
                            const modulinfo = JSON.parse(response);
                            let moduldetails = {
                                'modultitel': '',
                                'modulnotiz': 'Notiz...',
                                'pruefungsnote': 0.0,
                                'praktikum_bestanden': false
                            };
                            $.ajax({
                                type: "GET",
                                url: "/u20.php?action=moduldetails_dummy",
                                data: "shm_id=" + encodeURIComponent(shm_id),
                                dataType: "html",
                                success: function (response) {
                                    moduldetails = JSON.parse(response);

                                    moduldetails['pruefungsnote'] = parseFloat(moduldetails['pruefungsnote']);

                                    let dialog = document.createElement('dialog');
                                    dialog.innerHTML =
                                        '<input type="hidden" id="shm_id" name="shm_id" value="' + DOMPurify.sanitize(shm_id) + '">' +
                                        '<div class="topbar">Modul bearbeiten:</div>' +
                                        '<button class="X" onclick="$(\'#moduloption\').remove()">X</button>' +
                                        '<br>' +
                                        '<label for="note" style="position: relative;left: 0px">Note:</label> ' +
                                        '<input type="text" style="position: relative; left: 3px" id="note" name="note" value="' + ((moduldetails['pruefungsnote'] >= 1.0 && moduldetails['pruefungsnote'] <= 5.0) ? moduldetails['pruefungsnote'] : '') + '"><br>' +
                                        '<label for="titel" style="position: relative; left: 0px; margin-top: 10px">Titel: </label>' +
                                        '<input type="text" style="position: relative; left: 6px; margin-top: 10px" id="titel" name="titel" value="' + DOMPurify.sanitize(moduldetails['modultitel']) + '" ' + ((modulinfo['anzeigename_veraenderbar'] === 0) ? 'disabled' : '') + '><br>' +
                                        '<br>' +
                                        '<label for="notiz" style="position: relative; left: 0px;">Geben Sie eine Notiz für ihr Modul ein: </label><br>' +
                                        '<textarea style="position: relative; left: 0px; margin-top: 7px" id="notiz" name="notiz" cols="34" rows="10">' + ((moduldetails['modulnotiz'] !== null) ? DOMPurify.sanitize(moduldetails['modulnotiz']) : "Notiz...") + '</textarea><br>' +
                                        '<br>' +
                                        '<label for="praktikum">Praktikum bestanden?</label>' +
                                        '<input type="checkbox" id="praktikum" name="praktikum" ' + ' value="true" ' + ((moduldetails['praktikum_bestanden']) ? 'checked' : '') + '>' +
                                        '<br>' +
                                        '<br>' +
                                        '<button type="reset" onclick="$(\'#moduloption\').remove();" style="position: relative; left: 0px">Abbrechen</button> <button type="submit" onclick="change_moduloptionsdummy()" style="position: relative; right: 0px;background-color: #40beaa">Best&auml;tigen</button>';

                                    dialog.setAttribute('id', 'moduloption');
                                    document.body.appendChild(dialog);


                                    $('#moduloption').show();
                                }
                            });
                        }
                    });

                }
            });
        }

    }
    else {

        const semesterjahr = (ev.parentNode.parentNode.parentNode.parentNode).id;
        const modulname = ((ev.parentNode.parentNode).id).split('_')[0];

        $.ajax({
            type: "GET",
            url: "/u20.php?verify=" + modulname, // Abfrage zu Backend für Modul Informationen
            dataType: "html",
            success: function (response) {
                const modulinfo = JSON.parse(response);
                let moduldetails = {
                    'modultitel': '',
                    'modulnotiz': 'Notiz...',
                    'pruefungsnote': 0.0,
                    'praktikum_bestanden': false
                };
                $.ajax({
                    type: "GET",
                    url: "/u20.php?action=moduldetails",
                    data: "semesterjahr=" + encodeURIComponent(DOMPurify.sanitize(semesterjahr)) + "&modulname=" + encodeURIComponent(DOMPurify.sanitize(modulname)),
                    dataType: "html",
                    success: function (response) {
                        moduldetails = JSON.parse(response);

                        moduldetails['pruefungsnote'] = parseFloat(moduldetails['pruefungsnote']);

                        let dialog = document.createElement('dialog');
                        dialog.innerHTML =
                            '<input type="hidden" id="modulname" name="modulname" value="' + DOMPurify.sanitize(modulname) + '">' +
                            '<input type="hidden" id="semesterjahr" name="semesterjahr" value="' + DOMPurify.sanitize(semesterjahr) + '">' +
                            '<div class="topbar">Modul bearbeiten:</div>' +
                            '<button class="X" onclick="$(\'#moduloption\').remove()">X</button>' +
                            '<br>' +
                            '<label for="note" style="position: relative;left: 0px">Note:</label> ' +
                            '<input type="text" style="position: relative; left: 3px" id="note" name="note" value="' + ((moduldetails['pruefungsnote'] >= 1.0 && moduldetails['pruefungsnote'] <= 5.0) ? moduldetails['pruefungsnote'] : '') + '"><br>' +
                            '<label for="titel" style="position: relative; left: 0px; margin-top: 10px">Titel: </label>' +
                            '<input type="text" style="position: relative; left: 6px; margin-top: 10px" id="titel" name="titel" value="' + DOMPurify.sanitize(moduldetails['modultitel']) + '" ' + ((modulinfo['anzeigename_veraenderbar'] === 0) ? 'disabled' : '') + '><br>' +
                            '<br>' +
                            '<label for="notiz" style="position: relative; left: 0px;">Geben Sie eine Notiz für ihr Modul ein: </label><br>' +
                            '<textarea style="position: relative; left: 0px; margin-top: 7px" id="notiz" name="notiz" cols="34" rows="10">' + ((moduldetails['modulnotiz'] !== null) ? DOMPurify.sanitize(moduldetails['modulnotiz']) : "Notiz...") + '</textarea><br>' +
                            '<br>' +
                            '<label for="praktikum">Praktikum bestanden?</label>' +
                            '<input type="checkbox" id="praktikum" name="praktikum" ' + ' value="true" ' + ((moduldetails['praktikum_bestanden']) ? 'checked' : '') + '>' +
                            '<br>' +
                            '<br>' +
                            '<button type="reset" onclick="$(\'#moduloption\').remove();" style="position: relative; left: 0px">Abbrechen</button> <button type="submit" onclick="change_moduloptions()" style="position: relative; right: 0px;background-color: #40beaa">Best&auml;tigen</button>';

                        dialog.setAttribute('id', 'moduloption');
                        document.body.appendChild(dialog);


                        $('#moduloption').show();
                    }
                });
            }
        });


    }
}

function change_pruefung() {
    const semesterjahr = document.getElementById('semesterjahr').value;
    const modulname = document.getElementById('modulname').value;
    const pruefungsnote = document.querySelector('input[name="note"]').value;

    $.ajax({
        type: "POST",
        url: "/u20.php?action=veranstaltungoption",
        data: "semesterjahr="+DOMPurify.sanitize(semesterjahr)+"&modulname="+DOMPurify.sanitize(modulname)+"&pruefungsnote="+pruefungsnote,
        dataType: "html",
        success: function (response) {
            if (response === "OK")
            {
                getStudienverlaufsplan();
            }
        }
    });

    $('#veranstaltungoption').remove();
}
function change_praktikum() {
    const semesterjahr = document.getElementById('semesterjahr').value;
    const modulname = document.getElementById('modulname').value;
    const el = document.querySelector('input[name="praktikum"]:checked');
    let praktikum_bestanden = false;
    if(el !== null) {
        praktikum_bestanden = true;
    }

    $.ajax({
        type: "POST",
        url: "/u20.php?action=veranstaltungoption",
        data: "semesterjahr="+DOMPurify.sanitize(semesterjahr)+"&modulname="+DOMPurify.sanitize(modulname)+"&praktikum_bestanden="+praktikum_bestanden,
        dataType: "html",
        success: function (response) {
            if (response === "OK")
            {
                getStudienverlaufsplan();
            }
        }
    });

    $('#veranstaltungoption').remove();
}

function show_veranstaltungoptions(ev) {

    const veranstaltung = ev.parentNode.parentNode.innerText;
    const modulname = (ev.parentNode.parentNode.id).split('_')[0];
    const semesterjahr = ev.parentNode.parentNode.parentNode.parentNode.parentNode.id;


    if (veranstaltung === "Prüfung")
    {
        let dialog = document.createElement('dialog');
        dialog.innerHTML =
            '<div class="topbarklein">Note bearbeiten:</div>'+
            '<button class="X"  onclick="$(\'#veranstaltungoption\').remove();">X</button>'+
            '<br>'+
            '<input type="hidden" id="semesterjahr" name="semesterjahr" value="' + DOMPurify.sanitize(semesterjahr) +'">' +
            '<input type="hidden" id="modulname" name="modulname" value="' + DOMPurify.sanitize(modulname) +'">' +
            '<label for="note">Note:</label>' +
            '<input style="margin-left: 5px" type="text" id="note" name="note" value="">' +
            '<br>' +
            '<br>' +
            '<button style="position: relative" type="reset" onclick="$(\'#veranstaltungoption\').remove();">Abbrechen</button> <button style="background-color: #40beaa" type="submit" onclick="change_pruefung()">Bestätigen</button>';

        dialog.setAttribute('id', 'veranstaltungoption');
        document.body.appendChild(dialog);


        $('#veranstaltungoption').show();
    }
    else if (veranstaltung === "Praktikum")
    {
        let dialog = document.createElement('dialog');
        dialog.innerHTML =
            '<div class="topbarklein">Praktikum bearbeiten:</div>'+
            '<button class="X"  onclick="$(\'#veranstaltungoption\').remove();">X</button>'+
            '<br>'+
            '<input type="hidden" id="semesterjahr" name="semesterjahr" value="' + DOMPurify.sanitize(semesterjahr) +'">' +
            '<input type="hidden" id="modulname" name="modulname" value="' + DOMPurify.sanitize(modulname) +'">' +
            '<label for="praktikum">Praktikum bestanden</label>' +
            '<input type="checkbox" id="praktikum" name="praktikum" value="true"><br>' +
            '<br>' +
            '<button style="position: relative" type="reset" onclick="$(\'#veranstaltungoption\').remove();">Abbrechen</button> <button style="background-color: #40beaa" type="submit" onclick="change_praktikum()">Bestätigen</button>';
        dialog.setAttribute('id', 'veranstaltungoption');
        document.body.appendChild(dialog);


        $('#veranstaltungoption').show();
    }

}

function change_semesteroption() {
    const semesterjahr = document.getElementById('semesterjahr').value;
    const semestertyp = document.querySelector('input[name="semestertyp"]:checked').value;

    $.ajax({
        type: "POST",
        url: "/u20.php?action=semesteroptions",
        data: "semestertyp="+ DOMPurify.sanitize(semestertyp) + "&semesterjahr="+DOMPurify.sanitize(semesterjahr),
        dataType: "html",
        success: function (response) {
            if (response === "OK")
            {
                getStudienverlaufsplan();
            }
        }
    });

    $('#semesteroption').remove();
}

function show_semesteroptions(ev) {
    let semester_data = ev.parentNode.childNodes[0].innerText.split(' ');
    let current_semestertyp = DOMPurify.sanitize(ev.parentNode.childNodes[1].innerText);

    let vorlesungchecked = "",
        praxischecked = "",
        auslandchecked = "",
        urlaubchecked = "",
        krankheitchecked = "";

    if (current_semestertyp === "Vorlesungssemester") {
        vorlesungchecked = "checked";
    }
    else if (current_semestertyp === "Praxissemester") {
        praxischecked = "checked";
    }
    else if (current_semestertyp === "Auslandssemester") {
        auslandchecked = "checked";
    }
    else if (current_semestertyp === "Urlaubssemester") {
        urlaubchecked = "checked";
    }
    else if (current_semestertyp === "Krankheitssemester") {
        krankheitchecked = "checked";
    }

    let dialog = document.createElement('dialog');
    dialog.innerHTML = '<form method="dialog">' +
        '<div class="topbarklein">Semestertyp auswählen:</div>' +
        '<button class="X" onclick="$(\'#semesteroption\').remove()">X</button>' +
        '<br>' +
        '<input type="hidden" id="semesterjahr" name="semesterjahr" value="' + DOMPurify.sanitize(semester_data[1]) +'">' +
        '        <input type="radio" id="vorlesung" name="semestertyp" value="vorlesung"' + vorlesungchecked + '>' +
        '        <label for="vorlesung">Vorlesungssemester</label><br>' +
        '        <input type="radio" id="praxis" name="semestertyp" value="praxis"' + praxischecked + '>' +
        '        <label for="praxis">Praxissemester</label><br>' +
        '        <input type="radio" id="ausland" name="semestertyp" value="ausland"' + auslandchecked + '>' +
        '        <label for="ausland">Auslandssemester</label><br>' +
        '        <input type="radio" id="urlaub" name="semestertyp" value="urlaub"' + urlaubchecked + '>' +
        '        <label for="urlaub">Urlaubssemester</label><br>' +
        '        <input type="radio" id="krankheit" name="semestertyp" value="krankheit"' + krankheitchecked + '>' +
        '        <label for="krankheit">Krankheitssemester</label><br>' +
        '        <br>'+
        '        <button type="reset" onclick="$(\'#semesteroption\').remove();">Abbrechen</button>' +
        '        <button type="submit" onclick="change_semesteroption()" style="background-color: #40beaa">Bestätigen</button>' +
        '    </form>';

    dialog.setAttribute('id', 'semesteroption');
    document.body.appendChild(dialog);


    $('#semesteroption').show();
}

$(document).ready(function(){
    getModules();
    getStudienverlaufsplan();

    // TODO: Sync mit DB
    // OVERKILL!
    //observeChangesModuleBoard()
    //observeChangesSemesterBoard()
    // TODO: Nur Sync. mit DB wenn Benutzer Semester, Module hinzufügt oder löscht

    // TODO: Verwalter hat Modul geändert, aber Modulliste noch nicht aktualisiert, Fehlermeldung (Überprüfung)


    // TODO: IF DnD no update
    // Periodische Abfrage der Daten
    //setInterval(getModules, 15000);
    //setInterval(getStudienverlaufsplan, 5000);
    document.addEventListener('dragend', function(event) {
        dragged = false;
        const data = dragid; //event.dataTransfer.getData("text/html");
        const el = document.getElementById(data);
        el.classList.remove('dragged');

        for (let s of disabled_semesters) {
            s.classList.remove('deadzone');
        }

        for (let s of disabled_semesters_credits) {
            s.classList.remove('deadzone');
        }

        for (let m of disabled_modules) {
            m.classList.remove('deadzone');
        }

        for (let s of enabled_semesters) {
            if(s.lastChild.lastChild !== null) {
                if(s.lastChild.lastChild.classList.contains('lightzone')) {
                    s.lastChild.lastChild.remove();
                }
            }
        }
    });

    /*
    document.addEventListener('dragexit', function(event) {

    });*/

});

