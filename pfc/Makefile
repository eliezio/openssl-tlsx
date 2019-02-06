all: PFC.pdf

TEX_SOURCES = \
	PFC.tex \
	capa.tex \
	folharosto.tex \
	folhaaprovacao.tex \
	dedicatoria.tex \
	agradecimentos.tex \
	epigrafe.tex \
	resumo.tex \
	abstract.tex \
	acronimos.tex \
	introducao.tex \
	intro_cripto.tex \
	intro_tls.tex \
	intro_rfc3546.tex \
	impl.tex \
	impl_sni.tex \
	impl_mfl.tex \
	impl_ccu.tex \
	impl_tmac.tex \
	impl_tci.tex \
	impl_scci.tex \
	conclusao.tex \
	anexo_tlsx.tex \
	anexo_mkpki.tex \
	bibliografia.tex

PFC.pdf : ${TEX_SOURCES}
	pdflatex PFC
	-bibtex PFC
	pdflatex PFC
	pdflatex PFC

clean:
	rm -fv *.aux *.bbl *.blg *.lof *.log *.lol *.lot *.out *.pdf *.toc
