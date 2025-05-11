int valor;
int teste();

int teste()
begin
    write "valor: ";
    write valor; 
    write "\n";
end

begin
    write "Digite um valor:\n";
    read valor;

    while (valor <= 10)
    begin
        write "print do while\n";
        teste();
        valor = valor + 1;
    end
    write "fim\n";
end