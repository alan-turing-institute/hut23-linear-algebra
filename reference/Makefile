pdfs = all-the-maths-we-know.pdf all-the-rules-we-know.pdf

all: $(pdfs)

$(pdfs): %.pdf: %.tex
	latexmk -output-format=pdf $<

clean:
	rm -f *.blg *.log *.pdf *.bbl *.aux *.out *.fdb_latexmk *.fls

