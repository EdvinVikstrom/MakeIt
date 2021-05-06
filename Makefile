NAME = MakeIt_2021
VERSION = 2021
CC = clang++
BUILD = ./build
OUTPUT = makeit
INCD = -I./extern/libme/include -I./include
LIBD = -L./extern/libme/
LIBS = -lme
CFLAGS = $(INCD)
C_CFLAGS = $(CFLAGS) -xc 
CXX_CFLAGS = $(CFLAGS) -xc++ -std=c++20 -g -Og
OBJC_CFLAGS = $(CFLAGS) -xobjc 
LFLAGS = $(LIBD) $(LIBS) 
SRCS = ./src/makeit/MakeIt.cpp \
	./src/makeit/Text.cpp \
	./src/makeit/Logger.cpp \
	./src/makeit/basic/Function.cpp \
	./src/makeit/basic/Variable.cpp \
	./src/makeit/functions/FnAddLibrary.cpp \
	./src/makeit/functions/FnAddInclude.cpp \
	./src/makeit/functions/FnAddIncludeDir.cpp \
	./src/makeit/functions/FnAddLibraryDir.cpp \
	./src/makeit/functions/FnAddDefine.cpp \
	./src/makeit/functions/FnAddCFlags.cpp \
	./src/makeit/functions/FnAddLFlags.cpp \
	./src/makeit/functions/FnAddPackage.cpp \
	./src/makeit/functions/FnPrint.cpp \
	./src/makeit/functions/FnSource.cpp \
	./src/makeit/functions/FnProject.cpp \
	./src/makeit/functions/FnFiles.cpp \
	./src/makeit/functions/FnExtern.cpp \
	./src/makeit/functions/FnInstall.cpp \
	./src/makeit/lexer/Lexer.cpp \
	./src/makeit/lexer/Token.cpp \
	./src/makeit/parser/Parser.cpp \
	./src/makeit/parser/ExprParser.cpp \
	./src/makeit/parser/FuncParser.cpp \
	./src/makeit/parser/StmtParser.cpp \
	./src/makeit/parser/VariParser.cpp \
	./src/makeit/target/GMakeTarget.cpp \
	./src/makeit/target/YCMTarget.cpp
OBJS = $(SRCS:%=$(BUILD)/%.o)
DEPS = $(OBJS:%.o=%.d)

EXTS = 

.PHONY: $(NAME)
$(NAME): $(OUTPUT) $(EXTS)

$(OUTPUT): $(OBJS)
	@$(CC) -o $@ $^ $(LFLAGS)

-include $(DEPS)

$(BUILD)/./src/makeit/MakeIt.cpp.o: ./src/makeit/MakeIt.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/Text.cpp.o: ./src/makeit/Text.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/Logger.cpp.o: ./src/makeit/Logger.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/basic/Function.cpp.o: ./src/makeit/basic/Function.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/basic/Variable.cpp.o: ./src/makeit/basic/Variable.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/functions/FnAddLibrary.cpp.o: ./src/makeit/functions/FnAddLibrary.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/functions/FnAddInclude.cpp.o: ./src/makeit/functions/FnAddInclude.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/functions/FnAddIncludeDir.cpp.o: ./src/makeit/functions/FnAddIncludeDir.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/functions/FnAddLibraryDir.cpp.o: ./src/makeit/functions/FnAddLibraryDir.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/functions/FnAddDefine.cpp.o: ./src/makeit/functions/FnAddDefine.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/functions/FnAddCFlags.cpp.o: ./src/makeit/functions/FnAddCFlags.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/functions/FnAddLFlags.cpp.o: ./src/makeit/functions/FnAddLFlags.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/functions/FnAddPackage.cpp.o: ./src/makeit/functions/FnAddPackage.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/functions/FnPrint.cpp.o: ./src/makeit/functions/FnPrint.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/functions/FnSource.cpp.o: ./src/makeit/functions/FnSource.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/functions/FnProject.cpp.o: ./src/makeit/functions/FnProject.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/functions/FnFiles.cpp.o: ./src/makeit/functions/FnFiles.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/functions/FnExtern.cpp.o: ./src/makeit/functions/FnExtern.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/functions/FnInstall.cpp.o: ./src/makeit/functions/FnInstall.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/lexer/Lexer.cpp.o: ./src/makeit/lexer/Lexer.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/lexer/Token.cpp.o: ./src/makeit/lexer/Token.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/parser/Parser.cpp.o: ./src/makeit/parser/Parser.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/parser/ExprParser.cpp.o: ./src/makeit/parser/ExprParser.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/parser/FuncParser.cpp.o: ./src/makeit/parser/FuncParser.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/parser/StmtParser.cpp.o: ./src/makeit/parser/StmtParser.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/parser/VariParser.cpp.o: ./src/makeit/parser/VariParser.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/target/GMakeTarget.cpp.o: ./src/makeit/target/GMakeTarget.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD

$(BUILD)/./src/makeit/target/YCMTarget.cpp.o: ./src/makeit/target/YCMTarget.cpp
	@echo "compiling source '$<'"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CXX_CFLAGS) -MMD



.PHONY: install
install:
	cp makeit /bin/makeit

.PHONY: clean
clean:
	rm -f $(OUT) $(OBJS) $(DEPS)
