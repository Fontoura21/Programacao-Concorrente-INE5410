from time import sleep
from random import randint
from threading import Thread, Lock, Condition

def produtor():
  global buffer
  for i in range(10):
    sleep(randint(0,2))           # fica um tempo produzindo...
    item = 'item ' + str(i)
    lock.acquire()
    if len(buffer) == tam_buffer:
      print('>>> Buffer cheio. Produtor ira aguardar.')
      lugar_no_buffer.wait()    # aguarda que haja lugar no buffer
    buffer.append(item)
    print('Produzido %s (ha %i itens no buffer)' % (item,len(buffer)))
    item_no_buffer.notify()
    lock.release()

def consumidor():
  global buffer
  for i in range(10):
    lock.acquire()
    if len(buffer) == 0:
      print('>>> Buffer vazio. Consumidor ira aguardar.')
      item_no_buffer.wait()   # aguarda que haja um item para consumir 
    item = buffer.pop(0)
    print('Consumido %s (ha %i itens no buffer)' % (item,len(buffer)))
    lugar_no_buffer.notify()
    lock.release()
    sleep(randint(0,2))         # fica um tempo consumindo...

buffer = []
tam_buffer = 5
lock = Lock()
lugar_no_buffer = Condition(lock)
item_no_buffer = Condition(lock)
produtor_0 = Thread(target=produtor)
produtor_1 = Thread(target=produtor) 
consumidor_1 = Thread(target=consumidor)
consumidor_2 = Thread(target=consumidor)
produtor_0.start()
produtor_1.start()
consumidor_1.start()
consumidor_2.start()
produtor_0.join()
produtor_1.join()
consumidor_1.join()
consumidor_2.join() 