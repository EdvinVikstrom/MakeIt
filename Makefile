NAME = MakeIt_2021
VERSION = 2021
OUTPUT = makeit

# Directory for the object files
BUILD = ./build

# Compiler for the language C
CC = clang

# Compiler for the language C++
CXXC = clang++

# Compiler for the language Objective C
OBJCC = clang

# Linker
LINKER = clang++

# Compiler flags for language C
CFLAGS = -I./extern/libme/include -I./include

# Compiler flags for language C++
CXXFLAGS = -std=c++20 -g -Og --include=./include/makeit/Config.hpp -I./extern/libme/include -I./include

# Compiler flags for language Objective C
OBJCFLAGS = -I./extern/libme/include -I./include

# Linker flags
LFLAGS = -lme -L./extern/libme/

SOURCES = \
	./src/makeit/MakeIt.cpp \
	./src/makeit/Text.cpp \
	./src/makeit/Logger.cpp \
	./src/makeit/basic/Function.cpp \
	./src/makeit/basic/Variable.cpp \
	./src/makeit/basic/Project.cpp \
	./src/makeit/basic/BuildConfig.cpp \
	./src/makeit/functions/FnSetProperty.cpp \
	./src/makeit/functions/FnAddProperty.cpp \
	./src/makeit/functions/FnAddExtern.cpp \
	./src/makeit/functions/FnAddFiles.cpp \
	./src/makeit/functions/FnAddInstall.cpp \
	./src/makeit/functions/FnConfigure.cpp \
	./src/makeit/functions/FnPrint.cpp \
	./src/makeit/functions/FnProject.cpp \
	./src/makeit/functions/FnSource.cpp \
	./src/makeit/lexer/Lexer.cpp \
	./src/makeit/lexer/Token.cpp \
	./src/makeit/parser/Parser.cpp \
	./src/makeit/parser/ExprParser.cpp \
	./src/makeit/parser/FuncParser.cpp \
	./src/makeit/parser/StmtParser.cpp \
	./src/makeit/parser/VariParser.cpp \
	./src/makeit/target/GMakeTarget.cpp \
	./src/makeit/target/YCMTarget.cpp
OBJECTS = $(SOURCES:%=$(BUILD)/%.o)
DEPENDS = $(SOURCES:%=$(BUILD)/%.d)

EXTERNALS =

.PHONY: $(NAME)
$(NAME): $(OUTPUT) $(EXTERNALS)

$(OUTPUT): $(OBJECTS)
	$(LINKER) -o $@ $^ $(LFLAGS)

-include $(DEPENDS)

$(BUILD)/./src/makeit/MakeIt.cpp.o: ./src/makeit/MakeIt.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/Text.cpp.o: ./src/makeit/Text.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/Logger.cpp.o: ./src/makeit/Logger.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/basic/Function.cpp.o: ./src/makeit/basic/Function.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/basic/Variable.cpp.o: ./src/makeit/basic/Variable.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/basic/Project.cpp.o: ./src/makeit/basic/Project.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/basic/BuildConfig.cpp.o: ./src/makeit/basic/BuildConfig.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/functions/FnSetProperty.cpp.o: ./src/makeit/functions/FnSetProperty.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/functions/FnAddProperty.cpp.o: ./src/makeit/functions/FnAddProperty.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/functions/FnAddExtern.cpp.o: ./src/makeit/functions/FnAddExtern.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/functions/FnAddFiles.cpp.o: ./src/makeit/functions/FnAddFiles.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/functions/FnAddInstall.cpp.o: ./src/makeit/functions/FnAddInstall.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/functions/FnConfigure.cpp.o: ./src/makeit/functions/FnConfigure.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/functions/FnPrint.cpp.o: ./src/makeit/functions/FnPrint.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/functions/FnProject.cpp.o: ./src/makeit/functions/FnProject.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/functions/FnSource.cpp.o: ./src/makeit/functions/FnSource.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/lexer/Lexer.cpp.o: ./src/makeit/lexer/Lexer.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/lexer/Token.cpp.o: ./src/makeit/lexer/Token.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/parser/Parser.cpp.o: ./src/makeit/parser/Parser.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/parser/ExprParser.cpp.o: ./src/makeit/parser/ExprParser.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/parser/FuncParser.cpp.o: ./src/makeit/parser/FuncParser.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/parser/StmtParser.cpp.o: ./src/makeit/parser/StmtParser.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/parser/VariParser.cpp.o: ./src/makeit/parser/VariParser.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/target/GMakeTarget.cpp.o: ./src/makeit/target/GMakeTarget.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

$(BUILD)/./src/makeit/target/YCMTarget.cpp.o: ./src/makeit/target/YCMTarget.cpp
	$(CXXC) $(CXXFLAGS) -c -o $@ $< -MMD

.PHONY: install
install:
	install makeit /bin/makeit

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(DEPENDS)
