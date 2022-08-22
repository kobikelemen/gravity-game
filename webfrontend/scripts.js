

function request(str)
{
    var url = '192.168.0.91:1234';
    var xml = new XMLHttpRequest();
    xml.open('GET', url, false);
    xml.send(null);

}

document.addEventListener('keydown', function(event) {
    if(event.keyCode == 37) {
        alert('Left was pressed');
        request('left');
    }
    else if(event.keyCode == 39) {
        alert('Right was pressed');
        request('right');
    }
});