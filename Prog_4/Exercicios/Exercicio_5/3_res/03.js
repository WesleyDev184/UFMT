/*Crie um array contendo os valores Pedra, Papel e Tesoura. Pe¸ca ao usu´ario via prompt para
informar o item escolhido. Mostre via console o resultado do jogo. Exemplo: Papel venceu
Pedra.*/

let jqp = ["pedra", "papel", "tesoura"];

let res = jqp[Math.floor(Math.random() * 3)];

let user = window.prompt("Informe pedra, papel ou tesoura: ");
window.alert(res);

//Caso usuario informe pedra
if(user == "pedra" && res == "tesoura"){
    console.log("Você ganhou!");
}
else if(user == "pedra" && res == "papel"){
    console.log("Você perdeu!");
}
else if(user == "pedra" && res == "pedra"){
    console.log("Empate!");
}

//Caso usuario informe papel
if(user == "papel" && res == "tesoura"){
    console.log("Você perdeu!");
}
else if(user == "papel" && res == "papel"){
    console.log("Empate!");
}
else if(user == "papel" && res == "pedra"){
    console.log("Você ganhou!");
}

//Caso usuario informe tesoura
if(user == "tesoura" && res == "tesoura"){
    console.log("Empate!");
}
else if(user == "tesoura" && res == "papel"){
    console.log("Você ganhou!");
}
else if(user == "tesoura" && res == "pedra"){
    console.log("Você perdeu!");
}


