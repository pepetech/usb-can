CC = gcc
CXX = g++

%.o: %.c
	$(CC) -c -o $@ $< -std=gnu99

%.o: %.cpp
	$(CXX) -c -o $@ $< -std=gnu++11

mcp_test: mcp2210.o mcp2515.o mcp2210test.o hid.o
	$(CXX) -o mcp_test mcp2210.o mcp2515.o mcp2210test.o hid.o -std=gnu++11 -ludev
