import json

class State:
    def __init__(self, name, is_final, token):
        self.name = name
        self.is_final = is_final
        self.token = token
        self.transitions = {}

    def add_transition(self, input_char, next_state):
        self.transitions[input_char] = next_state

    def get_next_state(self, input_char):
        return self.transitions.get(input_char, None)


class StateMachine:
    def __init__(self, states, initial_state):
        self.current_state = initial_state
        self.states = states

    def print_Machine(self):
        print("Máquina de estado:")
        for state in self.states.values():
            print("Estado:", state.name)
            print("  Final:", state.is_final)
            print("  Token:", state.token)
            for char, next_state in state.transitions.items():
                print("  ->", char, ":", next_state.name)

    def load_Machine(self, file_path):
        with open(file_path, 'r') as file:
            machine_data = json.load(file)
    
        states = {}
        for state_data in machine_data['states']:
            state = State(state_data['state'], state_data['is_final'], state_data['token'])
            states[state_data['state']] = state
    
        # Adicionando transições após todos os estados terem sido criados
        for state_data in machine_data['states']:
            state = states[state_data['state']]
            for transition in state_data['transitions']:
                state.add_transition(transition['input'], states[transition['next_state']])
    
        self.states = states
    
        # Definindo o estado inicial como o primeiro estado se 'initial_state' não estiver presente
        initial_state_name = machine_data.get('initial_state', machine_data['states'][0]['state'])
        self.current_state = states[initial_state_name]


    def process_input(self, input_string):
        for char in input_string:
            print(self.current_state.name, "<-", char)
            self.current_state = self.current_state.get_next_state(char)
            if self.current_state is None:
                return "Entrada inválida"
            print("Próximo estado:", self.current_state.name)

        if self.current_state.is_final:
            return self.current_state.token
        return "Entrada inválida"


def transform_input_from_file(file_path, replace_char):
    with open(file_path, 'r') as file:
        text = file.read()

    # se o arquivo estiver vazio retorna o caractere específico
    if not text:
        return replace_char

    # Substituir espaços e quebras de linha pelo caractere específico
    transformed_input = text.replace(' ', replace_char).replace('\n', replace_char)

    return transformed_input

def main():
    # Criando uma instância vazia de StateMachine
    machine = StateMachine({}, None)

    # Carregando a máquina de estado do arquivo JSON
    machine.load_Machine("states.json")

    # Imprimindo a máquina de estado carregada
    machine.print_Machine()
    print('\n')

    # Testando a máquina de estado carregada
    # input_str = transform_input_from_file("input.txt", '$')
    input_str = "abbaab"
    print("Entrada:", input_str)
    result = machine.process_input(input_str)
    print("Token:", result)

if __name__ == "__main__":
    main()
