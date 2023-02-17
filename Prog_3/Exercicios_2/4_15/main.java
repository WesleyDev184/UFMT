// A) O problema com esse código é que há um ponto e vírgula após a condição do if o certo seria 

if (age >= 65) {
    System.out.println("Age is greater than or equal to 65");
} else {
    System.out.println("Age is less than 65");
}

// B) problema com este código, e que a variável "total" não foi inicializada com um valor inicial o certo seria 
int x = 1;
int total = 0; // inicializar a variável "total" com 0

while (x <= 10) {
 total += x;
 ++x;
}

// C) o erro seria a falta da declaração das varia vereáveis e a abertura da chave para exceção do código o certo seria

int x = 1;
int total = 0;

while (x <= 100) {
 total += x;
 ++x;
}

// D) o erro seria a falta da declaração das varia veriaveis e a falta do fechamento da chave para a execução do codigo o certo seria

int y = 1;

while (y > 0){
 System.out.println(y);
 ++y;
}