books:	main.cpp SQLDatabase.cpp
	g++ -o book.out -lsqlite3 main.cpp SQLDatabase.cpp

clean:
	rm *.o books.out
