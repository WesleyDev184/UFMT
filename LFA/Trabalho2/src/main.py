import sys
import devMenuLex as MenuLex
import devMenuSint as MenuSint
import lexico as lexico 
import sintatico as sintatico

def main() -> None:
    if len(sys.argv) > 1 and sys.argv[1] == 'dev':
        print("1. Lexico")
        print("2. Sintatico")
        choise = input("escolha uma opção: ")
        if choise == '1':
            menu = MenuLex.DevMenu()
            menu.run()
        elif choise == '2':
            menu = MenuSint.PDAMenu()
            menu.run()
        else:
            print("Invalid option")
    else:
        lexico.main()
        sintatico.main()

if __name__ == "__main__":
    main()