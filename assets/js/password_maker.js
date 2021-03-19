//DOMs - document object model elements
const resultEle = document.getElementById('result');
const lengthEle = document.getElementById('length');
const uppercaseEle = document.getElementById('uppercase');
const lowercaseEle = document.getElementById('lowercase');
const numbersEle = document.getElementById('numbers');
const symbolsEle = document.getElementById('symbols');
const generateEle = document.getElementById('generate');
const clipboardEle = document.getElementById('clipboard');


const randomFunction = {
    lower: getRandomLower,
    upper: getRandomUpper,
    number: getRandomNumber,
    symbol: getRandomSymbol
};

//Copy to clipboard functionanilty
clipboardEle.addEventListener('click', () => {
    const textarea = document.createElement('textarea');
    const password = resultEle.innerText;

    if(!password){
        return;
    }

    textarea.value = password;
    document.body.appendChild(textarea);
    textarea.select();
    document.execCommand('copy');
    textarea.remove();
    alert('Password coped to clipboard')
});

//Password maker button
generate.addEventListener('click', () => {
    const length = +lengthEle.value;
    const isLower = lowercaseEle.checked;
    const isUpper = uppercaseEle.checked;
    const isNumber = numbersEle.checked;
    const isSymbol = symbolsEle.checked;

    resultEle.innerText = generatePassword(length, isLower, isUpper, isNumber, isSymbol);
});

function generatePassword(length, lower, upper, number, symbol){
    let pw = '';

    const checked = lower + upper + number + symbol;
    const arr = [{lower}, {upper}, {number}, {symbol}].filter
    (
        item => Object.values(item)[0]
    );
    if(checked == 0){
        return '';
    }
    
    for(let i=0; i<length; i+= checked){
        arr.forEach(type => {
            const funcName = Object.keys(type)[0];
            pw += randomFunc[funcName]();
        });
    }

    const final = pw.slice(0, length);
    return final;
}

/*
    Genertor Functions based on ascii values
*/
function getRandomLower() {
    return String.fromCharCode(Math.floor(Math.random() * 26) + 97);
}
function getRandomUpper() {
    return String.fromCharCode(Math.floor(Math.random() * 26) + 65);
}
function getRandomNumber() {
    return String.fromCharCode(Math.floor(Math.random() * 10) + 48);
}
function getRandomSymbol() {
    const symbols = '!@#$%^&*(){}[]=<>,./'
    return symbols[Math.floor(Math.random() * symbols.length)];
}