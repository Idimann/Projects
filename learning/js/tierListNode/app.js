//import { readFileSync } from "fs";

//const list = 'codeEditors';

//const object = JSON.parse(readFileSync('tierlists/' + list + '.json'));

const tiers = //object['Tiers'];
{
    0: ['S', 'fireBrick'],
    1: ['A', 'orangeRed'],
    2: ['B', 'orange'],
    3: ['C', 'yellow'],
    4: ['D', 'seaGreen'],
    5: ['F', 'green']
};

const elements = //object['Inputs'];
[
    "Vim",
    "Neovim",
    "Emacs",
    "VSCode",
    "Nano",
    "JetBrains"
];

function emptyTiers() {
    let returning = [];

    for(const [_key, _value] of Object.entries(tiers)) {
        returning.push([]);
    }

    return returning;
}

let state = emptyTiers();
let stateIndex = 0;

function addElement(index, element) {
    if(index >= state.length)
        return false;

    state.at(index).push(element);
    display(index);
    return true;
}

let settingIndex = -1;

function display(index) {
    document.getElementById(index).innerHTML = tiers[index].at(0) + ":\t\t";
    document.getElementById(index).style.backgroundColor = tiers[index].at(1);

    let first = true;
    for(const element of state.at(index)) {
        document.getElementById(index).innerHTML += (first ? "" : ",\t") + element;
        first = false;
    }

    if(settingIndex == index)
        document.getElementById(index).innerHTML += (first ? "" : ",\t") +
           elements[stateIndex]  + "\t";
}

function displayAll() {
    for(const [key, _value] of Object.entries(tiers)) {
        display(key);
    }
}

function resetAll() {
    state = emptyTiers();
    displayAll();
}

document.addEventListener('keydown', (e) => {
    if(stateIndex >= elements.length)
        return;

    if(e.key === "Enter") {
        const old = settingIndex;
        settingIndex = -1;

        if(addElement(old, elements.at(stateIndex)))
            ++stateIndex;

        return;
    }

    const keyIndex = Number(e.key);
    if(isNaN(keyIndex))
        return;

    if(keyIndex >= elements.length)
        return;

    const old = settingIndex;
    settingIndex = keyIndex;

    if(old != -1)
        display(old);
    display(settingIndex);
});

