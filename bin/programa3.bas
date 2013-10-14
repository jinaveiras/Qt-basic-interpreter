		  REM multiplica
		  DIM prueba as ENTERO
		  DIM contador as ENTERO
		  LET contador = 0
		  INPUT "Introduzca valor: ",prueba
		  WHILE contador < prueba
			LET contador = contador + 1
			PRINT "Iteracion: ",contador
			IF contador == prueba
				PRINT "Saliendo del while"
			ENDIF
		  WEND
		  PRINT "Fin de programa"		  