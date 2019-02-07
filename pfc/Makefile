all: PFC.pdf

TEX_SOURCES = $(wildcard *.tex)

PFC.pdf : ${TEX_SOURCES}
	mkdir -p out
	pdflatex --output-directory out PFC
	cd out && BIBINPUTS="..:" bibtex PFC
	pdflatex --output-directory out PFC
	pdflatex --output-directory out PFC
	cp -v out/PFC.pdf PFC.pdf

clean:
	rm -rfv out PFC.pdf
