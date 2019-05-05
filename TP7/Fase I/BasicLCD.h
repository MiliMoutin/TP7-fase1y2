#pragma once

struct cursorPosition
{
	int row;
	int column;
};


class BasicLCD {
	public:
		/*=====================================================
		* Name: basicLCD
		* Entra: -
		* Resulta: Constructor de la clase. Inicializa el LCD y deja
		* todo listo comenzar a utilizarlo.
		*
		* cadd =1 (cursor address) (ver NOTA 1)
		*=====================================================*/
		BasicLCD() {}

		/*=====================================================
		* Name: ~basicLCD
		* Entra: -
		* Resulta: Destructor de la clase. Libera cualquier recurso
		* que se hubiera tomado de forma de evitar
		* "resources leak".
		*=====================================================*/
		virtual ~BasicLCD() {}
			/*=====================================================
			* Name: lcdInitOk
			* Entra: -
			* Resulta: No genera ning�n cambio en el display.
			* Devuelve en su nombre �true� si el display se inicializ�
			* correctam
			20/22
			/*=====================================================
			* Name: operator<<()
			* Entra: Una cadena de caracteres NULL terminated
			* Resulta: imprime la cadena de caracteres en la posici�n actual
			* del cursor y avanza el cursor al final de la cadena respetando
			* el gap (si alg�n car�cter no es imprimible lo ignora). Si recibe una
			* cadena de m�s de 32 caracteres, muestra los �ltimos 32 en el display.
			* Modifica: (cadd)
			* Devuelve en su nombre una referencia a un basicLCD que permite
			* encascar la funci�n:
			* basicLCD lcd;
			* lcd << �Hola� << � � << �Mundo�;
			*=====================================================*/
			virtual BasicLCD& operator<<(const unsigned char * c) = 0;
		/*=====================================================
		* Name: lcdMoveCursorUp
		*
		* Entra: -
		* Resulta: Pasa el cursor a la primera l�nea del display sin
		* alterar la columna en la que estaba.
		* Modifica: (cadd)
		* Devuelve en su nombre �true� si fue satisfactoria �false�
		* en caso contrario.
		*=====================================================*/
		virtual bool lcdMoveCursorUp() = 0;

		/*=====================================================
		* Name: lcdMoveCursorDown
		*
		* Entra: -
		* Resulta: Pasa el cursor a la segunda l�nea del display sin
		* alterar la columna en la que estaba.
		* Modifica: (cadd).
		* Devuelve en su nombre �true� si fue satisfactoria �false�
		* en caso contrario.
		*=====================================================*/
		virtual bool lcdMoveCursorDown() = 0;
		/*=====================================================
		* Name: lcdMoveCursorRight
		*
		* Entra: -
		* Resulta: Avanza el cursor una posici�n
		* Modifica: (cadd).
		* Devuelve en su nombre �true� si fue satisfactoria �false�
		* en caso contrario.
		*=====================================================*/
		virtual bool lcdMoveCursorRight() = 0;
		/*=====================================================
		* Name: lcdMoveCursorLeft
		*
		* Entra: -
		* Resulta: Retrocede el cursor una posici�n
		* Modifica: (cadd).
		* Devuelve en su nombre �true� si fue satisfactoria �false�
		* en caso contrario.
		*=====================================================*/
		virtual bool lcdMoveCursorLeft() = 0;
			/*=====================================================
			* Name: lcdSetCursorPosition
			* Entra: Recibe una estructura tipo cursorPosition
			* Resulta: Posiciona el cursor en la posici�n dada
			* por row y column. row[0-1] col[0-19]. Ante un valor inv�lido
			* de row y/o column ignora la instrucci�n (no hace nada).
			* Modifica: (cadd).
			* Devuelve en su nombre �true� si fue satisfactoria �false�
			* en caso contrario.
			*=====================================================*/
			virtual bool lcdSetCursorPosition(const cursorPosition pos) = 0;
		/*=====================================================
		* Name: lcdGetCursorPosition
		* Entra: -
		* Resulta: Devuelve la posici�n actual del cursor.
		* cadd = No se altera
		*
		* Devuelve una estructura tipo cursorPosition
		*=====================================================*/
		virtual cursorPosition lcdGetCursorPosition() = 0;
	protected:
		/*=====================================================
		* Nota 1: cadd (cursor address) es una variable
		* que contiene la direcci�n actual del cursor en el
		* display+1. Esta variable es necesaria pues no podemos
		* leer el LCD para saber d�nde est� el cursor. Mediante
		* la funciones como lcdClear () o lcdSetCursorPosition()
		* podemos poner el cursor del display en una posici�n
		* conocida y por lo tanto sincronizarlo con cadd.
		* El constructor la inicializa y asegura su sincronismo.
		*=====================================================*/
		int cadd;

		/*=====================================================
		* Name: lcdUpdateCursor ver NOTA 2
		* Entra: -
		* Resulta: Posiciona el cursor del display en la posici�n
		* dada por (cadd)-1. (cadd) = No se altera
		*
		* El prop�sito de la funci�n lcdUpdateCursor() es
		* informarle al display del valor de cadd cada vez que es
		* alterado. Esto es necesario pues si llamamos por ejemplo a
		* lcdMoveCursorUp() esta �ltima calcular� un nuevo valor
		* para cadd. Este nuevo valor de cadd deber� ser transferido
		* al cursor del display para poder sincronizar ambos.
		*=====================================================*/
		void lcdUpdateCursor() {}

};