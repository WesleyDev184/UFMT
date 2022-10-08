/*Crie trˆes vari´aveis a, b e c adicionando valores diretamente. Em seguida, some a e b, divida este
valor por c e substitua o valor de c pelo resto de c e b. Imprima os trˆes números no console.*/

let a  = 2;
let b = 4;
let c = 6;

let soma = a+b;
let div = soma/c;
c = c%b; //Módulo

console.log("Soma: ", soma);
console.log("Divisão: ", div);
console.log("Resto de C e B", c);
