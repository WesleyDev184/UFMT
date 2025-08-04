import os
import rpyc

def rpyc_call():
  conn = rpyc.connect("localhost", 8888)
  pid = os.getpid()
  
  myval = conn.root.say_hello(pid)
  print(f"RPYC client received: {myval}")

  myval = conn.root.say_hello_again(pid)
  print(f"RPYC client received: {myval}")

  conn.close()

if __name__ == "__main__":
  rpyc_call()
  print("RPYC client done.")