#!/bin/bash

gcc -Wall -o Desassembleur Desassembleur.c lib/B_Type/extractor_B.c lib/I_Type/extractor_I.c lib/J_Type/extractor_J.c lib/R_Type/extractor_R.c lib/S_Type/extractor_S.c lib/U_Type/extractor_U.c
