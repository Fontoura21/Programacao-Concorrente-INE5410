from time import sleep
from random import randint
from threading import Thread, Semaphore

def produtor():
  global buffer
  for i in range(10):
    sleep(randint(0,2))           # fica um tempo produzindo...
    item = 'item ' + str(i)
    espaco_livre.acquire()
    mutex.acquire()
    buffer.append(item)
    print('Produzido %s (ha %i itens no buffer)' % (item,len(buffer)))
    mutex.release()
    disponiveis.release()

def consumidor():
  global buffer
  for i in range(10):
    disponiveis.acquire()
    mutex.acquire()
    item = buffer.pop(0)
    print('Consumido %s (ha %i itens no buffer)' % (item,len(buffer)))
    mutex.release()
    espaco_livre.release()
    sleep(randint(0,2))         # fica um tempo consumindo...

buffer = []
tam_buffer = 3
espaco_livre = Semaphore(tam_buffer)
disponiveis = Semaphore(0)
mutex = Semaphore(1)
produtor = Thread(target=produtor) 
consumidor = Thread(target=consumidor) 
produtor.start()
consumidor.start()
produtor.join()
consumidor.join() 