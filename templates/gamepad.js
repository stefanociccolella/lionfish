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
        console.log({"buttons": myGamepad.buttons.map(e => e.value)})
        const options = {
            method: 'POST', 
            headers: {
                "Content-type": "application/json"
            }, 
            body: JSON.stringify({"axes": myGamepad.axes, 
                                "buttons": myGamepad.buttons.map(e => e.value)
                            })
        };
        fetch('http://192.168.4.38:8000/controller_status', options)
            .then(response => response.json())
            .then(response => console.log(response))
            .catch(err => console.error(err));

    }
}, 1000) // print axes 10 times per second


function moveLeft() {
    const options = { method: 'GET' };
    fetch('http://192.168.4.38:8000/esp?position=1', options)
        .then(response => response.json())
        .then(response => console.log(response))
        .catch(err => console.error(err));
}

function moveRight() {
    const options = { method: 'GET' };
    fetch('http://192.168.4.38:8000/esp?position=~', options)
        .then(response => response.json())
        .then(response => console.log(response))
        .catch(err => console.error(err));
}
