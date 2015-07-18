MAIN	=main
INCLUDE	=-I../tex/

.PHONY:clean
all:../$(MAIN).pdf

$(MAIN).dvi:../tex/$(MAIN).tex
	platex -o $< $@

../$(MAIN).pdf:$(MAIN).dvi
	dvipdfmx -o $@ $<

clean:
	rm $(MAIN).*
