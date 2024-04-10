// Copyright [2023] <Rafael Correa Bitencourt e Pedro Augusto da Fontoura>
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
class LinkedStack {
public:
    LinkedStack();  // Construtor simples
    ~LinkedStack();  // Destrutor

    void clear();  // Limpa pilha
    void push(const T& data);  // Empilha
    T pop();  // Desempilha

    T& top() const;  // Dado no topo
    bool empty() const;  // Pilha vazia
    std::size_t size() const; // Tamanho da pilha

private:
    class Node {
    public:
		explicit Node(const T& data):
            data_{data}
        {}
		Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // Getter: dado
            return data_;
        }
		const T& data() const {  // Getter-constante: info
            return data_;
        }

		Node* next() {  // Getter: próximo
            return next_;
        }
		const Node* next() const {  // Getter-constante: próximo
            return next_;
        }

        void next(Node* node) {  // Setter: próximo
            next_ = node;
        }

    private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_; // nodo-topo
    std::size_t size_; // tamanho
};

}  // namespace structures

#endif

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
	top_ = nullptr;
	size_ = 0;
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
	clear();
}

template<typename T>
void structures::LinkedStack<T>::clear() {
	while (!empty()) {
		pop();
	}
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
	Node *novo = new Node(data, top_);
	
	if (novo == nullptr) {
		throw std::out_of_range("Pilha cheia");
	} else {
		top_ = novo;
		size_++;
	}
}

template<typename T>
T structures::LinkedStack<T>::pop() {
	if (empty()) {
		throw std::out_of_range("Pilha vazia");
	} else {
		Node *saiu = top_;
		T volta = saiu->data();
		top_ = saiu->next();
		size_--;
		delete saiu;
		return volta;
	}
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
	if (empty()) {
		throw std::out_of_range("Pilha vazia");
	} else {
		return top_->data();
	}
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
	return size_ == 0;
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
	return size_;
}
