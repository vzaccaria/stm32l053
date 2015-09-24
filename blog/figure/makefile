all: arch.pdf arch-1.png

arch.pdf: arch.md
	cat arch.md | org2kf arch.pdf

arch-1.png: arch.pdf
	pdftocairo -r 300 -png arch.pdf

edit:
	open arch.pdf -a "Skim"
	watchman arch.md 'make arch.pdf arch-1.png'
