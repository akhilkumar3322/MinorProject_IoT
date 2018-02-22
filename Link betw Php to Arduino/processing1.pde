 import processing.serial.*;
 import java.io.*;
 Serial port;
 
 
 int index = 0;
 
 
 void setup()  {
 
   size (500,  500);     // Size of the serial window, you can increase or decrease as you want

   port  =  new Serial (this, "COM5",  9600); // Set the com port and the baud rate according to the Arduino IDE

  // port.bufferUntil ( '\n' );   // Receiving the data from the Arduino IDE

   /* This part must be altered to fit your local settings. The number in brackets after "Serial.list()" is where you declare what COM port your Arduino is connected to.
      If you get error messages, try a different number starting from 0 (e.g. 0, 1, 2, 3...) . */
   // port = new Serial(this, Serial.list()[5], 9600);  // Open the port that the Arduino board is connected to, at 9600 baud
   
  
  
 }
 
 void draw() {
   
  try{
  delay(10000);
   File file1 = new File("C:\\xampp\\htdocs\\ArduinoPirInterface\\fan.txt");  
  if(file1.length()!=0){
  String fanstate = readData("C:\\xampp\\htdocs\\ArduinoPirInterface\\fan.txt");
  println(fanstate);
  char ch = fanstate.charAt(0);
  println(ch);
  port.write(ch);
  println("def");
  FileWriter fw1 = new FileWriter(file1); //this erases previous content
  fw1.close();
  }
  File file = new File("C:\\xampp\\htdocs\\ArduinoPirInterface\\avg.txt");
  if(file.length()!=0){
  String favg = readData("C:\\xampp\\htdocs\\ArduinoPirInterface\\avg.txt");
  println(favg);
  Double ifavg = Double.parseDouble(favg);
  println(ifavg);
  Integer i = ifavg.intValue(); // i becomes 5
  i = i/100;
  println(i);
  delay(i*1000);
  port.write('A');
  println("abc");
  FileWriter fw = new FileWriter(file); //this erases previous content
  fw.close();
 
  } 
  }catch(Exception e)
  {
  }
  
   
 }
 

  //avg = loadStrings("C:\xampp\htdocs\ArduinoPirInterface\avg.txt"); // Insert the location of your .txt file
 // print(avg[index]);  // Prints whatever is in the file ("1" or "0")
 
 // if (onoroff[0].equals("1") == true) {
  //  println(" - TELLING ARDUINO TO TURN LED ON");
   // port.write(avg[0]); // Send "H" over serial to set LED to HIGH
 
//  } else {
 
  //  println(" - TELLING ARDUINO TO TURN LED OFF");
  //  port.write('L');  // Send "L" over serial to set LED to LOW
 //}
 
  //delay(7000); // Set your desired interval here, in milliseconds

 
 String readData(String myFileName){
 
 File file=new File(myFileName);
 BufferedReader br=null;
 String text = null;
 try{
 br=new BufferedReader(new FileReader(file));
 
 /* keep reading each line until you get to the end of the file */
 text=br.readLine();
 /* Spilt each line up into bits and pieces using a comma as a separator */
 
 }catch(FileNotFoundException e){
 e.printStackTrace();
 }catch(IOException e){
 e.printStackTrace();
 }finally{
 try {
 if (br != null){
 br.close();
 }
 } catch (IOException e) {
 e.printStackTrace();
 }
 }
  return text;

}