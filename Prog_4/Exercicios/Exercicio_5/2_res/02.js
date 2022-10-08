/*Crie um array contendo trˆes valores. Crie um segundo array de três posi¸c˜oes e adicione em cada
posi¸c˜ao o primeiro array criado. Mostre no console, para cada array interno, a posi¸c˜ao correspondente do array externo.*/

let v1 = [1, 2, 3];

let v2 = [4, 5, 6];

let v3 = [7, 8, 9];

let v4  = [v1, v2, v3]; //EXTERNO

for (let i = 0; i < v4.length; i++) {
    console.log(v4[i]);
    
}
