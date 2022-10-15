// 1. Defina uma função chamada mensagem que exiba a mensagem ’Olá’ e em seguida retorne uma
// segunda função que exiba na tela a mensagem ’Tudo bem?’. Garanta que uma variável a receba
// a função e mostre a mensagem ’Tudo bem?’ a partir de a. Realize uma invocação da função
// mensagem de maneira que ela mostre as duas mensagens que estão dentro dela.

let menssage = () =>{
    alert('OLA')
    return function () {
        alert('Tudo Bem?');
    };
}

const a = mensagem(); //Printa alert
a(); //Executa retorno
mensagem()(); 