// Copyright [2023] <Rafael Correa Bitencourt e Pedro Augusto da Fontoura>

#include <iostream>
#include <fstream>
#include <cstdint>
#include <sstream>
#include <vector>
#include <cstddef>
#include "array_stack.h"
#include "leitor_xml.h"

int area_regiao(int x_robo, int y_robo, int largura_matriz, int altura_matriz, std::vector<std::vector<int>>& matriz);

std::vector<std::vector<int>> matriz_analise(const std::string& matriz_string, int largura, int altura) {
    
    std::istringstream xmlfile(matriz_string);
    std::string line = "";
    std::vector<std::vector<int>> matriz(altura, std::vector<int>(largura));
    std::getline(xmlfile, line);

    for (int i = 0; i < altura; i++) {
        
        std::getline(xmlfile, line);
        
        for (int j = 0; j < largura; j++) {
            
            char caracter = line[j];
            
            if (caracter == '0') {
                matriz[i][j] = 0;
            } else if (caracter == '1') {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = -1;
            }
        }
    }
    
    return matriz;

}


int main() {
    
    char xmlfilename[100];
    
    std::cin >> xmlfilename;
    std::ifstream xmlfile(xmlfilename);

    if (!xmlfile.is_open()) {
        return 1;
    }

    if (!xml_valido(xmlfile)) {
        std::cout << "erro" << std::endl;
        return 1;
    }

    xmlfile.clear();
    xmlfile.seekg(0);

    std::stringstream conteudo_xml;
    conteudo_xml << xmlfile.rdbuf();
    std::string xmlstring = conteudo_xml.str();
    
    structures::ArrayList<std::string> array = casos(xmlstring, 101);

    for (std::size_t i = 0; i < array.size(); i++) {
        
        std::string nome = conteudo(array[i], "nome");
        std::cout << nome;

        int largura = std::stoi(conteudo(array[i], "largura"));
        int altura = std::stoi(conteudo(array[i], "altura"));
        int x = std::stoi(conteudo(array[i], "x"));
        int y = std::stoi(conteudo(array[i], "y"));

        std::string matriz_string = conteudo(array[i], "matriz");
        std::vector<std::vector<int>> matriz = matriz_analise(matriz_string, largura, altura);

        int area = area_regiao(y, x, largura, altura, matriz);
        std::cout << " " << area << std::endl;
    }

    xmlfile.close();
    
    return 0;
    
}

int area_regiao(int x_robo, int y_robo, int largura_matriz, int altura_matriz, std::vector<std::vector<int>>& matriz) {
    
    int area = 0;
    
    if (y_robo < 0 || y_robo >= altura_matriz || x_robo < 0 || x_robo >= largura_matriz) {
        return -1;
    }
    
    int robot_value = matriz[y_robo][x_robo];
    
    if (robot_value == 0) {
        return 0;
    }

    structures::ArrayStack<std::pair<int, int>> stack(100000);
    
    stack.push(std::make_pair(y_robo, x_robo));

    while (stack.size() > 0) {
        
        std::pair<int, int> p = stack.pop();
        
        int y = p.first;
        int x = p.second;

        if (y < 0 || y >= altura_matriz || x < 0 || x >= largura_matriz) {
            continue;
        }

        int value = matriz[y][x];

        if (value != 1) {
            continue;
        }
        
        stack.push(std::make_pair(y - 1, x));
        stack.push(std::make_pair(y + 1, x)); 
        stack.push(std::make_pair(y, x - 1));
        stack.push(std::make_pair(y, x + 1));
        
        matriz[y][x] = 2;
        area++;
        
    }
    
    return area;
    
}