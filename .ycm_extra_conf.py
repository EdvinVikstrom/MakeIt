INCD = [ '-I./extern/libme/include', '-I./include' ]
C_CFLAGS = INCD + [ '-xc',  ]
CXX_CFLAGS = INCD + [ '-xc++', '-std=c++20', '-g', '-Og' ]
OBJC_CFLAGS = INCD + [ '-xobjc',  ]

SOURCES = {
	'/home/edvin/Dokument/MakeIt/src/makeit/MakeIt.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/Text.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/Logger.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/basic/Function.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/basic/Variable.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/functions/FnAddLibrary.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/functions/FnAddInclude.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/functions/FnAddIncludeDir.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/functions/FnAddLibraryDir.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/functions/FnAddDefine.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/functions/FnAddCFlags.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/functions/FnAddLFlags.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/functions/FnAddPackage.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/functions/FnPrint.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/functions/FnSource.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/functions/FnProject.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/functions/FnFiles.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/functions/FnExtern.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/functions/FnInstall.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/lexer/Lexer.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/lexer/Token.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/parser/Parser.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/parser/ExprParser.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/parser/FuncParser.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/parser/StmtParser.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/parser/VariParser.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/target/GMakeTarget.cpp': CXX_CFLAGS + [  ],
	'/home/edvin/Dokument/MakeIt/src/makeit/target/YCMTarget.cpp': CXX_CFLAGS + [  ]
}

def Settings(**kwargs):
	key = kwargs['filename']
	if key in SOURCES:
		return { 'flags': SOURCES[key] }
	else:
		if IsCFile(key):
			return { 'flags': C_CFLAGS }
		elif IsCXXFile(key):
			return { 'flags': CXX_CFLAGS }
		elif IsOBJCFile(key):
			return { 'flags': OBJC_CFLAGS }
	return { 'flags': [ ] }

def IsCXXFile(file):
	CXX_FILES = ['.cpp', '.cxx', '.cc', '.hpp', '.hxx', '.hh']
	for ext in CXX_FILES:
		if file.endswith(ext):
			return True
	return False

def IsCFile(file):
	C_FILES = ['.c', '.h']
	for ext in C_FILES:
		if file.endswith(ext):
			return True
	return False

def IsOBJCFile(file):
	OBJC_FILES = ['.h', '.m', '.mm', '.M']
	for ext in OBJC_FILES:
		if file.endswith(ext):
			return True
	return False

