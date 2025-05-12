// Decides to open or close the Menu
function decideMenuState() {
    let menu = document.getElementById("Menu");
    let stateButton = document.getElementById("state");
    console.log(stateButton.dataset);
    if (stateButton.dataset.state == "close") {

        stateButton.textContent = "Open";
        stateButton.dataset.state = "open";

        closeMenu(menu);
    } else {

        stateButton.textContent = "Close";
        stateButton.dataset.state = "close";

        openMenu(menu);
    }
}

// Open Menu
function openMenu(menu) {
    menu.style.width = "50%";
    for (let child of menu.children) {
        if (!child.classList.contains("open")) {
            child.style.display = "block";
        };
    };
    // Turn opacity to 0.8
    document.body.style.backgroundColor = "rgba(65,105,225,0.8)";
}

// Close Menu Bar
function closeMenu(menu) {
    menu.style.width = "7%";
    for (let child of menu.children) {
        if (child.classList.contains("header")) {
            console.log("FUK");
            child.remove();
            continue;
        }
        if (!child.classList.contains("open")) {
            child.style.display = "none";
        };
    };
    // Turn opacity back to 1
    document.body.style.backgroundColor = "rgba(65,105,225,1)";

}

// Changes Content of Menu into the topic/type
function changeMenuContent(buttonObject) {
    console.log("FUCK");

    let type = buttonObject.id;
    let menu = document.getElementById("Menu");
    
    for (child of menu.children) {
        if (child.id != "state") {
            child.style.display = "none";
        };
    };

    let title = document.createElement("h1");
    title.textContent = type;
    title.className = "header center";
    menu.appendChild(title);


    if (type == "import") {
        return 0
    }

    // Read database for type and
    let data = readDB(type);
    changeContent(data);
}

function readDB(type) {
    // func from other files
};

function changeContent(data) {
    
}

// Add New Record or Event in Current Schedule
function addNewRecord() {
    
    let body = document.createElement("div");
    body.className = "Popup";
    body.id = "addDiv";

    const parameters = [
        "Period",
        "Event"
    ]

    for (let parameter of parameters) {
        let box = document.createElement("div");
        box.className = "center";

        let text = document.createElement("label");
        text.textContent = parameter;

        let input = document.createElement("input");
        text.className = parameter + " input";

        box.appendChild(text);
        box.appendChild(input);

        body.appendChild(box);
    }

    document.body.appendChild(body);
}

//runs on start up
window.onload = () => {
    createTable();
}


// Listens to event where the mouse click off menu while menu is open, close it
window.addEventListener('mouseup', function(e) {
    let menu = document.getElementById("Menu");
    let stateButton = document.getElementById("state");
    for (child of menu.children) {
        if (e.target == child) {
            return
        } 
    };
    if (e.target != menu) {
        if (stateButton.className == "close") {
            stateButton.textContent = "Open";
            stateButton.className = "open";
            closeMenu(menu);
        }
    };
});