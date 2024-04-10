// Copyright [2023] <Rafael Correa Bitencourt e Pedro Augusto da Fontoura>

#ifndef LEITOR_XML_H
#define LEITOR_XML_H

#include <iostream>
#include <fstream>
#include <cstdint>
#include <sstream>
#include "linked_stack.h"
#include "array_list.h"

bool xml_valido(std::ifstream &arquivo_xml);

std::string conteudo(const std::string &xml_string, const std::string &tag);

structures::ArrayList<std::string> casos(const std::string &xml_string, std::size_t list_size);

#endif

bool xml_valido(std::ifstream &arquivo_xml) {
    
    std::stringstream conteudo_xml;
    conteudo_xml << arquivo_xml.rdbuf();
    std::string xmlstring = conteudo_xml.str();
    structures::LinkedStack<std::string> stack{}; 
    
    for (std::size_t i = 0; i < xmlstring.size(); i++) {

        bool tag_fechamento = false;

        if (xmlstring[i] == '<') {
            i++;
            
            if (xmlstring[i] == '/') {
                tag_fechamento = true;
                i++;
            }

            std::string nome_tag = "";
            
            while (xmlstring[i] != '>') {
                
                char caracter = xmlstring[i];
                
                if (caracter == '\0') {
                    return false;                   
                }
                
                if (caracter != ' ' && caracter != '\n') {
                    nome_tag += caracter;
                }
                
                i++;
            }
            
            if (!tag_fechamento) {
                stack.push(nome_tag);
                
            } else {
                
                if (stack.empty()) {
                    return false;
                }
                
                if (nome_tag == stack.top()) {
                    stack.pop();
                    
                } else {
                    return false;
                }
            }
            
        } else if (xmlstring[i] == '>') {
            return false;
        }
    }

    if (stack.empty()) {
        return true;
        
    } else {
        return false;
    }

}

std::string conteudo(const std::string &xml_string, const std::string &tag) {
    
    std::string tag_abertura = "<" + tag + ">";
    std::string tag_fechamento = "</" + tag + ">";
    
    std::size_t tag_abertura_inicio = xml_string.find(tag_abertura);
    std::size_t tag_abertura_fim = tag_abertura_inicio + tag_abertura.size() - 1;
    std::size_t tag_fechamento_inicio = xml_string.find(tag_fechamento, tag_abertura_fim);

    std::string conteudo = xml_string.substr(tag_abertura_fim + 1, tag_fechamento_inicio - tag_abertura_fim - 1);

    return conteudo;
}

structures::ArrayList<std::string> casos(const std::string &xml_string, std::size_t list_size) {
    
    structures::ArrayList<std::string> casos{list_size};

    std::istringstream arquivo_xml(xml_string);
    std::string linha = "";
    
    int numero_linha = 0;

    bool tag_aberta = false;
    std::string conteudo_caso = "";

    while(std::getline(arquivo_xml, linha)) {
        numero_linha++;

        for (size_t i = 0; i < linha.size(); i++) {
            
            if (linha[i] == '<') {
                
                size_t comeco_tag = i;
                size_t fim_tag = linha.find('>', comeco_tag); 

                std::string tag_atual = linha.substr(comeco_tag, fim_tag - comeco_tag + 1);

                if (tag_atual == "<cenario>") {
                    
                    tag_aberta = true;
                    i = fim_tag + 1;
                    
                } else if (tag_atual == "</cenario>") {
                    
                    tag_aberta = false;
                    casos.push_back(conteudo_caso);
                    conteudo_caso = "";
                    
                }
            }
            
            if (tag_aberta) {
                conteudo_caso += linha[i];
            }
        }

        if (tag_aberta) {
            conteudo_caso += '\n';
        }
    }

    return casos;
}
