CC = gcc

%.o: %.c
	$(CC) -c -o $@ $<

mcp_test: mcp2210.o mcp2515.o mcp2210test.o hid.o
	$(CC) -o mcp_test mcp2210.o mcp2515.o mcp2210test.o hid.o -ludev
