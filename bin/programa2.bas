		  REM programa de prueba
		  DIM prueba as CADENA
		  DIM numero as FLOTANTE
		  DIM contador as ENTERO
		  DIM iterador as ENTERO
		  PRINT "Probando literales de tipo flotante: -3.45 + 4.56"
		  LET numero = -3.45 + 4.56
		  PRINT "Resultado: ",numero
		  LET iterador = 0
		  INPUT "Intruduzca valor: ",contador
		  PRINT "Valor introducido: ",contador
		  WHILE iterador < contador
			LET iterador = iterador + 1
			IF 3 > iterador 
				PRINT "Iteracion ",iterador,": VERDADERO: FUNCIONA EL IF"
			ELSE
				PRINT "Iteracion ",iterador,": FALSO: FUNCIONA EL IF"
				IF 4 < iterador 
				  PRINT "Iteracion ",iterador,": VERDADERO anidado: FUNCIONA EL IF"
				ELSE
				  PRINT "Iteracion ",iterador,": FALSO anidado: SALIENDO DEL BUCLE"
				  GOTO finbucle
				ENDIF
			ENDIF
		  WEND
:finbucle LET prueba = "cadena"
		  PRINT prueba
		  LET prueba = prueba + " nueva"
		  PRINT prueba
		  PRINT "Resultado: ", prueba, " insercion"		  