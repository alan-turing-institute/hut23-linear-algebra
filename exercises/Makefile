pdfs = axler-1a.pdf

all: $(pdfs)

$(pdfs): %.pdf: %.tex
	latexmk -output-format=pdf $<
