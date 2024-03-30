from typing import Set, List
from tinydb import TinyDB, Query

class State:
    def __init__(self, name: str, is_final: bool):
        self.name = name
        self.is_final = is_final
        self.transitions: List[Transition] = []

    def add_transition(self, transition: 'Transition') -> None:
        self.transitions.append(transition)
    
    @classmethod
    def from_json(self, json_data: dict) -> 'State':
        state = State(json_data['name'], json_data['is_final'])
        for transition in json_data['transitions']:
            state.add_transition(Transition(transition['input_symbol'], transition['stack_top'], transition['next_state'], transition['stack_replacement']))
        return state
    
    def to_json(self) -> dict:
        return {
            'name': self.name,
            'is_final': self.is_final,
            'transitions': [transition.to_json() for transition in self.transitions]
        }
    
    def __str__(self) -> str:
        return f"Nome: {self.name}, Final: {self.is_final}"

class Transition:
    def __init__(self, input_symbol: str, stack_top: str, next_state: str, stack_replacement: str):
        self.input_symbol = input_symbol
        self.stack_top = stack_top
        self.next_state = next_state
        self.stack_replacement = stack_replacement

    def to_json(self) -> dict:
        return {
            'input_symbol': self.input_symbol,
            'stack_top': self.stack_top,
            'next_state': self.next_state,
            'stack_replacement': self.stack_replacement
        }

    def __str__(self) -> str:
        return f"Caractere: {self.input_symbol}\n Topo da Pilha: {self.stack_top}\n Próximo Estado: {self.next_state}\n Substituição da Pilha: {self.stack_replacement}\n"

class DatabaseManager:
    def __init__(self):
        self.db = TinyDB('dataBase/pda_db.json')
        self.table = self.db.table('states')
        self.query = Query()


    def create_state(self, state: State) -> None:
        if not self.table.contains(self.query.name == state.name):
            self.table.insert(state.to_json())
        print(f"State {state.name} already exists in database.")

    def load_states(self) -> List[State]:
        states = []

        for state_data in self.table.all():
            states.append(State.from_json(state_data))

        return states
    
    def get_state(self, state_name: str) -> State:
        state = self.table.search(self.query.name == state_name)
        if state:
            return State.from_json(state[0])
        
        print(f"State {state_name} not found in database.")
        return None
    
    def update_state(self, state: State) -> None:
        if self.table.contains(self.query.name == state.name):
            self.table.update(state.to_json(), self.query.name == state.name)
        print(f"State {state.name} not found in database.")

    def delete_state(self, state_name: str) -> None:
        if self.table.contains(self.query.name == state_name):
            self.table.remove(self.query.name == state_name)
        print(f"State {state_name} has bean deleted.")

class Stack:
    def __init__(self, initial_symbol: str):
        self.items: List[str] = [initial_symbol]

    def push(self, symbol: str) -> None:
        self.items.append(symbol)

    def pop(self) -> str:
        if not self.is_empty():
            return self.items.pop()
        return ""

    def top(self) -> str:
        if not self.is_empty():
            return self.items[-1]
        return ""

    def is_empty(self) -> bool:
        return len(self.items) == 0
    
    def __str__(self) -> str:
        return str(self.items)

class PushdownAutomaton:
    def __init__(self, alphabet: Set[str], stack_alphabet: Set[str], initial_state: State, initial_stack_symbol: str):
        self.alphabet = alphabet
        self.stack_alphabet = stack_alphabet
        self.current_state = initial_state
        self.stack = Stack(initial_stack_symbol)
        self.db_manager = DatabaseManager()

    def transition(self, input_symbol: str) -> bool:
        current_transition = None
        for transition in self.current_state.transitions:
            if transition.input_symbol == input_symbol:
                current_transition = transition
                break

        if current_transition:
            print(f"Current state: {self.current_state.name} <- {input_symbol}")
            print(f"Stack: {self.stack}\n")
            self.current_state = self.db_manager.get_state(current_transition.next_state)
            
            self.stack.pop()
            if current_transition.stack_replacement:
                for symbol in current_transition.stack_replacement[::-1]:
                    self.stack.push(symbol)
            return True
        else:
            return False

    def is_accepted(self) -> bool:
        if self.current_state.is_final:
            print(f"Stack: {self.stack}")
            return self.stack.is_empty()
        return False

    def process_input(self, input_string: str) -> bool:
        for symbol in input_string:
            if symbol not in self.alphabet:
                print(f"Invalid input symbol: {symbol}")
                return False
            if not self.transition(symbol):
                print(f"No transition defined for current state: {self.current_state.name} and input symbol: {symbol}")
                return False
        return True

def main() -> None:
    db_manager = DatabaseManager()
    q0 = db_manager.get_state('q0')

    alphabet: Set[str] = {'0', '1'}
    stack_alphabet: Set[str] = {'A', 'B'}
    initial_state = q0
    initial_stack_symbol = 'A'

    pda = PushdownAutomaton(alphabet, stack_alphabet, initial_state, initial_stack_symbol)
    input_string = '001110'
    if pda.process_input(input_string):
        if pda.is_accepted():
            print(f"Input string '{input_string}' is accepted by the PDA.")
        else:
            print(f"Input string '{input_string}' is not accepted by the PDA.")