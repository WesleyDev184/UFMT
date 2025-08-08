from rpyc.utils import server
import rpyc

class DoStuff(rpyc.Service):
  def exposed_say_hello(self, pid):
    print(f"RPYC server in say_hello, pid = {pid}!")
    return f"Hello from {pid}!"
  
  def exposed_say_hello_again(self, pid):
    print(f"RPYC server in say_hello_again, pid = {pid}!")
    return f"Hello again from {pid}!"
  
if __name__ == "__main__":
  server.OneShotServer(DoStuff, hostname="localhost", port=8888).start()