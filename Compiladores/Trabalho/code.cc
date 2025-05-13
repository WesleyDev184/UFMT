int valor;
void teste(int v);

void teste(int v)
begin
    write "valor: ";
    write v; 
    write "\n";
end

begin
    write "Digite um valor:\n";
    read valor;

    while (valor <= 10)
    begin
        write "print do while\n";
        teste(valor);
        valor = valor + 1;
    end
    write "fim\n";
end