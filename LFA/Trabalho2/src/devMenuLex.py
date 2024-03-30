import os
import lexico as lexico

def clear_screen():
    os.system('clear')

class DevMenu:
    def __init__(self):
        self.state_crud = lexico.StateCRUD()

    def display_menu(self):
        clear_screen()
        print("===== Menu de Desenvolvimento =====")
        print("1. Listar todos os estados")
        print("2. Criar um novo estado")
        print("3. Ler detalhes de um estado")
        print("4. Atualizar um estado existente")
        print("5. Deletar um estado existente")
        print("6. Sair")

    def list_states(self):
        states = self.state_crud.read_all()
        num_states = len(states)
        page_size = 5
        num_pages = (num_states + page_size - 1) // page_size

        current_page = 1
        while True:
            clear_screen()
            print(f"=== Página {current_page}/{num_pages} ===")
            start_index = (current_page - 1) * page_size
            end_index = min(start_index + page_size, num_states)
            if start_index >= end_index:
                print("Nenhum estado nesta página.")
                break
              
            for state in states[start_index:end_index]:
                print(state)

            if current_page < (num_pages+1):
                next_page = input("Pressione 'Enter' ou o numero da pagina para avançar, ou digite 'q' para sair: ")
                if next_page.lower() == 'q':
                    break
                
                if next_page.isdigit() and 1 <= int(next_page) <= num_pages:
                    current_page = int(next_page)
                else:
                  current_page += 1
            else:
                break

    def create_state(self):
        clear_screen()
        name = input("Digite o nome do novo estado: ")
        is_final = input("O estado é final? (S/N): ").upper() == 'S'
        token = input("Digite o token do estado (ou 'null' para nenhum): ")
        new_state = lexico.State(name=name, is_final=is_final, token=token)
        self.state_crud.create(new_state)

        while True:
            newtransitions = input("Deseja adicionar transições para o estado? (S/N): ").upper()
            if newtransitions == 'S':
                char = input("Digite o caractere de transição: ")
                next_state = input("Digite o próximo estado: ")
                new_state.add_transition(char, next_state)
                self.state_crud.update(new_state)
            else:
                break

        print("Estado criado com sucesso.")

    def read_state(self):
        clear_screen()
        state_name = input("Digite o nome do estado: ")
        state = self.state_crud.read(state_name)
        if state:
            print("\nDetalhes do Estado:")
            print(state)
            print("\nTransições:")
            items = state.transitions.items()
            for key, value in items:
              print(f"Caractere: {key}, Próximo Estado: {value}")
        else:
            print("Estado não encontrado.")

        while True:
            next_state = input("\nDeseja carregar um novo estado? (S/N): ").lower()
            if next_state == 's':
                self.read_state()
            else:
                break

    def update_state(self):
        clear_screen()
        state_name = input("Digite o nome do estado que deseja atualizar: ")
        state = self.state_crud.read(state_name)
        if state:
            print("\nEstado atual:", state)
            
            new_name = input("\nDigite o novo nome do estado, ou pressione 'Enter' para manter o mesmo: ")
            new_is_final = input("O estado é final? (S/N): ").upper()
            new_token = input("Digite o novo token do estado, ou pressione 'Enter' para manter o mesmo: ")

            if new_name:
                state.name = new_name
            
            if new_is_final:
                state.is_final = new_is_final == 'S'
            
            if new_token:
                state.token = new_token

            while True:
                newtransitions = input("\nDeseja adicionar ou atualizar transições para o estado? (S/N): ").upper()
                if newtransitions == 'S':
                    

                    choice = input("Escolha uma opção: ")

                    if choice == '1':
                        char = input("Digite o caractere de transição: ")
                        next_state = input("Digite o próximo estado: ")
                        existState = self.state_crud.read(next_state)
                        if existState != None:
                            state.add_transition(char, next_state)
                        else:
                            print("Estado invalido.")
                            continue

                    elif choice == '2':
                        print("Transições atuais:\n")
                        items = state.transitions.items()
                        for key, value in items:
                            print(f"Caractere: {key}, Próximo Estado: {value}")

                        index = input("\nDigite o caracter da transição que deseja atualizar, ou pressione 'Enter' para sair: ")

                        if not index:
                            continue

                        char = input("\nDigite o novo caractere da transição, ou pressione 'Enter' para manter o mesmo : ")
                        next_state = input("Digite o próximo estado, ou pressione 'Enter' para manter o mesmo: ")

                        existState = self.state_crud.read(next_state)
                        
                        if index in state.transitions:
                            
                            if char:
                                if existState != None:
                                    state.transitions[index] = next_state
                                statOfindex = state.transitions[index]
                                state.transitions.pop(index)
                                state.add_transition(char, statOfindex)

                            elif existState != None:
                                state.transitions[index] = next_state 
                            else:
                                print("\nTransição não encontrada ou estado invalido.")  
                                continue
                        else:
                            print("\nTransição não encontrada.")
                            continue
                    else:
                        break
                else:
                    break

            self.state_crud.update(state)
        else:
            print("Estado não encontrado.")

        while True:
            next_state = input("\nDeseja atualizar outro estado? (S/N): ").upper()
            if next_state == 'S':
                self.update_state()
            else:
                break

    def delete_state(self):
        clear_screen()
        state_name = input("Digite o nome do estado que deseja deletar: ")
        self.state_crud.delete(state_name)

        while True:
            next_state = input("\nDeseja remover outro estado? (S/N): ").upper()
            if next_state == 'S':
                self.delete_state()
            else:
                break

    def run(self):
        while True:
            self.display_menu()
            choice = input("Escolha uma opção: ")
            if choice == '1':
                self.list_states()
            elif choice == '2':
                self.create_state()
            elif choice == '3':
                self.read_state()
            elif choice == '4':
                self.update_state()
            elif choice == '5':
                self.delete_state()
            elif choice == '6':
                print("Saindo do menu de desenvolvimento.")
                break
            else:
                print("Opção inválida. Tente novamente.")