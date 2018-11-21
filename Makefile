CC = gcc

%.o: %.c
	$(CC) -c -o $@ $< -std=gnu99

%.o: %.cpp
	$(CC) -c -o $@ $< -std=gnu++11

mcp_test: mcp2210.o mcp2515.o mcp2210test.o hid.o
	$(CC) -o mcp_test mcp2210.o mcp2515.o mcp2210test.o hid.o -std=gnu++11 -ludev
