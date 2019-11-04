# Path to spt3g_software/
G3 = ..

test_memory_leak: test_memory_leak.cxx
	c++ $< -o $@ \
	-I $(G3)/core/include/ -I $(G3)/core/include/core \
	-I /usr/include/python3.7m \
	-L$(G3)/build/spt3g \
	-l:core.so \
	-lpython3.7m

test.g3: test_memory_leak.py
	python test_memory_leak.py

run: test.g3 test_memory_leak
	./test_memory_leak test.g3


