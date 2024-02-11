URL-interpreter = https://raw.githubusercontent.com/Mikhail57/cow-interpreter/master/interpreter.py
URL-teste-cow = https://raw.githubusercontent.com/Mikhail57/cow-interpreter/master/test.cow

INTERPRETER_FILE = interpreter.py
TEST_COW_FILE = test.cow

all: run

get-interpreter:
	@if [ ! -f $(INTERPRETER_FILE) ]; then \
		wget $(URL-interpreter) -O $(INTERPRETER_FILE); \
	fi

get-teste-cow:
	@if [ ! -f $(TEST_COW_FILE) ]; then \
		wget $(URL-teste-cow) -O $(TEST_COW_FILE); \
	fi

exec: get-interpreter get-teste-cow
	@clear && python3 $(INTERPRETER_FILE) $(TEST_COW_FILE)

run: exec

clean:
	@rm -f $(INTERPRETER_FILE) $(TEST_COW_FILE) && clear
