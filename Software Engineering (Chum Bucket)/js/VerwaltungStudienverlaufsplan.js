 function gear_function(d)
    {
        var id = d.getAttribute("id");
        //alert(d.getAttribute("id"));
        window.location.href = "VerwaltungStudienverlaufsplan.php?id=" + id;
    }



    $(document).ready(function()
    {
        //$( ".modul" ).appendTo( $( ".fenster" ) );

        $( ".modul" ).draggable({
            helper: 'clone',
            revert: 'invalid',
            appendTo: 'body'
        });

        $( "dialog" ).draggable({
        });

        $(".fenster").droppable({
            accept: ".modul",
            drop: function(ev, ui)
                 {
                     var droppedItem = $(ui.draggable);
                     $(this).append(droppedItem);

                     var droppableId = $(this).attr("id");
                     var draggableId = ui.draggable.attr("id");
                    window.location.href = "VerwaltungStudienverlaufsplan.php?p=" + droppableId + "&c=" + draggableId;
                }
        });
    });
