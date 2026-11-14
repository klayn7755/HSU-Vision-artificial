 String inputString = "";      // Cadena para guardar el comando recibido 
 bool stringComplete = false;  // Bandera boleana que nos indica cuando el comando fue recibido y podemos compararlo con los 2 comandos válidos  
 void setup() 
 {   
  pinMode(13, OUTPUT);   // initialize serial:   
  Serial.begin(9600);   // reserve 200 bytes for the inputString:   
  inputString.reserve(200); 
  }  
void loop() 
{     
    while (Serial.available()) 
    {
      //Mientras tengamos caracteres disponibles en el buffer     
      char inChar = (char)Serial.read();
      //Leemos el siguiente caracter     
      if (inChar == '\n') 
      {
        //Si el caracter recibido corresponde a un salto de línea       
        stringComplete = true;
        //Levantamos la bandera      
      }     
      else
      {
        //Si el caracter recibido no corresponde a un salto de línea       
        inputString += inChar;
        //Agregamos el caracter a la cadena      
      }   
     } 
  if (stringComplete) 
  {
    //El comando fue recibido, procedemos a compararlo          
    if (inputString.equals("off") )
    {
      //Si el comando es "off"       
      digitalWrite(13,0);       
      Serial.println("Apagado");     
    }     
    else 
    if (inputString.equals("on") )
    {
      //Si el comando es "on"       
      digitalWrite(13,1);       
      Serial.println("Encendido");     
    }     
    inputString = "";
    //Limpiamos la cadena para poder recibir el siguiente comando     
    stringComplete = false;
    //Bajamos la bandera para no volver a ingresar a la comparación hasta que recibamos un nuevo comando   
  }  
}  
 
