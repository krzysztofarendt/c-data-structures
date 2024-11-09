.PHONY: clean tests

BIN_DIR=bin


clean:
	-rm -r $(BIN_DIR)


tests: clean
	mkdir $(BIN_DIR)
	# Test vector
	gcc src/test_vector.c src/vector.c -o $(BIN_DIR)/test_vector
	$(BIN_DIR)/test_vector
