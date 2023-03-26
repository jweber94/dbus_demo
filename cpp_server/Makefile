BUILD_TYPE ?= Debug

build_project:
	mkdir build
	cmake . -Bbuild -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
	make -C build -j12

clean:
	rm -rf build
