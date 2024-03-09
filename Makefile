COMPILER = g++
COMPILER_FLAGS = -Wall -std=c++17 -I/opt/homebrew/include/opencv4 -O2 
LINKER_FLAGS = -L/opt/homebrew/lib 
LINK_LIBRARIES = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc 
IMAGE_FILE ?= ""

all: image2Ascii

image2Ascii: image2Ascii.cpp
	mkdir -p ascii
	$(COMPILER) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(LINK_LIBRARIES) image2Ascii.cpp -o image2Ascii
	if [ -z "$(IMAGE_FILE)" ]; then \
		echo "No image file specified."; \
	else \
		./image2Ascii $(IMAGE_FILE); \
	fi
	
clean:
	rm -f image2Ascii
	rm -rf ascii
