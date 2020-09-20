# Cpp-tree-analyzer-of-include-files-
console application for display sorted tree of header files by frequency of includes and alphabetical order.

Application accept at least one directory with source files and additional arguments for header files with -i flag.
```
Example: .\TestApp.exe .\sources -i ".\path\libs\" -i ".\path\include"
```

Response:
```
root
|..app.cpp
|..|..app.hpp (!)
|..|..main.cpp
|..|..|..b.hpp
|..|..|..c.hpp
|..|..|..deleted.hpp (!)
|..|..|..deleted.hpp (!)
|..|..|..some.hpp
|..|..|..|..file.hpp
|..|..|..|..|..lib.hpp
|..|..|..|..|..|..doc.hpp
|..|..|..|..|..|..|..qq.hpp
|..|..|..|..|..|..|..|..ss.hpp
|..|..|..|..|..|..ww.hpp
|..|..|..a.hpp
|..|..|..o.h
|..|..|..|..b.hpp
|..|..|..lib.hpp
|..|..|..|..doc.hpp
|..|..|..|..|..qq.hpp
|..|..|..|..|..|..ss.hpp
|..|..|..|..file.hpp
|..|..|..|..ww.hpp
|..|..a.hpp
|..|..o.h
|..|..|..b.hpp
|..|..lib.hpp
|..|..|..doc.hpp
|..|..|..|..qq.hpp
|..|..|..|..|..ss.hpp
|..|..|..file.hpp
|..|..|..ww.hpp
|..deep.cpp
|..foo.cpp
|..|..bar.hpp
|..test.cpp
|..|..aa.hpp
|..|..c.hpp
|..|..lol.hpp
|..|..ww.hpp
|..|..main.cpp
|..|..|..b.hpp
|..|..|..c.hpp
|..|..|..deleted.hpp (!)
|..|..|..deleted.hpp (!)
|..|..|..some.hpp
|..|..|..|..file.hpp
|..|..|..|..|..lib.hpp
|..|..|..|..|..|..doc.hpp
|..|..|..|..|..|..|..qq.hpp
|..|..|..|..|..|..|..|..ss.hpp
|..|..|..|..|..|..ww.hpp
|..|..|..a.hpp
|..|..|..o.h
|..|..|..|..b.hpp
|..|..|..lib.hpp
|..|..|..|..doc.hpp
|..|..|..|..|..qq.hpp
|..|..|..|..|..|..ss.hpp
|..|..|..|..file.hpp
|..|..|..|..ww.hpp
|..|..b.hpp
|..main.cpp
|..|..b.hpp
|..|..c.hpp
|..|..deleted.hpp (!)
|..|..deleted.hpp (!)
|..|..some.hpp
|..|..|..file.hpp
|..|..|..|..lib.hpp
|..|..|..|..|..doc.hpp
|..|..|..|..|..|..qq.hpp
|..|..|..|..|..|..|..ss.hpp
|..|..|..|..|..ww.hpp
|..|..a.hpp
|..|..o.h
|..|..|..b.hpp
|..|..lib.hpp
|..|..|..doc.hpp
|..|..|..|..qq.hpp
|..|..|..|..|..ss.hpp
|..|..|..file.hpp
|..|..|..ww.hpp


"file.hpp" 7
"lib.hpp" 7
"doc.hpp" 7
"ss.hpp" 7
"qq.hpp" 7
"ww.hpp" 7
"b.hpp" 5
"o.h" 4
"a.hpp" 4
"deleted.hpp" 3
"some.hpp" 3
"b.hpp" 3
"c.hpp" 3
"deleted.hpp" 3
"main.cpp" 3
"app.hpp" 1
"aa.hpp" 1
"deep.cpp" 1
"lol.hpp" 1
"c.hpp" 1
"bar.hpp" 1
"app.cpp" 1
"foo.cpp" 1
"test.cpp" 1
"ww.hpp" 1
```
