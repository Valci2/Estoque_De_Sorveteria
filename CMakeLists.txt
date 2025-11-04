# Diz qual é a versão mínima do CMake necessária para processar esse arquivo
cmake_minimum_required(VERSION 3.20)

# Define o nome do projeto
project(Estoque)

# Define a versão do C++ que o compilador deve usar, neste caso, o C++20
set(CMAKE_CXX_STANDARD 20)

# Adiciona o diretório include/ como caminho para os arquivos de cabeçalho (.hpp)
include_directories(inc)

# Agrupa todos os arquivos automaticamente
file(GLOB_RECURSE SOURCES
	src/main.cpp
		src/negocios/Adm.cpp
		src/negocios/Loja.cpp
		src/negocios/Estoque.cpp
		src/negocios/Produto.cpp
		src/negocios/Cliente.cpp
		src/negocios/User.cpp
		src/interfaces/UIadm.cpp
		src/interfaces/UIcliente.cpp
		src/interfaces/UIloja.cpp
		src/interfaces/UIestoque.cpp
)

# Cria o executável do seu programa, chamado Estoque
add_executable(Estoque ${SOURCES})
