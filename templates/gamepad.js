let gamepadIndex;
window.addEventListener('gamepadconnected', (event) => {
    gamepadIndex = event.gamepad.index;
    let gamepadStatus = document.getElementById("gamepadStatus");
    gamepadStatus.textContent = "Gamepad Detected"
});

window.addEventListener('gamepaddisconnected', (event) => {
    gamepadIndex = event.gamepad.index;
    let gamepadStatus = document.getElementById("gamepadStatus");
    gamepadStatus.textContent = "Gamepad Not Detected"
});

async function getSensors() {
    let response = await fetch('http://169.254.127.13:8000/get_sensors').then(response => response.json());
    let sensors = JSON.parse(response.toString().replace(/'/g, '"'));
    document.getElementById("Leak").innerHTML = sensors.Leak;
    document.getElementById("Compass_Heading").innerHTML = sensors.Compass_Heading;
    document.getElementById("Cell_1").innerHTML = sensors.Cell_1;
    document.getElementById("Acceleration_X").innerHTML = sensors.Acceleration_X;
    document.getElementById("Gyroscope_X").innerHTML = sensors.Gyroscope_X;
    document.getElementById("Magnometer_X").innerHTML = sensors.Magnometer_X;
    document.getElementById("Battery_Voltage").innerHTML = sensors.Battery_Voltage;
    document.getElementById("Depth").innerHTML = sensors.Depth;
    document.getElementById("Cell_2").innerHTML = sensors.Cell_2;
    document.getElementById("Acceleration_Y").innerHTML = sensors.Acceleration_Y;
    document.getElementById("Gyroscope_Y").innerHTML = sensors.Gyroscope_Y;
    document.getElementById("Magnometer_Y").innerHTML = sensors.Magnometer_Y;
    document.getElementById("Internal_Temperature").innerHTML = sensors.Internal_Temperature;
    document.getElementById("Pressure").innerHTML = sensors.Pressure;
    document.getElementById("Cell_3").innerHTML = sensors.Cell_3;
    document.getElementById("Acceleration_Z").innerHTML = sensors.Acceleration_Z;
    document.getElementById("Gyroscope_Z").innerHTML = sensors.Gyroscope_Z;
    document.getElementById("Magnometer_Z").innerHTML = sensors.Magnometer_Z;
    document.getElementById("IMU_Temperature").innerHTML = sensors.IMU_Temperature;
    document.getElementById("Water_Temperature").innerHTML = sensors.Water_Temperature;
    document.getElementById("Cell_4").innerHTML = sensors.Cell_4;




    // console.log(sensors.Depth)
    return sensors

    // getSensors();
    // datafield1.textContent
}

function displayRadioValue() {
    let ele = document.getElementsByName('Mode');
    for (i = 0; i < ele.length; i++) {
        if (ele[i].checked) {
            // console.log(ele[i].value)
            return ele[i].value;
        }
    }
}

function GamepadMode() {
    if (gamepadIndex !== undefined) {
        // a gamepad is connected and has an index
        const myGamepad = navigator.getGamepads()[gamepadIndex];
        // console.log({ "buttons": myGamepad.buttons.map(e => e.value) })
        // console.log(JSON.stringify({ "axes": myGamepad.axes.map(e => parseFloat(e.value)) }))

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
        console.log(options)
        fetch('http://169.254.127.13:8000/controller_status', options)
            .then(response => response.json())
            // .then(response => console.log(response))
            .catch(err => console.error(err));
    }
    else {
        console.log("Gamepad not detected")
    }
}

async function AutoDepthMode() {
    if (document.getElementById("depthOn").checked) {
        let targetDepth = document.getElementById("depth").value;
        // console.log(document.getElementById("depth").value)
        let sensors = await getSensors()
        console.log(sensors.Depth)
        let instruction = [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0].map(x => x * (sensors.Depth - targetDepth) / (10 + Math.abs((sensors.Depth - targetDepth))))
        // [0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]       
        console.log(instruction);
        const options = {
            method: 'POST',
            headers: {
                "Content-type": "application/json"
            },
            body: JSON.stringify({
                "axes": [0, 0, 0, 0],
                "buttons": instruction
            })
        };
        console.log(options)
        fetch('http://169.254.127.13:8000/controller_status', options)
            .then(response => response.json())
            // .then(response => console.log(response))
            .catch(err => console.error(err));
    }
}

async function AutoHeadingMode() {
    let targetDirection = document.getElementById("direction").value;
    // Number(targetDirection)
    console.log(targetDirection)
    console.log(typeof targetDirection)
    // console.log(document.getElementById("depth").value)
    let sensors = await getSensors();
    let compass = sensors.Compass_Heading;
    // Number(compass)
    console.log(compass)
    console.log(typeof compass)
    let offset = 360 - (compass * 1);
    console.log(offset)
    // console.log(typeof offset)
    targetDirection = (offset + (targetDirection * 1)) % 360;
    console.log(targetDirection)
    // console.log(typeof targetDirection)

    let turn = 0;

    if (targetDirection < 180) {
        turn = targetDirection
    }
    else {
        turn = targetDirection - 360
    }
    console.log(turn)

    if ((Math.abs(turn) < 15) && (document.getElementById("headingOn").checked)) {
        let instruction = [0, .2, 0, 0]
        const options = {
            method: 'POST',
            headers: {
                "Content-type": "application/json"
            },
            body: JSON.stringify({
                "axes": instruction,
                "buttons": [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
            })
        };
        console.log(options);
        fetch('http://169.254.127.13:8000/controller_status', options)
            .then(response => response.json())
            // .then(response => console.log(response))
            .catch(err => console.error(err));
    }
    else if (document.getElementById("headingOn").checked) {
        let instruction = [0, 0, 1, 0].map(x => x * turn / (500 + Math.abs(turn)))
        const options = {
            method: 'POST',
            headers: {
                "Content-type": "application/json"
            },
            body: JSON.stringify({
                "axes": instruction,
                "buttons": [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
            })
        };
        console.log(options);
        fetch('http://169.254.127.13:8000/controller_status', options)
            .then(response => response.json())
            // .then(response => console.log(response))
            .catch(err => console.error(err));
    }
}


// main loop for the system
setInterval(() => {
    let mode = displayRadioValue();
    // console.log(mode)
    switch (mode) {
        case "Controller":
            document.getElementById("CurrentMode").innerHTML = "Current Mode: Controller";
            GamepadMode();
            break;
        case "AutoDepth":
            document.getElementById("CurrentMode").innerHTML = "Current Mode: AutoDepth";
            AutoDepthMode()
            break;
        case "AutoHeading":
            document.getElementById("CurrentMode").innerHTML = "Current Mode: AutoHeading";
            AutoHeadingMode()
            break;
    }

    getSensors();

}, 500) // print axes 10 times per second


