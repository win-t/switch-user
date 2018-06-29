all: swuser

swuser: main.c Dockerfile.build
	docker build --pull -t swuser_static_builder -f Dockerfile.build .
	docker run --rm swuser_static_builder | tar x
	docker rmi --no-prune swuser_static_builder

clean:
	rm -f swuser

.PHONY: all clean
