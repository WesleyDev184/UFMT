int valor;
string name;
void teste(int v, string n);

void teste(int v, string n)
begin
    write "valor: ";
    write v; 
    write "nome: ";
    write n;
    write "\n";
end

begin
    write "Digite um valor:\n";
    read valor;

    name = "teste";

    while (valor <= 10)
    begin
        write "print do while\n";
        teste(valor, name);
        valor = valor + 1;
    end
    write "fim\n";
end