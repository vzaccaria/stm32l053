all: run

run: src/proto/message.pb-c.c src/proto/message.pb-c.h
		platformio run

watch:
		platformio serialports monitor

# Install protoc from brew.
src/proto/message.pb-c.c src/proto/message.pb-c.h: proto/message.proto
		protoc-c --c_out=src proto/message.proto
