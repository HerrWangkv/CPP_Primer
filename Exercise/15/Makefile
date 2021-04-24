QueryMain: QueryMain.cpp TextQuery.o Query.o NotQuery.o AndQuery.o OrQuery.o
	g++ -o QueryMain QueryMain.cpp TextQuery.o Query.o NotQuery.o AndQuery.o OrQuery.o
TextQuey.o: TextQuery.cpp
	g++ -c -o TextQuery.o TextQuery.cpp
Query.o: Query.cpp
	g++ -c -o Query.o Query.cpp
NotQuery.o: NotQuery.cpp
	g++ -c -o NotQuery.o NotQuery.cpp
AndQuery.o: AndQuery.cpp
	g++ -c -o AndQuery.o AndQuery.cpp
OrQuery.o: OrQuery.cpp
	g++ -c -o OrQuery.o OrQuery.cpp
clean:
	rm -f TextQuery.o Query.o NotQuery.o AndQuery.o OrQuery.o 