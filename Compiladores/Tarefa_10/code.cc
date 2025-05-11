int valor;
float soma(float x, float y,);
int teste(int v,);
string frase(string fala,);

begin
    write "Informe um valor: ";
    read valor;

    while (valor > 0)
    begin
        write "valor: ";
        write valor;
        valor = (valor - 1);
    end
    
    teste(valor,);
end
