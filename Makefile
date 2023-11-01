CC=g++
CCX=gcc
CFLAGS=-std=c++11 -Wall
TARGET_MAIN=main
TARGET_TESTS=testes

TEST_BUILD_DIR = ./build_tests
BUILD_DIR = ./build
SRC_DIR = ./src
INCLUDE_DIR = ./include
TESTS_DIR = ./tests
OBJECTS_DIR = objects
LIB_DIR = ./lib

OSFLAG 				:=
ifeq ($(OS),Windows_NT)
	
else
	OSFLAG = -ldl -lpthread
endif

# Project - main
OBJ = $(addprefix $(BUILD_DIR)/,$(notdir $(SRC:.cpp=.o)))

# Compiling and linking
make:
	make sqlite3 project

sqlite3:
	${CCX} -c ${LIB_DIR}/sqlite3.c -o ${BUILD_DIR}/sqlite3.o

project: ${BUILD_DIR}/${TARGET_MAIN}

${BUILD_DIR}/${TARGET_MAIN}: ${BUILD_DIR}/Usuario.o ${BUILD_DIR}/Autenticacao.o ${BUILD_DIR}/Vendedor.o ${BUILD_DIR}/Comprador.o ${BUILD_DIR}/Produto.o ${BUILD_DIR}/Transacao.o ${BUILD_DIR}/main.o ${BUILD_DIR}/ServicoUsuario.o ${BUILD_DIR}/ServicoComprador.o ${BUILD_DIR}/ServicoVendedor.o ${BUILD_DIR}/ServicoEstoque.o ${BUILD_DIR}/ServicoProduto.o ${BUILD_DIR}/ServicoTransacoes.o
	${CC} ${CFLAGS} -lgcov --coverage ${BUILD_DIR}/*.o -o ${TARGET_MAIN}  $(OSFLAG)

# OBJECTS

${BUILD_DIR}/Usuario.o: ${INCLUDE_DIR}/objects/Usuario.hpp ${SRC_DIR}/${OBJECTS_DIR}/Usuario.cpp ${INCLUDE_DIR}/services/ServicoUsuario.hpp
	${CC} ${CFLAGS} --coverage -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -c ${SRC_DIR}/${OBJECTS_DIR}/Usuario.cpp -o ${BUILD_DIR}/Usuario.o

${BUILD_DIR}/Vendedor.o: ${INCLUDE_DIR}/objects/Vendedor.hpp ${SRC_DIR}/${OBJECTS_DIR}/Vendedor.cpp ${INCLUDE_DIR}/services/ServicoVendedor.hpp
	${CC} ${CFLAGS} --coverage -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -c ${SRC_DIR}/${OBJECTS_DIR}/Vendedor.cpp -o ${BUILD_DIR}/Vendedor.o

${BUILD_DIR}/Comprador.o: ${INCLUDE_DIR}/objects/Comprador.hpp ${SRC_DIR}/${OBJECTS_DIR}/Comprador.cpp ${INCLUDE_DIR}/services/ServicoComprador.hpp
	${CC} ${CFLAGS} --coverage -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -c ${SRC_DIR}/${OBJECTS_DIR}/Comprador.cpp -o ${BUILD_DIR}/Comprador.o

${BUILD_DIR}/Produto.o: ${INCLUDE_DIR}/objects/Produto.hpp ${SRC_DIR}/${OBJECTS_DIR}/Produto.cpp ${INCLUDE_DIR}/services/ServicoProduto.hpp
	${CC} ${CFLAGS} --coverage -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -c ${SRC_DIR}/${OBJECTS_DIR}/Produto.cpp -o ${BUILD_DIR}/Produto.o

${BUILD_DIR}/Autenticacao.o: ${INCLUDE_DIR}/objects/Autenticacao.hpp ${SRC_DIR}/${OBJECTS_DIR}/Autenticacao.cpp
	${CC} ${CFLAGS} --coverage -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -c ${SRC_DIR}/${OBJECTS_DIR}/Autenticacao.cpp -o ${BUILD_DIR}/Autenticacao.o

${BUILD_DIR}/Transacao.o: ${INCLUDE_DIR}/objects/Transacao.hpp ${SRC_DIR}/${OBJECTS_DIR}/Transacao.cpp
	${CC} ${CFLAGS} --coverage -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -c ${SRC_DIR}/${OBJECTS_DIR}/Transacao.cpp -o ${BUILD_DIR}/Transacao.o

# SERVICES
${BUILD_DIR}/ServicoUsuario.o: ${INCLUDE_DIR}/services/ServicoUsuario.hpp ${INCLUDE_DIR}/services/ServicoComprador.hpp ${INCLUDE_DIR}/services/ServicoVendedor.hpp  ${SRC_DIR}/services/ServicoUsuario.cpp
	${CC} ${CFLAGS} --coverage -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -c ${SRC_DIR}/services/ServicoUsuario.cpp -o ${BUILD_DIR}/ServicoUsuario.o

 ${BUILD_DIR}/ServicoComprador.o: ${INCLUDE_DIR}/services/ServicoComprador.hpp ${SRC_DIR}/services/ServicoComprador.cpp
	${CC} ${CFLAGS} --coverage -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -c ${SRC_DIR}/services/ServicoComprador.cpp -o ${BUILD_DIR}/ServicoComprador.o 

${BUILD_DIR}/ServicoVendedor.o: ${INCLUDE_DIR}/services/ServicoVendedor.hpp ${SRC_DIR}/services/ServicoVendedor.cpp
	${CC} ${CFLAGS} --coverage -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -c ${SRC_DIR}/services/ServicoVendedor.cpp -o ${BUILD_DIR}/ServicoVendedor.o 

${BUILD_DIR}/ServicoEstoque.o: ${INCLUDE_DIR}/services/ServicoEstoque.hpp ${SRC_DIR}/services/ServicoEstoque.cpp
	${CC} ${CFLAGS} --coverage -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -c ${SRC_DIR}/services/ServicoEstoque.cpp -o ${BUILD_DIR}/ServicoEstoque.o 

${BUILD_DIR}/ServicoProduto.o: ${INCLUDE_DIR}/services/ServicoProduto.hpp ${SRC_DIR}/services/ServicoProduto.cpp
	${CC} ${CFLAGS} --coverage -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -c ${SRC_DIR}/services/ServicoProduto.cpp -o ${BUILD_DIR}/ServicoProduto.o 

${BUILD_DIR}/ServicoTransacoes.o: ${INCLUDE_DIR}/services/ServicoTransacoes.hpp ${SRC_DIR}/services/ServicoTransacoes.cpp
	${CC} ${CFLAGS} --coverage -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -c ${SRC_DIR}/services/ServicoTransacoes.cpp -o ${BUILD_DIR}/ServicoTransacoes.o 
	
# MAIN
${BUILD_DIR}/main.o: ${INCLUDE_DIR}/objects/Usuario.hpp ${SRC_DIR}/main.cpp ${SRC_DIR}/menu.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -g -c ${SRC_DIR}/main.cpp -o ${BUILD_DIR}/main.o 

run:
	./$(TARGET_MAIN)

# Tests
tests: ${TEST_BUILD_DIR}/${TARGET_TESTS}

${TEST_BUILD_DIR}/${TARGET_TESTS}: ${TEST_BUILD_DIR}/TesteUsuario.o ${TEST_BUILD_DIR}/TesteVendedor.o ${TEST_BUILD_DIR}/TesteComprador.o ${TEST_BUILD_DIR}/TesteProduto.o ${TEST_BUILD_DIR}/TesteAutenticacao.o ${TEST_BUILD_DIR}/TesteTransacao.o ${TEST_BUILD_DIR}/TesteServicoUsuario.o ${TEST_BUILD_DIR}/TesteServicoComprador.o ${TEST_BUILD_DIR}/TesteServicoVendedor.o ${TEST_BUILD_DIR}/TesteServicoProduto.o ${TEST_BUILD_DIR}/TesteServicoEstoque.o ${TEST_BUILD_DIR}/TesteServicoTransacoes.o
	${CC} ${CFLAGS} -lgcov --coverage ${BUILD_DIR}/Usuario.o  ${BUILD_DIR}/ServicoUsuario.o ${BUILD_DIR}/Autenticacao.o  ${BUILD_DIR}/Comprador.o ${BUILD_DIR}/Produto.o  ${BUILD_DIR}/ServicoComprador.o ${BUILD_DIR}/ServicoEstoque.o ${BUILD_DIR}/ServicoProduto.o ${BUILD_DIR}/ServicoTransacoes.o ${BUILD_DIR}/ServicoVendedor.o ${BUILD_DIR}/sqlite3.o ${BUILD_DIR}/Transacao.o ${BUILD_DIR}/Vendedor.o ${TEST_BUILD_DIR}/*.o -o ${TARGET_TESTS}  $(OSFLAG)

${TEST_BUILD_DIR}/TesteUsuario.o: ${TESTS_DIR}/objects/TesteUsuario.cpp  ${INCLUDE_DIR}/objects/Usuario.hpp
	g++ ${CFLAGS} -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -I ./build  -c ./tests/objects/TesteUsuario.cpp -o ${TEST_BUILD_DIR}/TesteUsuario.o

${TEST_BUILD_DIR}/TesteVendedor.o: ${TESTS_DIR}/objects/TesteVendedor.cpp  ${INCLUDE_DIR}/objects/Usuario.hpp
	g++ ${CFLAGS} -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -I ./build  -c ./tests/objects/TesteVendedor.cpp -o ${TEST_BUILD_DIR}/TesteVendedor.o

${TEST_BUILD_DIR}/TesteComprador.o: ${TESTS_DIR}/objects/TesteComprador.cpp  ${INCLUDE_DIR}/objects/Usuario.hpp
	g++ ${CFLAGS}  -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -I ./build -c ./tests/objects/TesteComprador.cpp -o ${TEST_BUILD_DIR}/TesteComprador.o

${TEST_BUILD_DIR}/TesteTransacao.o: ${TESTS_DIR}/objects/TesteTransacao.cpp  
	g++ ${CFLAGS}  -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -I ./build -c ./tests/objects/TesteTransacao.cpp -o ${TEST_BUILD_DIR}/TesteTransacao.o

${TEST_BUILD_DIR}/TesteProduto.o: ${TESTS_DIR}/objects/TesteProduto.cpp
	g++ ${CFLAGS}  -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -I ./build -c ./tests/objects/TesteProduto.cpp -o ${TEST_BUILD_DIR}/TesteProduto.o

${TEST_BUILD_DIR}/TesteAutenticacao.o: ${TESTS_DIR}/objects/TesteAutenticacao.cpp
	g++ ${CFLAGS}  -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -I ./build -c ./tests/objects/TesteAutenticacao.cpp -o ${TEST_BUILD_DIR}/TesteAutenticacao.o

${TEST_BUILD_DIR}/TesteServicoComprador.o: ${TESTS_DIR}/services/TesteServicoComprador.cpp
	g++ ${CFLAGS}  -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -I ./build -c ./tests/services/TesteServicoComprador.cpp -o ${TEST_BUILD_DIR}/TesteServicoComprador.o

${TEST_BUILD_DIR}/TesteServicoUsuario.o: ${TESTS_DIR}/services/TesteServicoUsuario.cpp
	g++ ${CFLAGS}  -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -I ./build -c ./tests/services/TesteServicoUsuario.cpp -o ${TEST_BUILD_DIR}/TesteServicoUsuario.o

${TEST_BUILD_DIR}/TesteServicoVendedor.o: ${TESTS_DIR}/services/TesteServicoVendedor.cpp
	g++ ${CFLAGS}  -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -I ./build -c ./tests/services/TesteServicoVendedor.cpp -o ${TEST_BUILD_DIR}/TesteServicoVendedor.o

${TEST_BUILD_DIR}/TesteServicoProduto.o: ${TESTS_DIR}/services/TesteServicoProduto.cpp
	g++ ${CFLAGS}  -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -I ./build -c ./tests/services/TesteServicoProduto.cpp -o ${TEST_BUILD_DIR}/TesteServicoProduto.o

${TEST_BUILD_DIR}/TesteServicoEstoque.o: ${TESTS_DIR}/services/TesteServicoEstoque.cpp
	g++ ${CFLAGS}  -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -I ./build -c ./tests/services/TesteServicoEstoque.cpp -o ${TEST_BUILD_DIR}/TesteServicoEstoque.o

${TEST_BUILD_DIR}/TesteServicoTransacoes.o: ${TESTS_DIR}/services/TesteServicoTransacoes.cpp
	g++ ${CFLAGS}  -I ${INCLUDE_DIR}/ -I ${LIB_DIR} -I ./build -c ./tests/services/TesteServicoTransacoes.cpp -o ${TEST_BUILD_DIR}/TesteServicoTransacoes.o

# Rule for cleaning files generated during compilation.
# Call 'make clean' to use it
clean:
	rm -f ${BUILD_DIR}/* 
	rm -f ${TEST_BUILD_DIR}/*
