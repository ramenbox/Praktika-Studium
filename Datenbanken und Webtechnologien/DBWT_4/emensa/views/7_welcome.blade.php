@extends('home')

@section('title', 'E-Mensa')

@section('header')
    <meta charset="UTF-8">
    <link rel="stylesheet" href="./css/stylesheet.css">
    <link rel="shortcut icon" href="./img/favicon.ico" />
@endsection

@section('nav')
    <div class="photo" style="text-align: center">
        <img width="200" height="55" style="vertical-align:center" src="./img/FHAachen-logo2010.svg.png" alt="">
        <span style="vertical-align:center">
        <nav>
            <ul>
                 <li><a href="#ankuendigung">Ankündigungen</a></li>
                 <li><a href="#speisen">Speisen</a></li>
                 <li><a href="#zahlen">Zahlen</a></li>
                 <li><a href="#kontakt">Kontakt</a></li>
                 <li><a href="#wichtig">Wichtig für uns</a></li>
            </ul>
        </nav>
    </span>
    </div>
    <div class="restaurant" style="text-align: center">
        <img width="1000" height="300" style="vertical-align:center" src="./img/korean-restaurant.jpg" alt=""></div>
@endsection

@section('text')
    <h2 id="ankuendigung">Bald gibt es Essen auch Online</h2>
    <fieldset>
        Lorem ipsum dolor sit amet, consectetur adipiscing elit.
        Nunc ultricies efficitur magna, non fringilla purus dictum pellentesque.
        Maecenas vehicula lorem erat, vitae vehicula elit pretium ut. Sed elementum,
        urna at lobortis accumsan, nunc magna tempus nunc, a iaculis libero erat ac enim.
    </fieldset>
    <br>
@endsection



@section('gerichte')
    <h2 id="speisen">Köstlichkeiten, die Sie erwarten</h2>
    <table style="border-collapse: collapse">
        <thead>
        <tr>
            <th>Speise</th>
            <th>Beschreibung</th>
            <th>Preis Intern</th>
            <th>Preis extern</th>
        </tr>
        </thead>
        <tbody>


        @forelse($data as $meals)
            <tr>
                <td>{{$meals['name']}}</td>
                <td>{{$meals['beschreibung']}}</td>
                <td>{{$meals['preis_intern']}}</td>
                <td>{{$meals['preis_extern']}}</td>
            </tr>
        @empty
            <li>Keine Daten vorhanden.</li>
        @endforelse
        </tbody>
    </table>
    <br>
@endsection

@section('footer')
    <ul>
        <li>(c) E-Mensa GmbH</li>
        <li>Harun & Thava</li>
        <li>Impressum</li>
    </ul>
@endsection
