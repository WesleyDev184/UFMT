import sintatico as sint
import os

def clear_screen():
    os.system('clear')

class PDAMenu:
    def __init__(self):
        self.db_manager = sint.DatabaseManager()

    def print_menu(self):
        clear_screen()
        print("===== Menu de Desenvolvimento =====")
        print("1. Criar um novo estado")
        print("2. Listar todos os estados")
        print("3. Ler detalhes de um estado")
        print("4. Atualizar um estado existente")
        print("5. Deletar um estado existente")
        print("6. Sair")

    def create_state(self):
        clear_screen()
        name = input("Digite o nome do estado: ")
        is_final = input("O estado é final? (s/n): ").lower() == 's'
        state = sint.State(name, is_final)

        while True:
            add_transition = input("\nDeseja adicionar uma transição para este estado? (s/n): ").lower()
            if add_transition != 's':
                break

            input_symbol = input("\nDigite o símbolo de entrada: ")
            stack_top = input("Digite o topo da pilha: ")
            next_state = input("Digite o próximo estado: ")
            stack_replacement = input("Digite a substituição da pilha (ou 'null' para nenhum): ")

            if stack_replacement.lower() == 'null':
                stack_replacement = ""

            transiton = sint.Transition(input_symbol, stack_top, next_state, stack_replacement)
            state.add_transition(transiton)

        self.db_manager.create_state(state)

        while True:
            next_state = input("\nDeseja adicionar outro estado? (S/N): ").lower()
            if next_state == 's':
                self.create_state()
            else:
                break

    def load_states(self):
        states = self.db_manager.load_states()
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

    def display_state(self):
        clear_screen()
        name = input("Digite o nome do estado que deseja ver: ")
        state = self.db_manager.get_state(name)
        if state:
            print(state)
            print("\nTransições:\n")
            for transition in state.transitions:
                print(transition)
        
        while True:
            next_state = input("\nDeseja carregar um novo estado? (S/N): ").lower()
            if next_state == 's':
                self.display_state()
            else:
                break

    def update_state(self):
        clear_screen()
        name = input("Digite o nome do estado que deseja atualizar: ")
        state = self.db_manager.get_state(name)
        if state:
            print("\nEstado atual:", state)

            new_name = input("Digite o novo nome do estado: ")
            is_final = input("O estado é final? (s/n): ").lower()
            
            if new_name:
                state.name = new_name
            
            if is_final:
                state.is_final = is_final == 'S'

            while True:
                print("\nDeseja adicionar ou atualizar: ")
                print("1. Adicionar")
                print("2. Atualizar")

                choice = input("Escolha uma opção: ")

                if choice == '1':
                  input_symbol = input("Digite o símbolo de entrada: ")
                  stack_top = input("Digite o topo da pilha: ")
                  next_state = input("Digite o próximo estado: ")
                  stack_replacement = input("Digite a substituição da pilha (ou 'null' para nenhum):  ")

                  new_trasition = sint.Transition(input_symbol, stack_top, next_state, stack_replacement)
                  state.add_transition(new_trasition)

                elif choice == '2':
                  print("\nTransições:")
                  for i, transition in enumerate(state.transitions):
                      print(f"{i}.{transition}")

                  transition_index = int(input("Digite o índice da transição que deseja atualizar, ou pressione 'Enter' para sair:: "))

                  if not transition_index:
                      continue

                  if 0 <= transition_index < len(state.transitions):
                      input_symbol = input("Digite o símbolo de entrada: ")
                      stack_top = input("Digite o topo da pilha: ")
                      next_state = input("Digite o próximo estado: ")
                      stack_replacement = input("Digite a substituição da pilha (ou 'null' para nenhum):  ")

                      if input_symbol:
                          state.transitions[transition_index].input_symbol = input_symbol
                      if stack_top:
                          state.transitions[transition_index].stack_top = stack_top
                      if next_state:
                          state.transitions[transition_index].next_state = next_state
                      if stack_replacement:
                          if stack_replacement.lower() == 'null':
                              stack_replacement = ""
                          state.transitions[transition_index].stack_replacement = stack_replacement
                  else:
                      print("Índice inválido.")
                else:
                    break

        self.db_manager.update_state(state)

    def delete_state(self):
        clear_screen()
        name = input("Digite o nome do estado que deseja deletar: ")
        self.db_manager.delete_state(name)

        while True:
            next_state = input("\nDeseja deletar outro estado? (S/N): ").lower()
            if next_state == 's':
                self.delete_state()
            else:
                break

    def run(self):
        while True:
            self.print_menu()
            choice = input("Escolha uma opção: ")

            if choice == '1':
                self.create_state()
            elif choice == '2':
                self.load_states()
            elif choice == '3':
                self.display_state()
            elif choice == '4':
                self.update_state()
            elif choice == '5':
                self.delete_state()
            elif choice == '6':
                print("Saindo do programa.")
                break
            else:
                print("Opção inválida. Tente novamente.")
