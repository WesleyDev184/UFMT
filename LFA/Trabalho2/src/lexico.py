from typing import Dict, List, Optional
from tinydb import TinyDB, Query

REPLACE_CHAR: str = '$'
DB_FILE: str = 'dataBase/states_db.json'

class State:
    def __init__(self, name: str, is_final: bool, token: str) -> None:
        self.state_crud = StateCRUD()
        self.name: str = name
        self.is_final: bool = is_final
        self.token: str = token
        self.transitions: Dict[str, str] = {}

    def add_transition(self, input_char: str, next_state: str) -> None:
            self.transitions[input_char] = next_state

    def get_next_state(self, input_char: str) -> Optional['State']:
        next = self.transitions.get(input_char, None)
        next_state = self.state_crud.read(next)
        if next_state:
            return next_state
        return None

    def to_json(self):
        if self.transitions:
            transitions_json = [{"input": char, "next_state": state} for char, state in self.transitions.items()]
        else:
            transitions_json = []

        return {
            "state": self.name,
            "is_final": self.is_final,
            "token": self.token,
            "transitions": transitions_json
        }

    @classmethod
    def from_json(cls, json_data) -> 'State':
        state = cls(json_data['state'], json_data['is_final'], json_data['token'])
        for transition in json_data['transitions']:
            state.transitions[transition['input']] = transition['next_state']
        return state
    
    def __str__(self) -> str:
        return f"State: {self.name}, Final: {self.is_final}, Token: {self.token}"

class StateCRUD:
    StateQuery = Query()  # Definindo a variável de classe StateQuery

    def __init__(self):
        self.db = TinyDB(DB_FILE)
        self.table = self.db.table('states')

    def create(self, state: State):
        if self.table.contains(self.StateQuery.state == state.name):
            print("State already exists")
            return
        self.table.insert(state.to_json())

    def read_all(self) -> List[State]:
        states = [State.from_json(state) for state in self.table.all()]

        def custom_sort_key(state):
            # Remover o prefixo 'q' do nome do estado
            state_name = state.name.lstrip('q')
            # Ordenar números primeiro e depois letras
            if state_name.isdigit():
                return (0, int(state_name))
            else:
                return (1, state_name)

        sorted_states = sorted(states, key=custom_sort_key)
        return sorted_states

    def read(self, state_name: str) -> Optional[State]:
        result = self.table.get(self.StateQuery.state == state_name)
        if result:
            return State.from_json(result)
        return None

    def update(self, state: State):
        self.table.update(state.to_json(), self.StateQuery.state == state.name)

    def delete(self, state_name: str):
        print("\nTem certeza que deseja excluir o estado?")
        choice = input("Pode da merda não temos tratamento de erro nas transições (S/N): ").upper()
        if choice == 'S':
            self.table.remove(self.StateQuery.state == state_name)
        else:
            return

class StateMachine: 
    def __init__(self, initial_state: State) -> None:
        self.current_state: State = initial_state
        self.tokens: List[str] = []
        self.state_crud = StateCRUD()

    def load_Machine(self, state: str) -> None:
        current_state = self.state_crud.read(state)
        self.current_state = current_state

    # Criar o arquvo de saida com os tokens obitidos
    def exit_file(self, file_path):
        # Verifica se o arquivo já contém algum conteúdo
        try:
            with open(file_path, 'r') as file:
                if file.read().strip():
                    # Se o arquivo não estiver vazio, apaga seu conteúdo
                    open(file_path, 'w').close()
        except FileNotFoundError:
            # Se o arquivo não existir, não é necessário fazer nada
            pass

        # Escreve os tokens no arquivo
        with open(file_path, 'a') as file:
            for token in self.tokens:
                file.write(token + ' ')

    def process_input(self, input_string: str) -> List[str]:
        for char in input_string:
            print(self.current_state.name, "<-", char)
            if char == REPLACE_CHAR:
                if self.current_state.is_final and self.current_state.token != "null":
                    self.tokens.append(self.current_state.token)

            next_state = self.current_state.get_next_state(char)

            if next_state is None:
                print("entrada inválida\n")
                self.current_state = self.state_crud.read('qe')
                continue

            self.current_state = next_state
            print("Próximo estado:", self.current_state.name)

        if self.current_state.is_final:
            if self.current_state.token != "null":
                self.tokens.append(self.current_state.token)
            print("\nFinal da entrada\n")
        else:
            print("entrada inválida\n")
            self.tokens.append("-1")

        return self.tokens    

def transform_input_from_file(file_path: str, replace_char: str) -> str:
    with open(file_path, 'r') as file:
        text: str = file.read()

    if not text:
        return replace_char

    transformed_input: str = text.replace(' ', replace_char).replace('\n', replace_char)

    return transformed_input

def main() -> None:
    machine = StateMachine(None)
    machine.load_Machine('q0') 

    transformed_input = transform_input_from_file('input.txt', REPLACE_CHAR)
    print("Entrada:", transformed_input)
    result = machine.process_input(transformed_input)
    print("Resultado:", result)
    machine.exit_file('output.txt')