console.log('hello world')
let gamepadIndex;
window.addEventListener('gamepadconnected', (event) => {
    gamepadIndex = event.gamepad.index;
});

// now print the axes on the connected gamepad, for example: 
setInterval(() => {
    if (gamepadIndex !== undefined) {
        // a gamepad is connected and has an index
        const myGamepad = navigator.getGamepads()[gamepadIndex];
        console.log({ "buttons": myGamepad.buttons.map(e => e.value) })
        console.log(JSON.stringify({ "axes": myGamepad.axes.map(e => parseFloat(e.value)) }))

        const options = {
            method: 'POST',
            headers: {
                "Content-type": "application/json"
            },
            body: JSON.stringify({
                "axes": myGamepad.axes,
                "buttons": myGamepad.buttons.map(e => e.value)
            })
        };
        fetch('http://169.254.127.13:8000/controller_status', options)
            .then(response => response.json())
            .then(response => console.log(response))
            .catch(err => console.error(err));

    }
}, 1000) // print axes 10 times per second


function moveLeft() {
    const options = { method: 'GET' };
    fetch('http://169.254.127.13:8000/esp?position=1', options)
        .then(response => response.json())
        .then(response => console.log(response))
        .catch(err => console.error(err));
}

function moveRight() {
    const options = { method: 'GET' };
    fetch('http://169.254.127.13:8000/esp?position=~', options)
        .then(response => response.json())
        .then(response => console.log(response))
        .catch(err => console.error(err));
}

async function get_sensors() {
    const datafield1 = document.getElementById("datafield1");
    datafield1.textContent = await fetch('http://169.254.127.13:8000/get_sensors').then(response => response.json());
    // get_sensors();
}

setInterval(() => get_sensors(), 1000)