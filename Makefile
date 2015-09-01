.PHONY:clean
all:
	rm main.pdf && cd compile && make
clean:
	cd compile && make clean
