filename=a1

pdf: 
	pdflatex ${filename}
	#bibtex ${filename}
	pdflatex ${filename}
	pdflatex ${filename}

pdf2: ps
	ps2pdf ${filename}.ps

pdf-print: ps
	ps2pdf -dColorConversionStrategy=/LeaveColorUnchanged -dPDFSETTINGS=/printer ${filename}.ps

text: html
	html2text -width 100 -style pretty ${filename}/${filename}.html | sed -n '/./,$$p' | head -n-2 >${filename}.txt

html:
	@#latex2html -split +0 -info "" -no_navigation ${filename}
	htlatex ${filename}

ps:	dvi
	dvips -t letter ${filename}.dvi

dvi:
	latex ${filename}
	bibtex ${filename}
	latex ${filename}
	latex ${filename}

clean:
	rm -f ${filename}.ps ${filename}.pdf ${filename}.log ${filename}.aux ${filename}.out ${filename}.dvi ${filename}.bbl ${filename}.blg ${filename}.toc
