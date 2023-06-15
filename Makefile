TARGET = sf_chat
LIB = chat
SRC = main.cpp
OBJECTS = main.o
LIB_SRC = chat.cpp message.cpp user.cpp
LIB_OBJECTS = chat.o message.o user.o
PREFIX = ~

sf_chat: $(OBJECTS) lib
	g++ -o $(TARGET) $(OBJECTS) -L. -l$(LIB)

main.o: $(SRC)
	g++ -c $(SRC)

lib: 	$(LIB_SRC)
	g++ -c $(LIB_SRC)
	ar rc lib$(LIB).a $(LIB_OBJECTS)

install:
	install $(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)

clean:
	rm $(TARGET) $(OBJECTS) $(LIB_OBJECTS) *.a
