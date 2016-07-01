all: pfc.ps pfc.pdf

pfc.dvi : pfc.tex cap1.tex cap2.tex cap2_sni.tex cap2_mfl.tex cap2_ccu.tex \
	cap2_thmac.tex cap2_tci.tex cap2_scci.tex conclusao.tex
	latex pfc
	bibtex pfc
	latex pfc
	latex pfc
	
pfc.ps: pfc.dvi
	dvips -t a4 -o pfc.ps pfc
	
pfc.pdf: pfc.dvi
	pdflatex pfc

clean:
	rm -f *.aux *.log *.blg *.bbl *.dvi *.ps *.pdf *.toc *.lot *.lof
