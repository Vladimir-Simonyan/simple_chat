all :
	@mkdir bin
	@g++ src/c.cpp -lpthread -o bin/c
	@g++ src/s.cpp -lpthread -o bin/s
	@echo SUCCESS
	
.PHONY: cl
cl :
	@rm -rf bin
	@echo SUCCESS
