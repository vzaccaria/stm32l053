all: run

run: src/proto/message.pb-c.c src/proto/message.pb-c.h
		platformio run

watch:
		platformio serialports monitor

# Install protoc from brew.
src/proto/message.pb-c.c src/proto/message.pb-c.h: proto/message.proto
		protoc-c --c_out=src proto/message.proto

plot:
	./node_modules/.bin/stm32-proxy proto/message.proto -p '/dev/cu.usbmodemfd123' -g "`pwd`/tools/plotly-stm32-proxy-plugin.js"

plotd:
	DEBUG=* ./node_modules/.bin/stm32-proxy proto/message.proto -p '/dev/cu.usbmodemfd123' -g "`pwd`/tools/plotly-stm32-proxy-plugin.js"
