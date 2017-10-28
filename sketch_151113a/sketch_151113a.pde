import processing.serial.*;         
Serial myPort;                      
float x, y;
int radius = 350;                 
int w = 300;                      
int degree = 0;                     
int value = 0;                     
int motion = 0;                     
int[] newValue = new int[181];      
int[] oldValue = new int[181];      
PFont myFont;                       
int radarDist = 0;                 
int firstRun = 0;                   
int lf = 10;                      
void setup(){
size(750, 450);                    
background (0);                     
myFont = createFont("verdana", 12); 
textFont(myFont);                   
  
println(Serial.list());              
myPort = new Serial(this, Serial.list()[0], 9600);
myPort.bufferUntil(lf);              
}

void draw(){
  fill(0);                              
  noStroke();                           
  ellipse(radius, radius, 750, 750);    
  rectMode(CENTER);                    
  rect(350,402,800,100);               
  if (degree >= 179) {                  
  motion = 1;                         
  }
  if (degree <= 1) {                   
  motion = 0;                          
  }
  
  strokeWeight(7);                      
  if (motion == 0) {                    
    for (int i = 0; i <= 20; i++) {     
      stroke(0, (10*i), 0);             
      line(radius, radius, radius + cos(radians(degree+(180+i)))*w, radius + sin(radians(degree+(180+i)))*w); // line(start x, start y, end x, end y)
    }
  } else {                              
    for (int i = 20; i >= 0; i--) {     
      stroke(0,200-(10*i), 0);          
      line(radius, radius, radius + cos(radians(degree+(180+i)))*w, radius + sin(radians(degree+(180+i)))*w);
    }
  }
 
  noStroke();                          

  fill(0,50,0);                         
  beginShape();                         
    for (int i = 0; i < 180; i++) {     
      x = radius + cos(radians((180+i)))*((oldValue[i]));
      y = radius + sin(radians((180+i)))*((oldValue[i])); 
      vertex(x, y);                     
    }
  endShape();                           

  fill(0,110,0);
  beginShape();
    for (int i = 0; i < 180; i++) {
      x = radius + cos(radians((180+i)))*(newValue[i]);
      y = radius + sin(radians((180+i)))*(newValue[i]);
      vertex(x, y);
    }
  endShape();
 
  fill(0,170,0);
  beginShape();
    for (int i = 0; i < 180; i++) {
      x = radius + cos(radians((180+i)))*((newValue[i]+oldValue[i])/2); 
      y = radius + sin(radians((180+i)))*((newValue[i]+oldValue[i])/2);
      vertex(x, y);
    }
  endShape();
 
  if (firstRun >= 360) {
    stroke(150,0,0);
    strokeWeight(1);
    noFill();
      for (int i = 0; i < 180; i++) {
        if (oldValue[i] - newValue[i] > 35 || newValue[i] - oldValue[i] > 35) {
          x = radius + cos(radians((180+i)))*(newValue[i]);
          y = radius + sin(radians((180+i)))*(newValue[i]);
          ellipse(x, y, 10, 10);
        }
      }
  }
 
  for (int i = 0; i <=6; i++){
    noFill();
    strokeWeight(1);
    stroke(0, 255-(30*i), 0);
    ellipse(radius, radius, (100*i), (100*i));
    fill(0, 100, 0);
    noStroke();
    text(Integer.toString(radarDist+50), 380, (305-radarDist), 50, 50);
    radarDist+=50;
  }
  radarDist = 0;
  
  for (int i = 0; i <= 6; i++) {
    strokeWeight(1);
    stroke(0, 55, 0);
    line(radius, radius, radius + cos(radians(180+(30*i)))*w, radius + sin(radians(180+(30*i)))*w);
    fill(0, 55, 0);
    noStroke();
    if (180+(30*i) >= 300) {
      text(Integer.toString(180+(30*i)), (radius+10) + cos(radians(180+(30*i)))*(w+10), (radius+10) + sin(radians(180+(30*i)))*(w+10), 25,50);
    } else {
      text(Integer.toString(180+(30*i)), radius + cos(radians(180+(30*i)))*w, radius + sin(radians(180+(30*i)))*w, 60,40);
    }
  }
  
  noStroke();
  fill(0);
  rect(350,402,800,100);
  fill(0, 100, 0);
  text("Grados: "+Integer.toString(degree), 100, 380, 100, 50);          
  text("Distancia: "+Integer.toString(value), 100, 400, 100, 50);         
  text("Mr GTS", 540, 380, 250, 50);
  fill(0);
  rect(70,60,150,100);
  fill(0, 100, 0);
  text("Screen Key:", 100, 50, 150, 50);
  fill(0,50,0);
  rect(30,53,10,10);
  text("Primer barrido", 115, 70, 150, 50);
  fill(0,110,0);
  rect(30,73,10,10);
  text("Segundo barrido", 115, 90, 150, 50);
  fill(0,170,0);
  rect(30,93,10,10);
  text("Promedio", 115, 110, 150, 50);
  noFill();
  stroke(150,0,0);
  strokeWeight(1);
  ellipse(29, 113, 10, 10);
  fill(150,0,0);
  text("Movimiento", 115, 130, 150, 50);
}
/
void serialEvent (Serial myPort) {
  String xString = myPort.readStringUntil(lf);  
   
    if (xString != null) {  
        xString = trim(xString); 
        String getX = xString.substring(1, xString.indexOf("V")); 
        String getV = xString.substring(xString.indexOf("V")+1, xString.length());
        degree = Integer.parseInt(getX); 
        value = Integer.parseInt(getV);
        oldValue[degree] = newValue[degree]; 
        newValue[degree] = value;
       
        firstRun++;
        if (firstRun > 360) {
        firstRun = 360; 
        }
  }
}
